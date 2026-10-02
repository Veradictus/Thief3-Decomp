// Game/Unsorted_10BA3DD0.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

// Ion Storm's placement new and its delete (0x10905C10; the delete folded into ::operator delete).
void* operator new(unsigned int Size, const int& Tag, int A, int B, int C, int D);

void operator delete(void* Ptr, const int& Tag, int A, int B, int C, int D);

extern void* DAT_10e8c468[];

class Class_10e984f4
{
public:
    Class_10e984f4* FUN_10c12a90();

    void* Unknown00;
    int Unknown04;
};

class Class_10E8C468 : public Class_10e984f4
{
public:
    Class_10E8C468()
    {
        FUN_10c12a90();
        Unknown00 = DAT_10e8c468;
    }
};

class Class_10E8C5E4
{
public:
    virtual Class_10E8C468* FUN_10ba3dd0(int A, int B);
};

// FUNCTION: 0x10BA3DD0 ?FUN_10ba3dd0@Class_10E8C5E4@@UAEPAVClass_10E8C468@@HH@Z
Class_10E8C468* Class_10E8C5E4::FUN_10ba3dd0(int A, int B)
{
    return new(0, 0, 0, 0, 0) Class_10E8C468;
}
