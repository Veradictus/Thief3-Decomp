// Game/Unsorted_10AC98C0.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

class Class_10AC99D0
{
public:
    int FUN_10ac99d0(int Index);

    char Unknown00[4];
    int Unknown04;
    char Unknown08[4];
    int* Unknown0C;
};

class Class_10AC98B0
{
public:
    void FUN_10ac9620(int A);
    void FUN_10ac9840();
    void FUN_10ac98c0(int A);

    char Unknown00[0x4];
    bool Unknown04;
    bool Unknown05;
};

// FUNCTION: 0x10AC98C0 ?FUN_10ac98c0@Class_10AC98B0@@QAEXH@Z
void Class_10AC98B0::FUN_10ac98c0(int A)
{
    if (Unknown05)
        FUN_10ac9620(A);
    else if (Unknown04)
        FUN_10ac9840();
}

// FUNCTION: 0x10AC99D0 ?FUN_10ac99d0@Class_10AC99D0@@QAEHH@Z
int Class_10AC99D0::FUN_10ac99d0(int Index)
{
    if (Index + 1 < Unknown04)
        return Unknown0C[Index + 1];
    return 0;
}
