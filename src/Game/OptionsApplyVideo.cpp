// Game/OptionsApplyVideo.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

#include "Engine/EngineClasses.h"
#include "Game/Options.h"

class UViewport;

struct DisplayMode369 { int Width, Height, RefreshRate, Format; };

class Class_10C82440
{
public:
    virtual void Virtual0();
    virtual void Virtual1();
    virtual void Virtual2();
    virtual void Virtual3();
    virtual void Virtual4();
    virtual void Virtual5();
    virtual void Virtual6();
    virtual void Virtual7();
    virtual void Virtual8();
    virtual void Virtual9();
    virtual void Virtual10();
    virtual void Virtual11();
    virtual void Virtual12();
    virtual void Virtual13();
    virtual void Virtual14();
    virtual void Virtual15();
    virtual void Virtual16();
    virtual void Virtual17();
    virtual void Virtual18();
    virtual void Virtual19();
    virtual void Virtual20();
    virtual void Virtual21();
    virtual void Virtual22();
    virtual void Virtual23();
    virtual void Virtual24();
    virtual void Virtual25();
    virtual void Virtual26();
    virtual void Virtual27();
    virtual void Virtual28();
    virtual void Virtual29();
    virtual void Virtual30();
    virtual void Virtual31();
    virtual void Virtual32();
    virtual int Virtual33(UViewport* Viewport, int Width, int Height, int Fullscreen, int MultiSampling);
    int FUN_10c82440(int Fullscreen, int MultiSampling);
    int SupportsDisplayMode(int Width, int Height, int Depth);
    char Pad04[0x40D8];
    int VSync;
    char Pad40E0[0x520];
    DisplayMode369* Modes;
};

class UViewport
{
public:
    virtual void Virtual0();
    virtual void Virtual1();
    virtual void Virtual2();
    virtual void Virtual3();
    virtual void Virtual4();
    virtual void Virtual5();
    virtual void Virtual6();
    virtual void Virtual7();
    virtual void Virtual8();
    virtual void Virtual9();
    virtual void Virtual10();
    virtual void Virtual11();
    virtual void Virtual12();
    virtual void Virtual13();
    virtual void Virtual14();
    virtual void Virtual15();
    virtual void Virtual16();
    virtual void Virtual17();
    virtual void Virtual18();
    virtual void Virtual19();
    virtual void Virtual20();
    virtual void Virtual21();
    virtual void Virtual22();
    virtual void Virtual23();
    virtual void Virtual24();
    virtual void Virtual25();
    virtual void Virtual26();
    virtual void Virtual27();
    virtual void Virtual28();
    virtual void Virtual29();
    virtual void Virtual30();
    virtual void Virtual31();
    virtual void Virtual32();
    virtual void Virtual33();
    virtual void Virtual34();
    virtual int Virtual35();
    char Pad04[0x54];
    Class_10C82440* RenderDevice;
};

class UClient
{
public:
    char Pad00[0x30];
    UViewport** Viewports;
};

extern UEngine* GEngine;

// FUNCTION: 0x10AB61A0 ?ApplyVideo@Options@@QAEXXZ
void Options::ApplyVideo()
{
    int VSync = Values[9] != 0;
    int Resolution = Values[11];
    int Samples = Values[15];
    if (!GEngine || !GEngine->Client)
        return;
    UViewport* Viewport = GEngine->Client->Viewports[0];
    if (!Viewport)
        return;
    Class_10C82440* Device = Viewport->RenderDevice;
    if (!Device)
        return;
    if (Samples > 1 && !Device->FUN_10c82440(1, Samples))
    {
        bool Found = false;
        for (int Candidate = Samples - 1; Candidate > 0 && !Found; --Candidate)
        {
            if (Device->FUN_10c82440(1, Candidate) == 1)
            {
                Samples = Candidate;
                Found = true;
            }
        }
        if (!Found)
            Samples = 1;
        Values[15] = Samples;
    }
    Device->VSync = VSync;
    if (Resolution < 0)
        Resolution = 0;
    else if (Resolution >= 5)
        Resolution = 4;
    int Selected = Resolution;
    for (; Selected > 0; --Selected)
    {
        int Width = ResolutionWidths[Selected];
        int Height = ResolutionHeights[Selected];
        int Mode = Device->SupportsDisplayMode(Width, Height, 32);
        if (Mode >= 0 && Width == Device->Modes[Mode].Width && Height == Device->Modes[Mode].Height)
            break;
    }
    if (Selected < 0)
        Selected = 0;
    if (Resolution != Selected)
    {
        Resolution = Selected;
        Values[11] = Resolution;
    }
    if (Viewport->Virtual35())
        Viewport->RenderDevice->Virtual33(Viewport, ResolutionWidths[Resolution], ResolutionHeights[Resolution], 1, Samples);
}
