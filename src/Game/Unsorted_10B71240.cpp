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

class Class_10E67FD0
{
public:
    virtual void Virtual0();
    virtual void Virtual1();
    virtual void Virtual2();
    virtual void Virtual3();
    virtual void Virtual4();
    virtual void Virtual5();
    virtual void Virtual6();
    virtual void Virtual7();
    virtual void Virtual8();
    virtual void Virtual9();
    virtual void Virtual10();
    virtual void Virtual11();
    virtual void Virtual12();
    virtual void Virtual13();
    virtual void Virtual14();
    virtual void Virtual15();
    virtual void Virtual16();
    virtual void Virtual17();
    virtual void Virtual18();
    virtual void Virtual19();
    virtual void Virtual20();
    virtual void Virtual21();
    virtual void Virtual22();
    virtual void Virtual23();
    virtual void Virtual24();
    virtual void Virtual25();
    virtual void Virtual26();
    virtual void Virtual27();
    virtual void Virtual28();
    virtual void Virtual29();
    virtual void Virtual30();
    virtual void Virtual31();
    virtual void Virtual32();
    virtual void Virtual33();
    virtual void Virtual34();
    virtual void Virtual35();
    virtual void Virtual36();
    virtual void Virtual37();
    virtual void Virtual38();
    virtual void Virtual39();
    virtual void Virtual40();
    virtual void Virtual41();
    virtual void Virtual42();
    virtual void Virtual43();
    virtual void Virtual44();
    virtual void Virtual45();
    virtual void Virtual46();
    virtual void Virtual47();
    virtual void Virtual48();
    virtual void Virtual49();
    virtual void Virtual50();
    virtual void Virtual51();
    virtual void Virtual52();
    virtual void Virtual53();
    virtual void Virtual54();
    virtual void Virtual55();
    virtual void FUN_10a52a90(int A);
};

class Class_10B717E0
{
public:
    void FUN_10b717e0(bool Flag);

    char Unknown00[0x1E8];
    int Unknown1E8;
    char Unknown1EC[4];
    Class_10E67FD0** Unknown1F0;
};

// FUNCTION: 0x10B717E0 ?FUN_10b717e0@Class_10B717E0@@QAEX_N@Z
void Class_10B717E0::FUN_10b717e0(bool Flag)
{
    int State = Flag ? 2 : 0;
    for (int i = 0; i < Unknown1E8; i++)
        Unknown1F0[i]->FUN_10a52a90(State);
}

// FUNCTION: 0x10B71830 ??0Class_10E873B0@@QAE@XZ
Class_10E873B0::Class_10E873B0()
    : Unknown1B4(0), Unknown1B8(0), Unknown1BC(0), Unknown1C0(0), Unknown1C4(0), Unknown1CC(0), Unknown1F4(0)
{
    Unknown184 = 8;
}

// FUNCTION: 0x10B71AC0 ??_GClass_10E873B0@@UAEPAXI@Z
// Compiler-generated: emitted with the class's vtable by 0x10B71830's definition in this unit.
