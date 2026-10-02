// Game/Unsorted_10BA4C40_2.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

class Class_10E8C884
{
public:
    Class_10E8C884* FUN_10ba4c80();

    void** Unknown00;
};

// Ion Storm's placement new (0x10905C10).
void* operator new(unsigned int Size, const int& Tag, int A, int B, int C, int D);

class Class_10E8C6DC
{
public:
    virtual Class_10E8C884* FUN_10ba4c40();
};

// FUNCTION: 0x10BA4C40 ?FUN_10ba4c40@Class_10E8C6DC@@UAEPAVClass_10E8C884@@XZ
Class_10E8C884* Class_10E8C6DC::FUN_10ba4c40()
{
    Class_10E8C884* Object = (Class_10E8C884*)operator new(sizeof(Class_10E8C884), 0, 0, 0, 0, 0);
    if (Object)
        return Object->FUN_10ba4c80();
    return 0;
}
