// Game/Unsorted_10C3CF10_2.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

class Class_10E9AF80
{
public:
    virtual void Virtual0();
    virtual void Virtual1();
    virtual void Virtual2();
    virtual int FUN_10c3cf10(Class_10E9AF80* Other);
    virtual void Virtual4();
    virtual void FUN_10c3cfe0(float* A, float* B, float* C);

    char Unknown04[8];
    float Unknown0C;
    float Unknown10;
    float Unknown14;
    float Unknown18;
};

// FUNCTION: 0x10C3CF10 ?FUN_10c3cf10@Class_10E9AF80@@UAEHPAV1@@Z
int Class_10E9AF80::FUN_10c3cf10(Class_10E9AF80* Other)
{
    if (Other->Unknown0C == Unknown0C && Other->Unknown10 == Unknown10)
        return 1;
    return 0;
}
