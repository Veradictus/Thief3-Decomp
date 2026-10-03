// Game/Unsorted_10ABB5C0.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

struct Struct_10ABB300
{
    char Unknown00[0x10];
    bool Unknown10;
    char Unknown11[3];
};

class Class_10ABB300
{
public:
    virtual void Virtual0();

    void FUN_10abb300(Struct_10ABB300* P);
};

class Class_10E6F47C : public Class_10ABB300
{
public:
    virtual void Virtual1();
    virtual void Virtual2();
    virtual void Virtual3();
    virtual int Virtual4(int A);
    virtual bool FUN_10abb5c0(int A);

    char Unknown04[0x18];
    Struct_10ABB300* Unknown1C;
};

// FUNCTION: 0x10ABB5C0 ?FUN_10abb5c0@Class_10E6F47C@@UAE_NH@Z
bool Class_10E6F47C::FUN_10abb5c0(int A)
{
    int Index = Virtual4(A);
    if (Index >= 0 && Unknown1C[Index].Unknown10)
    {
        FUN_10abb300(&Unknown1C[Index]);
        return true;
    }
    return false;
}
