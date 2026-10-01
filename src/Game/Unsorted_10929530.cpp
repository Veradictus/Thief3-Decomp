// Game/Unsorted_10929530.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

struct Struct_10929510
{
    int Pitch;
    unsigned char* Bits;
};

class Class_10E49AE0
{
public:
    virtual void Virtual0();
    virtual void FUN_10929530(Struct_10929510* p1, int p2, int p3, int p4);
};

// FUNCTION: 0x10929530 ?FUN_10929530@Class_10E49AE0@@UAEXPAUStruct_10929510@@HHH@Z
void Class_10E49AE0::FUN_10929530(Struct_10929510* p1, int p2, int p3, int p4)
{
    ((int*)(p1->Bits + p1->Pitch * p3))[p2] = p4;
}
