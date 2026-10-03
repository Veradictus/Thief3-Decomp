// Game/Unsorted_10C165A0.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

void operator delete(void* P);

class Class_10FF667C_Member
{
public:
    virtual void Virtual0();
    virtual void Virtual1(int p1, int* p2);
    virtual void Virtual2();
    virtual void Virtual3(int* P);
};

class Class_10FF667C
{
public:
    char Unknown00[0x18];
    Class_10FF667C_Member* Unknown18;
};

extern Class_10FF667C* DAT_10ff667c;

class Class_10E98C8C;

class Class_10E98C88
{
public:
    virtual ~Class_10E98C88();

    void FUN_10c16470(Class_10E98C8C* P);

    int Unknown04;
};

extern Class_10E98C88* DAT_10ff7080;

class Class_10E98C8C
{
public:
    ~Class_10E98C8C();

    virtual void FUN_10c162e0(int p1);

    int Unknown04;
};

inline void FreeInstance(Class_10E98C88* P)
{
    P->Class_10E98C88::~Class_10E98C88();
    operator delete(P);
}

// FUNCTION: 0x10C165A0 ??1Class_10E98C8C@@QAE@XZ
Class_10E98C8C::~Class_10E98C8C()
{
    DAT_10ff667c->Unknown18->Virtual3(&Unknown04);
    DAT_10ff7080->FUN_10c16470(this);
    if (DAT_10ff7080->Unknown04 == 0)
    {
        FreeInstance(DAT_10ff7080);
        DAT_10ff7080 = 0;
    }
}
