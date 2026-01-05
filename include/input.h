/**
 * Author: Bobby Dilley
 * Created: 2019
 * SPDX-FileCopyrightText: 2019 Bobby Dilley <bobby@dilley.uk>
 * SPDX-License-Identifier: GPL-3.0-or-later
 **/

#ifndef INPUT_H_
#define INPUT_H_

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "jvs.h"

void initInputDefaultConfig(JVSConfig *config);
#include <linux/input-event-codes.h>
static StrIntMap keysLookUpMap = {.pairs = {
                                      {"KEY_UP", KEY_UP},
                                      {"KEY_DOWN", KEY_DOWN},
                                      {"KEY_LEFT", KEY_LEFT},
                                      {"KEY_RIGHT", KEY_RIGHT},
                                      {"KEY_LEFTALT", KEY_LEFTALT},
                                      {"KEY_LEFTCTRL", KEY_LEFTCTRL},
                                      {"KEY_ESC", KEY_ESC},
                                      {"KEY_ENTER", KEY_ENTER},
                                      {"KEY_SPACE", KEY_SPACE},
                                      {"KEY_U", KEY_U},
                                      {"KEY_I", KEY_I},
                                      {"KEY_Q", KEY_Q},
                                      {"KEY_W", KEY_W},
                                      {"KEY_E", KEY_E},
                                      {"KEY_R", KEY_R},
                                      {"KEY_F", KEY_F},
                                      {"KEY_Z", KEY_Z},
                                      {"KEY_Y", KEY_Y},
                                      {"KEY_T", KEY_T},
                                      {"KEY_X", KEY_X},
                                      {"KEY_C", KEY_C},
                                      {"KEY_V", KEY_V},
                                      {"KEY_B", KEY_B},
                                      {"KEY_N", KEY_N},
                                      {"KEY_M", KEY_M},
                                      {"KEY_I", KEY_I},
                                      {"KEY_K", KEY_K},
                                      {"KEY_J", KEY_J},
                                      {"KEY_L", KEY_L},
                                      {"KEY_A", KEY_A},
                                      {"KEY_S", KEY_S},
                                      {"KEY_D", KEY_D},
                                      {"KEY_0", KEY_0},
                                      {"KEY_1", KEY_1},
                                      {"KEY_2", KEY_2},
                                      {"KEY_3", KEY_3},
                                      {"KEY_4", KEY_4},
                                      {"KEY_5", KEY_5},
                                      {"KEY_6", KEY_6},
                                      {"KEY_7", KEY_7},
                                      {"KEY_8", KEY_8},
                                      {"KEY_8", KEY_8},
                                      {"KEY_9", KEY_9},
                                      {"KEY_F1", KEY_F1},
                                      {"KEY_F2", KEY_F2},
                                      {"KEY_F3", KEY_F3},
                                      {"KEY_F4", KEY_F4},
                                      {"KEY_F5", KEY_F5},
                                      {"KEY_F6", KEY_F6},
                                      {"KEY_F7", KEY_F7},
                                      {"KEY_F8", KEY_F8},
                                      {"KEY_F9", KEY_F9},
                                      {"KEY_F10", KEY_F10},
                                      {"KEY_F11", KEY_F11},
                                      {"KEY_F12", KEY_F12}}};

int initInput(JVSConfig *config, JVSCapabilities *sentCapabilities, char *name, int analogueFuzz);
int closeInput();
int updateSwitches(JVSConfig *config, unsigned char *switches);
int updateAnalogues(int *analogues);
int sendUpdate();
int emitCoinPress(JVSConfig *config, unsigned char slot);

#endif // INPUT_H_
