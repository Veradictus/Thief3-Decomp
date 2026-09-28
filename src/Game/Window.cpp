// Game/Window.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

typedef unsigned long DWORD;

typedef int BOOL;

// A UI window (System/T3UI.ini); docs/engine.md, "UI windows".
class Window
{
public:
    virtual Window* GetParent();
    virtual BOOL HasFlag(DWORD Flag);
    virtual void SetFlag(DWORD Flag);
    virtual void ClearFlag(DWORD Flag);

    char Unknown04[0xB0];
    Window* Parent;          // +0xB4
    char UnknownB8[0x30];
    DWORD Flags;             // +0xE8: 0x800 ListenForMouseClicks, 0x1000 IsModal
};

// FUNCTION: 0x109E3820 ?HasFlag@Window@@UAEHK@Z
BOOL Window::HasFlag(DWORD Flag)
{
    return (Flags & Flag) != 0;
}

// FUNCTION: 0x109E3840 ?SetFlag@Window@@UAEXK@Z
void Window::SetFlag(DWORD Flag)
{
    Flags |= Flag;
}

// FUNCTION: 0x109E38E0 ?GetParent@Window@@UAEPAV1@XZ
Window* Window::GetParent()
{
    return Parent;
}
