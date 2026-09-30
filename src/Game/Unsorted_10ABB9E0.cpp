// Game/Unsorted_10ABB9E0.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

class Class_10ABC040 {
public:
    Class_10ABC040* FUN_10abc040();

    int Unknown00;
    unsigned char Unknown04;
    int Unknown08;
};

extern float DAT_10f00e94;

extern float DAT_10e6f4d4;

// FUNCTION: 0x10ABC040 ?FUN_10abc040@Class_10ABC040@@QAEPAV1@XZ
Class_10ABC040* Class_10ABC040::FUN_10abc040()
{
    Unknown00 = 0;
    Unknown04 = 0;
    Unknown08 = 0;
    return this;
}

// FUNCTION: 0x10ABC090 ?FUN_10abc090@@YAXM@Z
void FUN_10abc090(float p1)
{
    DAT_10f00e94 = p1;
}

// FUNCTION: 0x10ABC0A0 ?FUN_10abc0a0@@YAMXZ
float FUN_10abc0a0()
{
    return DAT_10f00e94;
}

// FUNCTION: 0x10ABC110 ?FUN_10abc110@@YAMXZ
float FUN_10abc110()
{
    return DAT_10e6f4d4;
}
