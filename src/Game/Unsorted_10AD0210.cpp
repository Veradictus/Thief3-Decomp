// Game/Unsorted_10AD0210.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

class Class_1098E3D0
{
public:
    void FUN_1098e3d0(int A, void* B);
};

class Class_10AD0490
{
public:
    void FUN_10ad03f0(Class_1098E3D0* Obj);
    void FUN_10ad0490(Class_1098E3D0* Obj);
};

// FUNCTION: 0x10AD0490 ?FUN_10ad0490@Class_10AD0490@@QAEXPAVClass_1098E3D0@@@Z
void Class_10AD0490::FUN_10ad0490(Class_1098E3D0* Obj)
{
    int Value = 1;
    Obj->FUN_1098e3d0(0x800182, &Value);
    FUN_10ad03f0(Obj);
}
