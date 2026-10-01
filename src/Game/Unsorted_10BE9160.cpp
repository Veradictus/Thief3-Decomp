// Game/Unsorted_10BE9160.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

extern void* DAT_10e96eb0[];

class Class_10E90D70
{
public:
    Class_10E90D70(int A, int B);

    void** Unknown00;
    int Unknown04[15];
};

class Class_10E96EB0 : public Class_10E90D70
{
public:
    Class_10E96EB0* FUN_10be9160(int A, int B, int C, int D);

    int Unknown40;
    int Unknown44;
    int Unknown48;
};

// FUNCTION: 0x10BE9160 ?FUN_10be9160@Class_10E96EB0@@QAEPAV1@HHHH@Z
Class_10E96EB0* Class_10E96EB0::FUN_10be9160(int A, int B, int C, int D)
{
    this->Class_10E90D70::Class_10E90D70(A, B);
    Unknown00 = DAT_10e96eb0;
    Unknown40 = C;
    Unknown44 = 0;
    Unknown48 = D;
    return this;
}
