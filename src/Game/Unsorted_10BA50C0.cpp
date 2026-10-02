// Game/Unsorted_10BA50C0.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

class Class_10BA5100
{
public:
    Class_10BA5100* FUN_10ba5100();

    void** Unknown00;
};

// Ion Storm's placement new (0x10905C10).
void* operator new(unsigned int Size, const int& Tag, int A, int B, int C, int D);

class Class_10E8C70C
{
public:
    virtual Class_10BA5100* FUN_10ba50c0();
};

// FUNCTION: 0x10BA50C0 ?FUN_10ba50c0@Class_10E8C70C@@UAEPAVClass_10BA5100@@XZ
Class_10BA5100* Class_10E8C70C::FUN_10ba50c0()
{
    Class_10BA5100* Object = (Class_10BA5100*)operator new(sizeof(Class_10BA5100), 0, 0, 0, 0, 0);
    if (Object)
        return Object->FUN_10ba5100();
    return 0;
}
