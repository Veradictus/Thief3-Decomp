// Game/Unsorted_10ABDF10.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

class Class_1098E330
{
public:
    virtual void Virtual0();
    int FUN_1098e330(int Id, int* Out);

    char Unknown04[0xF0];
    int UnknownF4;
};

// FUNCTION: 0x10ABDF10 ?FUN_10abdf10@@YA_NPAVClass_1098E330@@@Z
bool FUN_10abdf10(Class_1098E330* Obj)
{
    int Value = 0;
    if (!Obj->FUN_1098e330(0x800814, &Value))
        Value = Obj->UnknownF4 & 1;
    return Value == 1;
}
