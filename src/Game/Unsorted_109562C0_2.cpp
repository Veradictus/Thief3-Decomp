// Game/Unsorted_109562C0_2.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

extern void* DAT_10e4ae20[];

class Class_10E4ADC0
{
public:
    Class_10E4ADC0(int A, int B);

    void** Unknown00;
    char Unknown04[8];
    int Unknown0C;
    char Unknown10[0x14];
    int Unknown24;
    char Unknown28[0xC];
    int Unknown34;
    char Unknown38[0x14];
    bool Unknown4C;
    char Unknown4D[0x247];
};

class Class_10E4AE20 : public Class_10E4ADC0
{
public:
    Class_10E4AE20* FUN_10956780(int A, int B);

    int Unknown294;
    int Unknown298;
    int Unknown29C;
    float Unknown2A0;
};

// FUNCTION: 0x10956780 ?FUN_10956780@Class_10E4AE20@@QAEPAV1@HH@Z
Class_10E4AE20* Class_10E4AE20::FUN_10956780(int A, int B)
{
    this->Class_10E4ADC0::Class_10E4ADC0(A, B);
    Unknown0C = B;
    Unknown00 = DAT_10e4ae20;
    Unknown294 = 0;
    Unknown298 = 0;
    Unknown29C = 0;
    Unknown2A0 = 1.0f;
    switch (B)
    {
    case 1:
        Unknown24 = 0;
        Unknown4C = true;
        Unknown34 = 4;
        break;
    default:
        Unknown34 = 0;
        break;
    }
    return this;
}
