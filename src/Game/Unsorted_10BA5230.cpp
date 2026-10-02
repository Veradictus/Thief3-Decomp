// Game/Unsorted_10BA5230.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

class Class_10BA5270
{
public:
    Class_10BA5270* FUN_10ba5270();

    void** Unknown00;
};

// Ion Storm's placement new (0x10905C10).
void* operator new(unsigned int Size, const int& Tag, int A, int B, int C, int D);

class Class_10E8C71C
{
public:
    virtual Class_10BA5270* FUN_10ba5230();
};

// FUNCTION: 0x10BA5230 ?FUN_10ba5230@Class_10E8C71C@@UAEPAVClass_10BA5270@@XZ
Class_10BA5270* Class_10E8C71C::FUN_10ba5230()
{
    Class_10BA5270* Object = (Class_10BA5270*)operator new(sizeof(Class_10BA5270), 0, 0, 0, 0, 0);
    if (Object)
        return Object->FUN_10ba5270();
    return 0;
}
