// Game/Class_10E92730.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

extern void* DAT_10e92730[];

class Class_10E95288
{
public:
    Class_10E95288(int A, int B);

    void** Unknown00;
};

class Class_10E92730 : public Class_10E95288
{
public:
    Class_10E92730* FUN_10bccb00(int A, int B);
};

// FUNCTION: 0x10BCCB00 ?FUN_10bccb00@Class_10E92730@@QAEPAV1@HH@Z
Class_10E92730* Class_10E92730::FUN_10bccb00(int A, int B)
{
    this->Class_10E95288::Class_10E95288(A, B);
    Unknown00 = DAT_10e92730;
    return this;
}
