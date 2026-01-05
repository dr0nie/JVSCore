/**
 * Author: Bobby Dilley
 * Created: 2019
 * SPDX-FileCopyrightText: 2019 Bobby Dilley <bobby@dilley.uk>
 * 2022 Contributor and DE10-Nano tester: Javier Rodas (@JaviRodasG) <javier.rodas@gmail.com>
 * SPDX-License-Identifier: GPL-3.0-or-later
 **/

#include "config.h"

#define DEFAULT_DEVICE_PATH "/dev/ttyUSB0"
#define DEFAULT_ANALOGUE_FUZZ 2
#define DEFAULT_ENABLE_ANALOGUE 1

/**
 * Retrieves the value for a given key from the map
 *
 * @param map The map containing key-value pairs
 * @param key The key to search for
 * @return The value associated with the key, or -1 if not found
 */
int get_value(StrIntMap *map, char *key)
{
    for (size_t i = 0; i < sizeof(map->pairs) / sizeof(StrIntPair); i++)
    {
        if (strcmp(map->pairs[i].key, key) == 0)
        {
            return map->pairs[i].value;
        }
    }
    return -1; // Key not found
}

StrIntMap playerOneIndexMap = {.pairs = {
                                   {"PLAYER_ONE_START", 0},
                                   {"PLAYER_ONE_UP", 2},
                                   {"PLAYER_ONE_DOWN", 3},
                                   {"PLAYER_ONE_LEFT", 4},
                                   {"PLAYER_ONE_RIGHT", 5},

                                   {"PLAYER_ONE_SEGA_CENTER", 6},
                                   {"PLAYER_ONE_SEGA_TOP", 7},
                                   {"PLAYER_ONE_SEGA_BOTTOM", 8}}};
StrIntMap playerTwoIndexMap = {.pairs = {
                                   {"PLAYER_TWO_START", 0},
                                   {"PLAYER_TWO_UP", 2},
                                   {"PLAYER_TWO_DOWN", 3},
                                   {"PLAYER_TWO_LEFT", 4},
                                   {"PLAYER_TWO_RIGHT", 5},

                                   {"PLAYER_TWO_SEGA_CENTER", 6},
                                   {"PLAYER_TWO_SEGA_TOP", 7},
                                   {"PLAYER_TWO_SEGA_BOTTOM", 8}}};

#include <linux/input-event-codes.h>
StrIntMap keysLookUpMap = {.pairs = {
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
StrIntMap actionsMap = {.pairs = {
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

int parseConfig(char *filePath, JVSConfig *jvsConfig)
{
    // Setup default values
    jvsConfig->analogueFuzz = DEFAULT_ANALOGUE_FUZZ;
    jvsConfig->enableAnalogue = DEFAULT_ENABLE_ANALOGUE;
    strcpy(jvsConfig->devicePath, DEFAULT_DEVICE_PATH);

    FILE *fp;
    char buffer[1024];
    if ((fp = fopen(filePath, "r")) != NULL)
    {
        fgets(buffer, 1024, fp);
        while (!feof(fp))
        {
            if (buffer[0] != '#' && buffer[0] != 0 && strcmp(buffer, "") != 0)
            {
                char *token = strtok(buffer, " ");

                /* Grab the Device Path */
                if (strcmp(token, "DEVICE_PATH") == 0)
                {
                    token = strtok(NULL, " ");
                    if (token[strlen(token) - 1] == '\n')
                        token[strlen(token) - 1] = '\0';
                    strcpy(jvsConfig->devicePath, token);
                }

                /* Grab the Fuzz Settings */
                if (strcmp(token, "ANALOGUE_FUZZ") == 0)
                {
                    token = strtok(NULL, " ");
                    if (token[strlen(token) - 1] == '\n')
                        token[strlen(token) - 1] = '\0';
                    jvsConfig->analogueFuzz = atoi(token);
                }

                /* Grab the Enable Analogue Settings */
                if (strcmp(token, "ENABLE_ANALOGUE") == 0)
                {
                    token = strtok(NULL, " ");
                    if (token[strlen(token) - 1] == '\n')
                        token[strlen(token) - 1] = '\0';
                    jvsConfig->enableAnalogue = atoi(token);
                }

                char action[64] = {"\0"};
                strcpy(action, token);
                /* Grab the Action to Key Mappings */
                for (size_t i = 0; i < sizeof(actionsMap.pairs) / sizeof(StrIntPair); i++)
                {
                    if (strcmp(action, actionsMap.pairs[i].key) == 0)
                    {
                        printf("Mapping %s", action);
                        token = strtok(NULL, " ");
                        if (token[strlen(token) - 1] == '\n')
                        {
                            token[strlen(token) - 1] = '\0';
                            int keyValue = get_value(&keysLookUpMap, token);
                            if (keyValue != -1)
                            {
                                int found = get_value(&playerOneIndexMap, action);
                                if (found)
                                {
                                    printf(" to %s (%d)\n", token, keyValue);
                                    jvsConfig->playerOneKeys[found] = keyValue;
                                }
                                else
                                {
                                    printf(" to %s (%d)\n", token, keyValue);
                                    jvsConfig->coinKeys[0] = keyValue;
                                }
                            }
                            else
                                printf(" to unknown \"%s\" failed\n", token);
                        }
                    }
                }
            }
            fgets(buffer, 1024, fp);
        }
    }
    else
    {
        return 0;
    }
    fclose(fp);
    return 1;
}
