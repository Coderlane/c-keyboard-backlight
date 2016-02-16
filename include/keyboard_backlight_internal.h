/**
 * @file keyboard_backlight_internal.h
 * @brief
 * @author Travis Lane
 * @version
 * @date 2016-02-15
 */

#ifndef KB_KEYBOARD_BACKLIGHT_INTERNAL_H
#define KB_KEYBOARD_BACKLIGHT_INTERNAL_H

struct kb_controller;

enum kb_controller_type {
  KBCT_XPS_9350 = 0,
  KBCT_MAX = 1,
};

typedef int (*kb_get_int_func)(struct kb_controller *, int *);
typedef int (*kb_set_int_func)(struct kb_controller *, int);

typedef struct udev_device *(*kb_find_first_func)(struct udev *);
typedef struct kb_controller *(*kb_new_func)(struct udev_device *);

struct kb_controller {
  struct udev_device *kbc_device;

  kb_get_int_func kbc_get_brightness;
  kb_set_int_func kbc_set_brightness;

  kb_get_int_func kbc_get_max_brightness;
  kb_get_int_func kbc_get_step_brightness;

  enum kb_controller_type kbc_type;
  void  *kbc_ctx;
};

/* Generic Keyboard Functions */
struct kb_controller *kb_controller_new(struct udev_device *device,
    enum kb_controller_type type, void *ctx);

/* Specific Keyboard Creation Functions */
struct kb_controller *kb_controller_xps_9350_new(struct udev_device *device);
struct udev_device *kb_controller_xps_9350_find_first(struct udev *udev_ctx);

#endif /* _KB_KEYBOARD_BACKLIGHT_INTERNAL_H */
