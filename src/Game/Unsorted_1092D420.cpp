// Game/Unsorted_1092D420.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

class Class_1092D420 {
public:
    int Unknown00;
    int Unknown04;
    int Unknown08;
    bool Unknown0C;
    Class_1092D420* FUN_1092d420();
};

extern int DAT_10f31b88;

class Class_1092D940
{
public:
    char Unknown00[0x7D];
    unsigned char Unknown7D;

    unsigned char FUN_1092d940(unsigned char param);
};

// FUNCTION: 0x1092D420 ?FUN_1092d420@Class_1092D420@@QAEPAV1@XZ
Class_1092D420* Class_1092D420::FUN_1092d420()
{
    DAT_10f31b88 = (int)this;
    Unknown00 = 0;
    Unknown04 = 0;
    Unknown08 = 0;
    Unknown0C = false;
    return this;
}

// FUNCTION: 0x1092D940 ?FUN_1092d940@Class_1092D940@@QAEEE@Z
unsigned char Class_1092D940::FUN_1092d940(unsigned char param)
{
    unsigned char old = Unknown7D;
    Unknown7D = param;
    return old;
}
