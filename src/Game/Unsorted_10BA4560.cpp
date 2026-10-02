// Game/Unsorted_10BA4560.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

class Class_10BA45A0
{
public:
    Class_10BA45A0* FUN_10ba45a0();

    void** Unknown00;
};

// Ion Storm's placement new (0x10905C10).
void* operator new(unsigned int Size, const int& Tag, int A, int B, int C, int D);

class Class_10E8C690
{
public:
    virtual Class_10BA45A0* FUN_10ba4560();
};

// FUNCTION: 0x10BA4560 ?FUN_10ba4560@Class_10E8C690@@UAEPAVClass_10BA45A0@@XZ
Class_10BA45A0* Class_10E8C690::FUN_10ba4560()
{
    Class_10BA45A0* Object = (Class_10BA45A0*)operator new(sizeof(Class_10BA45A0), 0, 0, 0, 0, 0);
    if (Object)
        return Object->FUN_10ba45a0();
    return 0;
}
