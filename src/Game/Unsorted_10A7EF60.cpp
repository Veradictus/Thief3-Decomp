// Game/Unsorted_10A7EF60.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

class Class_10905A90_Member
{
public:
    virtual void Virtual0();
    virtual void Virtual1();
    virtual void Virtual2();
    virtual void Virtual3();
    virtual void Virtual4();
    virtual void Virtual5(void* A);
};

Class_10905A90_Member* FUN_10905aa0();

class Class_109081E0
{
public:
    Class_109081E0(const char* In);
    ~Class_109081E0()
    {
        if (Unknown00)
        {
            char* Block = Unknown00 - 4;
            FUN_10905aa0()->Virtual5(Block);
            Unknown00 = 0;
        }
    }

    char* Unknown00;
};

extern const char DAT_10e5da48[];

class Class_10E6BF84
{
public:
    virtual ~Class_10E6BF84() {}
};

class Class_10E6BFBC : public Class_10E6BF84
{
public:
    Class_10E6BFBC(bool A);

    virtual int Virtual1();
    virtual void Virtual2();
    virtual void Virtual3();
    virtual void Virtual4();
    virtual void Virtual5();
    virtual void Virtual6();
    virtual int FUN_10a7f470();
    virtual void Virtual8();
    virtual int FUN_10a7f420();

    bool Unknown04;
    char Unknown05[2];
    bool Unknown07;
    Class_109081E0 Unknown08;
    int Unknown0C;
    int Unknown10;
};

// FUNCTION: 0x10A7EF60 ??0Class_10E6BFBC@@QAE@_N@Z
Class_10E6BFBC::Class_10E6BFBC(bool A) : Unknown04(A), Unknown07(true), Unknown08(DAT_10e5da48)
{
    Unknown10 = 0;
}
