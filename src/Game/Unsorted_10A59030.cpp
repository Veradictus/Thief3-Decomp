// Game/Unsorted_10A59030.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

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

// A growable array of pointers: a count, the bytes allocated and the block,
// grown and shrunk 16 entries at a time.
class Class_10BFBD70
{
public:
    void FUN_10bfbd70(int NewCount)
    {
        int Capacity = !Unknown08 ? 0 : Unknown04 / sizeof(void*);
        FUN_10905aa0()->Virtual8(0, 0);
        if (NewCount > Capacity)
        {
            int NewCapacity = NewCount;
            if (Capacity)
                NewCapacity = (NewCount & ~15) + 16;
            Unknown08 = (void**)FUN_10905aa0()->Virtual3(Unknown08, NewCapacity * sizeof(void*), 0, 0, 0, 0);
            Unknown04 = NewCapacity * sizeof(void*);
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
                Unknown08 = (void**)FUN_10905aa0()->Virtual3(Unknown08, NewCapacity * sizeof(void*), 0, 0, 0, 0);
                Unknown04 = NewCapacity * sizeof(void*);
            }
        }
        FUN_10905aa0()->Virtual9();
        Unknown00 = NewCount;
    }

    ~Class_10BFBD70()
    {
        FUN_10bfbd70(0);
        if (Unknown04)
        {
            FUN_10905aa0()->Virtual5(Unknown08);
            Unknown08 = 0;
            Unknown04 = 0;
        }
    }

    int Unknown00;
    int Unknown04;
    void** Unknown08;
};

// What the array at +0x0C owns, deleted through its virtual destructor.
class Class_10A59050_Element
{
public:
    virtual ~Class_10A59050_Element();
};

class Class_10E68F74
{
public:
    virtual ~Class_10E68F74() {}

    float Unknown04;
    int Unknown08;
};

class Class_10E69050 : public Class_10E68F74
{
public:
    virtual ~Class_10E69050();

    Class_10BFBD70 Unknown0C;
    int Unknown18;
};

// FUNCTION: 0x10A59050 ??1Class_10E69050@@UAE@XZ
Class_10E69050::~Class_10E69050()
{
    int Count = Unknown0C.Unknown00;
    Unknown18 = 0;
    for (int i = 0; i < Count; i++)
        delete (Class_10A59050_Element*)Unknown0C.Unknown08[i];
}
