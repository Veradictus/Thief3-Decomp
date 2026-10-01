// Game/Unsorted_10A89570_3.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

class Class_10E6C5D0
{
public:
    virtual void Virtual0();
    virtual void Virtual1();
    virtual int FUN_10a8a510(int p1, Class_10E6C5D0* p2);

    Class_10E6C5D0* Unknown04;
};

// FUNCTION: 0x10A8A510 ?FUN_10a8a510@Class_10E6C5D0@@UAEHHPAV1@@Z
int Class_10E6C5D0::FUN_10a8a510(int p1, Class_10E6C5D0* p2)
{
    if (!Unknown04)
        return 0;
    return Unknown04->FUN_10a8a510(p1, p2->Unknown04);
}
