// Game/Unsorted_10A4C200.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

struct Struct_10A4C470_Inner
{
    char Unknown00[0xE8];
    int UnknownE8;
};

struct Struct_10A4C470_Object
{
    char Unknown00[0x24];
    Struct_10A4C470_Inner* Unknown24;
};

class Class_10E67938
{
public:
    virtual void FUN_10a4c470(int Type, int A, int B, int C);
    virtual void Virtual1();
    virtual void Virtual2();
    virtual void Virtual3();
    virtual void Virtual4();
    virtual void Virtual5();
    virtual void Virtual6();
    virtual void Virtual7();
    virtual void Virtual8(int A, int B, int C);
};

// FUNCTION: 0x10A4C470 ?FUN_10a4c470@Class_10E67938@@UAEXHHHH@Z
void Class_10E67938::FUN_10a4c470(int Type, int A, int B, int C)
{
    if (A != ((Struct_10A4C470_Object*)A)->Unknown24->UnknownE8)
    {
        switch (Type)
        {
        case 1:
            Virtual8(A, B, C);
            break;
        }
    }
}
