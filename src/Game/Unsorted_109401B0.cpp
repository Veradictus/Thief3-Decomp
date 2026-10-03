// Game/Unsorted_109401B0.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

struct Struct_10941980
{
    short Unknown00;
    short Unknown02;
    short Unknown04;
};

class Class_1091A4F0
{
public:
    void FUN_1091a4f0(int NewCount);

    int Unknown00;
    int Unknown04;
    Struct_10941980* Unknown08;
};

class Class_109418E0
{
public:
    char Unknown00[6];
    char Unknown06;
    char Unknown07[0x25];
    Class_1091A4F0 Unknown2C;
    int Unknown38;
};

class Class_10941C40
{
public:
    void FUN_10941980(short A, short B, short C);

    char Unknown00[0x10];
    int Unknown10;
    char Unknown14[8];
    Class_109418E0* Unknown1C;
};

class Class_10941480
{
public:
    void FUN_10941480();

    char Unknown00[0x44];
};

class Class_10941570
{
public:
    void FUN_10941570();

    char Unknown00[4];
    int Unknown04;
    char Unknown08[4];
    Class_10941480* Unknown0C;
};

// A Direct3D matrix (D3DXMATRIX): four rows of four floats.
struct D3DXMATRIX
{
    float m[4][4];
};

// D3DX's inline identity (d3dx8math.inl).
inline D3DXMATRIX* D3DXMatrixIdentity(D3DXMATRIX* pOut)
{
    pOut->m[0][1] = pOut->m[0][2] = pOut->m[0][3] =
    pOut->m[1][0] = pOut->m[1][2] = pOut->m[1][3] =
    pOut->m[2][0] = pOut->m[2][1] = pOut->m[2][3] =
    pOut->m[3][0] = pOut->m[3][1] = pOut->m[3][2] = 0.0f;

    pOut->m[0][0] = pOut->m[1][1] = pOut->m[2][2] = pOut->m[3][3] = 1.0f;
    return pOut;
}

// D3DX's matrix product and transpose.
extern "C" D3DXMATRIX* __stdcall FUN_10d67f9a(D3DXMATRIX* pOut, const D3DXMATRIX* pM1, const D3DXMATRIX* pM2);

extern "C" D3DXMATRIX* __stdcall FUN_10d681e3(D3DXMATRIX* pOut, const D3DXMATRIX* pM);

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
    virtual long __stdcall Virtual61();
    virtual long __stdcall Virtual62();
    virtual long __stdcall Virtual63();
    virtual long __stdcall Virtual64();
    virtual long __stdcall Virtual65();
    virtual long __stdcall Virtual66();
    virtual long __stdcall Virtual67();
    virtual long __stdcall Virtual68();
    virtual long __stdcall Virtual69();
    virtual long __stdcall Virtual70();
    virtual long __stdcall Virtual71();
    virtual long __stdcall Virtual72();
    virtual long __stdcall Virtual73();
    virtual long __stdcall Virtual74();
    virtual long __stdcall Virtual75();
    virtual long __stdcall Virtual76();
    virtual long __stdcall Virtual77();
    virtual long __stdcall Virtual78();
    virtual long __stdcall SetVertexShaderConstant(unsigned long Register, const void* pConstantData, unsigned long ConstantCount);
};

extern IDirect3DDevice8* GDirect3DDevice8;

struct Struct_109401B0
{
    char Unknown00[0x144];
    D3DXMATRIX Unknown144;
    D3DXMATRIX Unknown184;
};

class Class_109401B0
{
public:
    void FUN_109401b0(Struct_109401B0* P, bool B);

    char Unknown00[0x310];
    D3DXMATRIX Unknown310;
};

// FUNCTION: 0x109401B0 ?FUN_109401b0@Class_109401B0@@QAEXPAUStruct_109401B0@@_N@Z
void Class_109401B0::FUN_109401b0(Struct_109401B0* P, bool B)
{
    D3DXMATRIX Product;
    D3DXMATRIX Matrix;
    D3DXMatrixIdentity(&Matrix);
    FUN_10d67f9a(&Product, &P->Unknown144, &P->Unknown184);
    FUN_10d67f9a(&Matrix, &Product, &Unknown310);
    FUN_10d681e3(&Matrix, &Matrix);
    if (B)
        GDirect3DDevice8->SetVertexShaderConstant(0x1d, &Matrix, 4);
    else
        GDirect3DDevice8->SetVertexShaderConstant(0x16, &Matrix, 4);
}

// FUNCTION: 0x10941570 ?FUN_10941570@Class_10941570@@QAEXXZ
void Class_10941570::FUN_10941570()
{
    for (int i = 0; i < Unknown04; i++)
        Unknown0C[i].FUN_10941480();
}

// FUNCTION: 0x10941980 ?FUN_10941980@Class_10941C40@@QAEXFFF@Z
void Class_10941C40::FUN_10941980(short A, short B, short C)
{
    Class_109418E0* Item = Unknown1C;
    Struct_10941980 Value;
    Value.Unknown00 = A;
    Value.Unknown02 = B;
    Value.Unknown04 = C;
    Class_1091A4F0* Array = &Item->Unknown2C;
    Item->Unknown06 = 0;
    int Index = Array->Unknown00;
    Array->FUN_1091a4f0(Index + 1);
    Array->Unknown08[Index] = Value;
}
