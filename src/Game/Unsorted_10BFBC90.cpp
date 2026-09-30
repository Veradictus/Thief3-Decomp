// Game/Unsorted_10BFBC90.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

void FUN_10bfbd30(int* A);

class Class_10BFC190
{
public:
    void FUN_10bfc190();

    char Unknown00[8];
    int Unknown08;
    char Unknown0C[8];
    int Unknown14;
    int Unknown18;
    int Unknown1C;
};

class Class_10BFD210
{
public:
    void FUN_10bfd210();
    void FUN_10bfc680(int param);
};

class Class_10C16580
{
public:
    Class_10C16580(int A);

    char Unknown00[8];
};

class Class_10E97AD4
{
public:
    Class_10E97AD4(int A, int B);

    virtual void Virtual0();

    int Unknown04;
    Class_10C16580 Unknown08;
    bool Unknown10;
};

class Class_10BFF240
{
public:
    char Unknown00[0x10];
    unsigned char Unknown10;

    void FUN_10bff240(unsigned char param);
};

extern void* DAT_10e97adc[];

class Class_10E97ADC
{
public:
    Class_10E97ADC* FUN_10bff720();

    void** Unknown00;
    int Unknown04;
    int Unknown08;
    int Unknown0C;
    int Unknown10;
    int Unknown14;
    int Unknown18;
    int Unknown1C;
    int Unknown20;
    int Unknown24;
    int Unknown28;
    int Unknown2C;
    int Unknown30;
    int Unknown34;
};

double FUN_1095af80();

// FUNCTION: 0x10BFC190 ?FUN_10bfc190@Class_10BFC190@@QAEXXZ
void Class_10BFC190::FUN_10bfc190()
{
    int* Head = &Unknown08;
    FUN_10bfbd30(Head);
    Unknown14 = 0;
    Unknown18 = 0;
    Unknown1C = 0;
    *Head = 0;
}

// FUNCTION: 0x10BFD210 ?FUN_10bfd210@Class_10BFD210@@QAEXXZ
void Class_10BFD210::FUN_10bfd210()
{
    FUN_10bfc680(0);
}

// FUNCTION: 0x10BFF210 ??0Class_10E97AD4@@QAE@HH@Z
Class_10E97AD4::Class_10E97AD4(int A, int B) : Unknown04(A), Unknown08(B)
{
    Unknown10 = false;
}

// FUNCTION: 0x10BFF240 ?FUN_10bff240@Class_10BFF240@@QAEXE@Z
void Class_10BFF240::FUN_10bff240(unsigned char param)
{
    Unknown10 = param;
}

// FUNCTION: 0x10BFF720 ?FUN_10bff720@Class_10E97ADC@@QAEPAV1@XZ
Class_10E97ADC* Class_10E97ADC::FUN_10bff720()
{
    Unknown00 = DAT_10e97adc;
    Unknown04 = 0;
    Unknown08 = 0;
    Unknown0C = 0;
    Unknown10 = 0;
    Unknown14 = 0;
    Unknown18 = 0;
    Unknown1C = 0;
    Unknown20 = 0;
    Unknown24 = 0;
    Unknown28 = 0;
    Unknown2C = 0;
    Unknown30 = 0;
    Unknown34 = 0;
    return this;
}

// FUNCTION: 0x10C00670 ?FUN_10c00670@@YANXZ
double FUN_10c00670()
{
    double Seconds = FUN_1095af80();
    return Seconds;
}
