// Game/Window_2.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

typedef unsigned long DWORD;

typedef int BOOL;

// A UI window (System/T3UI.ini); docs/engine.md, "UI windows".
class Window
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
    virtual void Virtual35();
    virtual void Virtual36();
    virtual void Virtual37();
    virtual void Virtual38();
    virtual void Virtual39();
    virtual void Virtual40();
    virtual Window* GetParent();
    virtual void Virtual42();
    virtual void Virtual43();
    virtual void Virtual44();
    virtual void Virtual45();
    virtual void Virtual46();
    virtual void Virtual47();
    virtual void Virtual48();
    virtual void Virtual49();
    virtual void Virtual50();
    virtual void Virtual51();
    virtual void Virtual52();
    virtual void Virtual53();
    virtual void Virtual54();
    virtual void Virtual55();
    virtual void Virtual56();
    virtual void Virtual57();
    virtual void Virtual58();
    virtual void Virtual59();
    virtual BOOL FUN_109e3810();
    virtual void Virtual61();
    virtual void Virtual62();
    virtual void Virtual63();
    virtual BOOL HasFlag(DWORD Flag);
    virtual void SetFlag(DWORD Flag);
    virtual void ClearFlag(DWORD Flag);

    char Unknown04[0xB0];
    Window* Parent;          // +0xB4
    char UnknownB8[0x30];
    DWORD Flags;             // +0xE8: 0x800 ListenForMouseClicks, 0x1000 IsModal
};

// FUNCTION: 0x109E3810 ?FUN_109e3810@Window@@UAEHXZ
BOOL Window::FUN_109e3810()
{
    return HasFlag(0x800);
}
