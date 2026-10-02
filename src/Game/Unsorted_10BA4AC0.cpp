// Game/Unsorted_10BA4AC0.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

class Class_10BA4B00
{
public:
    Class_10BA4B00* FUN_10ba4b00();

    void** Unknown00;
};

// Ion Storm's placement new (0x10905C10).
void* operator new(unsigned int Size, const int& Tag, int A, int B, int C, int D);

class Class_10E8C6CC
{
public:
    virtual Class_10BA4B00* FUN_10ba4ac0();
};

// FUNCTION: 0x10BA4AC0 ?FUN_10ba4ac0@Class_10E8C6CC@@UAEPAVClass_10BA4B00@@XZ
Class_10BA4B00* Class_10E8C6CC::FUN_10ba4ac0()
{
    Class_10BA4B00* Object = (Class_10BA4B00*)operator new(sizeof(Class_10BA4B00), 0, 0, 0, 0, 0);
    if (Object)
        return Object->FUN_10ba4b00();
    return 0;
}
