/**
 * @file keyboard_backlight.h
 * @brief
 * @author Travis Lane
 * @version
 * @date 2016-02-14
 */

#ifndef KB_KEYBOARD_BACKLIGHT_H
#define KB_KEYBOARD_BACKLIGHT_H

struct kb_controller;

struct kb_controller *kb_controller_find_first();
void kb_controller_delete(struct kb_controller **kbc_ptr);

int kb_controller_get_brightness(struct kb_controller *kb, int *out_brightness);
int kb_controller_set_brightness(struct kb_controller *kb, int brightness);

int kb_controller_get_max_brightness(struct kb_controller *kb, int *out_max);
int kb_controller_get_step_brightness(struct kb_controller *kb, int *out_step);

#endif /* _KB_KEYBOARD_BACKLIGHT_H */
