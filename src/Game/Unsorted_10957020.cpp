// Game/Unsorted_10957020.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

extern void* DAT_10e4ae8c;

class Class_10E4ADC0
{
public:
    Class_10E4ADC0(int A, int B);

    void** Unknown00;
    char Unknown04[0x290];
};

class Class_10956DB0 : public Class_10E4ADC0
{
public:
    Class_10956DB0(int A) : Class_10E4ADC0(A, 0), Unknown294(0) {}
    ~Class_10956DB0();

    void FUN_10956db0();

    unsigned char Unknown294;
};

class Class_10E4AE8C : public Class_10956DB0
{
public:
    Class_10E4AE8C(int A);
};

// FUNCTION: 0x10957020 ??0Class_10E4AE8C@@QAE@H@Z
Class_10E4AE8C::Class_10E4AE8C(int A)
    : Class_10956DB0(A)
{
    Unknown00 = &DAT_10e4ae8c;
    FUN_10956db0();
}
