#include <stdio.h>
#include <assert.h>

int access_rect_array(const int (*arr)[4], int row, int col) {
    // TODO: 存取連續二維陣列中的元素
    return arr[row][col];
}

int access_ragged_array(const int * const *arr, int row, int col) {
    // TODO: 存取指標陣列（雙重指標）中的元素
    return arr[row][col];
}

int main(void) {
    /* 1. 連續二維矩形陣列 */
    int rect_matrix[2][4] = {
        {10, 20, 30, 40},
        {50, 60, 70, 80}
    };

    /* 2. 指標陣列 */
    int row0[] = {10, 20, 30, 40};
    int row1[] = {50, 60, 70, 80};
    const int *ragged_matrix[2] = {row0, row1};

    assert(access_rect_array(rect_matrix, 1, 2) == 70);
    assert(access_ragged_array(ragged_matrix, 1, 2) == 70);

    return 0;
}

