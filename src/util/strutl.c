/*
 * This file is part of libbdplus
 * Copyright (C) 2008-2010  Accident
 * Copyright (C) 2013       VideoLAN
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library. If not, see
 * <http://www.gnu.org/licenses/>.
 */

#if HAVE_CONFIG_H
#include "config.h"
#endif

#include "strutl.h"

#include "macro.h"

#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>
#include <string.h>

char *str_dup(const char *str)
{
    return str ? strcpy (malloc(strlen(str) + 1), str) : NULL;
}

char *str_printf(const char *fmt, ...)
{
    /* Guess we need no more than 100 bytes. */
    va_list ap;
    int     len;
    int     size = 100;
    char   *tmp, *str = NULL;

    while (1) {

        tmp = realloc(str, size);
        if (tmp == NULL) {
            X_FREE(str);
            return NULL;
        }
        str = tmp;

        /* Try to print in the allocated space. */
        va_start(ap, fmt);
        len = vsnprintf(str, size, fmt, ap);
        va_end(ap);

        /* If that worked, return the string. */
        if (len > -1 && len < size) {
            return str;
        }

        /* Else try again with more space. */
        if (len > -1)    /* glibc 2.1 */
            size = len+1; /* precisely what is needed */
        else           /* glibc 2.0 */
            size *= 2;  /* twice the old size */
    }
}

const char *str_next_line(const char *p)
{
    while (*p && *p != '\r' && *p != '\n') {
        p++;
    }
    while (*p && (*p == '\r' || *p == '\n' || *p == ' ')) {
        p++;
    }

    return p;
}

const char *str_skip_white(const char *p)
{
    while (*p && (*p == ' ' || *p == '\r' || *p == '\n' || *p == '\t')) {
        p++;
    }

    return p;
}

char *str_print_hex(char *out, const uint8_t *buf, int count)
{
    int zz;
    for (zz = 0; zz < count; zz++) {
        sprintf(out + (zz * 2), "%02x", buf[zz]);
    }

    return out;
}
