// Game/Unsorted_10C47E70.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

class Class_10C662F0
{
public:
    bool FUN_10c662f0(int A, int B, int C);
};

Class_10C662F0* FUN_10c65090();

class Class_10E9BB4C
{
public:
    virtual void Virtual0();
    virtual void Virtual1();
    virtual void Virtual2();
    virtual bool FUN_10c47e70(int A, int B, int C);

    bool Unknown04;
};

// FUNCTION: 0x10C47E70 ?FUN_10c47e70@Class_10E9BB4C@@UAE_NHHH@Z
bool Class_10E9BB4C::FUN_10c47e70(int A, int B, int C)
{
    if (Unknown04)
        return FUN_10c65090()->FUN_10c662f0(A, B, C);
    return false;
}
