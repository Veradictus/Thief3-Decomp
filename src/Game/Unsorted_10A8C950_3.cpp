// Game/Unsorted_10A8C950_3.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

class Class_10E6C740_Member
{
public:
    char Unknown00[0x38];
    int Unknown38;
};

class Class_10E6C740
{
public:
    virtual void Virtual0();
    virtual void Virtual1();
    virtual int FUN_10a8c950(int A, const Class_10E6C740* B);

    Class_10E6C740_Member* Unknown04;
    int Unknown08;
};

// FUNCTION: 0x10A8C950 ?FUN_10a8c950@Class_10E6C740@@UAEHHPBV1@@Z
int Class_10E6C740::FUN_10a8c950(int A, const Class_10E6C740* B)
{
    switch (A)
    {
    case 1:
        return (Unknown04 && (Unknown08 == Unknown04->Unknown38 || B->Unknown08 == Unknown04->Unknown38))
            || B->Unknown08 == Unknown08;
    }
    return 0;
}
