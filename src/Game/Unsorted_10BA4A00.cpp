// Game/Unsorted_10BA4A00.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

class Class_10BA4A40
{
public:
    Class_10BA4A40* FUN_10ba4a40();

    void** Unknown00;
};

// Ion Storm's placement new (0x10905C10).
void* operator new(unsigned int Size, const int& Tag, int A, int B, int C, int D);

class Class_10E8C6C4
{
public:
    virtual Class_10BA4A40* FUN_10ba4a00();
};

// FUNCTION: 0x10BA4A00 ?FUN_10ba4a00@Class_10E8C6C4@@UAEPAVClass_10BA4A40@@XZ
Class_10BA4A40* Class_10E8C6C4::FUN_10ba4a00()
{
    Class_10BA4A40* Object = (Class_10BA4A40*)operator new(sizeof(Class_10BA4A40), 0, 0, 0, 0, 0);
    if (Object)
        return Object->FUN_10ba4a40();
    return 0;
}
