// Game/Unsorted_10BDB480_5.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

extern void* DAT_10e948d8[];

class Class_10E90D70
{
public:
    Class_10E90D70(int A, int B);

    void** Unknown00;
    int Unknown04[15];
};

class Class_10E948D8 : public Class_10E90D70
{
public:
    Class_10E948D8* FUN_10bdba10(int A, int B, int C, int D);

    int Unknown40;
    int Unknown44[3];
    float Unknown50;
    int Unknown54;
};

// FUNCTION: 0x10BDBA10 ?FUN_10bdba10@Class_10E948D8@@QAEPAV1@HHHH@Z
Class_10E948D8* Class_10E948D8::FUN_10bdba10(int A, int B, int C, int D)
{
    this->Class_10E90D70::Class_10E90D70(A, B);
    Unknown40 = C;
    for (int i = 0; i < 3; i++)
        Unknown44[i] = 0;
    Unknown54 = D;
    Unknown50 = -1.0f;
    Unknown00 = DAT_10e948d8;
    return this;
}
