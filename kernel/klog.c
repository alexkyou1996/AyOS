#include <stdint.h>
#include <stddef.h>
#include <stdarg.h>

#include "klog.h"

#define BUFFER_SIZE 1024

static size_t _strlen(const char *);
static int _vsnprintf(char *buffer, size_t buffer_size, const char *format, va_list arg);

int log_error(const char *file, const char * function, int line, char *format, ...)
{
    char buffer[BUFFER_SIZE] = {0};
    size_t log_length = 0;
    va_list args ={0};
    int ret = 0;
 
    snprintf(buffer, BUFFER_SIZE, "%s: In function (%s), line (%d): ", file, function, line);
    log_length = _strlen(buffer);
    va_start(args, format);
    vsnprintf(buffer + log_length, BUFFER_SIZE - log_length, format, args);
    va_end(args);
 
    if (verbose) {
        printf("%s\n", buffer);
        return ret;
    }
    syslog(LOG_ERR,"%s\n", buffer);
    return ret;
}

static size_t _strlen(const char *string)
{
    if (!string) {
        return 0;
    }
    size_t string_length = 0;
    while (*string++) {
        string_length++;
    }
    return string_length;
}

static int _vsnprintf(char *buffer, size_t buffer_size, const char *format, va_list arg)
{
    if (!buffer |!format) {
        return 0;
    }
    size_t buffer_current_position = 0;
    size_t format_index = 0;
    while (format[format_index]) {
        // return bool?
        size_t copied_count = _copy_until_specifier(buffer,
                buffer_size, &buffer_current_position, format, &format_index);
        switch (format[format_index]) {
            case 'c':
                break;
            case 'd':
                break;
            case 'f':
                break;
            case 'u':
                break;
            case 'p':
                break;
            case 's':
                break;
            case 'x':
                break;
            case '%':
                break;
            case '\0':
            default:
                break;
        }
    }
}
