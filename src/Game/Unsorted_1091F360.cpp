// Game/Unsorted_1091F360.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

class Class_1094D740
{
public:
    void FUN_1094d740(int A, int B, int C);
};

class Class_109243D0
{
public:
    void FUN_109243d0(int p1);

    char Unknown00[0x14];
    int Unknown14;
    char Unknown18[0x18];
    Class_1094D740 Unknown30;
};

class Class_10E49A0C
{
public:
    virtual void Virtual0();
    virtual void FUN_1091f360(int A, int B);
    virtual void Virtual2(int A, int B, int* C);
};

class IDirect3DBaseTexture8;

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
    virtual long __stdcall Virtual23();
    virtual long __stdcall Virtual24();
    virtual long __stdcall Virtual25();
    virtual long __stdcall Virtual26();
    virtual long __stdcall Virtual27();
    virtual long __stdcall Virtual28();
    virtual long __stdcall Virtual29();
    virtual long __stdcall Virtual30();
    virtual long __stdcall Virtual31();
    virtual long __stdcall Virtual32();
    virtual long __stdcall Virtual33();
    virtual long __stdcall Virtual34();
    virtual long __stdcall Virtual35();
    virtual long __stdcall Virtual36();
    virtual long __stdcall Virtual37();
    virtual long __stdcall Virtual38();
    virtual long __stdcall Virtual39();
    virtual long __stdcall Virtual40();
    virtual long __stdcall Virtual41();
    virtual long __stdcall Virtual42();
    virtual long __stdcall Virtual43();
    virtual long __stdcall Virtual44();
    virtual long __stdcall Virtual45();
    virtual long __stdcall Virtual46();
    virtual long __stdcall Virtual47();
    virtual long __stdcall Virtual48();
    virtual long __stdcall Virtual49();
    virtual long __stdcall Virtual50();
    virtual long __stdcall Virtual51();
    virtual long __stdcall Virtual52();
    virtual long __stdcall Virtual53();
    virtual long __stdcall Virtual54();
    virtual long __stdcall Virtual55();
    virtual long __stdcall Virtual56();
    virtual long __stdcall Virtual57();
    virtual long __stdcall Virtual58();
    virtual long __stdcall Virtual59();
    virtual long __stdcall Virtual60();
    virtual long __stdcall SetTexture(unsigned long Stage, IDirect3DBaseTexture8* Texture);
};

extern IDirect3DDevice8* GDirect3DDevice8;

class Class_109241E0
{
public:
    void FUN_109241e0(unsigned long Stage, IDirect3DBaseTexture8* Texture);

    char Unknown00[0x1C];
    IDirect3DBaseTexture8* Unknown1C[1];
};

struct Struct_10924210
{
    int Unknown00;
    int Unknown04;
    int Unknown08;
    int Unknown0C;
    int Unknown10;
    int Unknown14;
};

class Class_10936AC0
{
public:
    char Unknown00[0x7FC];
    Struct_10924210 Unknown7FC;
};

extern Class_10936AC0* DAT_10f31be0;

class Class_10924210
{
public:
    void FUN_10924210(const Struct_10924210& Value);

    char Unknown00[0x18];
    Struct_10924210 Unknown18;
};

// FUNCTION: 0x1091F360 ?FUN_1091f360@Class_10E49A0C@@UAEXHH@Z
void Class_10E49A0C::FUN_1091f360(int A, int B)
{
    Virtual2(A, B, &B);
}

// FUNCTION: 0x109241E0 ?FUN_109241e0@Class_109241E0@@QAEXKPAVIDirect3DBaseTexture8@@@Z
void Class_109241E0::FUN_109241e0(unsigned long Stage, IDirect3DBaseTexture8* Texture)
{
    if (Unknown1C[Stage] != Texture)
    {
        GDirect3DDevice8->SetTexture(Stage, Texture);
        Unknown1C[Stage] = Texture;
    }
}

// FUNCTION: 0x10924210 ?FUN_10924210@Class_10924210@@QAEXABUStruct_10924210@@@Z
void Class_10924210::FUN_10924210(const Struct_10924210& Value)
{
    Unknown18 = Value;
    DAT_10f31be0->Unknown7FC = Value;
}

// FUNCTION: 0x109243D0 ?FUN_109243d0@Class_109243D0@@QAEXH@Z
void Class_109243D0::FUN_109243d0(int p1)
{
    Unknown30.FUN_1094d740(Unknown14, p1, 0);
}
