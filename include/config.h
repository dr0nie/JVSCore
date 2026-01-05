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

static StrIntMap playerOneIndexMap = {.pairs = {
                                          {"PLAYER_ONE_START", 0},
                                          {"PLAYER_ONE_UP", 2},
                                          {"PLAYER_ONE_DOWN", 3},
                                          {"PLAYER_ONE_LEFT", 4},
                                          {"PLAYER_ONE_RIGHT", 5},

                                          {"PLAYER_ONE_SEGA_CENTER", 6},
                                          {"PLAYER_ONE_SEGA_TOP", 7},
                                          {"PLAYER_ONE_SEGA_BOTTOM", 8}}};
static StrIntMap playerTwoIndexMap = {.pairs = {
                                          {"PLAYER_TWO_START", 0},
                                          {"PLAYER_TWO_UP", 2},
                                          {"PLAYER_TWO_DOWN", 3},
                                          {"PLAYER_TWO_LEFT", 4},
                                          {"PLAYER_TWO_RIGHT", 5},

                                          {"PLAYER_TWO_SEGA_CENTER", 6},
                                          {"PLAYER_TWO_SEGA_TOP", 7},
                                          {"PLAYER_TWO_SEGA_BOTTOM", 8}}};

#include <linux/input-event-codes.h>
static StrIntMap actionsMap = {.pairs = {
                                   {"PLAYER_ONE_START", KEY_1},
                                   {"PLAYER_ONE_UP", KEY_UP},
                                   {"PLAYER_ONE_DOWN", KEY_DOWN},
                                   {"PLAYER_ONE_LEFT", KEY_LEFT},
                                   {"PLAYER_ONE_RIGHT", KEY_RIGHT},
                                   {"PLAYER_ONE_SEGA_CENTER", KEY_LEFTCTRL},
                                   {"PLAYER_ONE_SEGA_BOTTOM", KEY_LEFTALT},
                                   {"PLAYER_ONE_SEGA_TOP", KEY_SPACE},
                                   {"PLAYER_TWO_START", KEY_2},
                                   {"PLAYER_TWO_UP", KEY_W},
                                   {"PLAYER_TWO_DOWN", KEY_S},
                                   {"PLAYER_TWO_LEFT", KEY_A},
                                   {"PLAYER_TWO_RIGHT", KEY_D},
                                   {"INSERT_COIN", KEY_5},
                                   {"TEST", KEY_6},
                                   {"SERVICE", KEY_7}}};
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
