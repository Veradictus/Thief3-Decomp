// Game/Unsorted_10BA4510.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

class Class_10BA4550
{
public:
    Class_10BA4550* FUN_10ba4550();

    void** Unknown00;
};

// Ion Storm's placement new (0x10905C10).
void* operator new(unsigned int Size, const int& Tag, int A, int B, int C, int D);

class Class_10E8C68C
{
public:
    virtual Class_10BA4550* FUN_10ba4510();
};

// FUNCTION: 0x10BA4510 ?FUN_10ba4510@Class_10E8C68C@@UAEPAVClass_10BA4550@@XZ
Class_10BA4550* Class_10E8C68C::FUN_10ba4510()
{
    Class_10BA4550* Object = (Class_10BA4550*)operator new(sizeof(Class_10BA4550), 0, 0, 0, 0, 0);
    if (Object)
        return Object->FUN_10ba4550();
    return 0;
}
