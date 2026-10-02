// Game/Unsorted_10AA07A0.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

class Class_10AA0790
{
public:
    Class_10AA0790* FUN_10aa0790();

    void** Unknown00;
};

// Ion Storm's placement new (0x10905C10).
void* operator new(unsigned int Size, const int& Tag, int A, int B, int C, int D);

class Class_10E5D948
{
public:
    virtual Class_10AA0790* FUN_10aa07a0();
};

// FUNCTION: 0x10AA07A0 ?FUN_10aa07a0@Class_10E5D948@@UAEPAVClass_10AA0790@@XZ
Class_10AA0790* Class_10E5D948::FUN_10aa07a0()
{
    Class_10AA0790* Object = (Class_10AA0790*)operator new(sizeof(Class_10AA0790), 0, 0, 0, 0, 0);
    if (Object)
        return Object->FUN_10aa0790();
    return 0;
}
