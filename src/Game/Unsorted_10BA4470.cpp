// Game/Unsorted_10BA4470.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

class Class_10BA44B0
{
public:
    Class_10BA44B0* FUN_10ba44b0();

    void** Unknown00;
};

// Ion Storm's placement new (0x10905C10).
void* operator new(unsigned int Size, const int& Tag, int A, int B, int C, int D);

class Class_10E8C684
{
public:
    virtual Class_10BA44B0* FUN_10ba4470();
};

// FUNCTION: 0x10BA4470 ?FUN_10ba4470@Class_10E8C684@@UAEPAVClass_10BA44B0@@XZ
Class_10BA44B0* Class_10E8C684::FUN_10ba4470()
{
    Class_10BA44B0* Object = (Class_10BA44B0*)operator new(sizeof(Class_10BA44B0), 0, 0, 0, 0, 0);
    if (Object)
        return Object->FUN_10ba44b0();
    return 0;
}
