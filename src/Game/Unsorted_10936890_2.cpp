// Game/Unsorted_10936890_2.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

struct D3DVIEWPORT8
{
    unsigned long X;
    unsigned long Y;
    unsigned long Width;
    unsigned long Height;
    float MinZ;
    float MaxZ;
};

class IDirect3DDevice8
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
    virtual long __stdcall SetViewport(const D3DVIEWPORT8* Viewport);
};

extern IDirect3DDevice8* GDirect3DDevice8;

class Class_10936A40
{
public:
    void FUN_10936a40();

    char Unknown00[0x7FC];
    D3DVIEWPORT8 Viewport;
};

// FUNCTION: 0x10936A40 ?FUN_10936a40@Class_10936A40@@QAEXXZ
void Class_10936A40::FUN_10936a40()
{
    GDirect3DDevice8->SetViewport(&Viewport);
}
