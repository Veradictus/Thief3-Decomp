// Game/Unsorted_10A9D160.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
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

// FUN_10a9d150 is the constructor: it stores the vtable and returns this.
class Class_10A9D150
{
public:
    Class_10A9D150* FUN_10a9d150();

    void* Unknown00;
};

class Class_10E5D8C8
{
public:
    virtual Class_10A9D150* FUN_10a9d160();
};

// FUNCTION: 0x10A9D160 ?FUN_10a9d160@Class_10E5D8C8@@UAEPAVClass_10A9D150@@XZ
Class_10A9D150* Class_10E5D8C8::FUN_10a9d160()
{
    FUN_10905aa0()->Virtual8(0, 0);
    Class_10A9D150* Result = 0;
    void* Memory = operator new(sizeof(Class_10A9D150), 0, 0, 0, 0, 0);
    if (Memory)
        Result = static_cast<Class_10A9D150*>(Memory)->FUN_10a9d150();
    FUN_10905aa0()->Virtual9();
    return Result;
}
