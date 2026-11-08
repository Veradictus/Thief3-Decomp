// Game/StatsListenerInitialization.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

// Game/Unsorted_10A16FA0.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

class Class_10E9BB80
{
public:
    Class_10E9BB80() {}
    virtual void FUN_10c3e9f0(int A, int* B, int* C);
};

class Class_10EBFF38 : public Class_10E9BB80
{
public:
    Class_10EBFF38() {}
    virtual int CompareUnsigned(unsigned int* A, unsigned int* B);
    virtual void Virtual2();
};

class Class_10A163F0
{
public:
    Class_10A163F0()
        : m_Collisions(0), m_Count(0), m_BucketCount(0), m_FixedSize(false), m_Buckets(0)
    {
    }

    void Rehash(int Size);

    int m_Collisions;
    int m_Count;
    int m_BucketBits;
    int m_BucketCount;
    bool m_FixedSize;
    char Pad11[0x3];
    void** m_Buckets;
};

class Class_10A16BF0 : public Class_10A163F0
{
public:
    Class_10A16BF0()
    {
        Rehash(0x40);
    }

    void FUN_10a165c0(int A);

    ~Class_10A16BF0()
    {
        FUN_10a165c0(0x40);
        m_Collisions = 0;
        m_Count = 0;
        m_BucketCount = 0;
        m_Buckets = 0;
    }

    Class_10EBFF38 m_KeyTraits;
};

class Class_10BA12F0
{
public:
    void FUN_10ba12f0();

    void* Current;
    void* Container;
    int Index;
};

class Class_10E5D654;

class Class_10F46DA0
{
public:
    virtual void Virtual0();
    virtual void Virtual1(Class_10E5D654* Listener, int Code, int A, int B);
};

extern Class_10F46DA0* DAT_10f46da0;

class Class_10E5D654
{
public:
    Class_10E5D654();
    ~Class_10E5D654();

    virtual void FUN_10a173e0(int p1, int p2, int p3, int p4);

    void FUN_10a17210();

    Class_10A16BF0 Unknown04;
    Class_10BA12F0 Unknown20;
};

// FUNCTION: 0x10A172D0 ??0Class_10E5D654@@QAE@XZ
Class_10E5D654::Class_10E5D654()
{
    Unknown04.FUN_10a165c0(0x40);
    Class_10BA12F0* Queue = &Unknown20;
    Queue->Container = &Unknown04;
    Queue->FUN_10ba12f0();
    DAT_10f46da0->Virtual1(this, 0x5a, -1, -1);
}
