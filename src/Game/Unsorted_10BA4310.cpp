// Game/Unsorted_10BA4310.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

class Class_10BA4350
{
public:
    Class_10BA4350* FUN_10ba4350();

    void** Unknown00;
};

// Ion Storm's placement new (0x10905C10).
void* operator new(unsigned int Size, const int& Tag, int A, int B, int C, int D);

class Class_10E8C674
{
public:
    virtual Class_10BA4350* FUN_10ba4310();
};

// FUNCTION: 0x10BA4310 ?FUN_10ba4310@Class_10E8C674@@UAEPAVClass_10BA4350@@XZ
Class_10BA4350* Class_10E8C674::FUN_10ba4310()
{
    Class_10BA4350* Object = (Class_10BA4350*)operator new(sizeof(Class_10BA4350), 0, 0, 0, 0, 0);
    if (Object)
        return Object->FUN_10ba4350();
    return 0;
}
