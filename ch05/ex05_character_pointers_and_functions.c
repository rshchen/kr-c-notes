#include <stdio.h>
#include <assert.h>

void string_copy(char *dest, const char *src) {
    // TODO: 使用 K&R 指標簡化慣用法完成字串複製
    if (dest == NULL || src == NULL) return;
    while((*dest++ = *src++)!='\0');
}

int main(void) {
    char source[] = "K&R C Language";
    char destination[32];

    string_copy(destination, source);

    int idx = 0;
    while (source[idx] != '\0') {
        assert(destination[idx] == source[idx]);
        idx++;
    }
    assert(destination[idx] == '\0');

    return 0;
}

