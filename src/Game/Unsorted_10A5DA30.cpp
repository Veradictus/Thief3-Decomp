// Game/Unsorted_10A5DA30.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

class Class_10905A90_Member
{
public:
    virtual void Virtual0();
    virtual void Virtual1();
    virtual void Virtual2();
    virtual void Virtual3();
    virtual void Virtual4();
    virtual void Virtual5(int* Obj);
};

Class_10905A90_Member* FUN_10905aa0();

class Class_10A5DAB0
{
public:
    void FUN_10a5dab0();

    char Unknown00[0x24];
    int* Unknown24;
};

// FUNCTION: 0x10A5DAB0 ?FUN_10a5dab0@Class_10A5DAB0@@QAEXXZ
void Class_10A5DAB0::FUN_10a5dab0()
{
    if (Unknown24)
    {
        int* Obj = Unknown24 - 1;
        FUN_10905aa0()->Virtual5(Obj);
        Unknown24 = 0;
    }
}
