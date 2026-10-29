#include <stdio.h>
#include <assert.h>

typedef void (*sensor_alert_cb_t)(int sensor_id, void *context);

typedef struct {
    int sensor_id;
    sensor_alert_cb_t callback;
    void *context;
} SensorHub;

// 【通用層】初始化
void sensor_hub_init(SensorHub *hub, int sensor_id) {
    // TODO: 初始化各成員
    if (hub == NULL) return;
    hub->sensor_id = sensor_id;
    hub-> callback = NULL;
    hub->context = NULL;
}

// 【通用層】註冊回呼與上下文
void sensor_hub_register(SensorHub *hub, sensor_alert_cb_t cb, void *context) {
    // TODO: 保存回呼函式與上下文指標
    if (hub == NULL) return;
    hub->callback = cb;
    hub->context = context;
}

// 【通用層】模擬觸發
void sensor_hub_trigger(const SensorHub *hub) {
    // TODO: 觸發回呼並回傳 sensor_id 與 context
    if (hub == NULL || hub->callback == NULL) return;
    hub->callback(hub->sensor_id, hub->context);

}

// 【應用層】業務狀態定義
typedef struct {
    int trigger_count;
    double threshold_value;
} MonitorContext;

// 【應用層】業務回呼實作
void on_sensor_threshold_exceeded(int sensor_id, void *context) {
    // TODO: 1. 型別顯式還原為 MonitorContext*
    // TODO: 2. 更新 trigger_count
    if (context == NULL) return;
    MonitorContext *monitor_context = (MonitorContext*)context;
    ++monitor_context->trigger_count;

}

int main(void) {
    SensorHub hub;
    sensor_hub_init(&hub, 8080);

    // 建立生命週期貫穿程式運行期的上下文實體
    MonitorContext monitor = {.trigger_count = 0, .threshold_value = 95.5};

    sensor_hub_register(&hub, on_sensor_threshold_exceeded, &monitor);

    // 連續觸發兩次
    sensor_hub_trigger(&hub);
    sensor_hub_trigger(&hub);

    assert(monitor.trigger_count == 2);

    printf("ex03_stateful_context tests passed!\n");
    return 0;
}

