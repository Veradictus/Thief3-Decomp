// Game/Unsorted_10BA5110.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

class Class_10BA5150
{
public:
    Class_10BA5150* FUN_10ba5150();

    void** Unknown00;
};

// Ion Storm's placement new (0x10905C10).
void* operator new(unsigned int Size, const int& Tag, int A, int B, int C, int D);

class Class_10E8C710
{
public:
    virtual Class_10BA5150* FUN_10ba5110();
};

// FUNCTION: 0x10BA5110 ?FUN_10ba5110@Class_10E8C710@@UAEPAVClass_10BA5150@@XZ
Class_10BA5150* Class_10E8C710::FUN_10ba5110()
{
    Class_10BA5150* Object = (Class_10BA5150*)operator new(sizeof(Class_10BA5150), 0, 0, 0, 0, 0);
    if (Object)
        return Object->FUN_10ba5150();
    return 0;
}
