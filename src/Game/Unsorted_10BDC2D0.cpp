// Game/Unsorted_10BDC2D0.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

extern void* DAT_10e94e00[];

class FArray
{
public:
    FArray() : Data(0), ArrayNum(0), ArrayMax(0) {}

    void* Data;
    int ArrayNum;
    int ArrayMax;
};

class Class_10E90D70
{
public:
    Class_10E90D70(int A, int B);

    void** Unknown00;
    int Unknown04[15];
};

class Class_10E94E00 : public Class_10E90D70
{
public:
    Class_10E94E00* FUN_10bdc2d0(int A, int B, int C, int D, int E, bool F);

    int Unknown40;
    FArray Unknown44;
    float Unknown50;
    int Unknown54;
    int Unknown58;
    FArray Unknown5C;
    bool Unknown68;
    int Unknown6C;
    int Unknown70;
    int Unknown74;
    bool Unknown78;
    bool Unknown79;
    FArray Unknown7C;
};

// FUNCTION: 0x10BDC2D0 ?FUN_10bdc2d0@Class_10E94E00@@QAEPAV1@HHHHH_N@Z
Class_10E94E00* Class_10E94E00::FUN_10bdc2d0(int A, int B, int C, int D, int E, bool F)
{
    this->Class_10E90D70::Class_10E90D70(A, B);
    Unknown40 = C;
    Unknown44.FArray::FArray();
    Unknown50 = -1.0f;
    Unknown00 = DAT_10e94e00;
    Unknown54 = 0;
    Unknown58 = 0;
    Unknown5C.FArray::FArray();
    Unknown68 = false;
    Unknown6C = D;
    Unknown70 = 0;
    Unknown74 = E;
    Unknown78 = F;
    Unknown79 = false;
    Unknown7C.FArray::FArray();
    return this;
}
