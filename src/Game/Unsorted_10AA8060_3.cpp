// Game/Unsorted_10AA8060_3.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

class Object_10AA8080
{
public:
    virtual void Virtual0(int* Value);
};

class Class_10E6C170
{
public:
    virtual void Virtual0();
    virtual void Virtual1();
    virtual void Virtual2();
    virtual void Virtual3();
    virtual void Virtual4();
    virtual int FUN_10aa8080(Object_10AA8080* Stream);

    int Unknown04;
    int Unknown08;
};

// FUNCTION: 0x10AA8080 ?FUN_10aa8080@Class_10E6C170@@UAEHPAVObject_10AA8080@@@Z
int Class_10E6C170::FUN_10aa8080(Object_10AA8080* Stream)
{
    Stream->Virtual0(&Unknown04);
    Stream->Virtual0(&Unknown08);
    return 1;
}
