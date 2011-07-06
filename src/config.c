/*
 * Copyright (c) 2010, 2011 Toni Spets <toni.spets@iki.fi>
 *
 * Permission to use, copy, modify, and distribute this software for any
 * purpose with or without fee is hereby granted, provided that the above
 * copyright notice and this permission notice appear in all copies.
 *
 * THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES
 * WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR
 * ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
 * WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN
 * ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF
 * OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
 */

#include "config.h"

#include <windows.h>
#include <stdio.h>

#define INI_NAME "carmanet.ini"

char        config_server[64] = "hifi.iki.fi";
uint16_t    config_server_port = 8055;

void config_init()
{
    char cwd[MAX_PATH];
    char ini_path[MAX_PATH];
    GetCurrentDirectoryA(sizeof(cwd), cwd);
    snprintf(ini_path, sizeof(ini_path), "%s\\%s", cwd, INI_NAME);

    if(GetFileAttributes(ini_path) == 0xFFFFFFFF)
    {
        FILE *fh = fopen(ini_path, "w");
        fprintf(fh,
            "[CarmaNet]\n"
            "; lobby server address\n"
            "Server=%s\n"
            "; lobby server port\n"
            "ServerPort=%d\n"
        , config_server, config_server_port);
        fclose(fh);
    }

    uint16_t itmp;
    GetPrivateProfileStringA("CarmaNet", "Server", config_server, config_server, sizeof(config_server), ini_path);

    itmp = GetPrivateProfileIntA("CarmaNet", "ServerPort", config_server_port, ini_path);
    if(itmp > 1024 && itmp < 65535)
    {
        config_server_port = (uint16_t)itmp;
    }
}
