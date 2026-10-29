#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

// 【應用層 / 獨立核心業務】
typedef struct {
    int session_id;
    int payload_processed;
} Session;

// 核心業務函式維持強型別規範，不依賴任何底層抽象
void session_process(Session *session) {
    if (session != NULL) {
        session->payload_processed++;
    }
}

// ==========================================
// TODO 1: 定義通用管線層的回呼型別
// - task_run_cb_t: 接收 void*，無回傳值
// - task_destroy_cb_t: 接收 void*，無回傳值
// ==========================================
typedef void (*task_run_cb_t)(void *context);
typedef void (*task_destroy_cb_t)(void *context);
// ==========================================
// TODO 2: 定義通用任務結構體 ManagedTask
// 需包含：
// - 執行回呼指標
// - 解構回呼指標
// - 上下文泛型指標
// ==========================================

typedef struct
{
    task_run_cb_t run;
    task_destroy_cb_t destroy;
    void *context;
} ManagedTask;


// ==========================================
// TODO 3: 實作通用層介面
// ==========================================
void managed_task_init(ManagedTask *task, task_run_cb_t run, task_destroy_cb_t destroy, void *ctx) {
    // 初始化並防禦 NULL 指針
    if (task == NULL) return;
    task->run = run;
    task->destroy = destroy;
    task->context = ctx;
}

void managed_task_run(const ManagedTask *task) {
    // 執行任務回呼
    if (task == NULL || task->run == NULL) return;
    task->run(task->context);
}

void managed_task_destroy(ManagedTask *task) {
    // 調用解構回呼清理資源，並將內部指標清空
    if (task == NULL) return;
    if (task->destroy != NULL && task->context != NULL)
    {
        task->destroy(task->context);
        task->context=NULL;
    }
    task->run=NULL;
    task->destroy=NULL;
}

// ==========================================
// TODO 4: 實作應用層中介轉接函式 (Thunk) 與 解構清理函式
// 提示：簽名必須符合 task_run_cb_t 與 task_destroy_cb_t
// ==========================================
// void session_thunk_adapter(...);
// void session_cleanup(...);
void session_thunk_adapter(void *ctx)
{
    Session *session = (Session*)ctx;
    session_process(session);
    
}
void session_cleanup(void *ctx)
{
    Session *session = (Session*)ctx;
    if (session != NULL)        
    {
        free(session);
        session = NULL;
    }
}


int main(void) {
    // 應用層於堆積配置業務上下文
    Session *s = (Session *)malloc(sizeof(Session));
    assert(s != NULL);
    s->session_id = 999;
    s->payload_processed = 0;

    ManagedTask task;
    // 註冊 Thunk 與 Cleanup 回呼
    managed_task_init(&task, session_thunk_adapter, session_cleanup, s);

    // 模擬調度執行
    managed_task_run(&task);
    managed_task_run(&task);
    assert(s->payload_processed == 2);

    // 銷毀任務並觸發所有權釋放
    managed_task_destroy(&task);
    assert(task.context == NULL);

    printf("ex04_thunk_and_managed_lifecycle tests passed!\n");
    return 0;
}

