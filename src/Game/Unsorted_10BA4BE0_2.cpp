// Game/Unsorted_10BA4BE0_2.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

class Class_10E8C878
{
public:
    Class_10E8C878* FUN_10ba4c20();

    void** Unknown00;
};

// Ion Storm's placement new (0x10905C10).
void* operator new(unsigned int Size, const int& Tag, int A, int B, int C, int D);

class Class_10E8C6D8
{
public:
    virtual Class_10E8C878* FUN_10ba4be0();
};

// FUNCTION: 0x10BA4BE0 ?FUN_10ba4be0@Class_10E8C6D8@@UAEPAVClass_10E8C878@@XZ
Class_10E8C878* Class_10E8C6D8::FUN_10ba4be0()
{
    Class_10E8C878* Object = (Class_10E8C878*)operator new(sizeof(Class_10E8C878), 0, 0, 0, 0, 0);
    if (Object)
        return Object->FUN_10ba4c20();
    return 0;
}
