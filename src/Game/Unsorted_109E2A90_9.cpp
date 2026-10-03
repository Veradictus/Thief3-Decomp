// Game/Unsorted_109E2A90_9.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

// Ion Storm's memory manager (0x10905AA0): the allocation happens inside a
// scope of it (slots 8 and 9).
class Class_10905A90_Member
{
public:
    virtual void Virtual0();
    virtual void Virtual1();
    virtual void Virtual2();
    virtual void Virtual3();
    virtual void Virtual4();
    virtual void Virtual5();
    virtual void Virtual6();
    virtual void Virtual7();
    virtual void Virtual8(int A, int B);
    virtual void Virtual9();
};

Class_10905A90_Member* FUN_10905aa0();

// Ion Storm's placement new (0x10905C10).
void* operator new(unsigned int Size, const int& Tag, int A, int B, int C, int D);

extern void* DAT_10e5b2ac[];

class Class_10E5B2AC
{
public:
    Class_10E5B2AC() : VTable(DAT_10e5b2ac) {}

    void** VTable;
};

extern Class_10E5B2AC* DAT_10f35dc0;

// FUNCTION: 0x109E34B0 ?FUN_109e34b0@@YAPAVClass_10E5B2AC@@XZ
Class_10E5B2AC* FUN_109e34b0()
{
    if (!DAT_10f35dc0)
    {
        FUN_10905aa0()->Virtual8(0, 0);
        Class_10E5B2AC* Result = new(0, 0, 0, 0, 0) Class_10E5B2AC;
        DAT_10f35dc0 = Result;
        FUN_10905aa0()->Virtual9();
    }
    return DAT_10f35dc0;
}
