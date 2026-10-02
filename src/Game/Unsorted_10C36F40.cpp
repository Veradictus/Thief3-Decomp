// Game/Unsorted_10C36F40.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

class Class_10E9ADE8
{
public:
    virtual void Virtual0();
    virtual void Virtual1();
    virtual void Virtual2();
    virtual void Virtual3();
    virtual void Virtual4();
    virtual int FUN_10c36f40();

    int FUN_10c27140();

    char Unknown04[0x88];
    unsigned char Unknown8C;
};

class Class_10E98C8C
{
public:
    Class_10E98C8C(int p1);
    ~Class_10E98C8C();

    virtual void FUN_10c162e0(int p1);

    int Unknown04;
};

class Class_10E99314
{
public:
    ~Class_10E99314();

    void** Unknown00;
    char Unknown04[0x48];
};

class Class_10C37390 : public Class_10E99314
{
public:
    ~Class_10C37390();

    Class_10E98C8C Unknown4C;
};

// FUNCTION: 0x10C36F40 ?FUN_10c36f40@Class_10E9ADE8@@UAEHXZ
int Class_10E9ADE8::FUN_10c36f40()
{
    int Result = FUN_10c27140();
    if (Result == 0x15 && Unknown8C == 1)
        return 0x16;
    return Result;
}

// FUNCTION: 0x10C37490 ??1Class_10C37390@@QAE@XZ
Class_10C37390::~Class_10C37390()
{
}
