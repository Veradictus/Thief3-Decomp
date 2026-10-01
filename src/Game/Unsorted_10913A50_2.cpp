// Game/Unsorted_10913A50_2.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

extern void* DAT_10e49384[];

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

inline void FreeBlock(int*& Block)
{
    if (Block)
    {
        int* Obj = Block - 1;
        FUN_10905aa0()->Virtual5(Obj);
        Block = 0;
    }
}

class Class_10E49384
{
public:
    ~Class_10E49384();

    void** VTable;
    int* Unknown04;
};

class Class_109081E0 {
public:
    Class_109081E0& operator=(const Class_109081E0& Other);

    void* Unknown00;
};

class Class_10913D70 {
public:
    int Unknown00;
    Class_109081E0 Unknown04;

    Class_10913D70* FUN_10913d70(Class_10913D70* Other);
};

// FUNCTION: 0x10913A50 ??1Class_10E49384@@QAE@XZ
Class_10E49384::~Class_10E49384()
{
    VTable = DAT_10e49384;
    FreeBlock(Unknown04);
}

// FUNCTION: 0x10913D70 ?FUN_10913d70@Class_10913D70@@QAEPAV1@PAV1@@Z
Class_10913D70* Class_10913D70::FUN_10913d70(Class_10913D70* Other)
{
    Unknown04 = Other->Unknown04;
    return this;
}
