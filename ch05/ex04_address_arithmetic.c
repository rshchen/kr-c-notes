#include <stdio.h>
#include <stddef.h>
#include <assert.h>

ptrdiff_t pointer_distance(const int *p1, const int *p2) {
    // TODO: 計算並回傳 p1 與 p2 之間相隔的元素數量 (p1 - p2)
    return (p1 - p2);
}

int main(void) {
    int buffer[10];
    int *p_start = &buffer[2];
    int *p_end = &buffer[7];

    ptrdiff_t diff = pointer_distance(p_end, p_start);
    ptrdiff_t neg_diff = pointer_distance(p_start, p_end);
    assert(diff == 5);
    assert(neg_diff == -5);

    return 0;
}

