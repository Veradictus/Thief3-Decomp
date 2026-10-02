// Game/Unsorted_10C382F0_2.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

extern void* DAT_10e9af04[];

class Class_10C37390
{
public:
    Class_10C37390(int A, int B, int C, int D, int E, int F, int G, int H);

    void** Unknown00;
};

class Class_10E9AF04 : public Class_10C37390
{
public:
    Class_10E9AF04* FUN_10c382f0(int A, int B, int C, int D, int E, int F);
};

// FUNCTION: 0x10C382F0 ?FUN_10c382f0@Class_10E9AF04@@QAEPAV1@HHHHHH@Z
Class_10E9AF04* Class_10E9AF04::FUN_10c382f0(int A, int B, int C, int D, int E, int F)
{
    this->Class_10C37390::Class_10C37390(A, B, C, D, 0, 0, 0, E);
    Unknown00 = DAT_10e9af04;
    return this;
}
