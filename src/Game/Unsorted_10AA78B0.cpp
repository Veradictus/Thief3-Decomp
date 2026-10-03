// Game/Unsorted_10AA78B0.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

class Class_10905A90_Member
{
public:
    virtual void Virtual0();
    virtual void Virtual1();
    virtual void Virtual2();
    virtual void Virtual3();
    virtual void Virtual4();
    virtual void Virtual5(void* Block);
};

Class_10905A90_Member* FUN_10905aa0();

// Ion Storm's string (0x109081E0): a char pointer to a block allocated 4 bytes before it.
class Class_109081E0
{
public:
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

class Class_10A810F0
{
public:
    Class_109081E0 Unknown00;
};

class Class_10E6C104 : public Class_10A810F0
{
public:
    virtual ~Class_10E6C104() {}
};

// The objects Class_10E6D940 owns at +0x08 and +0x0C, deleted through their virtual destructors.
class Class_10AA78B0_Field08
{
public:
    virtual ~Class_10AA78B0_Field08();
};

class Class_10AA78B0_Field0C
{
public:
    virtual ~Class_10AA78B0_Field0C();
};

class Class_10E6D940 : public Class_10E6C104
{
public:
    virtual ~Class_10E6D940();

    Class_10AA78B0_Field08* Unknown08;
    Class_10AA78B0_Field0C* Unknown0C;
    Class_109081E0 Unknown10;
    int Unknown14;
    int Unknown18;
};

// FUNCTION: 0x10AA78B0 ??1Class_10E6D940@@UAE@XZ
Class_10E6D940::~Class_10E6D940()
{
    delete Unknown08;
    delete Unknown0C;
    Unknown08 = 0;
    Unknown0C = 0;
}
