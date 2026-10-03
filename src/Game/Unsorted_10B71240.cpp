// Game/Unsorted_10B71240.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

class FArray
{
public:
    FArray() : Data(0), ArrayNum(0), ArrayMax(0) {}

    void* Data;
    int ArrayNum;
    int ArrayMax;
};

// A growable array (count, allocated, data); 0x10B71920 shows its inline destructor.
class Class_10BFBD70
{
public:
    Class_10BFBD70() : Unknown00(0), Unknown04(0), Unknown08(0) {}
    ~Class_10BFBD70();

    void FUN_10bfbd70(int NewCount);

    int Unknown00;
    int Unknown04;
    int* Unknown08;
};

class Class_10E88AF8
{
public:
    Class_10E88AF8();

    virtual ~Class_10E88AF8();

    char Unknown04[0xE4];
    int Unknown0E8;
    char Unknown0EC[0x74];
};

class Class_10E886D0 : public Class_10E88AF8
{
public:
    Class_10E886D0();

    virtual ~Class_10E886D0();

    int Unknown160;
    int Unknown164;
    FArray Unknown168;
    int Unknown174;
    int Unknown178;
    int Unknown17C;
    int Unknown180;
    int Unknown184;
    int Unknown188;
    bool Unknown18C;
};

class Class_10E873B0 : public Class_10E886D0
{
public:
    Class_10E873B0();

    virtual ~Class_10E873B0();

    Class_10BFBD70 Unknown190;
    Class_10BFBD70 Unknown19C;
    Class_10BFBD70 Unknown1A8;
    int Unknown1B4;
    int Unknown1B8;
    int Unknown1BC;
    int Unknown1C0;
    int Unknown1C4;
    char Unknown1C8[4];
    int Unknown1CC;
    Class_10BFBD70 Unknown1D0;
    Class_10BFBD70 Unknown1DC;
    Class_10BFBD70 Unknown1E8;
    int Unknown1F4;
};

// FUNCTION: 0x10B71830 ??0Class_10E873B0@@QAE@XZ
Class_10E873B0::Class_10E873B0()
    : Unknown1B4(0), Unknown1B8(0), Unknown1BC(0), Unknown1C0(0), Unknown1C4(0), Unknown1CC(0), Unknown1F4(0)
{
    Unknown184 = 8;
}

// FUNCTION: 0x10B71AC0 ??_GClass_10E873B0@@UAEPAXI@Z
// Compiler-generated: emitted with the class's vtable by 0x10B71830's definition in this unit.
