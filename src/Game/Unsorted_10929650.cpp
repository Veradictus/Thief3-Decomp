// Game/Unsorted_10929650.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

class IDirect3DTexture8;

class IDirect3DDevice8
{
public:
    virtual long __stdcall Virtual0();
    virtual long __stdcall Virtual1();
    virtual long __stdcall Virtual2();
    virtual long __stdcall Virtual3();
    virtual long __stdcall Virtual4();
    virtual long __stdcall Virtual5();
    virtual long __stdcall Virtual6();
    virtual long __stdcall Virtual7();
    virtual long __stdcall Virtual8();
    virtual long __stdcall Virtual9();
    virtual long __stdcall Virtual10();
    virtual long __stdcall Virtual11();
    virtual long __stdcall Virtual12();
    virtual long __stdcall Virtual13();
    virtual long __stdcall Virtual14();
    virtual long __stdcall Virtual15();
    virtual long __stdcall Virtual16();
    virtual long __stdcall Virtual17();
    virtual long __stdcall Virtual18();
    virtual long __stdcall Virtual19();
    virtual long __stdcall CreateTexture(unsigned int Width, unsigned int Height, unsigned int Levels, unsigned long Usage, int Format, int Pool, IDirect3DTexture8** ppTexture);
};

extern IDirect3DDevice8* GDirect3DDevice8;

struct Struct_10929600
{
    char Unknown00[0x18];
    unsigned int Width;
    unsigned int Height;
    char Unknown20[0x10];
    IDirect3DTexture8* Unknown30;
};

extern int DAT_10f31ad4;

extern Struct_10929600** DAT_10f31adc;

// FUNCTION: 0x10929650 ?FUN_10929650@@YAXXZ
void FUN_10929650()
{
    for (int i = 0; i < DAT_10f31ad4; i++)
    {
        Struct_10929600* Item = DAT_10f31adc[i];
        GDirect3DDevice8->CreateTexture(Item->Width, Item->Height, 1, 1, 0x15, 0, &Item->Unknown30);
    }
}
