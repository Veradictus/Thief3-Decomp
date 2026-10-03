// Game/Unsorted_10917C90_3.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

// The viewport Direct3D takes: D3DVIEWPORT8.
struct Struct_10924210
{
    int X;
    int Y;
    int Width;
    int Height;
    float MinZ;
    float MaxZ;
};

typedef Struct_10924210 D3DVIEWPORT8;

class IDirect3DDevice8
{
public:
    virtual int __stdcall Virtual0();
    virtual int __stdcall Virtual1();
    virtual int __stdcall Virtual2();
    virtual int __stdcall Virtual3();
    virtual int __stdcall Virtual4();
    virtual int __stdcall Virtual5();
    virtual int __stdcall Virtual6();
    virtual int __stdcall Virtual7();
    virtual int __stdcall Virtual8();
    virtual int __stdcall Virtual9();
    virtual int __stdcall Virtual10();
    virtual int __stdcall Virtual11();
    virtual int __stdcall Virtual12();
    virtual int __stdcall Virtual13();
    virtual int __stdcall Virtual14();
    virtual int __stdcall Virtual15();
    virtual int __stdcall Virtual16();
    virtual int __stdcall Virtual17();
    virtual int __stdcall Virtual18();
    virtual int __stdcall Virtual19();
    virtual int __stdcall Virtual20();
    virtual int __stdcall Virtual21();
    virtual int __stdcall Virtual22();
    virtual int __stdcall Virtual23();
    virtual int __stdcall Virtual24();
    virtual int __stdcall Virtual25();
    virtual int __stdcall Virtual26();
    virtual int __stdcall Virtual27();
    virtual int __stdcall Virtual28();
    virtual int __stdcall Virtual29();
    virtual int __stdcall Virtual30();
    virtual int __stdcall Virtual31();
    virtual int __stdcall Virtual32();
    virtual int __stdcall Virtual33();
    virtual int __stdcall Virtual34();
    virtual int __stdcall Virtual35();
    virtual int __stdcall Virtual36();
    virtual int __stdcall Virtual37();
    virtual int __stdcall Virtual38();
    virtual int __stdcall Virtual39();
    virtual int __stdcall SetViewport(const D3DVIEWPORT8* pViewport);
};

class Class_10924210
{
public:
    void FUN_10924210(const Struct_10924210& A);
};

class Class_109242E0 : public Class_10924210
{
};

extern IDirect3DDevice8* GDirect3DDevice8;

extern Class_109242E0* DAT_10f319a0;

extern Struct_10924210 DAT_10f2c780;

// FUNCTION: 0x10917C90 ?FUN_10917c90@@YAXHHHH@Z
void FUN_10917c90(int A, int B, int C, int D)
{
    Struct_10924210 Viewport;
    Viewport.X = A;
    Viewport.Y = B;
    Viewport.Width = C;
    Viewport.Height = D;
    Viewport.MinZ = 0.0f;
    Viewport.MaxZ = 1.0f;
    GDirect3DDevice8->SetViewport(&Viewport);
    DAT_10f2c780 = Viewport;
    DAT_10f319a0->FUN_10924210(Viewport);
}
