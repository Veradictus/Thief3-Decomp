// Game/Unsorted_10A8D5A0_2.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
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

extern bool DAT_10f45c0e;

class Class_10E6C7F8 : public Class_10AAB5C0, public Class_10E5B578
{
public:
    virtual int Virtual0(int A, int B, int C, int* D);
};

// FUNCTION: 0x10A8D640 ?Virtual0@Class_10E6C7F8@@UAEHHHHPAH@Z
int Class_10E6C7F8::Virtual0(int A, int B, int C, int* D)
{
    if (!DAT_10f45c0e)
        return FUN_10978090()->Virtual3(Virtual4(), FUN_10aab5c0());
}
