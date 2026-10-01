// Game/Unsorted_10BCE920.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

extern void* DAT_10e92a00[];

class Class_10E90D70
{
public:
    Class_10E90D70(int A, int B);

    void** Unknown00;
    int Unknown04[15];
};

class Class_10E92A00 : public Class_10E90D70
{
public:
    Class_10E92A00* FUN_10bce920(int A, int B, int C);

    double Unknown40;
    double Unknown48;
    int Unknown50;
};

// FUNCTION: 0x10BCE920 ?FUN_10bce920@Class_10E92A00@@QAEPAV1@HHH@Z
Class_10E92A00* Class_10E92A00::FUN_10bce920(int A, int B, int C)
{
    this->Class_10E90D70::Class_10E90D70(A, B);
    Unknown40 = -1.0;
    Unknown00 = DAT_10e92a00;
    Unknown48 = -1.0;
    Unknown50 = C;
    return this;
}
