// Game/Unsorted_10C29EF0.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

extern void* DAT_10e9aa20[];

class Class_10E9AA20
{
public:
    Class_10E9AA20* FUN_10c2e350(int p1);

    void** VTable;
    int Unknown04;
};

extern void* DAT_10e9aa2c[];

class Class_10E9AA2C
{
public:
    Class_10E9AA2C* FUN_10c2e370(int p1);

    void** VTable;
    int Unknown04;
};

// FUNCTION: 0x10C2E350 ?FUN_10c2e350@Class_10E9AA20@@QAEPAV1@H@Z
Class_10E9AA20* Class_10E9AA20::FUN_10c2e350(int p1)
{
    VTable = DAT_10e9aa20;
    Unknown04 = p1;
    return this;
}

// FUNCTION: 0x10C2E370 ?FUN_10c2e370@Class_10E9AA2C@@QAEPAV1@H@Z
Class_10E9AA2C* Class_10E9AA2C::FUN_10c2e370(int p1)
{
    VTable = DAT_10e9aa2c;
    Unknown04 = p1;
    return this;
}
