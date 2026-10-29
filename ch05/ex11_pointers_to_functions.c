#include <stdio.h>
#include <stddef.h>
#include <assert.h>

typedef int (*comparator_t)(const void *, const void *);

static void swap_bytes(char *a, char *b, size_t size)
{
    char temp;
    while(size-- > 0)
    {
        temp = *a;
        *a++ = *b;
        *b++ = temp;    
    }
}

void generic_bubble_sort(void *base, size_t nitems, size_t size, comparator_t comp) {
    // TODO: 使用函式指標 comp 進行元素比較
    // TODO: 進行逐位元組記憶體交換
    if (base == NULL || comp == NULL || nitems < 2 || size == 0) return;
    char *bytes = (char*)base;
    for (int i = 0; i < nitems - 1; ++i)
    {
        for (int j = 0; j < nitems - 1 - i; ++j)
        {
            char *p1 = bytes + j * size;
            char *p2 = p1 + size;
            if (comp(p1, p2) > 0)
            {
                swap_bytes(p1, p2, size);
            }

        }
    }
}

int compare_int_asc(const void *a, const void *b) {
    // TODO: 將 void* 轉回 int* 並進行數值遞增比較
    int *val1 = (int*)a;
    int *val2 = (int*)b;
    if (*val1 > *val2) return 1;
    if (*val1 < *val2) return -1;
    return 0;
}

int main(void) {
    int arr[5] = {50, 10, 40, 20, 30};

    generic_bubble_sort(arr, 5, sizeof(int), compare_int_asc);

    for (int i = 0; i < 4; i++) {
        assert(arr[i] <= arr[i + 1]);
    }
    assert(arr[0] == 10 && arr[4] == 50);

    return 0;
}

