// Game/Unsorted_10936A60_3.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

class IDirect3DIndexBuffer8;

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
    virtual long __stdcall Virtual79();
    virtual long __stdcall Virtual80();
    virtual long __stdcall Virtual81();
    virtual long __stdcall Virtual82();
    virtual long __stdcall Virtual83();
    virtual long __stdcall Virtual84();
    virtual long __stdcall SetIndices(IDirect3DIndexBuffer8* IndexData, unsigned int BaseVertexIndex);
};

extern IDirect3DDevice8* GDirect3DDevice8;

class Class_10936AC0
{
public:
    void FUN_10936b20(int Indices, int BaseVertexIndex);

    char Unknown00[0x14];
    int Unknown14;
    int Unknown18;
};

// FUNCTION: 0x10936B20 ?FUN_10936b20@Class_10936AC0@@QAEXHH@Z
void Class_10936AC0::FUN_10936b20(int Indices, int BaseVertexIndex)
{
    if (Indices)
    {
        if (Indices != Unknown14 || BaseVertexIndex != Unknown18)
        {
            GDirect3DDevice8->SetIndices((IDirect3DIndexBuffer8*)Indices, BaseVertexIndex);
            Unknown14 = Indices;
            Unknown18 = BaseVertexIndex;
        }
    }
    else
    {
        Unknown14 = 0;
    }
}
