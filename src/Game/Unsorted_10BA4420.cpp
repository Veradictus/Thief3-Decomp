// Game/Unsorted_10BA4420.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

class Class_10BA4460
{
public:
    Class_10BA4460* FUN_10ba4460();

    void** Unknown00;
};

// Ion Storm's placement new (0x10905C10).
void* operator new(unsigned int Size, const int& Tag, int A, int B, int C, int D);

class Class_10E8C680
{
public:
    virtual Class_10BA4460* FUN_10ba4420();
};

// FUNCTION: 0x10BA4420 ?FUN_10ba4420@Class_10E8C680@@UAEPAVClass_10BA4460@@XZ
Class_10BA4460* Class_10E8C680::FUN_10ba4420()
{
    Class_10BA4460* Object = (Class_10BA4460*)operator new(sizeof(Class_10BA4460), 0, 0, 0, 0, 0);
    if (Object)
        return Object->FUN_10ba4460();
    return 0;
}
