// Game/Unsorted_10A2ED50.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

struct Struct_10A2ED50
{
    char Unknown00[0x8C];
    unsigned int Unknown8C;
};

int FUN_10a2e900(void* p1);

class Class_10E662D0
{
public:
    virtual void Virtual0();
    virtual void Virtual1();
    virtual int FUN_10a2ed70(Class_10E662D0* Other);

    int Unknown04;
};

// FUNCTION: 0x10A2ED50 ?FUN_10a2ed50@@YAHPAUStruct_10A2ED50@@@Z
int FUN_10a2ed50(Struct_10A2ED50* p1)
{
    if (p1->Unknown8C & 0x2000)
        return -1;
    return FUN_10a2e900(p1);
}

// FUNCTION: 0x10A2ED70 ?FUN_10a2ed70@Class_10E662D0@@UAEHPAV1@@Z
int Class_10E662D0::FUN_10a2ed70(Class_10E662D0* Other)
{
    if (Unknown04 != 0 && Other->Unknown04 != 0 && Unknown04 != Other->Unknown04)
        return 0;
    return 1;
}
