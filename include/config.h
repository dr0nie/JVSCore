/**
 * Author: Bobby Dilley
 * Created: 2019
 * SPDX-FileCopyrightText: 2019 Bobby Dilley <bobby@dilley.uk>
 * SPDX-License-Identifier: GPL-3.0-or-later
 **/

#ifndef CONFIG_H_
#define CONFIG_H_

#define MAX_STRING_LENGTH 1024

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct
{
    char key[64];
    int value;
} StrIntPair;

typedef struct
{
    StrIntPair pairs[32];
} StrIntMap;

int get_value(StrIntMap *map, char *key);

/* Reserve spaces for coin buttons at the start of the mapping */
#define COIN_KEYS 5
#define SYSTEM_KEYS 8

typedef struct JVSConfig
{
    char devicePath[MAX_STRING_LENGTH];
    int analogueFuzz;
    int enableAnalogue;

    int playerOneKeys[16];
    int playerTwoKeys[16];
    int coinKeys[COIN_KEYS];
    int systemKeys[SYSTEM_KEYS];

} JVSConfig;

int parseConfig(char *filePath, JVSConfig *jvsConfig);

#endif // CONFIG_H_
