// Game/Unsorted_10B4FF40.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

struct Struct_10B53A00
{
    char Unknown00[0x450];
    int Unknown450;
};

class Class_10E816E0
{
public:
    virtual void Virtual0();
    virtual void Virtual1();
    virtual void Virtual2();
    virtual void Virtual3();
    virtual void Virtual4();
    virtual int FUN_10b53a00(Struct_10B53A00* P, int Code);

    void FUN_10b3b260(Struct_10B53A00* P);
};

// FUNCTION: 0x10B53A00 ?FUN_10b53a00@Class_10E816E0@@UAEHPAUStruct_10B53A00@@H@Z
int Class_10E816E0::FUN_10b53a00(Struct_10B53A00* P, int Code)
{
    if (Code == 0x52)
    {
        if (P->Unknown450 & 0x20)
        {
            P->Unknown450 &= ~0x20;
            FUN_10b3b260(P);
        }
    }
    return 2;
}
