// Game/Unsorted_10A35A70.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

class Class_10A359D0
{
public:
    int FUN_10a358b0();
    void FUN_10a35e50(int A);

    char Unknown00[0x1C];
    int Unknown1C;
    char Unknown20[8];
    int Unknown28;
    int Unknown2C;
    char Unknown30[4];
    int Unknown34;
    int Unknown38;
    int Unknown3C;
    char Unknown40[0x44];
    int Unknown84;
    int Unknown88;
};

// FUNCTION: 0x10A35E50 ?FUN_10a35e50@Class_10A359D0@@QAEXH@Z
void Class_10A359D0::FUN_10a35e50(int A)
{
    Unknown88 = A;
    int Value = FUN_10a358b0();
    if (Value > Unknown3C || Unknown34 == 0)
        Unknown3C = Value;
    Unknown84 = A;
    Value = FUN_10a358b0();
    if (Value > Unknown38 || Unknown2C == Unknown1C)
        Unknown38 = Value;
}
