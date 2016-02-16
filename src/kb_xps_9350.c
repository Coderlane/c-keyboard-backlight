/**
 * @file xps_9350.c
 * @brief
 * @author Travis Lane
 * @version
 * @date 2016-02-15
 */

#include <assert.h>
#include <libudev.h>

#include "keyboard_backlight.h"
#include "keyboard_backlight_internal.h"
#include "sysfs_utils.h"

struct kb_xps_9350 {
  const char *kbx_brightness_path;
  const char *kbx_max_brightness_path;
};

#define kb_xps_9350_path "/sys/devices/platform/dell-laptop/leds/dell::kbd_backlight"

static struct kb_xps_9350 g_xps_9350_ctx = {
  kb_xps_9350_path "/brightness",
  kb_xps_9350_path "/max_brightness"
};

int xps_9350_get_brightness(struct kb_controller *kb, int *out_brightness);
int xps_9350_set_brightness(struct kb_controller *kb, int brightness);
int xps_9350_get_max_brightness(struct kb_controller *kb, int *out_max);
int xps_9350_get_step_brightness(struct kb_controller *kb, int *out_step);

struct kb_controller *
kb_controller_xps_9350_new(struct udev_device *device)
{
  struct kb_controller *kb;
  kb = kb_controller_new(device, KBCT_XPS_9350, &g_xps_9350_ctx);


  kb->kbc_get_brightness = xps_9350_get_brightness;
  kb->kbc_set_brightness = xps_9350_set_brightness;

  kb->kbc_get_max_brightness = xps_9350_get_max_brightness;
  kb->kbc_get_step_brightness = xps_9350_get_step_brightness;

  return kb;
}

struct udev_device *
kb_controller_xps_9350_find_first(struct udev *udev_ctx)
{
  struct udev_device *dev = NULL;
	struct udev_enumerate *enumer = NULL;
	struct udev_list_entry *devs = NULL,  *dev_entry = NULL;

	enumer = udev_enumerate_new(udev_ctx);
  udev_enumerate_add_syspath(enumer, kb_xps_9350_path);

	// Scan and get the list of items found.
	udev_enumerate_scan_devices(enumer);
	devs = udev_enumerate_get_list_entry(enumer);


	udev_list_entry_foreach(dev_entry, devs) {
    const char *path;
		path = udev_list_entry_get_name(dev_entry);
		dev = udev_device_new_from_syspath(udev_ctx, path);

    /* Found the device we were looking for. */
    udev_device_ref(dev);
    break;
	}

	udev_enumerate_unref(enumer);
  return dev;
}

int
xps_9350_get_brightness(struct kb_controller *kb, int *out_brightness)
{
  struct kb_xps_9350 *ctx;
  assert(kb->kbc_type == KBCT_XPS_9350);
  assert(kb->kbc_ctx != NULL);

  ctx = kb->kbc_ctx;

  return sysfs_read_attr_int(ctx->kbx_brightness_path, out_brightness);
}


int
xps_9350_set_brightness(struct kb_controller *kb, int brightness)
{
  struct kb_xps_9350 *ctx;
  assert(kb->kbc_type == KBCT_XPS_9350);
  assert(kb->kbc_ctx != NULL);

  ctx = kb->kbc_ctx;

  return sysfs_write_attr_int(ctx->kbx_brightness_path, brightness);
}

int
xps_9350_get_max_brightness(struct kb_controller *kb, int *out_max)
{
  struct kb_xps_9350 *ctx;
  assert(kb->kbc_type == KBCT_XPS_9350);
  assert(kb->kbc_ctx != NULL);

  ctx = kb->kbc_ctx;

  return sysfs_read_attr_int(ctx->kbx_max_brightness_path, out_max);
}

int
xps_9350_get_step_brightness(struct kb_controller *kb, int *out_step)
{
  assert(kb->kbc_type == KBCT_XPS_9350);

  *out_step = 1;
  return 0;
}
