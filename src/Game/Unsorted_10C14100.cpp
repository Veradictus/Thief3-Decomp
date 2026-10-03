// Game/Unsorted_10C14100.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

class Class_10C08940
{
public:
    virtual void Virtual0();
    virtual void Virtual1();
    virtual void Virtual2();
    virtual int Virtual3(int A, int B);
};

class Class_10978090
{
public:
    virtual void Virtual0();
    virtual void Virtual1();
    virtual void Virtual2();
    virtual void Virtual3();
    virtual int Virtual4();

    Class_10C08940* FUN_10978090();

    Class_10C08940* Unknown04;
};

class Class_10AAB5C0 : public Class_10978090
{
public:
    int FUN_10aab5c0();

    int Unknown08;
};

class Class_10E5B578
{
public:
    virtual int Virtual0(int A, int B, int C, int* D) = 0;
};

struct Struct_10AA3520
{
    char Unknown00[8];
    int Unknown08;
};

extern Struct_10AA3520* DAT_10f35dec;

class Class_10E8C268 : public Class_10AAB5C0, public Class_10E5B578
{
public:
    virtual int Virtual0(int A, int B, int C, int* D);
};

// FUNCTION: 0x10C14100 ?Virtual0@Class_10E8C268@@UAEHHHHPAH@Z
int Class_10E8C268::Virtual0(int A, int B, int C, int* D)
{
    if (B && B == DAT_10f35dec->Unknown08)
        return FUN_10978090()->Virtual3(Virtual4(), FUN_10aab5c0());
}
