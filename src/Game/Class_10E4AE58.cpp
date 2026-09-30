// Game/Class_10E4AE58.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

extern void* DAT_10e4ae58[];

class Class_10E4ADC0
{
public:
    Class_10E4ADC0(int A, int B);

    void** Unknown00;
    char Unknown04[0x290];
};

class Class_10E4AE58 : public Class_10E4ADC0
{
public:
    Class_10E4AE58* FUN_10956f70(int A);

    unsigned char Unknown294;
};

// FUNCTION: 0x10956F70 ?FUN_10956f70@Class_10E4AE58@@QAEPAV1@H@Z
Class_10E4AE58* Class_10E4AE58::FUN_10956f70(int A)
{
    this->Class_10E4ADC0::Class_10E4ADC0(A, 0);
    Unknown00 = DAT_10e4ae58;
    Unknown294 = 0;
    return this;
}
