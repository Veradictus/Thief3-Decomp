// Game/Unsorted_10C12970.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

class Class_10E8C4A4
{
public:
    virtual void Virtual0();
    virtual void Virtual1();
    virtual int FUN_10c12970(int A, Class_10E8C4A4* Other);

    char Unknown04[4];
    int Unknown08;
};

// FUNCTION: 0x10C12970 ?FUN_10c12970@Class_10E8C4A4@@UAEHHPAV1@@Z
int Class_10E8C4A4::FUN_10c12970(int A, Class_10E8C4A4* Other)
{
    switch (A)
    {
    case 1:
        if (Other->Unknown08 == Unknown08)
            return 1;
        break;
    case 6:
        if (Other->Unknown08 != Unknown08)
            return 1;
        break;
    }
    return 0;
}
