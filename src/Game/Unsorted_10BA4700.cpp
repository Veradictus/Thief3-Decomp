// Game/Unsorted_10BA4700.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

class Class_10BA4740
{
public:
    Class_10BA4740* FUN_10ba4740();

    void** Unknown00;
};

// Ion Storm's placement new (0x10905C10).
void* operator new(unsigned int Size, const int& Tag, int A, int B, int C, int D);

class Class_10E8C6A4
{
public:
    virtual Class_10BA4740* FUN_10ba4700();
};

// FUNCTION: 0x10BA4700 ?FUN_10ba4700@Class_10E8C6A4@@UAEPAVClass_10BA4740@@XZ
Class_10BA4740* Class_10E8C6A4::FUN_10ba4700()
{
    Class_10BA4740* Object = (Class_10BA4740*)operator new(sizeof(Class_10BA4740), 0, 0, 0, 0, 0);
    if (Object)
        return Object->FUN_10ba4740();
    return 0;
}
