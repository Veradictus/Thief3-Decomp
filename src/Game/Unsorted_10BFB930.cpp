// Game/Unsorted_10BFB930.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

extern void* DAT_10e97a48[];

class Class_10E97A48;

class Class_10F46DA0
{
public:
    virtual void Virtual0();
    virtual void Virtual1(Class_10E97A48* A, int B, int C, int D);
};

extern Class_10F46DA0* DAT_10f46da0;

class Class_10E97A48
{
public:
    Class_10E97A48* FUN_10bfb930();

    void** Unknown00;
};

// FUNCTION: 0x10BFB930 ?FUN_10bfb930@Class_10E97A48@@QAEPAV1@XZ
Class_10E97A48* Class_10E97A48::FUN_10bfb930()
{
    Unknown00 = DAT_10e97a48;
    DAT_10f46da0->Virtual1(this, 0x5a, -1, -1);
    return this;
}
