// Game/Unsorted_10AA7F30.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

class Class_10AAB590_Param
{
public:
    virtual void Virtual0(int* Value);
    virtual void Virtual1(int Value);
};

class Class_10E6C14C
{
public:
    virtual void Virtual0();
    virtual void Virtual1();
    virtual void Virtual2();
    virtual void Virtual3();
    virtual void Virtual4();
    virtual int FUN_10aa7f30(Class_10AAB590_Param* Writer);

    int Unknown04;
    int Unknown08;
    int Unknown0C;
};

// FUNCTION: 0x10AA7F30 ?FUN_10aa7f30@Class_10E6C14C@@UAEHPAVClass_10AAB590_Param@@@Z
int Class_10E6C14C::FUN_10aa7f30(Class_10AAB590_Param* Writer)
{
    Writer->Virtual0(&Unknown04);
    Writer->Virtual0(&Unknown08);
    Writer->Virtual1(Unknown0C);
    return 1;
}
