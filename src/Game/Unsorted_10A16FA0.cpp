// Game/Unsorted_10A16FA0.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

class Class_10A16BC0
{
public:
    void FUN_10a16370(int A);

    ~Class_10A16BC0()
    {
        FUN_10a16370(0x40);
        ::operator delete(Unknown14);
        Unknown04 = 0;
        Unknown0C = 0;
        Unknown14 = 0;
        Unknown00 = 0;
    }

    int Unknown00;
    int Unknown04;
    char Unknown08[4];
    int Unknown0C;
    char Unknown10[4];
    void* Unknown14;
};

class Class_10E5D650;

class Class_10F46DA0
{
public:
    virtual void Virtual0();
    virtual void Virtual1();
    virtual void Virtual2();
    virtual void Virtual3(Class_10E5D650* Listener, int Code, int A, int B);
};

extern Class_10F46DA0* DAT_10f46da0;

class Class_10E5D650
{
public:
    ~Class_10E5D650();

    virtual void FUN_10a17200(int p1, int p2, int p3, int p4);

    void FUN_10a17210();

    Class_10A16BC0 Unknown04;
};

// FUNCTION: 0x10A17180 ??1Class_10E5D650@@QAE@XZ
Class_10E5D650::~Class_10E5D650()
{
    DAT_10f46da0->Virtual3(this, 0x5a, -1, -1);
}
