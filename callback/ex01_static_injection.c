#include <stdio.h>
#include <stdbool.h>
#include <assert.h>

// 定義回呼判定函式指標型別
typedef bool (*predicate_fn)(int value);

// 【通用管線層】走訪陣列並過濾元素
size_t filter_array(const int *src, size_t len, int *dst, predicate_fn pred) {
    // TODO: 走訪 src，若 pred 判斷為 true，則依序存入 dst，最後回傳匹配總數
    size_t matched_count = 0;
    for (int i = 0; i < len; ++i)
    {
        if (pred(src[i])) 
        {
            *dst++ = src[i];
            ++matched_count;
        }
    }
    return matched_count;
}

// 【應用層 / 業務邏輯】判斷是否為偶數
bool is_even(int value) {
    // TODO: 實作偶數判定邏輯
    return value % 2 == 0;
}

// 【應用層 / 業務邏輯】判斷是否為正數
bool is_positive(int value) {
    // TODO: 實作正數判定邏輯
    return value > 0;
}

int main(void) {
    int input[] = {-3, -2, -1, 0, 1, 2, 3, 4};
    size_t len = sizeof(input) / sizeof(input[0]);
    int output[8];

    // 測試注入 is_even
    size_t count_even = filter_array(input, len, output, is_even);
    assert(count_even == 4);
    assert(output[0] == -2);
    assert(output[1] == 0);
    assert(output[2] == 2);
    assert(output[3] == 4);

    // 測試注入 is_positive
    size_t count_pos = filter_array(input, len, output, is_positive);
    assert(count_pos == 4);
    assert(output[0] == 1);
    assert(output[1] == 2);
    assert(output[2] == 3);
    assert(output[3] == 4);

    printf("ex01_static_injection tests passed!\n");
    return 0;
}

