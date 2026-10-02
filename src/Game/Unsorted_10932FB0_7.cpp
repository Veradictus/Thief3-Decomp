// Game/Unsorted_10932FB0_7.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

class Class_10E49D44
{
public:
    ~Class_10E49D44();

    virtual void Virtual0();
    virtual int FUN_109331a0();

    int Unknown04;
};

// FUNCTION: 0x109331A0 ?FUN_109331a0@Class_10E49D44@@UAEHXZ
int Class_10E49D44::FUN_109331a0()
{
    int Count = --Unknown04;
    if (Count == 0)
        delete this;
    return Count;
}
