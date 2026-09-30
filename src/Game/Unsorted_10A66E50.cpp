// Game/Unsorted_10A66E50.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

#include <float.h>

int FUN_10a66c80(void* A, void* B, float Epsilon);

class Class_10E6B4AC
{
public:
    virtual void Virtual0();
    virtual void Virtual1();
    virtual void Virtual2();
    virtual void Virtual3();
    virtual void Virtual4();
    virtual void Virtual5();
    virtual bool FUN_10a66e90(Class_10E6B4AC* Other);

    char Unknown04[4];
    int Unknown08;
};

// FUNCTION: 0x10A66E90 ?FUN_10a66e90@Class_10E6B4AC@@UAE_NPAV1@@Z
bool Class_10E6B4AC::FUN_10a66e90(Class_10E6B4AC* Other)
{
    return FUN_10a66c80(&Unknown08, &Other->Unknown08, FLT_EPSILON) == 1;
}
