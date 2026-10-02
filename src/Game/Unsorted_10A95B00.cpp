// Game/Unsorted_10A95B00.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

class TimeManager
{
public:
    static TimeManager* Instance();
    bool IsPaused();
};

class Class_10E6CE78
{
public:
    virtual void Virtual0();
    virtual void Virtual1();
    virtual void Virtual2();
    virtual void Virtual3();
    virtual void Virtual4();
    virtual void Virtual5();
    virtual bool FUN_10a95b40(int p1, int p2);
};

class Class_10A95AF0
{
public:
    Class_10A95AF0* FUN_10a95af0();

    void** Unknown00;
};

// Ion Storm's placement new (0x10905C10).
void* operator new(unsigned int Size, const int& Tag, int A, int B, int C, int D);

class Class_10E5D9DC
{
public:
    virtual Class_10A95AF0* FUN_10a95b00();
};

// FUNCTION: 0x10A95B00 ?FUN_10a95b00@Class_10E5D9DC@@UAEPAVClass_10A95AF0@@XZ
Class_10A95AF0* Class_10E5D9DC::FUN_10a95b00()
{
    Class_10A95AF0* Object = (Class_10A95AF0*)operator new(sizeof(Class_10A95AF0), 0, 0, 0, 0, 0);
    if (Object)
        return Object->FUN_10a95af0();
    return 0;
}

// FUNCTION: 0x10A95B40 ?FUN_10a95b40@Class_10E6CE78@@UAE_NHH@Z
bool Class_10E6CE78::FUN_10a95b40(int p1, int p2)
{
    return TimeManager::Instance()->IsPaused() != 0;
}
