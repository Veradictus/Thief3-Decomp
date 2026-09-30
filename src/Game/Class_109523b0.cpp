// Game/Class_109523b0.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

struct Struct_109523b0_Field00 {
    char Unknown00[0x28c];
    unsigned char Field28c;
};

class Class_109523b0
{
public:
    Struct_109523b0_Field00* Field00;
    unsigned char FUN_109523b0();
};

// FUNCTION: 0x109523B0 ?FUN_109523b0@Class_109523b0@@QAEEXZ
unsigned char Class_109523b0::FUN_109523b0()
{
    return Field00->Field28c;
}
