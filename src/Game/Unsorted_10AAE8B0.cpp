// Game/Unsorted_10AAE8B0.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

class Class_10AAEB70
{
public:
    bool FUN_10aaeb70(int A, float* Out);
    unsigned char FUN_10aae350(int A);
};

// FUNCTION: 0x10AAEB70 ?FUN_10aaeb70@Class_10AAEB70@@QAE_NHPAM@Z
bool Class_10AAEB70::FUN_10aaeb70(int A, float* Out)
{
    if ((A >= 200 && A <= 215) || (A >= 240 && A <= 243))
    {
        *Out = FUN_10aae350(A) * 0.003921569f;
        return true;
    }
    *Out = 0.0f;
    return false;
}
