// Game/Unsorted_10BDF380_2.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

extern void* DAT_10e95170[];

class Class_10E90D70
{
public:
    Class_10E90D70(int A, int B);

    void** Unknown00;
    int Unknown04[15];
};

class Class_10E95170 : public Class_10E90D70
{
public:
    Class_10E95170* FUN_10bdf380(int A, int B);

    int Unknown40;
    int Unknown44;
};

// FUNCTION: 0x10BDF380 ?FUN_10bdf380@Class_10E95170@@QAEPAV1@HH@Z
Class_10E95170* Class_10E95170::FUN_10bdf380(int A, int B)
{
    this->Class_10E90D70::Class_10E90D70(A, B);
    Unknown40 = 0;
    Unknown44 = 0;
    Unknown00 = DAT_10e95170;
    return this;
}
