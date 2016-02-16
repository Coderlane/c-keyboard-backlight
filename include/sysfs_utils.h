/**
 * @file sysfs_utils.h
 * @brief
 * @author Travis Lane
 * @version
 * @date 2016-02-15
 */

#include <unistd.h>

int sysfs_read_attr_str(const char *path, char *buff, size_t buff_size,
                        ssize_t *out_len);
int sysfs_write_attr_str(const char *path, const char *buff, size_t buff_len,
                         ssize_t *out_len);
int sysfs_read_attr_int(const char *path, int *data);
int sysfs_write_attr_int(const char *path, int data);
int sysfs_read_attr_float(const char *path, float *data);
int sysfs_write_attr_float(const char *path, float data);
