// Game/Unsorted_10BA4FA0.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

class Class_10BA4FE0
{
public:
    Class_10BA4FE0* FUN_10ba4fe0();

    void** Unknown00;
};

// Ion Storm's placement new (0x10905C10).
void* operator new(unsigned int Size, const int& Tag, int A, int B, int C, int D);

class Class_10E8C700
{
public:
    virtual Class_10BA4FE0* FUN_10ba4fa0();
};

// FUNCTION: 0x10BA4FA0 ?FUN_10ba4fa0@Class_10E8C700@@UAEPAVClass_10BA4FE0@@XZ
Class_10BA4FE0* Class_10E8C700::FUN_10ba4fa0()
{
    Class_10BA4FE0* Object = (Class_10BA4FE0*)operator new(sizeof(Class_10BA4FE0), 0, 0, 0, 0, 0);
    if (Object)
        return Object->FUN_10ba4fe0();
    return 0;
}
