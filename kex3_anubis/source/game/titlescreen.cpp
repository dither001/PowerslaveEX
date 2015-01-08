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
// DESCRIPTION:
//      Title screen logic
//

#include "kexlib.h"
#include "renderMain.h"
#include "game.h"
#include "titlescreen.h"

typedef void(*menuItemSelect_t)(kexMenuItem*);

typedef enum
{
    TSI_NEWGAME     = 0,
    TSI_LOADGAME,
    TSI_OPTIONS,
    TSI_QUIT,
    TSI_GAMEPLAY,
    TSI_KEYBOARD,
    TSI_MOUSE,
    TSI_GAMEPAD,
    TSI_GRAPHICS,
    TSI_AUDIO,
    TSI_SFXVOLUME,
    TSI_MUSICVOLUME,
    TSI_EXIT_AUDIO,
    TSI_EXIT_OPTIONS,

    NUMTITLESCREENITEMS
} titleScreenItems_t;

typedef enum
{
    TSS_IDLE    = 0,
    TSS_NEWGAME,

    NUMTITLESCREENSTATES
} titleScreenState_t;

typedef struct
{
    kexMenuItem         item;
    menuItemSelect_t    callback;
} menuGroup_t;

static menuGroup_t *titleMenu[NUMTITLESCREENITEMS];

#define MENUITEM(name, label, x, y, center, lerpblock, block)   \
    static void LerpCallback_ ## name(kexMenuItem *item);   \
    static void Callback_ ## name(kexMenuItem *item);   \
    static menuGroup_t menuGroup_ ## name = { kexMenuItem(label, x, y, center, LerpCallback_ ## name), Callback_ ## name };   \
    static void LerpCallback_ ## name(kexMenuItem *item)    \
    lerpblock   \
    static void Callback_ ## name(kexMenuItem *item)    \
    block

//-----------------------------------------------------------------------------
//
// New Game
//
//-----------------------------------------------------------------------------

MENUITEM(NewGame, "New Game", -100, 128, 1,
{
    if(kex::cGame->TitleScreen()->SelectedItem() != TSI_NEWGAME)
    {
        return;
    }
    
    kex::cGame->TitleScreen()->FadeOut(TSS_NEWGAME);
},
{
    titleMenu[TSI_NEWGAME]->item.LerpTo(-100);
    titleMenu[TSI_LOADGAME]->item.LerpTo(420);
    titleMenu[TSI_OPTIONS]->item.LerpTo(-100);
    titleMenu[TSI_QUIT]->item.LerpTo(420);
});

//-----------------------------------------------------------------------------
//
// Load Game
//
//-----------------------------------------------------------------------------

MENUITEM(LoadGame, "Load Game", 420, 146, 1,
{
},
{
    kex::cGame->TitleScreen()->DeselectAllItems();
});

//-----------------------------------------------------------------------------
//
// Options
//
//-----------------------------------------------------------------------------

MENUITEM(Options, "Options", 420, 164, 1,
{
    if(kex::cGame->TitleScreen()->SelectedItem() != TSI_OPTIONS)
    {
        return;
    }
    
    titleMenu[TSI_GAMEPLAY]->item.LerpTo(160);
    titleMenu[TSI_KEYBOARD]->item.LerpTo(160);
    titleMenu[TSI_MOUSE]->item.LerpTo(160);
    titleMenu[TSI_GAMEPAD]->item.LerpTo(160);
    titleMenu[TSI_GRAPHICS]->item.LerpTo(160);
    titleMenu[TSI_AUDIO]->item.LerpTo(160);
    titleMenu[TSI_EXIT_OPTIONS]->item.LerpTo(160);
},
{
    titleMenu[TSI_NEWGAME]->item.LerpTo(-100);
    titleMenu[TSI_LOADGAME]->item.LerpTo(420);
    titleMenu[TSI_OPTIONS]->item.LerpTo(160, 64);
    titleMenu[TSI_OPTIONS]->item.Toggle(false);
    titleMenu[TSI_QUIT]->item.LerpTo(-100);
});

//-----------------------------------------------------------------------------
//
// Quit
//
//-----------------------------------------------------------------------------

MENUITEM(Quit, "Quit", 420, 182, 1,
{
},
{
    kex::cCommands->Execute("quit");
});

//-----------------------------------------------------------------------------
//
// Options: Gameplay
//
//-----------------------------------------------------------------------------

MENUITEM(Gameplay, "Gameplay", -100, 96, 1,
{
},
{
    kex::cGame->TitleScreen()->DeselectAllItems();
});

//-----------------------------------------------------------------------------
//
// Options: Keyboard
//
//-----------------------------------------------------------------------------

MENUITEM(Keyboard, "Keyboard", 420, 114, 1,
{
},
{
    kex::cGame->TitleScreen()->DeselectAllItems();
});

//-----------------------------------------------------------------------------
//
// Options: Mouse
//
//-----------------------------------------------------------------------------

MENUITEM(Mouse, "Mouse", -100, 132, 1,
{
},
{
    kex::cGame->TitleScreen()->DeselectAllItems();
});

//-----------------------------------------------------------------------------
//
// Options: Gamepad
//
//-----------------------------------------------------------------------------

MENUITEM(Gamepad, "Gamepad", 420, 150, 1,
{
},
{
    kex::cGame->TitleScreen()->DeselectAllItems();
});

//-----------------------------------------------------------------------------
//
// Options: Graphics
//
//-----------------------------------------------------------------------------

MENUITEM(Graphics, "Graphics", -100, 168, 1,
{
},
{
    kex::cGame->TitleScreen()->DeselectAllItems();
});

//-----------------------------------------------------------------------------
//
// Options: Audio
//
//-----------------------------------------------------------------------------

MENUITEM(Audio, "Audio", 420, 186, 1,
{
    if(kex::cGame->TitleScreen()->SelectedItem() != TSI_AUDIO)
    {
        return;
    }
    
    titleMenu[TSI_SFXVOLUME]->item.LerpTo(160);
    titleMenu[TSI_MUSICVOLUME]->item.LerpTo(160);
    titleMenu[TSI_EXIT_AUDIO]->item.LerpTo(160);
},
{
    titleMenu[TSI_OPTIONS]->item.LerpTo(-100, 64);
    titleMenu[TSI_GAMEPLAY]->item.LerpTo(-100);
    titleMenu[TSI_KEYBOARD]->item.LerpTo(420);
    titleMenu[TSI_MOUSE]->item.LerpTo(-100);
    titleMenu[TSI_GAMEPAD]->item.LerpTo(420);
    titleMenu[TSI_GRAPHICS]->item.LerpTo(-100);
    titleMenu[TSI_AUDIO]->item.LerpTo(160, 64);
    titleMenu[TSI_AUDIO]->item.Toggle(false);
    titleMenu[TSI_EXIT_OPTIONS]->item.LerpTo(-100);
});

//-----------------------------------------------------------------------------
//
// Options: Exit
//
//-----------------------------------------------------------------------------

MENUITEM(OptionExit, "Exit", -100, 204, 1,
{
    if(kex::cGame->TitleScreen()->SelectedItem() != TSI_EXIT_OPTIONS)
    {
        return;
    }
    
    titleMenu[TSI_NEWGAME]->item.LerpTo(160);
    titleMenu[TSI_LOADGAME]->item.LerpTo(160);
    titleMenu[TSI_OPTIONS]->item.LerpTo(160, 164);
    titleMenu[TSI_OPTIONS]->item.Toggle(true);
    titleMenu[TSI_QUIT]->item.LerpTo(160);
    kex::cGame->TitleScreen()->DeselectAllItems();
},
{
    titleMenu[TSI_GAMEPLAY]->item.LerpTo(-100);
    titleMenu[TSI_KEYBOARD]->item.LerpTo(420);
    titleMenu[TSI_MOUSE]->item.LerpTo(-100);
    titleMenu[TSI_GAMEPAD]->item.LerpTo(420);
    titleMenu[TSI_GRAPHICS]->item.LerpTo(-100);
    titleMenu[TSI_AUDIO]->item.LerpTo(420);
    titleMenu[TSI_EXIT_OPTIONS]->item.LerpTo(-100);
});

//-----------------------------------------------------------------------------
//
// Audio: SFX Volume
//
//-----------------------------------------------------------------------------

MENUITEM(SoundVolume, "Sound FX Volume", -100, 146, 1,
{
},
{
    kex::cGame->TitleScreen()->DeselectAllItems();
});

//-----------------------------------------------------------------------------
//
// Audio: Music Volume
//
//-----------------------------------------------------------------------------

MENUITEM(MusicVolume, "Music Volume", 420, 164, 1,
{
},
{
    kex::cGame->TitleScreen()->DeselectAllItems();
});

//-----------------------------------------------------------------------------
//
// Audio: Exit
//
//-----------------------------------------------------------------------------

MENUITEM(AudioExit, "Exit", 420, 182, 1,
{
    if(kex::cGame->TitleScreen()->SelectedItem() != TSI_EXIT_AUDIO)
    {
        return;
    }
    
    titleMenu[TSI_OPTIONS]->item.LerpTo(160, 64);
    titleMenu[TSI_GAMEPLAY]->item.LerpTo(160);
    titleMenu[TSI_KEYBOARD]->item.LerpTo(160);
    titleMenu[TSI_MOUSE]->item.LerpTo(160);
    titleMenu[TSI_GAMEPAD]->item.LerpTo(160);
    titleMenu[TSI_GRAPHICS]->item.LerpTo(160);
    titleMenu[TSI_AUDIO]->item.LerpTo(160, 186);
    titleMenu[TSI_AUDIO]->item.Toggle(true);
    titleMenu[TSI_EXIT_OPTIONS]->item.LerpTo(160);
    kex::cGame->TitleScreen()->DeselectAllItems();
},
{
    titleMenu[TSI_SFXVOLUME]->item.LerpTo(-100);
    titleMenu[TSI_MUSICVOLUME]->item.LerpTo(420);
    titleMenu[TSI_EXIT_AUDIO]->item.LerpTo(420);
});

//
// kexTitleScreen::kexTitleScreen
//

kexTitleScreen::kexTitleScreen(void)
{
    this->fadeTime = 0;
    this->curFadeTime = 0;
    this->bFadeIn = true;
    this->bFading = false;
    this->selectedItem = -1;
    
    titleMenu[TSI_NEWGAME] = &menuGroup_NewGame;
    titleMenu[TSI_LOADGAME] = &menuGroup_LoadGame;
    titleMenu[TSI_OPTIONS] = &menuGroup_Options;
    titleMenu[TSI_QUIT] = &menuGroup_Quit;
    titleMenu[TSI_GAMEPLAY] = &menuGroup_Gameplay;
    titleMenu[TSI_KEYBOARD] = &menuGroup_Keyboard;
    titleMenu[TSI_MOUSE] = &menuGroup_Mouse;
    titleMenu[TSI_GAMEPAD] = &menuGroup_Gamepad;
    titleMenu[TSI_GRAPHICS] = &menuGroup_Graphics;
    titleMenu[TSI_AUDIO] = &menuGroup_Audio;
    titleMenu[TSI_SFXVOLUME] = &menuGroup_SoundVolume;
    titleMenu[TSI_MUSICVOLUME] = &menuGroup_MusicVolume;
    titleMenu[TSI_EXIT_AUDIO] = &menuGroup_AudioExit;
    titleMenu[TSI_EXIT_OPTIONS] = &menuGroup_OptionExit;
}

//
// kexTitleScreen::~kexTitleScreen
//

kexTitleScreen::~kexTitleScreen(void)
{
}

//
// kexTitleScreen::Init
//

void kexTitleScreen::Init(void)
{
    titlePic = kexRender::cTextures->Cache("gfx/title.png", TC_CLAMP, TF_NEAREST);
    Start();
}

//
// kexTitleScreen::Start
//

void kexTitleScreen::Start(void)
{
    fadeTime = kex::cSession->GetTicks();
    state = TSS_IDLE;
    curFadeTime = 0;
    bFading = true;
    kex::cInput->ToggleMouseGrab(false);
}

//
// kexTitleScreen::Stop
//

void kexTitleScreen::Stop(void)
{
    kex::cInput->ToggleMouseGrab(true);
    kex::cSession->ToggleCursor(false);
}

//
// kexTitleScreen::FadeOut
//

void kexTitleScreen::FadeOut(int state)
{
    fadeTime = kex::cSession->GetTicks();
    this->state = state;
    curFadeTime = 0;
    bFading = true;
    bFadeIn = false;
}

//
// kexTitleScreen::DeselectAllItems
//

void kexTitleScreen::DeselectAllItems(void)
{
    for(unsigned int i = 0; i < ARRLEN(titleMenu); ++i)
    {
        kexMenuItem *item = &titleMenu[i]->item;
        item->Select(false);
    }
}

//
// kexTitleScreen::FadeDone
//

void kexTitleScreen::FadeDone(void)
{
    switch(state)
    {
    case TSS_IDLE:
        titleMenu[TSI_NEWGAME]->item.LerpTo(160);
        titleMenu[TSI_LOADGAME]->item.LerpTo(160);
        titleMenu[TSI_OPTIONS]->item.LerpTo(160);
        titleMenu[TSI_QUIT]->item.LerpTo(160);
        break;
    case TSS_NEWGAME:
        kex::cGame->SetGameState(GS_LEVEL);
        break;
    default:
        break;
    }
}

//
// kexTitleScreen::Draw
//

void kexTitleScreen::Draw(void)
{
    int fade;

    if(!bFading)
    {
        fade = 0xff;
    }
    else if(bFadeIn)
    {
        fade = curFadeTime;
        kexMath::Clamp(fade, 0, 255);

        if(fade >= 255)
        {
            bFading = false;
            FadeDone();
        }
    }
    else
    {
        fade = 255 - curFadeTime;
        kexMath::Clamp(fade, 0, 255);

        if(fade <= 0)
        {
            bFading = false;
            FadeDone();
        }
    }

    kexRender::cScreen->SetOrtho();
    kexRender::cScreen->DrawTexture(titlePic, 0, 0, fade, fade, fade, 0xff);

    for(unsigned int i = 0; i < ARRLEN(titleMenu); ++i)
    {
        kexMenuItem *item = &titleMenu[i]->item;
        item->Draw();
    }
}

//
// kexTitleScreen::Tick
//

void kexTitleScreen::Tick(void)
{
    if(bFading)
    {
        curFadeTime = ((kex::cSession->GetTicks() - fadeTime)) << 3;
    }
    else
    {
        for(unsigned int i = 0; i < ARRLEN(titleMenu); ++i)
        {
            kexMenuItem *item = &titleMenu[i]->item;
            item->Tick();
        }
    }
}

//
// kexTitleScreen::ProcessInput
//

bool kexTitleScreen::ProcessInput(inputEvent_t *ev)
{
    if(ev->type == ev_mousedown)
    {
        if(ev->data1 == KMSB_LEFT)
        {
            for(unsigned int i = 0; i < ARRLEN(titleMenu); ++i)
            {
                if(titleMenu[i]->item.IsHighlighted())
                {
                    if(titleMenu[i]->callback)
                    {
                        selectedItem = i;
                        titleMenu[i]->item.Select(true);
                        titleMenu[i]->callback(&titleMenu[i]->item);
                        return true;
                    }
                }
            }
        }
    }

    return false;
}