#include <stdio.h>
#include <stdlib.h>
#include <string.h>
char* input_string() {
    char buffer[256];

    printf("input exp: ");

    if (fgets(buffer, sizeof(buffer), stdin) == NULL) {
        return NULL;
    }

    size_t len = strlen(buffer);
    if (len > 0 && buffer[len - 1] == '\n') {
        buffer[len - 1] = '\0';
    }

    char* result = malloc(strlen(buffer) + 1);
    if (result != NULL) {
        strcpy(result, buffer);
    }

    return result;
}