// Game/Unsorted_10BED060.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

extern void* DAT_10e97258[];

class Class_10E90D70
{
public:
    Class_10E90D70(int A, int B);

    void** Unknown00;
    int Unknown04[15];
};

class Class_10E97258 : public Class_10E90D70
{
public:
    Class_10E97258* FUN_10bed080(int A, int B, int C, int D, int E, int F);

    bool Unknown40;
    int Unknown44;
    int Unknown48;
    int Unknown4C;
    int Unknown50;
};

// FUNCTION: 0x10BED080 ?FUN_10bed080@Class_10E97258@@QAEPAV1@HHHHHH@Z
Class_10E97258* Class_10E97258::FUN_10bed080(int A, int B, int C, int D, int E, int F)
{
    this->Class_10E90D70::Class_10E90D70(E, F);
    Unknown44 = A;
    Unknown48 = B;
    Unknown40 = 1;
    Unknown00 = DAT_10e97258;
    Unknown4C = C;
    Unknown50 = D;
    return this;
}
