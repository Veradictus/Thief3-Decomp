// Game/Unsorted_10933970.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

class IDirect3DVertexBuffer8;

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
    virtual long __stdcall Virtual20();
    virtual long __stdcall Virtual21();
    virtual long __stdcall Virtual22();
    virtual long __stdcall CreateVertexBuffer(unsigned int Length, unsigned long Usage, unsigned long FVF, int Pool, IDirect3DVertexBuffer8** ppVertexBuffer);
};

class Class_109343B0
{
public:
    void FUN_109343b0(IDirect3DVertexBuffer8** A);
};

class Class_10E49EB8
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
    virtual void FUN_10933f10(IDirect3DDevice8* Device);

    char Unknown04[0xC];
    unsigned int Unknown10;
    unsigned int Unknown14;
    char Unknown18[4];
    IDirect3DVertexBuffer8* Unknown1C;
    Class_109343B0 Unknown20;
};

// FUNCTION: 0x10933F10 ?FUN_10933f10@Class_10E49EB8@@UAEXPAVIDirect3DDevice8@@@Z
void Class_10E49EB8::FUN_10933f10(IDirect3DDevice8* Device)
{
    if (Unknown1C == 0)
    {
        Device->CreateVertexBuffer(Unknown10, 0x208, 0, (Unknown14 >> 1) & 1, &Unknown1C);
        Unknown20.FUN_109343b0(&Unknown1C);
    }
}
