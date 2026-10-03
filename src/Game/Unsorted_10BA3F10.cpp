// Game/Unsorted_10BA3F10.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

// Ion Storm's placement new and its delete (0x10905C10; the delete folded into ::operator delete).
void* operator new(unsigned int Size, const int& Tag, int A, int B, int C, int D);

void operator delete(void* Ptr, const int& Tag, int A, int B, int C, int D);

extern void* DAT_10e8c4e0[];

class Class_10E98530
{
public:
    Class_10E98530();

    void* Unknown00;
    int Unknown04;
    int Unknown08;
    int Unknown0C;
};

class Class_10E8C4E0 : public Class_10E98530
{
public:
    Class_10E8C4E0()
    {
        Unknown00 = DAT_10e8c4e0;
    }
};

class Class_10E8C5EC
{
public:
    virtual Class_10E8C4E0* FUN_10ba3f10(int A, int B);
};

// FUNCTION: 0x10BA3F10 ?FUN_10ba3f10@Class_10E8C5EC@@UAEPAVClass_10E8C4E0@@HH@Z
Class_10E8C4E0* Class_10E8C5EC::FUN_10ba3f10(int A, int B)
{
    return new(0, 0, 0, 0, 0) Class_10E8C4E0;
}
