// Game/Unsorted_10938F10.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

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
    virtual long __stdcall SetRenderState(int State, unsigned long Value);
};

extern IDirect3DDevice8* GDirect3DDevice8;

void __stdcall FUN_10938f10(int Mode);

struct Struct_10938F80
{
    int Unknown00;
    char Unknown04;
    bool Unknown05;
    bool Unknown06;
    char Unknown07;
    int Unknown08;
};

// FUNCTION: 0x10938F80 ?FUN_10938f80@@YGXPAUStruct_10938F80@@@Z
void __stdcall FUN_10938f80(Struct_10938F80* P)
{
    FUN_10938f10(P->Unknown00);
    GDirect3DDevice8->SetRenderState(7, P->Unknown05);
    if (P->Unknown05)
    {
        GDirect3DDevice8->SetRenderState(14, P->Unknown06);
        GDirect3DDevice8->SetRenderState(23, P->Unknown08);
    }
}
