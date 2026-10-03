// Game/Unsorted_10916CD0.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

class Class_109081E0
{
public:
    Class_109081E0() : Unknown00(0) {}
    ~Class_109081E0();

    char* Unknown00;
};

class Class_10E499A8
{
public:
    virtual void Virtual0();
    virtual int FUN_1090f3c0(int* A, int* B);
};

class Class_10915D50
{
public:
    Class_10915D50() : Unknown00(0), Unknown04(0), Unknown0C(0), Unknown10(false), Unknown14(0) {}

    void FUN_10915e30(int Size);

    int Unknown00;
    int Unknown04;
    int Unknown08;
    int Unknown0C;
    bool Unknown10;
    void* Unknown14;
    Class_10E499A8 Unknown18;
};

class Class_10E495FC
{
public:
    Class_10E495FC();

    virtual ~Class_10E495FC();

    Class_109081E0 Unknown04;
    Class_10915D50 Unknown08;
};

// FUNCTION: 0x10916CD0 ??0Class_10E495FC@@QAE@XZ
Class_10E495FC::Class_10E495FC()
{
    Unknown08.FUN_10915e30(8);
}

// FUNCTION: 0x109178D0 ?FUN_109178d0@@YAIII@Z
unsigned int FUN_109178d0(unsigned int Value, unsigned int Alignment)
{
    return (Value + Alignment - 1) / Alignment * Alignment - Value;
}
