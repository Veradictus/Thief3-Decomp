// Game/Unsorted_10BE2F50.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

extern void* DAT_10e95e18;

class Class_10E90D70
{
public:
    Class_10E90D70(int A, int B);

    void** Unknown00;
    int Unknown04[15];
};

class Class_10E95E18 : public Class_10E90D70
{
public:
    Class_10E95E18* FUN_10be2f50(int A, int B, int C, int D);

    int Unknown40;
    char Unknown44;
    int Unknown48;
};

// FUNCTION: 0x10BE2F50 ?FUN_10be2f50@Class_10E95E18@@QAEPAV1@HHHH@Z
Class_10E95E18* Class_10E95E18::FUN_10be2f50(int A, int B, int C, int D)
{
    this->Class_10E90D70::Class_10E90D70(A, B);
    Unknown00 = &DAT_10e95e18;
    Unknown40 = C;
    Unknown44 = 0;
    Unknown48 = D;
    return this;
}
