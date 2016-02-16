/**
 * @file xps_9350.c
 * @brief
 * @author Travis Lane
 * @version
 * @date 2016-02-15
 */

#include <assert.h>

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

int xps_9350_get_brightness(struct kb_keyboard *kb, int *out_brightness);
int xps_9350_set_brightness(struct kb_keyboard *kb, int brightness);
int xps_9350_get_max_brightness(struct kb_keyboard *kb, int *out_max);
int xps_9350_get_step_brightness(struct kb_keyboard *kb, int *out_step);

struct kb_keyboard *
kb_keyboard_xps_9350_new(struct udev_device *device)
{
  struct kb_keyboard *kb;
  kb = kb_keyboard_new(device, KBKT_XPS_9350, &g_xps_9350_ctx);


  kb->kbk_get_brightness = xps_9350_get_brightness;
  kb->kbk_set_brightness = xps_9350_set_brightness;

  kb->kbk_get_max_brightness = xps_9350_get_max_brightness;
  kb->kbk_get_step_brightness = xps_9350_get_step_brightness;

  return kb;
}

int
xps_9350_get_brightness(struct kb_keyboard *kb, int *out_brightness)
{
  struct kb_xps_9350 *ctx;
  assert(kb->kbk_type == KBKT_XPS_9350);
  assert(kb->kbk_ctx != NULL);

  ctx = kb->kbk_ctx;

  return sysfs_read_attr_int(ctx->kbx_brightness_path, out_brightness);
}


int
xps_9350_set_brightness(struct kb_keyboard *kb, int brightness)
{
  struct kb_xps_9350 *ctx;
  assert(kb->kbk_type == KBKT_XPS_9350);
  assert(kb->kbk_ctx != NULL);

  ctx = kb->kbk_ctx;

  return sysfs_write_attr_int(ctx->kbx_brightness_path, brightness);
}

int
xps_9350_get_max_brightness(struct kb_keyboard *kb, int *out_max)
{
  struct kb_xps_9350 *ctx;
  assert(kb->kbk_type == KBKT_XPS_9350);
  assert(kb->kbk_ctx != NULL);

  ctx = kb->kbk_ctx;

  return sysfs_read_attr_int(ctx->kbx_max_brightness_path, out_max);
}

int
xps_9350_get_step_brightness(struct kb_keyboard *kb, int *out_step)
{
  assert(kb->kbk_type == KBKT_XPS_9350);

  *out_step = 1;
  return 0;
}
