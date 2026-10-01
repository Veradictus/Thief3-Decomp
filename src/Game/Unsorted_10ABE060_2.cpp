// Game/Unsorted_10ABE060_2.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

class Class_1098E330
{
public:
    virtual void Virtual0();
    int FUN_1098e330(int Id, int* Out);

    char Unknown04[0xF4];
    int UnknownF8;
    int UnknownFC;
    char Unknown100[0x8];
    int Unknown108;
};

// FUNCTION: 0x10ABE060 ?FUN_10abe060@@YAHPAVClass_1098E330@@@Z
int FUN_10abe060(Class_1098E330* Obj)
{
    int Value = -1;
    if (!Obj->FUN_1098e330(0x200819, &Value))
        return Obj->Unknown108;
    return Value;
}
