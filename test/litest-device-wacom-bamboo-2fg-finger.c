/*
 * Copyright © 2017 Red Hat, Inc.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a
 * copy of this software and associated documentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modify, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice (including the next
 * paragraph) shall be included in all copies or substantial portions of the
 * Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.  IN NO EVENT SHALL
 * THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
 * DEALINGS IN THE SOFTWARE.
 */

#include "config.h"

#include "litest.h"
#include "litest-int.h"

static struct input_event down[] = {
	{ .type = EV_ABS, .code = ABS_X, .value = LITEST_AUTO_ASSIGN },
	{ .type = EV_ABS, .code = ABS_Y, .value = LITEST_AUTO_ASSIGN },
	{ .type = EV_ABS, .code = ABS_MT_SLOT, .value = LITEST_AUTO_ASSIGN },
	{ .type = EV_ABS, .code = ABS_MT_TRACKING_ID, .value = LITEST_AUTO_ASSIGN },
	{ .type = EV_ABS, .code = ABS_MT_POSITION_X, .value = LITEST_AUTO_ASSIGN },
	{ .type = EV_ABS, .code = ABS_MT_POSITION_Y, .value = LITEST_AUTO_ASSIGN },
	{ .type = EV_SYN, .code = SYN_REPORT, .value = 0 },
	{ .type = -1, .code = -1 },
};

static struct input_event move[] = {
	{ .type = EV_ABS, .code = ABS_MT_SLOT, .value = LITEST_AUTO_ASSIGN },
	{ .type = EV_ABS, .code = ABS_X, .value = LITEST_AUTO_ASSIGN },
	{ .type = EV_ABS, .code = ABS_Y, .value = LITEST_AUTO_ASSIGN },
	{ .type = EV_ABS, .code = ABS_MT_POSITION_X, .value = LITEST_AUTO_ASSIGN },
	{ .type = EV_ABS, .code = ABS_MT_POSITION_Y, .value = LITEST_AUTO_ASSIGN },
	{ .type = EV_SYN, .code = SYN_REPORT, .value = 0 },
	{ .type = -1, .code = -1 },
};

static struct litest_device_interface interface = {
	.touch_down_events = down,
	.touch_move_events = move,
};

static struct input_absinfo absinfo[] = {
	{ ABS_X, 0, 15360, 0, 0, 128 },
	{ ABS_Y, 0, 10240, 0, 0, 128 },
	{ ABS_MT_SLOT, 0, 1, 0, 0, 0 },
	{ ABS_MT_POSITION_X, 0, 15360, 0, 0, 128 },
	{ ABS_MT_POSITION_Y, 0, 10240, 0, 0, 128 },
	{ ABS_MT_TRACKING_ID, 0, 65535, 0, 0, 0 },
	{ ABS_MISC, 0, 0, 0, 0, 0 },
	{ .value = -1 },
};

static struct input_id input_id = {
	.bustype = 0x3,
	.vendor = 0x56a,
	.product = 0xd1,
	.version = 0x110,
};

static int events[] = {
	EV_KEY, BTN_TOOL_FINGER,
	EV_KEY, BTN_TOUCH,
	EV_KEY, BTN_TOOL_DOUBLETAP,
	INPUT_PROP_MAX, INPUT_PROP_POINTER,
	-1, -1,
};

static const char udev_rule[] =
"ACTION==\"remove\", GOTO=\"rule_end\"\n"
"KERNEL!=\"event*\", GOTO=\"rule_end\"\n"
"\n"
"ATTRS{name}==\"litest Wacom Bamboo 2FG 4x5 Finger*\",\\\n"
"    ENV{LIBINPUT_DEVICE_GROUP}=\"wacom-bamboo-2fg-group\"\n"
"\n"
"LABEL=\"rule_end\"";

TEST_DEVICE("wacom-bamboo-2fg-finger",
	.type = LITEST_WACOM_BAMBOO_2FG_FINGER,
	.features = LITEST_TOUCHPAD,
	.interface = &interface,

	.name = "Wacom Bamboo 2F 4x5 Finger",
	.id = &input_id,
	.events = events,
	.absinfo = absinfo,
	.udev_rule = udev_rule,
)
