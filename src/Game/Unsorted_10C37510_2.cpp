// Game/Unsorted_10C37510_2.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

extern void* DAT_10e9ae24[];

class Class_10C37390
{
public:
    Class_10C37390(int A, int B, int C, int D, int E, int F, int G, int H);

    void** Unknown00;
    char Unknown04[0x90];
};

class Class_10E9AE24 : public Class_10C37390
{
public:
    Class_10E9AE24* FUN_10c37700(int A, int B, int C, int D, int E, int F, int G, int H);

    int Unknown94;
    int Unknown98;
};

// FUNCTION: 0x10C37700 ?FUN_10c37700@Class_10E9AE24@@QAEPAV1@HHHHHHHH@Z
Class_10E9AE24* Class_10E9AE24::FUN_10c37700(int A, int B, int C, int D, int E, int F, int G, int H)
{
    this->Class_10C37390::Class_10C37390(A, B, C, D, 0, 0, G, H);
    Unknown94 = E;
    Unknown00 = DAT_10e9ae24;
    Unknown98 = F;
    return this;
}
