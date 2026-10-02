// Game/Unsorted_10BA4E20.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

class Class_10BA4E60
{
public:
    Class_10BA4E60* FUN_10ba4e60();

    void** Unknown00;
};

// Ion Storm's placement new (0x10905C10).
void* operator new(unsigned int Size, const int& Tag, int A, int B, int C, int D);

class Class_10E8C6F0
{
public:
    virtual Class_10BA4E60* FUN_10ba4e20();
};

// FUNCTION: 0x10BA4E20 ?FUN_10ba4e20@Class_10E8C6F0@@UAEPAVClass_10BA4E60@@XZ
Class_10BA4E60* Class_10E8C6F0::FUN_10ba4e20()
{
    Class_10BA4E60* Object = (Class_10BA4E60*)operator new(sizeof(Class_10BA4E60), 0, 0, 0, 0, 0);
    if (Object)
        return Object->FUN_10ba4e60();
    return 0;
}
