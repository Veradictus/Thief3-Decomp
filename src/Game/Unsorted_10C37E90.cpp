// Game/Unsorted_10C37E90.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

extern void* DAT_10e9ae88[];

class Class_10C37390
{
public:
    Class_10C37390(int A, int B, int C, int D, int E, int F, int G, int H);

    void** Unknown00;
};

class Class_10E9AE88 : public Class_10C37390
{
public:
    Class_10E9AE88* FUN_10c37e90(int A, int B, int C, int D, int E, int F, int G);
};

// FUNCTION: 0x10C37E90 ?FUN_10c37e90@Class_10E9AE88@@QAEPAV1@HHHHHHH@Z
Class_10E9AE88* Class_10E9AE88::FUN_10c37e90(int A, int B, int C, int D, int E, int F, int G)
{
    this->Class_10C37390::Class_10C37390(A, B, C, D, 0, E, F, G);
    Unknown00 = DAT_10e9ae88;
    return this;
}
