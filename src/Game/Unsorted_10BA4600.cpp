// Game/Unsorted_10BA4600.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

class Class_10BA4640
{
public:
    Class_10BA4640* FUN_10ba4640();

    void** Unknown00;
};

// Ion Storm's placement new (0x10905C10).
void* operator new(unsigned int Size, const int& Tag, int A, int B, int C, int D);

class Class_10E8C698
{
public:
    virtual Class_10BA4640* FUN_10ba4600();
};

// FUNCTION: 0x10BA4600 ?FUN_10ba4600@Class_10E8C698@@UAEPAVClass_10BA4640@@XZ
Class_10BA4640* Class_10E8C698::FUN_10ba4600()
{
    Class_10BA4640* Object = (Class_10BA4640*)operator new(sizeof(Class_10BA4640), 0, 0, 0, 0, 0);
    if (Object)
        return Object->FUN_10ba4640();
    return 0;
}
