// Game/Unsorted_10BA5290.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

class Class_10BA52D0
{
public:
    Class_10BA52D0* FUN_10ba52d0();

    void** Unknown00;
};

// Ion Storm's placement new (0x10905C10).
void* operator new(unsigned int Size, const int& Tag, int A, int B, int C, int D);

class Class_10E8C720
{
public:
    virtual Class_10BA52D0* FUN_10ba5290();
};

// FUNCTION: 0x10BA5290 ?FUN_10ba5290@Class_10E8C720@@UAEPAVClass_10BA52D0@@XZ
Class_10BA52D0* Class_10E8C720::FUN_10ba5290()
{
    Class_10BA52D0* Object = (Class_10BA52D0*)operator new(sizeof(Class_10BA52D0), 0, 0, 0, 0, 0);
    if (Object)
        return Object->FUN_10ba52d0();
    return 0;
}
