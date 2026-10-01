// Game/Unsorted_10ABB300.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

struct Struct_10ABB4B0
{
    char Unknown00[0x14];
};

class Class_10E6F47C
{
public:
    virtual void Virtual0();
    virtual void Virtual1();
    virtual void Virtual2();
    virtual void Virtual3();
    virtual int Virtual4(int A);
    virtual void Virtual5();
    virtual Struct_10ABB4B0* FUN_10abb4b0(int A);

    char Unknown04[0x18];
    Struct_10ABB4B0* Unknown1C;
};

// FUNCTION: 0x10ABB4B0 ?FUN_10abb4b0@Class_10E6F47C@@UAEPAUStruct_10ABB4B0@@H@Z
Struct_10ABB4B0* Class_10E6F47C::FUN_10abb4b0(int A)
{
    int Index = Virtual4(A);
    if (Index == -1)
        return 0;
    return Unknown1C + Index;
}
