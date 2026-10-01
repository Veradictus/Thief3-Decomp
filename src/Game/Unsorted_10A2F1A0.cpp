// Game/Unsorted_10A2F1A0.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

class Class_10E66500
{
public:
    virtual void Virtual0();
    virtual void Virtual1();
    virtual int FUN_10a2f1a0(Class_10E66500* Other);

    char Unknown04[4];
    char Unknown08;
};

// FUNCTION: 0x10A2F1A0 ?FUN_10a2f1a0@Class_10E66500@@UAEHPAV1@@Z
int Class_10E66500::FUN_10a2f1a0(Class_10E66500* Other)
{
    if (Unknown08 == Other->Unknown08 && FUN_10a2f1a0(Other))
        return 1;
    return 0;
}
