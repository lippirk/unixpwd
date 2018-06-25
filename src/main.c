/*
 * Copyright (C) Citrix Systems Inc.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published
 * by the Free Software Foundation; version 2.1 only. with the special
 * exception on linking described in file LICENSE.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Lesser General Public License for more details.
 */

#include <errno.h>
#include <malloc.h>
#include <stdio.h>
#include <stdlib.h>

#include "unixpwd.h"

int
main(int argc, char **argv)
{
    int             rc;
    char           *pw;
    char           *buf;

    switch (argc) {
    case 1:
        buf = unixpwd_unshadow();
        if (buf) {
            puts(buf);
            free(buf);
        } else {
            fprintf(stderr, "can't unshadow\n");
        }
        break;

    case 2:
        pw = unixpwd_get(argv[1]);
        if (pw) {
            printf("%s: %s\n", argv[1], pw);
            free(pw);
            rc = 0;
        } else {
            fprintf(stderr, "can't find entry for %s\n", argv[1]);
            rc = 1;
        }
        break;

    case 3:
        rc = unixpwd_setpwd(argv[1], argv[2]);
        if (rc != 0) {
            fprintf(stderr, "error setting password: %d\n", rc);
            rc = 1;
            break;
        }
        rc = unixpwd_setspw(argv[1], argv[2]);
        if (rc != 0) {
            fprintf(stderr, "error setting shadow password: %d\n", rc);
            rc = 1;
            break;
        }
        break;

    default:
        fprintf(stderr, "usage: opasswd user [password]\n");
        rc = 1;
    }
    exit(rc);
}
