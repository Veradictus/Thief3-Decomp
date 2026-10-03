// Game/Unsorted_10A9B0F0.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

class Class_10C56E40_Field00
{
public:
    virtual void Virtual0();
    virtual void Virtual1();
    virtual void Virtual2();
};

class Class_10C56E40
{
public:
    ~Class_10C56E40()
    {
        if (Unknown00)
            Unknown00->Virtual2();
    }

    Class_10C56E40_Field00* Unknown00;
};

class Class_10E6CA18
{
public:
    virtual ~Class_10E6CA18() {}
    virtual int FUN_10a9b0e0() = 0;
    virtual int FUN_10a9b8d0(int A, int B, void* C) = 0;
};

class Class_10E6D1AC_Secondary
{
public:
    virtual void FUN_10a9b260(int A) = 0;
};

class Class_10E5B578
{
public:
    virtual int FUN_10a9b210(int A, int B, int C, int* D) = 0;
};

class Class_10F46DA0
{
public:
    virtual void Virtual0();
    virtual void Virtual1(Class_10E5B578* A, int B, int C, int D);
    virtual void Virtual2(Class_10E5B578* A);
};

extern Class_10F46DA0* DAT_10f46da0;

class Class_10E6D1AC : public Class_10E6CA18, public Class_10E6D1AC_Secondary, public Class_10E5B578
{
public:
    virtual ~Class_10E6D1AC();
    virtual int FUN_10a9b0e0();
    virtual int FUN_10a9b8d0(int A, int B, void* C);
    virtual void FUN_10a9b260(int A);
    virtual int FUN_10a9b210(int A, int B, int C, int* D);

    int Unknown0C;
    void* Unknown10;
    Class_10C56E40 Unknown14;
};

// FUNCTION: 0x10A9B110 ??1Class_10E6D1AC@@UAE@XZ
Class_10E6D1AC::~Class_10E6D1AC()
{
    if (DAT_10f46da0)
        DAT_10f46da0->Virtual2(this);
}
