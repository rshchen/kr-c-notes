#include <stdio.h>
#include <assert.h>

typedef void (*event_action_t)(void);

typedef struct {
    event_action_t action;
} EventSlot;

// 【通用層】初始化事件插槽
void event_slot_init(EventSlot *slot) {
    // TODO: 將內部函式指標初始化為 NULL
    slot->action = NULL;
}

// 【通用層】註冊事件
void event_slot_register(EventSlot *slot, event_action_t action) {
    // TODO: 保存函式指標
    if (slot != NULL) slot->action = action;
}

// 【通用層】觸發事件
void event_slot_trigger(const EventSlot *slot) {
    // TODO: 檢查指標是否有效，若有效則調用
    if (slot!=NULL && slot->action != NULL) slot->action();
}

// 模擬業務計數標記
static int g_flag_a = 0;
static int g_flag_b = 0;

void on_action_a(void) {
    g_flag_a++;
}

void on_action_b(void) {
    g_flag_b += 5;
}

int main(void) {
    EventSlot slot;
    event_slot_init(&slot);

    // 未註冊前觸發不應崩潰
    event_slot_trigger(&slot);
    assert(g_flag_a == 0 && g_flag_b == 0);

    // 註冊 A 並測試觸發
    event_slot_register(&slot, on_action_a);
    event_slot_trigger(&slot);
    event_slot_trigger(&slot);
    assert(g_flag_a == 2);

    // 替換註冊 B
    event_slot_register(&slot, on_action_b);
    event_slot_trigger(&slot);
    assert(g_flag_b == 5);

    printf("ex02_async_registration tests passed!\n");
    return 0;
}

