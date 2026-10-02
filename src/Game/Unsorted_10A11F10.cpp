// Game/Unsorted_10A11F10.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

class Class_1098CFE0
{
public:
    void FUN_1098cfe0(void* A);
};

class Class_10B06220 : public Class_1098CFE0
{
public:
    int FUN_10b06220();
};

// FUNCTION: 0x10A11F10 ?FUN_10a11f10@@YGXPAVClass_10B06220@@@Z
void __stdcall FUN_10a11f10(Class_10B06220* Obj)
{
    if (Obj->FUN_10b06220() == 0)
        Obj->FUN_1098cfe0(0);
}
