/**
 * @file keyboard_backlight.c
 * @brief
 * @author Travis Lane
 * @version
 * @date 2016-02-15
 */


#include <assert.h>
#include <errno.h>
#include <stdlib.h>

#include <libudev.h>

#include "keyboard_backlight.h"
#include "keyboard_backlight_internal.h"

/**
 * @brief Create a new generic keyboard backlight object.
 *
 *
 * @param device The udev device that represents this keyboard backlight. This
 * device will be referenced internally.
 * @param type The type of the keyboard backlight.
 * @param ctx A context for the specific type of keyboard backlight. This
 * memory must be externally tracked.
 *
 * @return A new generic keyboard  backlight object initialized with the
 * specified input. However, all of the capabilities are not yet initalized.
 */
struct kb_keyboard *
kb_keyboard_new(struct udev_device *device,
    enum kb_keyboard_type type, void *ctx)
{
  struct kb_keyboard *kb = calloc(sizeof(struct kb_keyboard), 1);
  assert(kb != NULL);

  assert(device != NULL);
  udev_device_ref(device);
  kb->kbk_device = device;

  kb->kbk_type = type;
  kb->kbk_ctx = ctx;

  return kb;
}

/**
 * @brief Destroy a generic keyboard backlight object.
 *
 * Unref's the udev_device.
 *
 * @param kb_ptr A pointer to a pointer to a keyboard backlight.
 */
void
kb_keyboard_delete(struct kb_keyboard **kb_ptr)
{
  struct kb_keyboard *kb;
  assert(kb_ptr != NULL);

  kb = *kb_ptr;

  udev_device_unref(kb->kbk_device);

  free(kb);
  *kb_ptr = NULL;
}

/**
 * @brief Get the current brightness of a keyboard backlight.
 *
 * @param kb The keyboard backlight to get the brightness of.
 * @param out_brightness The current brightness of the keyboard backlight.
 *
 * @return 0 on success, !0 on failure.
 * ENOTSUP: The keyboard backlight does not support this operation.
 */
int
kb_keyboard_get_brightness(struct kb_keyboard *kb, int *out_brightness)
{
  assert(kb != NULL);
  assert(out_brightness != NULL);

  if (kb->kbk_get_brightness == NULL) {
    return ENOTSUP;
  }

  return kb->kbk_get_brightness(kb, out_brightness);
}

/**
 * @brief Set the current brightness of a keyboard backlight.
 *
 * @param kb The keyboard backlight to set the brightness of.
 * @param brightness The new brightness of the keyboard backlight.
 *
 * @return 0 on success, !0 on failure.
 * ENOTSUP: The keyboard backlight does not support this operation.
 */
int
kb_keyboard_set_brightness(struct kb_keyboard *kb, int brightness)
{
  assert(kb != NULL);

  if (kb->kbk_set_brightness == NULL) {
    return ENOTSUP;
  }

  return kb->kbk_set_brightness(kb, brightness);
}

/**
 * @brief Get the max brightness of a keyboard backlight.
 *
 * @param kb The keyboard backlight to get the max brightness of.
 * @param out_max The maximum brightness of the keyboard backlight.
 *
 * @return 0 on success, !0 on failure.
 * ENOTSUP: The keyboard backlight does not support this operation.
 */
int
kb_keyboard_get_max_brightness(struct kb_keyboard *kb, int *out_max)
{
  assert(kb != NULL);
  assert(out_max != NULL);

  if (kb->kbk_get_max_brightness == NULL) {
    return ENOTSUP;
  }

  return kb->kbk_get_max_brightness(kb, out_max);
}

/**
 * @brief Get the steps in brightness that a keyboard backlight supports.
 *
 * @param kb The keyboard backlight to get the supported steps in brightness of.
 * @param out_step The steps in brightness that a keyboard backlight supports.
 *
 * @return 0 on success, !0 on failure.
 * ENOTSUP: The keyboard backlight does not support this operation.
 */
int
kb_keyboard_get_step_brightness(struct kb_keyboard *kb, int *out_step)
{
  assert(kb != NULL);
  assert(out_step != NULL);

  if (kb->kbk_get_step_brightness == NULL) {
    return ENOTSUP;
  }

  return kb->kbk_get_step_brightness(kb, out_step);
}
