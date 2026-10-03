// Game/Unsorted_10AA6180.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

// Ion Storm's placement new (0x10905C10).
void* operator new(unsigned int Size, const int& Tag, int A, int B, int C, int D);

class Class_10B0AED0
{
public:
    Class_10B0AED0() : RefCount(0), Unknown04(0), Unknown08(0), Unknown0C(0) {}
    ~Class_10B0AED0();

    int RefCount;
    int Unknown04;
    int Unknown08;
    int Unknown0C;
};

extern Class_10B0AED0* DAT_10f3a248;

class Class_10E67938
{
public:
    void FUN_10aa6180();
};

// FUNCTION: 0x10AA6180 ?FUN_10aa6180@Class_10E67938@@QAEXXZ
void Class_10E67938::FUN_10aa6180()
{
    if (DAT_10f3a248 == 0)
        DAT_10f3a248 = new(0, 0, 0, 0, 0) Class_10B0AED0;
    DAT_10f3a248->RefCount++;
}
