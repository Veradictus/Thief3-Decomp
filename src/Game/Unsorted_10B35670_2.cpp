// Game/Unsorted_10B35670_2.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

class Class_10EB766C
{
public:
    virtual ~Class_10EB766C();

    int Unknown04;
    int Unknown08;
};

class Class_10E5B578
{
public:
    virtual int Virtual0(int A, int B, int C, int* D) = 0;
};

class Class_10E6DC88 : public Class_10EB766C, public Class_10E5B578
{
public:
    virtual ~Class_10E6DC88();

    int Unknown10;
};

class Class_10F46DA0
{
public:
    virtual void Virtual0();
    virtual void Virtual1(Class_10E5B578* A, int B, int C, int D);
    virtual void Virtual2(Class_10E5B578* A);
};

extern Class_10F46DA0* DAT_10f46da0;

class Class_10E7C2CC : public Class_10E6DC88
{
public:
    virtual ~Class_10E7C2CC();
    virtual int Virtual0(int A, int B, int C, int* D);
};

class Class_10E7C2EC : public Class_10E6DC88
{
public:
    virtual ~Class_10E7C2EC();
    virtual int Virtual0(int A, int B, int C, int* D);
};

class Class_10E7C30C : public Class_10E6DC88
{
public:
    virtual ~Class_10E7C30C();
    virtual int Virtual0(int A, int B, int C, int* D);
};

// FUNCTION: 0x10B35710 ??1Class_10E7C2CC@@UAE@XZ
Class_10E7C2CC::~Class_10E7C2CC()
{
    DAT_10f46da0->Virtual2(this);
}

// FUNCTION: 0x10B35840 ??1Class_10E7C2EC@@UAE@XZ
Class_10E7C2EC::~Class_10E7C2EC()
{
    DAT_10f46da0->Virtual2(this);
}

// FUNCTION: 0x10B35970 ??1Class_10E7C30C@@UAE@XZ
Class_10E7C30C::~Class_10E7C30C()
{
    DAT_10f46da0->Virtual2(this);
}
