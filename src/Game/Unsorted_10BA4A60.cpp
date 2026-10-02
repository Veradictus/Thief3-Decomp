// Game/Unsorted_10BA4A60.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

class Class_10BA4AA0
{
public:
    Class_10BA4AA0* FUN_10ba4aa0();

    void** Unknown00;
};

// Ion Storm's placement new (0x10905C10).
void* operator new(unsigned int Size, const int& Tag, int A, int B, int C, int D);

class Class_10E8C6C8
{
public:
    virtual Class_10BA4AA0* FUN_10ba4a60();
};

// FUNCTION: 0x10BA4A60 ?FUN_10ba4a60@Class_10E8C6C8@@UAEPAVClass_10BA4AA0@@XZ
Class_10BA4AA0* Class_10E8C6C8::FUN_10ba4a60()
{
    Class_10BA4AA0* Object = (Class_10BA4AA0*)operator new(sizeof(Class_10BA4AA0), 0, 0, 0, 0, 0);
    if (Object)
        return Object->FUN_10ba4aa0();
    return 0;
}
