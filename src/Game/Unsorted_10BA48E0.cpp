// Game/Unsorted_10BA48E0.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

class Class_10BA4920
{
public:
    Class_10BA4920* FUN_10ba4920();

    void** Unknown00;
};

// Ion Storm's placement new (0x10905C10).
void* operator new(unsigned int Size, const int& Tag, int A, int B, int C, int D);

class Class_10E8C6B8
{
public:
    virtual Class_10BA4920* FUN_10ba48e0();
};

// FUNCTION: 0x10BA48E0 ?FUN_10ba48e0@Class_10E8C6B8@@UAEPAVClass_10BA4920@@XZ
Class_10BA4920* Class_10E8C6B8::FUN_10ba48e0()
{
    Class_10BA4920* Object = (Class_10BA4920*)operator new(sizeof(Class_10BA4920), 0, 0, 0, 0, 0);
    if (Object)
        return Object->FUN_10ba4920();
    return 0;
}
