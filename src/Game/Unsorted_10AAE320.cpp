// Game/Unsorted_10AAE320.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

class Class_10AAEBD0
{
public:
    void FUN_10aaebd0(int param);

    char Unknown00[0x814];
    int Unknown814;
    char Unknown818[4];
    int Unknown81c;
};

class Class_10AAEBF0
{
public:
    void FUN_10aaebf0(int param);

    char Unknown00[0x818];
    int Unknown818;
    int Unknown81c;
};

class Class_10AAF4D0
{
public:
    void FUN_10aaf320(int A);
    void FUN_10aae8b0();
    void FUN_10aaf4d0(int A);

    char Unknown00[0x812];
    bool Unknown812;
};

// FUNCTION: 0x10AAE320 ?FUN_10aae320@@YG_NH@Z
bool __stdcall FUN_10aae320(int A)
{
    if ((A >= 200 && A <= 215) || (A >= 240 && A <= 243))
        return true;
    return false;
}

// FUNCTION: 0x10AAEBD0 ?FUN_10aaebd0@Class_10AAEBD0@@QAEXH@Z
void Class_10AAEBD0::FUN_10aaebd0(int param)
{
    Unknown814 += Unknown81c * param;
}

// FUNCTION: 0x10AAEBF0 ?FUN_10aaebf0@Class_10AAEBF0@@QAEXH@Z
void Class_10AAEBF0::FUN_10aaebf0(int param)
{
    Unknown818 += Unknown81c * param;
}

// FUNCTION: 0x10AAF4D0 ?FUN_10aaf4d0@Class_10AAF4D0@@QAEXH@Z
void Class_10AAF4D0::FUN_10aaf4d0(int A)
{
    FUN_10aaf320(A);
    if (Unknown812)
        FUN_10aae8b0();
}
