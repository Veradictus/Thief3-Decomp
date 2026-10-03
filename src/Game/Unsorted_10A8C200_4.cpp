// Game/Unsorted_10A8C200_4.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

class Class_10E6C6FC
{
public:
    virtual void Virtual0();
    virtual void Virtual1();
    virtual int FUN_10a8c200(int p1, Class_10E6C6FC* p2);

    char Unknown04[4];
    int Unknown08;
};

// FUNCTION: 0x10A8C200 ?FUN_10a8c200@Class_10E6C6FC@@UAEHHPAV1@@Z
int Class_10E6C6FC::FUN_10a8c200(int p1, Class_10E6C6FC* p2)
{
    switch (p1)
    {
    case 1:
        return Unknown08 == p2->Unknown08;
    case 6:
        return Unknown08 != p2->Unknown08;
    case 2:
        return Unknown08 < p2->Unknown08;
    case 3:
        return Unknown08 <= p2->Unknown08;
    case 4:
        return Unknown08 > p2->Unknown08;
    case 5:
        return Unknown08 >= p2->Unknown08;
    }
    return 0;
}
