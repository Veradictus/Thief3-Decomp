// Game/Unsorted_10C35990.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

class Class_10E9AD9C
{
public:
    virtual void Virtual0();
    virtual void Virtual1();
    virtual void Virtual2();
    virtual void Virtual3();
    virtual void Virtual4();
    virtual void Virtual5();
    virtual void Virtual6();
    virtual void Virtual7();
    virtual void FUN_10c365f0(int A, int B);

    char Unknown04[0x48];
    bool Unknown4C;
    char Unknown4D[0x1F];
    int Unknown6C;
    unsigned char Unknown70;
};

// FUNCTION: 0x10C365F0 ?FUN_10c365f0@Class_10E9AD9C@@UAEXHH@Z
void Class_10E9AD9C::FUN_10c365f0(int A, int B)
{
    if (Unknown70 == 1)
        return;
    if (Unknown6C == 0 || Unknown6C == A)
        Unknown4C = true;
}
