// Game/Unsorted_10BA3FB0.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

// Ion Storm's placement new and its delete (0x10905C10; the delete folded into ::operator delete).
void* operator new(unsigned int Size, const int& Tag, int A, int B, int C, int D);

void operator delete(void* Ptr, const int& Tag, int A, int B, int C, int D);

extern void* DAT_10e8c51c[];

class Class_10E98530
{
public:
    Class_10E98530();

    void* Unknown00;
    int Unknown04;
    int Unknown08;
    int Unknown0C;
};

class Class_10E8C51C : public Class_10E98530
{
public:
    Class_10E8C51C()
    {
        Unknown00 = DAT_10e8c51c;
    }
};

class Class_10E8C5F0
{
public:
    virtual Class_10E8C51C* FUN_10ba3fb0(int A, int B);
};

// FUNCTION: 0x10BA3FB0 ?FUN_10ba3fb0@Class_10E8C5F0@@UAEPAVClass_10E8C51C@@HH@Z
Class_10E8C51C* Class_10E8C5F0::FUN_10ba3fb0(int A, int B)
{
    return new(0, 0, 0, 0, 0) Class_10E8C51C;
}
