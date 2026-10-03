// Game/Unsorted_10A56B40.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

class FString
{
public:
    bool FUN_10af80a0(const FString& Other);
    FString& operator=(const FString& Other);

    void* Data;
    int ArrayNum;
    int ArrayMax;
};

class Class_10A626F0
{
public:
    void FUN_10a64d70();
    void FUN_10a56b40(const FString& Value);

    char Unknown00[0x158];
    FString Unknown158;
};

// FUNCTION: 0x10A56B40 ?FUN_10a56b40@Class_10A626F0@@QAEXABVFString@@@Z
void Class_10A626F0::FUN_10a56b40(const FString& Value)
{
    if (Unknown158.FUN_10af80a0(Value))
    {
        Unknown158 = Value;
        FUN_10a64d70();
    }
}
