// Game/Unsorted_10A32C30.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

#include <new>

// Ion Storm's memory manager (0x10905AA0).
class Class_10905A90_Member
{
public:
    virtual void Virtual0();
    virtual void Virtual1();
    virtual void Virtual2();
    virtual void* Virtual3(void* Block, int Size, int A, int B, int C, int D);
    virtual void Virtual4();
    virtual void Virtual5(void* Block);
    virtual void Virtual6();
    virtual void Virtual7();
    virtual void Virtual8(int A, int B);
    virtual void Virtual9();
};

Class_10905A90_Member* FUN_10905aa0();

// The element: itself a growable array (a count, the bytes allocated and the block).
class Class_10A32370
{
public:
    Class_10A32370() : Unknown00(0), Unknown04(0), Unknown08(0) {}

    ~Class_10A32370()
    {
        FUN_10a32370(0);
        if (Unknown04)
        {
            FUN_10905aa0()->Virtual5(Unknown08);
            Unknown08 = 0;
            Unknown04 = 0;
        }
    }

    void FUN_10a32370(int NewCount);

    int Unknown00;
    int Unknown04;
    void* Unknown08;
};

// A growable array of Class_10A32370: a count, the bytes allocated and the
// block, grown and shrunk 16 entries at a time.
class Class_10A32D60
{
public:
    void FUN_10a32c30(int NewCount);

    int Unknown00;
    int Unknown04;
    Class_10A32370* Unknown08;
};

// FUNCTION: 0x10A32C30 ?FUN_10a32c30@Class_10A32D60@@QAEXH@Z
void Class_10A32D60::FUN_10a32c30(int NewCount)
{
    int OldCount = Unknown00;
    int Capacity = !Unknown08 ? 0 : Unknown04 / sizeof(Class_10A32370);
    for (int i = NewCount; i < OldCount; i++)
        Unknown08[i].~Class_10A32370();
    FUN_10905aa0()->Virtual8(0, 0);
    if (NewCount > Capacity)
    {
        int NewCapacity = NewCount;
        if (Capacity)
            NewCapacity = (NewCount & ~15) + 16;
        Unknown08 = (Class_10A32370*)FUN_10905aa0()->Virtual3(Unknown08, NewCapacity * sizeof(Class_10A32370), 0, 0, 0, 0);
        Unknown04 = NewCapacity * sizeof(Class_10A32370);
    }
    else if (NewCount <= Capacity - 16)
    {
        if (NewCount == 0)
        {
            FUN_10905aa0()->Virtual5(Unknown08);
            Unknown08 = 0;
            Unknown04 = 0;
        }
        else
        {
            int NewCapacity = (NewCount & ~15) + 16;
            Unknown08 = (Class_10A32370*)FUN_10905aa0()->Virtual3(Unknown08, NewCapacity * sizeof(Class_10A32370), 0, 0, 0, 0);
            Unknown04 = NewCapacity * sizeof(Class_10A32370);
        }
    }
    for (int j = OldCount; j < NewCount; j++)
        new (&Unknown08[j]) Class_10A32370;
    FUN_10905aa0()->Virtual9();
    Unknown00 = NewCount;
}
