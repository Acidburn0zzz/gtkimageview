/* -*- Mode: C; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4; coding: utf-8 -*- 
 *
 * Copyright © 2007-2008 Björn Lindqvist <bjourne@gmail.com>
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public License
 * as published by the Free Software Foundation; either version 2, or
 * (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA
 * 02111-1307, USA.
 */
#include "cursors.h"

static const char void_data[] = { 0x00 };
static const char void_mask[] = { 0x00 };

static const char hand_open_data[] =
{
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x06, 0x00,
    0x60, 0x36, 0x00, 0x60, 0x36, 0x00, 0xc0, 0x36, 0x01, 0xc0, 0xb6, 0x01,
    0x80, 0xbf, 0x01, 0x98, 0xff, 0x01, 0xb8, 0xff, 0x00, 0xf0, 0xff, 0x00,
    0xe0, 0xff, 0x00, 0xe0, 0x7f, 0x00, 0xc0, 0x7f, 0x00, 0x80, 0x3f, 0x00,
    0x00, 0x3f, 0x00, 0x00, 0x3f, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};
static const char hand_open_mask[] =
{
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x06, 0x00, 0x60, 0x3f, 0x00,
   0xf0, 0x7f, 0x00, 0xf0, 0x7f, 0x01, 0xe0, 0xff, 0x03, 0xe0, 0xff, 0x03,
   0xd8, 0xff, 0x03, 0xfc, 0xff, 0x03, 0xfc, 0xff, 0x01, 0xf8, 0xff, 0x01,
   0xf0, 0xff, 0x01, 0xf0, 0xff, 0x00, 0xe0, 0xff, 0x00, 0xc0, 0x7f, 0x00,
   0x80, 0x7f, 0x00, 0x80, 0x7f, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};

static const char hand_closed_data[] =
{
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x06, 0x00, 0x80, 0x3f, 0x00,
   0x80, 0xff, 0x00, 0x80, 0xff, 0x00, 0xb0, 0xff, 0x00, 0xf0, 0xff, 0x00,
   0xe0, 0xff, 0x00, 0xe0, 0x7f, 0x00, 0xc0, 0x7f, 0x00, 0x80, 0x3f, 0x00,
   0x00, 0x3f, 0x00, 0x00, 0x3f, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};
static const char hand_closed_mask[] =
{
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x06, 0x00, 0x80, 0x3f,
    0x00, 0xc0, 0xff, 0x00, 0xc0, 0xff, 0x01, 0xf0, 0xff, 0x01,
    0xf8, 0xff, 0x01, 0xf8, 0xff, 0x01, 0xf0, 0xff, 0x01, 0xf0,
    0xff, 0x00, 0xe0, 0xff, 0x00, 0xc0, 0x7f, 0x00, 0x80, 0x7f,
    0x00, 0x80, 0x7f, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};

static struct
{
    const char *data;
    const char *mask;
    int   width;
    int   height;
} cursors[] =
{
    { void_data, void_mask, 1, 1 },
    { hand_open_data, hand_open_mask, 20, 20 },
    { hand_closed_data, hand_closed_mask, 20, 20 }
};

/**
 * cursor_get:
 * @type: A #CursorType.
 * @returns: A new cursor.
 *
 * Returns a new cursor showing the image specified in @type.
 **/
GdkCursor *
cursor_get (CursorType type)
{
    int width = cursors[type].width;
    int height = cursors[type].height;

    GdkBitmap *data = gdk_bitmap_create_from_data (NULL,
                                                   cursors[type].data,
                                                   width, height);
    GdkBitmap *mask = gdk_bitmap_create_from_data (NULL,
                                                   cursors[type].mask,
                                                   width, height);

    GdkColor black, white;
    gdk_color_parse ("#000000", &black);
    gdk_color_parse ("#ffffff", &white);

    GdkCursor *cursor = gdk_cursor_new_from_pixmap (data, mask,
                                                    &white, &black,
                                                    width / 2, height / 2);

    g_object_unref (data);
    g_object_unref (mask);

    return cursor;
}