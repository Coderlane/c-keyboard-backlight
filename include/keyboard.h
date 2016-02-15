/**
 * @file keyboard.h
 * @brief
 * @author Travis Lane
 * @version
 * @date 2016-02-14
 */

#ifndef KB_KEYBOARD_H
#define KB_KEYBOARD_H

struct kb_keyboard;

enum kb_keyboard_type {
  KBKT_DELL_9350 = 1,
};


typedef int (*kb_get_int_func)(struct kb_keyboard *, int *);
typedef int (*kb_set_int_func)(struct kb_keyboard *, int);

struct kb_keyboard {
  struct udev_device *kbk_device;

  kb_get_int_func kbk_get_brightness;
  kb_get_int_func kbk_set_brightness;

  kb_get_int_func kbk_get_max_brightness;
  kb_get_int_func kbk_get_step_brightness;

  enum kb_keyboard_type kbk_type;
  void  *kbk_ctx;
};


#endif /* _KB_KEYBOARD_H */
