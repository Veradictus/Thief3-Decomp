// Game/Unsorted_10BA4940.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

class Class_10BA4980
{
public:
    Class_10BA4980* FUN_10ba4980();

    void** Unknown00;
};

// Ion Storm's placement new (0x10905C10).
void* operator new(unsigned int Size, const int& Tag, int A, int B, int C, int D);

class Class_10E8C6BC
{
public:
    virtual Class_10BA4980* FUN_10ba4940();
};

// FUNCTION: 0x10BA4940 ?FUN_10ba4940@Class_10E8C6BC@@UAEPAVClass_10BA4980@@XZ
Class_10BA4980* Class_10E8C6BC::FUN_10ba4940()
{
    Class_10BA4980* Object = (Class_10BA4980*)operator new(sizeof(Class_10BA4980), 0, 0, 0, 0, 0);
    if (Object)
        return Object->FUN_10ba4980();
    return 0;
}
