// Game/Unsorted_10C63EF0_2.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

extern void* DAT_10e4e098[];

extern void* DAT_10e9cd90[];

int FUN_10b06260();

class Class_10E4E098
{
public:
    Class_10E4E098()
        : Unknown00(DAT_10e4e098), Unknown04(95), Unknown08(600), Unknown0C(FUN_10b06260()), Unknown10(0),
          Unknown14(0), Unknown18(0), Unknown1C(0), Unknown20(0), Unknown24(1), Unknown28(1), Unknown2C(1),
          Unknown30(0)
    {
    }

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
};

class Class_10E9CD90 : public Class_10E4E098
{
public:
    Class_10E9CD90* FUN_10c63f70(int A, int B);

    int Unknown34;
    int Unknown38;
    int Unknown3C;
};

class Class_10C64AA0
{
public:
    void FUN_10c64aa0(unsigned Value, unsigned* Hi, unsigned* Lo);
};

// FUNCTION: 0x10C63F70 ?FUN_10c63f70@Class_10E9CD90@@QAEPAV1@HH@Z
Class_10E9CD90* Class_10E9CD90::FUN_10c63f70(int A, int B)
{
    this->Class_10E4E098::Class_10E4E098();
    Unknown00 = DAT_10e9cd90;
    Unknown34 = A;
    Unknown38 = B;
    Unknown3C = 0;
    Unknown14 = Unknown1C = 1;
    return this;
}

// FUNCTION: 0x10C64AA0 ?FUN_10c64aa0@Class_10C64AA0@@QAEXIPAI0@Z
void Class_10C64AA0::FUN_10c64aa0(unsigned Value, unsigned* Hi, unsigned* Lo)
{
    *Hi = Value >> 29;
    *Lo = Value & 0x1fffffff;
}
