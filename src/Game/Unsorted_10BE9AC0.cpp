// Game/Unsorted_10BE9AC0.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

extern void* DAT_10e96fd0[];

class Class_10E90D70
{
public:
    Class_10E90D70(int A, int B);

    void** Unknown00;
    int Unknown04[15];
};

class Class_10E96FD0 : public Class_10E90D70
{
public:
    Class_10E96FD0* FUN_10be9b80(int A, int B, int C);

    int Unknown40;
};

// FUNCTION: 0x10BE9B80 ?FUN_10be9b80@Class_10E96FD0@@QAEPAV1@HHH@Z
Class_10E96FD0* Class_10E96FD0::FUN_10be9b80(int A, int B, int C)
{
    this->Class_10E90D70::Class_10E90D70(A, B);
    Unknown00 = DAT_10e96fd0;
    Unknown40 = C;
    return this;
}
