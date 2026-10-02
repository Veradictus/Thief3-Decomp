// Game/Unsorted_10BA52F0.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

class Class_10BA5330
{
public:
    Class_10BA5330* FUN_10ba5330();

    void** Unknown00;
};

// Ion Storm's placement new (0x10905C10).
void* operator new(unsigned int Size, const int& Tag, int A, int B, int C, int D);

class Class_10E8C724
{
public:
    virtual Class_10BA5330* FUN_10ba52f0();
};

// FUNCTION: 0x10BA52F0 ?FUN_10ba52f0@Class_10E8C724@@UAEPAVClass_10BA5330@@XZ
Class_10BA5330* Class_10E8C724::FUN_10ba52f0()
{
    Class_10BA5330* Object = (Class_10BA5330*)operator new(sizeof(Class_10BA5330), 0, 0, 0, 0, 0);
    if (Object)
        return Object->FUN_10ba5330();
    return 0;
}
