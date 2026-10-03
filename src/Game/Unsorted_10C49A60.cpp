// Game/Unsorted_10C49A60.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

struct Entry_10C32C30;

class Class_10C49740
{
public:
    bool FUN_10c49740(int* A, Entry_10C32C30** B);
    void FUN_10c49ab0(int* A);
};

class Class_10E9BBC0_Unknown3C
{
public:
    virtual void Virtual0();
    virtual void Virtual1(Entry_10C32C30* Entry);
};

class Class_10E9BBC0
{
public:
    virtual void Virtual0();
    virtual void Virtual1();
    virtual void Virtual2();
    virtual void Virtual3();
    virtual void Virtual4();
    virtual void FUN_10c49a60(int A);

    Class_10C49740 Unknown04;
    char Unknown05[0x37];
    Class_10E9BBC0_Unknown3C* Unknown3C;
};

// FUNCTION: 0x10C49A60 ?FUN_10c49a60@Class_10E9BBC0@@UAEXH@Z
void Class_10E9BBC0::FUN_10c49a60(int A)
{
    Entry_10C32C30* Entry = 0;
    if (Unknown04.FUN_10c49740(&A, &Entry))
    {
        Unknown3C->Virtual1(Entry);
        Unknown04.FUN_10c49ab0(&A);
    }
}
