#include <stdio.h>
#include <time.h>
#include "print_module.h"

int print_char(char ch) {
    return putchar(ch);
}

void print_log(int (*print)(char), const char* message) {
    time_t raw_time;
    const struct tm* time_info;
    time(&raw_time);
    time_info = localtime(&raw_time);

    char time_str[9];
    strftime(time_str, sizeof(time_str), "%H:%M:%S", time_info);

    char log_message[256];
    snprintf(log_message, sizeof(log_message), "%s %s %s", Log_prefix, time_str, message);

    for (int i = 0; log_message[i] != '\0'; ++i) {
        print(log_message[i]);
        
    }
    print('\n');
}
