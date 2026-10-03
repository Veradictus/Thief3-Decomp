// Game/Unsorted_10AA80D0_3.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
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

class Class_109081E0
{
public:
    ~Class_109081E0()
    {
        if (Unknown00)
        {
            char* Block = Unknown00 - 4;
            FUN_10905aa0()->Virtual5(Block);
        }
    }
    Class_109081E0& operator=(const Class_109081E0& Other);

    char* Unknown00;
};

class Class_10AA8110_Param
{
public:
    virtual void Virtual0();
    virtual void Virtual1();
    virtual Class_109081E0 Virtual2();
};

class Class_10E6C170
{
public:
    virtual void Virtual0();
    virtual void Virtual1();
    virtual void Virtual2();
    virtual void Virtual3();
    virtual int FUN_10aa8110(Class_10AA8110_Param* Src);

    Class_109081E0 Unknown04;
    Class_109081E0 Unknown08;
};

// FUNCTION: 0x10AA8110 ?FUN_10aa8110@Class_10E6C170@@UAEHPAVClass_10AA8110_Param@@@Z
int Class_10E6C170::FUN_10aa8110(Class_10AA8110_Param* Src)
{
    Unknown04 = Src->Virtual2();
    Unknown08 = Src->Virtual2();
    return 1;
}
