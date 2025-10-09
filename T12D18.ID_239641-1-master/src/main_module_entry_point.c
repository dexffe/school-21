#include <stdio.h>
#include <stdlib.h>
#include "documentation_module.h"
#include "print_module.h"

int main() {
    int* availability_mask = check_available_documentation_module(validate, Documents_count, Documents);

    if (availability_mask) {
        char* documents[] = { "Linked lists", "Queues", "Maps", "Binary Trees" };

        for (int i = 0; i < Documents_count; ++i) {
            char status[12];
            if (availability_mask[i]) {
                snprintf(status, sizeof(status), "available");
            } else {
                snprintf(status, sizeof(status), "unavailable");
            }

            char message[50];
            snprintf(message, sizeof(message), "%-15s : %s", documents[i], status);

            print_log(print_char, message);
        }

        free(availability_mask);
    }

    return 0;
}
