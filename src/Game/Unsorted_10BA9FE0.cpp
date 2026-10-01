// Game/Unsorted_10BA9FE0.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

class Class_10e9092c
{
public:
    virtual void Virtual0();

    bool FUN_10bb7500(int p1, bool p2);

    int Unknown04;
    int Unknown08;
    void* Unknown0C;
};

class Class_10ba9fe0
{
public:
    void FUN_10ba9fe0(int p1);

    char Unknown00[0x54];
    Class_10e9092c Unknown54;
};

// FUNCTION: 0x10BA9FE0 ?FUN_10ba9fe0@Class_10ba9fe0@@QAEXH@Z
void Class_10ba9fe0::FUN_10ba9fe0(int p1)
{
    Unknown54.FUN_10bb7500(p1, false);
}
