// Game/Unsorted_10919190.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

class Class_10936AC0
{
public:
    void FUN_10936ac0(int A, int B);
    void FUN_10936b20(int A, int B);
};

extern Class_10936AC0* DAT_10f31be0;

// A Direct3D matrix (D3DXMATRIX): four rows of four floats.
struct D3DXMATRIX
{
    float m[4][4];
};

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
    virtual long __stdcall SetTransform(int State, const D3DXMATRIX* pMatrix);
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

class Class_1091E400
{
public:
    void* FUN_1091e400();
};

extern Class_1091E400* DAT_10f2c8c0;

struct Struct_10919190
{
    D3DXMATRIX Unknown00;
};

// FUNCTION: 0x10919190 ?FUN_10919190@@YAXPAUStruct_10919190@@@Z
void FUN_10919190(Struct_10919190* P)
{
    if (DAT_10f2c8c0)
    {
        D3DXMATRIX World = P->Unknown00;
        GDirect3DDevice8->SetTransform(0x100, &World);
        D3DXMATRIX Combined;
        FUN_10d67f9a(&Combined, &World, (D3DXMATRIX*)DAT_10f2c8c0->FUN_1091e400());
        FUN_10d681e3(&Combined, &Combined);
        GDirect3DDevice8->SetVertexShaderConstant(1, &Combined, 4);
        FUN_10d681e3(&World, &World);
        GDirect3DDevice8->SetVertexShaderConstant(0xc, &World, 4);
    }
}

// FUNCTION: 0x109192E0 ?FUN_109192e0@@YAXHHH@Z
void FUN_109192e0(int A, int B, int C)
{
    DAT_10f31be0->FUN_10936ac0(A, B);
    DAT_10f31be0->FUN_10936b20(C, 0);
}
