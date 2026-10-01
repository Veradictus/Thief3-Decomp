// Game/Unsorted_10C0B3D0.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

extern void* DAT_10e97c18[];

class Class_10E97C18
{
public:
    Class_10E97C18* FUN_10c0b8d0();

    void** Unknown00;
    bool Unknown04;
    int Unknown08[6];
    int Unknown20;
    int Unknown24;
    int Unknown28;
    int Unknown2C;
    int Unknown30;
    int Unknown34;
    int Unknown38;
    int Unknown3C;
    bool Unknown40;
    bool Unknown41;
    bool Unknown42;
};

// FUNCTION: 0x10C0B8D0 ?FUN_10c0b8d0@Class_10E97C18@@QAEPAV1@XZ
Class_10E97C18* Class_10E97C18::FUN_10c0b8d0()
{
    Unknown00 = DAT_10e97c18;
    Unknown04 = false;
    for (int i = 0; i < 6; i++)
        Unknown08[i] = 0;
    Unknown20 = 0;
    Unknown24 = 0;
    Unknown28 = 0;
    Unknown2C = 0;
    Unknown30 = 0;
    Unknown34 = 0;
    Unknown38 = 0;
    Unknown3C = 0;
    Unknown40 = true;
    Unknown41 = true;
    Unknown42 = false;
    return this;
}
