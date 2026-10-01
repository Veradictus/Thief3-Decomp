// Game/Unsorted_10ABE0A0.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

class Class_1098E330
{
public:
    int FUN_1098e330(int Id, int* Out);
};

// FUNCTION: 0x10ABE0D0 ?FUN_10abe0d0@@YAHPAVClass_1098E330@@@Z
int FUN_10abe0d0(Class_1098E330* Obj)
{
    int Value = -1;
    if (!Obj->FUN_1098e330(0x200826, &Value))
        return -1;
    return Value;
}
