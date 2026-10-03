// Game/Unsorted_1092C780.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

extern "C" __declspec(dllimport) void* __stdcall SetCursor(void* Cursor);

extern "C" __declspec(dllimport) int __stdcall ShowCursor(int Show);

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
    virtual int __stdcall ShowCursor(int Show);
};

extern IDirect3DDevice8* GDirect3DDevice8;

class Class_1092D3D0
{
public:
    void FUN_1092d3d0();

    char Unknown00[8];
    void* Unknown08;
    bool Unknown0C;
};

// FUNCTION: 0x1092D3D0 ?FUN_1092d3d0@Class_1092D3D0@@QAEXXZ
void Class_1092D3D0::FUN_1092d3d0()
{
    SetCursor(0);
    ShowCursor(0);
    if (GDirect3DDevice8 && Unknown08)
        GDirect3DDevice8->ShowCursor(0);
    Unknown0C = false;
}
