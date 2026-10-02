// Game/Unsorted_10BA49A0.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

class Class_10BA49E0
{
public:
    Class_10BA49E0* FUN_10ba49e0();

    void** Unknown00;
};

// Ion Storm's placement new (0x10905C10).
void* operator new(unsigned int Size, const int& Tag, int A, int B, int C, int D);

class Class_10E8C6C0
{
public:
    virtual Class_10BA49E0* FUN_10ba49a0();
};

// FUNCTION: 0x10BA49A0 ?FUN_10ba49a0@Class_10E8C6C0@@UAEPAVClass_10BA49E0@@XZ
Class_10BA49E0* Class_10E8C6C0::FUN_10ba49a0()
{
    Class_10BA49E0* Object = (Class_10BA49E0*)operator new(sizeof(Class_10BA49E0), 0, 0, 0, 0, 0);
    if (Object)
        return Object->FUN_10ba49e0();
    return 0;
}
