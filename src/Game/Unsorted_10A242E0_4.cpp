// Game/Unsorted_10A242E0_4.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

class Class_10D3F460
{
public:
    void FUN_10d3f460(unsigned char A);
};

struct Static_10A35EA0 : public Class_10D3F460
{
    char Unknown0C;
};

Static_10A35EA0* FUN_10a35ea0();

class Class_10A24320
{
public:
    void FUN_10a24320(unsigned char A);

    char Unknown00[0x54];
    unsigned char Unknown54;
};

// FUNCTION: 0x10A24320 ?FUN_10a24320@Class_10A24320@@QAEXE@Z
void Class_10A24320::FUN_10a24320(unsigned char A)
{
    FUN_10a35ea0()->FUN_10d3f460(A);
    Unknown54 = A;
}
