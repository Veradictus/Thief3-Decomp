// Game/Unsorted_109E5770.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

class Class_10BFBD70
{
public:
    void FUN_10bfbd70(int NewCount);

    int Count;
    int Unknown04;
    int* Data;
};

class Class_10E5B2C0
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
    virtual void FUN_109e60e0(int Value);

    char Unknown04[0xB4];
    Class_10BFBD70 Unknown0B8;
};

int FUN_10af36e0(const char* A, const char* B);

extern const char DAT_10e47660[];

// Ion Storm's string (0x109081E0): a char pointer, null when empty.
class Class_109081E0
{
public:
    char* Unknown00;
};

class Class_109E5910
{
public:
    int FUN_109e5910(const Class_109081E0& Name);
};

struct Entry_10C32C30
{
    Entry_10C32C30* Next;
    Entry_10C32C30* Prev;
};

class Class_10D3F830
{
public:
    bool FUN_10d3f830(int* Key);
};

class Class_10C49740 : public Class_10D3F830
{
public:
    bool FUN_10c49740(int* Key, Entry_10C32C30** Out);
};

class Class_109E59D0
{
public:
    Entry_10C32C30* FUN_109e59d0(int* Key);

    char Unknown00[0x3C];
    Class_10C49740 Unknown3C;
};

// FUNCTION: 0x109E5910 ?FUN_109e5910@Class_109E5910@@QAEHABVClass_109081E0@@@Z
int Class_109E5910::FUN_109e5910(const Class_109081E0& Name)
{
    if (!FUN_10af36e0(Name.Unknown00 ? Name.Unknown00 : DAT_10e47660, "ABSOLUTE"))
        return 1;
    return FUN_10af36e0(Name.Unknown00 ? Name.Unknown00 : DAT_10e47660, "RELATIVE") != 0;
}

// FUNCTION: 0x109E59D0 ?FUN_109e59d0@Class_109E59D0@@QAEPAUEntry_10C32C30@@PAH@Z
Entry_10C32C30* Class_109E59D0::FUN_109e59d0(int* Key)
{
    Entry_10C32C30* Entry = 0;
    Entry_10C32C30* Found = 0;
    if (Unknown3C.FUN_10d3f830(Key))
    {
        Unknown3C.FUN_10c49740(Key, &Found);
        Entry = Found;
    }
    return Entry;
}

// FUNCTION: 0x109E60E0 ?FUN_109e60e0@Class_10E5B2C0@@UAEXH@Z
void Class_10E5B2C0::FUN_109e60e0(int Value)
{
    Class_10BFBD70* List = &Unknown0B8;
    int Index = List->Count;
    List->FUN_10bfbd70(Index + 1);
    List->Data[Index] = Value;
}
