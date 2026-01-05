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
                                      {"KEY_0", KEY_0},
                                      {"KEY_1", KEY_1},
                                      {"KEY_5", KEY_5}}};

int initInput(JVSConfig *config, JVSCapabilities *sentCapabilities, char *name, int analogueFuzz);
int closeInput();
int updateSwitches(JVSConfig *config, unsigned char *switches);
int updateAnalogues(int *analogues);
int sendUpdate();
int emitCoinPress(JVSConfig *config, unsigned char slot);

#endif // INPUT_H_
