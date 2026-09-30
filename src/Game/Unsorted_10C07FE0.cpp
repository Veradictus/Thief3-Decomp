// Game/Unsorted_10C07FE0.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

extern void* DAT_10ff66ac;

void FUN_10ad1dc0(void* P);

extern void* DAT_10e97bb8[];

class Class_10E97BB8 {
public:
    Class_10E97BB8();

    void** Unknown00;
    int Unknown04;
};

// FUNCTION: 0x10C07FE0 ?FUN_10c07fe0@@YAXXZ
void FUN_10c07fe0()
{
    --*(int*)DAT_10ff66ac;
    if (*(int*)DAT_10ff66ac == 0)
    {
        FUN_10ad1dc0(DAT_10ff66ac);
        DAT_10ff66ac = 0;
    }
}

// FUNCTION: 0x10C08870 ??0Class_10E97BB8@@QAE@XZ
Class_10E97BB8::Class_10E97BB8()
{
    Unknown00 = DAT_10e97bb8;
    Unknown04 = 0;
}
