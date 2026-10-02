// Game/Unsorted_10BA4370.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

class Class_10BA43B0
{
public:
    Class_10BA43B0* FUN_10ba43b0();

    void** Unknown00;
};

// Ion Storm's placement new (0x10905C10).
void* operator new(unsigned int Size, const int& Tag, int A, int B, int C, int D);

class Class_10E8C678
{
public:
    virtual Class_10BA43B0* FUN_10ba4370();
};

// FUNCTION: 0x10BA4370 ?FUN_10ba4370@Class_10E8C678@@UAEPAVClass_10BA43B0@@XZ
Class_10BA43B0* Class_10E8C678::FUN_10ba4370()
{
    Class_10BA43B0* Object = (Class_10BA43B0*)operator new(sizeof(Class_10BA43B0), 0, 0, 0, 0, 0);
    if (Object)
        return Object->FUN_10ba43b0();
    return 0;
}
