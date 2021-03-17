#ifndef __KLOG_H__
#define __KLOG_H__
#define KLOG_ERROR(format, ...) klog_error(__FILE__, __func__, __LINE__, format, ## __VA_ARGS__)
#define KLOG_INFO(format, ...) klog_info(__FILE__, __func__, __LINE__, format, ## __VA_ARGS__)
void klog_error(const char *file, const char *function_name, const char *line_number, ...);
void klog_info(const char *file, const char *function_name, const char *line_number, ...);
#endif
