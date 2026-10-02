// Game/Unsorted_10BA42B0.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

class Class_10BA42F0
{
public:
    Class_10BA42F0* FUN_10ba42f0();

    void** Unknown00;
};

// Ion Storm's placement new (0x10905C10).
void* operator new(unsigned int Size, const int& Tag, int A, int B, int C, int D);

class Class_10E8C670
{
public:
    virtual Class_10BA42F0* FUN_10ba42b0();
};

// FUNCTION: 0x10BA42B0 ?FUN_10ba42b0@Class_10E8C670@@UAEPAVClass_10BA42F0@@XZ
Class_10BA42F0* Class_10E8C670::FUN_10ba42b0()
{
    Class_10BA42F0* Object = (Class_10BA42F0*)operator new(sizeof(Class_10BA42F0), 0, 0, 0, 0, 0);
    if (Object)
        return Object->FUN_10ba42f0();
    return 0;
}
