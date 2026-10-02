// Game/Unsorted_10BA41F0.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

class Class_10BA4230
{
public:
    Class_10BA4230* FUN_10ba4230();

    void** Unknown00;
};

// Ion Storm's placement new (0x10905C10).
void* operator new(unsigned int Size, const int& Tag, int A, int B, int C, int D);

class Class_10E8C668
{
public:
    virtual Class_10BA4230* FUN_10ba41f0();
};

// FUNCTION: 0x10BA41F0 ?FUN_10ba41f0@Class_10E8C668@@UAEPAVClass_10BA4230@@XZ
Class_10BA4230* Class_10E8C668::FUN_10ba41f0()
{
    Class_10BA4230* Object = (Class_10BA4230*)operator new(sizeof(Class_10BA4230), 0, 0, 0, 0, 0);
    if (Object)
        return Object->FUN_10ba4230();
    return 0;
}
