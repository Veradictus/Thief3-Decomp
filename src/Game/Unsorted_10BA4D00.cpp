// Game/Unsorted_10BA4D00.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

class Class_10BA4D40
{
public:
    Class_10BA4D40* FUN_10ba4d40();

    void** Unknown00;
};

// Ion Storm's placement new (0x10905C10).
void* operator new(unsigned int Size, const int& Tag, int A, int B, int C, int D);

class Class_10E8C6E4
{
public:
    virtual Class_10BA4D40* FUN_10ba4d00();
};

// FUNCTION: 0x10BA4D00 ?FUN_10ba4d00@Class_10E8C6E4@@UAEPAVClass_10BA4D40@@XZ
Class_10BA4D40* Class_10E8C6E4::FUN_10ba4d00()
{
    Class_10BA4D40* Object = (Class_10BA4D40*)operator new(sizeof(Class_10BA4D40), 0, 0, 0, 0, 0);
    if (Object)
        return Object->FUN_10ba4d40();
    return 0;
}
