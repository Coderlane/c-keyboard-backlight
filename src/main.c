
#include <assert.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>

#include <libudev.h>

#include "keyboard_backlight.h"

static const char *usage = "usage: keyboard-backlight <option>\n"
"options:\n"
" -inc <amount>\n"
" -dec <amount>\n"
" -set <value>\n"
" -get\n"
" -help\n";

void do_usage();
void do_error(const char *err);

int do_cmd(int cmd, char *str);
int do_inc(struct kb_controller *kb, int val);
int do_dec(struct kb_controller *kb, int val);
int do_set(struct kb_controller *kb, int val);
int do_get(struct kb_controller *kb);

int
main(int argc, char *argv[]) {
  int inc = 0, dec = 0, set = 0, get = 0, tot = 0, cmd = 0;
  char *int_str = NULL;

  int c, long_option_index;
  static struct option long_options[] = {
    {"inc",  1, 0, 'i'},
    {"dec",  1, 0, 'd'},
    {"set",  1, 0, 's'},
    {"get",  0, 0, 'g'},
    {"help", 0, 0, 'h'},
    {0,      0, 0, 0}
  };

  do {
    c = getopt_long(argc, argv, "ghi:d:s:", long_options, &long_option_index);
    if (c < 0) {
      break;
    }

    switch(c) {
      case 'i':
        inc++;
        int_str = optarg;
        cmd = c;
        break;
      case 'd':
        dec++;
        int_str = optarg;
        cmd = c;
        break;
      case 's':
        set++;
        int_str = optarg;
        cmd = c;
        break;
      case 'g':
        get++;
        cmd = c;
        break;
      case 'h':
        do_usage();
        return 0;
      default:
        do_error("Invalid option.");
        return 1;
    }
  } while(c >= 0);

  tot = inc + dec + get + set;
  if (tot != 1) {
    do_error("Please choose only one option at a time.");
    return 2;
  }

  return do_cmd(cmd, int_str);
}

void
do_error(const char *err) {
  printf("Error: %s\n", err);
  do_usage();
}

void
do_usage() {
  printf("%s\n", usage);
}

int
do_cmd(int cmd, char *str) {
  int val = 0, rv = 0;
  struct kb_controller *kb;
  struct udev *udev_ctx;

  if (str != NULL) {
    val = atoi(str);
  }

  udev_ctx = udev_new();
  kb = kb_controller_find_first(udev_ctx);

  if (kb == NULL) {
    printf("Failed to find a supported keyboard backlight controller.\n");
    return 2;
  }

  switch(cmd) {
    case 'i':
      rv = do_inc(kb, val);
      goto out;
    case 'd':
      rv = do_dec(kb, val);
      goto out;
    case 's':
      rv = do_set(kb, val);
      goto out;
    case 'g':
      rv = do_get(kb);
      goto out;
    default:
      printf("Invalid option.\n");
      rv = 3;
      goto out;
  }

out:
  if (kb != NULL) {
    kb_controller_delete(&kb);
  }

  if (udev_ctx != NULL) {
    udev_unref(udev_ctx);
  }
  return rv;
}

int
do_inc(struct kb_controller *kb, int val)
{
  int cur, max, rv, set;

  rv = kb_controller_get_brightness(kb, &cur);
  if (rv != 0) {
    printf("Failed to get current brightness.\n");
    return rv;
  }

  rv = kb_controller_get_max_brightness(kb, &max);
  if (rv != 0) {
    printf("Failed to get maximum brightness.\n");
    return rv;
  }

  set = cur + val;
  if (set > max || set < 0) {
    printf("Invalid value.\n");
    return ERANGE;
  }

  rv = kb_controller_set_brightness(kb, set);
  if (rv != 0) {
    printf("Failed to set brightness.\n");
    return rv;
  }

  return 0;
}

int
do_dec(struct kb_controller *kb, int val)
{
  int cur, max, rv, set;

  rv = kb_controller_get_brightness(kb, &cur);
  if (rv != 0) {
    printf("Failed to get current brightness.\n");
    return rv;
  }

  rv = kb_controller_get_max_brightness(kb, &max);
  if (rv != 0) {
    printf("Failed to get maximum brightness.\n");
    return rv;
  }

  set = cur - val;
  if (set > max || set < 0) {
    printf("Invalid value.\n");
    return ERANGE;
  }

  rv = kb_controller_set_brightness(kb, set);
  if (rv != 0) {
    printf("Failed to set brightness.\n");
    return rv;
  }

  return 0;
}

int
do_set(struct kb_controller *kb, int set)
{
  int cur, max, rv;

  rv = kb_controller_get_brightness(kb, &cur);
  if (rv != 0) {
    printf("Failed to get current brightness.\n");
    return rv;
  }

  rv = kb_controller_get_max_brightness(kb, &max);
  if (rv != 0) {
    printf("Failed to get maximum brightness.\n");
    return rv;
  }

  if (set > max || set < 0) {
    printf("Invalid value.\n");
    return ERANGE;
  }

  rv = kb_controller_set_brightness(kb, set);
  if (rv != 0) {
    printf("Failed to set brightness.\n");
    return rv;
  }

  return 0;
}

int
do_get(struct kb_controller *kb)
{
  int cur, rv;

  rv = kb_controller_get_brightness(kb, &cur);
  if (rv != 0) {
    printf("Failed to get current brightness.\n");
    return rv;
  }

  printf("%d\n", cur);
  return 0;
}

