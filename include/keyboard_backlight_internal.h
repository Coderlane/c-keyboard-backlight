/**
 * @file keyboard_backlight_internal.h
 * @brief
 * @author Travis Lane
 * @version
 * @date 2016-02-15
 */

#ifndef KB_KEYBOARD_BACKLIGHT_INTERNAL_H
#define KB_KEYBOARD_BACKLIGHT_INTERNAL_H

enum kb_keyboard_type {
  KBKT_XPS_9350 = 1,
};

typedef int (*kb_get_int_func)(struct kb_keyboard *, int *);
typedef int (*kb_set_int_func)(struct kb_keyboard *, int);

struct kb_keyboard {
  struct udev_device *kbk_device;

  kb_get_int_func kbk_get_brightness;
  kb_set_int_func kbk_set_brightness;

  kb_get_int_func kbk_get_max_brightness;
  kb_get_int_func kbk_get_step_brightness;

  enum kb_keyboard_type kbk_type;
  void  *kbk_ctx;
};

/* Generic Keyboard Functions */
struct kb_keyboard *kb_keyboard_new(struct udev_device *device,
    enum kb_keyboard_type type, void *ctx);

/* Specific Keyboard Creation Functions */
struct kb_keyboard *kb_keyboard_xps_9350_new(struct udev_device *device);

#endif /* _KB_KEYBOARD_BACKLIGHT_INTERNAL_H */
