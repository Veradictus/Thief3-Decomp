// Game/Unsorted_10A13A70.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

class InnerObject {
public:
    char Unknown00[0xb4];
    int UnknownB4;
};

extern int DAT_10f323fc;

class Class_Thiscall {
public:
    void FUN_1093dfa0();
};

// FUNCTION: 0x10A1E610 ?FUN_10a1e610@@YAHPAVInnerObject@@@Z
int FUN_10a1e610(InnerObject* obj)
{
    return obj->UnknownB4;
}

// FUNCTION: 0x10A1F940 ?FUN_10a1f940@@YAXXZ
void FUN_10a1f940()
{
    ((Class_Thiscall*)(long)DAT_10f323fc)->FUN_1093dfa0();
}
