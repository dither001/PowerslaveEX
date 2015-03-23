//
// Copyright(C) 2014-2015 Samuel Villarreal
//
// This program is free software; you can redistribute it and/or
// modify it under the terms of the GNU General Public License
// as published by the Free Software Foundation; either version 2
// of the License, or (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//

#ifndef __ACTIONS_H__
#define __ACTIONS_H__

#include "keyboard.h"
#include "mouse.h"
#include "joystick.h"

#define MAX_KEYS    (NUMKEYBOARDKEYS + NUMMOUSEBUTTONS + NUMJOYSTICKBUTTONS)

typedef struct keyaction_s
{
    byte                keyid;
    kexStr              name;
} keyaction_t;

typedef struct cmdlist_s
{
    char                *command;
    keyaction_t         *action;
    struct cmdlist_s    *next;
} cmdlist_t;

typedef struct
{
    cmdlist_t           *cmds;
} keycmd_t;

class kexInputAction
{
public:
    void                    Clear(void);
    int                     FindAction(const char *name);
    void                    AddAction(byte id, const char *name);
    bool                    ActionExists(const char *name);
    void                    WriteBindings(FILE *file);
    void                    ExecuteCommand(int key, bool up, const int eventType);
    void                    ExecuteMouseCommand(int button, bool up);
    int                     GetKeyCode(char *key);
    char                    *GetKeyName(int key);
    void                    BindCommand(int key, const char *string);
    void                    ListBindings(void);
    
    const int               GetAction(const int id);
    keycmd_t                *KeyCommands(void) { return keycmds; }

private:
    keycmd_t                keycmds[MAX_KEYS];
    kexArray<keyaction_t>   keyActions;
    kexArray<int>           heldActions;
};

#endif
