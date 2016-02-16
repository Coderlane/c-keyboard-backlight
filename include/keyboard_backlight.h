/**
 * @file keyboard_backlight.h
 * @brief
 * @author Travis Lane
 * @version
 * @date 2016-02-14
 */

#ifndef KB_KEYBOARD_BACKLIGHT_H
#define KB_KEYBOARD_BACKLIGHT_H

struct kb_keyboard;

struct kb_keyboard *kb_keyboard_find_first();
void kb_keyboard_delete(struct kb_keyboard **kbk_ptr);

int kb_keyboard_get_brightness(struct kb_keyboard *kb, int *out_brightness);
int kb_keyboard_set_brightness(struct kb_keyboard *kb, int brightness);

int kb_keyboard_get_max_brightness(struct kb_keyboard *kb, int *out_max);
int kb_keyboard_get_step_brightness(struct kb_keyboard *kb, int *out_step);

#endif /* _KB_KEYBOARD_BACKLIGHT_H */
