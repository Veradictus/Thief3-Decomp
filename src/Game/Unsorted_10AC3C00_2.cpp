// Game/Unsorted_10AC3C00_2.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

struct Struct_10AC3C10
{
    int Unknown00;
    int Unknown04;
    int Unknown08;

    Struct_10AC3C10 operator-(const Struct_10AC3C10& Other) const
    {
        Struct_10AC3C10 Result;
        Result.Unknown00 = Unknown00 - Other.Unknown00;
        Result.Unknown04 = Unknown04 - Other.Unknown04;
        Result.Unknown08 = Unknown08 - Other.Unknown08;
        return Result;
    }
};

class Class_10AC3C10
{
public:
    void FUN_10ac3c10(const Struct_10AC3C10& Value);

    char Unknown00[0x10];
    Struct_10AC3C10 Unknown10;
    Struct_10AC3C10 Unknown1C;
    Struct_10AC3C10 Unknown28;
};

// FUNCTION: 0x10AC3C10 ?FUN_10ac3c10@Class_10AC3C10@@QAEXABUStruct_10AC3C10@@@Z
void Class_10AC3C10::FUN_10ac3c10(const Struct_10AC3C10& Value)
{
    Unknown1C = Value;
    Unknown28 = Unknown1C - Unknown10;
}
