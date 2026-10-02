// Game/Unsorted_10BA51D0.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

class Class_10BA5210
{
public:
    Class_10BA5210* FUN_10ba5210();

    void** Unknown00;
};

// Ion Storm's placement new (0x10905C10).
void* operator new(unsigned int Size, const int& Tag, int A, int B, int C, int D);

class Class_10E8C718
{
public:
    virtual Class_10BA5210* FUN_10ba51d0();
};

// FUNCTION: 0x10BA51D0 ?FUN_10ba51d0@Class_10E8C718@@UAEPAVClass_10BA5210@@XZ
Class_10BA5210* Class_10E8C718::FUN_10ba51d0()
{
    Class_10BA5210* Object = (Class_10BA5210*)operator new(sizeof(Class_10BA5210), 0, 0, 0, 0, 0);
    if (Object)
        return Object->FUN_10ba5210();
    return 0;
}
