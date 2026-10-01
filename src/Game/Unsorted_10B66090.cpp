// Game/Unsorted_10B66090.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

extern void* DAT_10e84d80[];

class Class_10B78780
{
public:
    void FUN_10b78780();

    void** Unknown00;
};

class Class_10E84D80 : public Class_10B78780
{
public:
    Class_10E84D80* FUN_10b67180();
};

// FUNCTION: 0x10B67180 ?FUN_10b67180@Class_10E84D80@@QAEPAV1@XZ
Class_10E84D80* Class_10E84D80::FUN_10b67180()
{
    FUN_10b78780();
    Unknown00 = DAT_10e84d80;
    return this;
}
