// Game/Unsorted_10AAAA90_2.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

extern const char DAT_10e6c100[];

class Class_109081E0
{
public:
    Class_109081E0() : Unknown00(0) {}
    ~Class_109081E0();

    Class_109081E0& FUN_1090a590(const char* In);

    char* Unknown00;
};

class Class_10AAACB0_Param
{
public:
    virtual void Virtual0();
    virtual void Virtual1();
    virtual Class_109081E0 Virtual2();
};

class Class_10A810F0
{
public:
    Class_10A810F0() { Unknown00.FUN_1090a590(DAT_10e6c100); }

    Class_109081E0 Unknown00;
};

class Class_10E6C104 : public Class_10A810F0
{
public:
    Class_10E6C104();

    virtual ~Class_10E6C104();
};

class Class_10E6D9E8 : public Class_10E6C104
{
public:
    Class_10E6D9E8();

    virtual void Virtual1();
    virtual void FUN_10aaaa20(void* Reader, int Version, int Unused);
    virtual void FUN_10aaaa40(void* Writer, int Unused1, int Unused2);
    virtual int FUN_10aaacb0(Class_10AAACB0_Param* Src);

    Class_109081E0 Unknown08;
};

// FUNCTION: 0x10AAAB10 ??0Class_10E6D9E8@@QAE@XZ
Class_10E6D9E8::Class_10E6D9E8()
{
    Unknown08.FUN_1090a590(DAT_10e6c100);
}
