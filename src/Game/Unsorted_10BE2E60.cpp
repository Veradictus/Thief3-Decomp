// Game/Unsorted_10BE2E60.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

extern void* DAT_10e95d00;

class FVector
{
public:
    float X, Y, Z;
};

class Class_10E90D70
{
public:
    Class_10E90D70(int A, int B);

    void** Unknown00;
    int Unknown04[15];
};

class Class_10E95D00 : public Class_10E90D70
{
public:
    Class_10E95D00* FUN_10be2e60(int A, int B, const FVector& C, const FVector& D);

    bool Unknown40;
    FVector Unknown44;
    FVector Unknown50;
    int Unknown5C;
    int Unknown60;
};

// FUNCTION: 0x10BE2E60 ?FUN_10be2e60@Class_10E95D00@@QAEPAV1@HHABVFVector@@0@Z
Class_10E95D00* Class_10E95D00::FUN_10be2e60(int A, int B, const FVector& C, const FVector& D)
{
    this->Class_10E90D70::Class_10E90D70(A, B);
    Unknown00 = &DAT_10e95d00;
    Unknown40 = false;
    Unknown44 = C;
    Unknown50 = D;
    Unknown5C = 0;
    Unknown60 = 0;
    return this;
}
