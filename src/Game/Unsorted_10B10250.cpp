// Game/Unsorted_10B10250.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

class Class_10B10C30 {
public:
    void FUN_10b10ab0(int p1, int p2);
    void FUN_10b10c30(int p1);
};

extern "C" void* memset(void*, int, unsigned);

extern bool DAT_10ff35ce;

extern int DAT_10f7b5c8[0x1e000];

class Class_10B10A70
{
public:
    Class_10B10A70* FUN_10b10a70();

    int Unknown00[4];
};

class Class_10B10B80
{
public:
    unsigned short FUN_10ad24b0(int p1);

    bool FUN_10b10b80(int p1);
};

// FUNCTION: 0x10B10A70 ?FUN_10b10a70@Class_10B10A70@@QAEPAV1@XZ
Class_10B10A70* Class_10B10A70::FUN_10b10a70()
{
    memset(Unknown00, 0, sizeof(Unknown00));
    if (!DAT_10ff35ce)
    {
        memset(DAT_10f7b5c8, 0, sizeof(DAT_10f7b5c8));
        DAT_10ff35ce = true;
    }
    return this;
}

// FUNCTION: 0x10B10B80 ?FUN_10b10b80@Class_10B10B80@@QAE_NH@Z
bool Class_10B10B80::FUN_10b10b80(int p1)
{
    return FUN_10ad24b0(p1) != 0;
}

// FUNCTION: 0x10B10C30 ?FUN_10b10c30@Class_10B10C30@@QAEXH@Z
void Class_10B10C30::FUN_10b10c30(int p1)
{
    FUN_10b10ab0(0, p1);
}
