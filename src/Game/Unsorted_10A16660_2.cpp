// Game/Unsorted_10A16660_2.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

struct Struct_10A16120
{
    int Unknown00;
    int Unknown04;
    int Unknown08;
    int Unknown0C;
};

class Class_10A16120
{
public:
    Struct_10A16120 FUN_10a16120(int A);
};

class Class_10E5D688
{
public:
    virtual int FUN_10a16660(int A);
    virtual void Virtual1();
    virtual bool Virtual2(int A);

    char Unknown04[0x2C];
    Class_10A16120 Unknown30;
};

// FUNCTION: 0x10A16660 ?FUN_10a16660@Class_10E5D688@@UAEHH@Z
int Class_10E5D688::FUN_10a16660(int A)
{
    if (!Virtual2(A))
        return 0;
    Struct_10A16120 Result;
    Result = Unknown30.FUN_10a16120(A);
    return Result.Unknown0C;
}
