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

static kb_find_first_func kb_find_first_funcs[] = {
  kb_controller_xps_9350_find_first
};

static kb_new_func kb_new_funcs[] = {
  kb_controller_xps_9350_new
};

/**
 * @brief Create a new generic keyboard backlight controller object.
 *
 *
 * @param device The udev device that represents this keyboard backlight
 * controller. This device will be referenced internally.
 * @param type The type of the keyboard backlight controller.
 * @param ctx A context for the specific type of keyboard backlight
 * controller. This memory must be externally tracked.
 *
 * @return A new generic keyboard  backlight object initialized with the
 * specified input. However, all of the capabilities are not yet initalized.
 */
struct kb_controller *
kb_controller_new(struct udev_device *device,
    enum kb_controller_type type, void *ctx)
{
  struct kb_controller *kb = calloc(sizeof(struct kb_controller), 1);
  assert(kb != NULL);

  assert(device != NULL);
  udev_device_ref(device);
  kb->kbc_device = device;

  kb->kbc_type = type;
  kb->kbc_ctx = ctx;

  return kb;
}

/**
 * @brief Destroy a generic keyboard backlight controller object.
 *
 * Unref's the udev_device.
 *
 * @param kb_ptr A pointer to a pointer to a keyboard backlight controller.
 */
void
kb_controller_delete(struct kb_controller **kb_ptr)
{
  struct kb_controller *kb;
  assert(kb_ptr != NULL);

  kb = *kb_ptr;

  udev_device_unref(kb->kbc_device);

  free(kb);
  *kb_ptr = NULL;
}

/**
 * @brief Find the first avalibale keyboard backlight controller.
 *
 * @return The first keyboard backlight controller found or
 * NULL if none are found.
 */
struct kb_controller *kb_controller_find_first(struct udev *udev_ctx)
{
  struct udev_device *dev;
  struct kb_controller *kb = NULL;

  for(enum kb_controller_type type = 0; type < KBCT_MAX; type++) {
    dev = kb_find_first_funcs[type](udev_ctx);

    if (dev != NULL) {
      /* Found a possible device, try to create it. */
      kb = kb_new_funcs[type](dev);
      udev_device_unref(dev);

      if (kb != NULL) {
        /* Success! Just return now. */
        goto out;
      }
    }
  }

out:
  return kb;
}


/**
 * @brief Get the current brightness of a keyboard backlight controller.
 *
 * @param kb The keyboard backlight controller to get the brightness of.
 * @param out_brightness The current brightness of the keyboard
 * backlight controller.
 *
 * @return 0 on success, !0 on failure.
 * ENOTSUP: The keyboard backlight controller does not support this operation.
 */
int
kb_controller_get_brightness(struct kb_controller *kb, int *out_brightness)
{
  assert(kb != NULL);
  assert(out_brightness != NULL);

  if (kb->kbc_get_brightness == NULL) {
    return ENOTSUP;
  }

  return kb->kbc_get_brightness(kb, out_brightness);
}

/**
 * @brief Set the current brightness of a keyboard backlight controller.
 *
 * @param kb The keyboard backlight controller to set the brightness of.
 * @param brightness The new brightness of the keyboard backlight controller.
 *
 * @return 0 on success, !0 on failure.
 * ENOTSUP: The keyboard backlight controller does not support this operation.
 */
int
kb_controller_set_brightness(struct kb_controller *kb, int brightness)
{
  assert(kb != NULL);

  if (kb->kbc_set_brightness == NULL) {
    return ENOTSUP;
  }

  return kb->kbc_set_brightness(kb, brightness);
}

/**
 * @brief Get the max brightness of a keyboard backlight controller.
 *
 * @param kb The keyboard backlight controller to get the max brightness of.
 * @param out_max The maximum brightness of the keyboard backlight controller.
 *
 * @return 0 on success, !0 on failure.
 * ENOTSUP: The keyboard backlight controller does not support this operation.
 */
int
kb_controller_get_max_brightness(struct kb_controller *kb, int *out_max)
{
  assert(kb != NULL);
  assert(out_max != NULL);

  if (kb->kbc_get_max_brightness == NULL) {
    return ENOTSUP;
  }

  return kb->kbc_get_max_brightness(kb, out_max);
}

/**
 * @brief Get the steps in brightness that a keyboard
 * backlight controller supports.
 *
 * @param kb The keyboard backlight controller to get the
 * supported steps in brightness of.
 * @param out_step The steps in brightness that a keyboard
 * backlight controller supports.
 *
 * @return 0 on success, !0 on failure.
 * ENOTSUP: The keyboard backlight controller does not support this operation.
 */
int
kb_controller_get_step_brightness(struct kb_controller *kb, int *out_step)
{
  assert(kb != NULL);
  assert(out_step != NULL);

  if (kb->kbc_get_step_brightness == NULL) {
    return ENOTSUP;
  }

  return kb->kbc_get_step_brightness(kb, out_step);
}
