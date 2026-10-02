// Game/Unsorted_10BA4DC0.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

class Class_10BA4E00
{
public:
    Class_10BA4E00* FUN_10ba4e00();

    void** Unknown00;
};

// Ion Storm's placement new (0x10905C10).
void* operator new(unsigned int Size, const int& Tag, int A, int B, int C, int D);

class Class_10E8C6EC
{
public:
    virtual Class_10BA4E00* FUN_10ba4dc0();
};

// FUNCTION: 0x10BA4DC0 ?FUN_10ba4dc0@Class_10E8C6EC@@UAEPAVClass_10BA4E00@@XZ
Class_10BA4E00* Class_10E8C6EC::FUN_10ba4dc0()
{
    Class_10BA4E00* Object = (Class_10BA4E00*)operator new(sizeof(Class_10BA4E00), 0, 0, 0, 0, 0);
    if (Object)
        return Object->FUN_10ba4e00();
    return 0;
}
