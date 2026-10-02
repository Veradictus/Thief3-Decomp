// Game/Unsorted_10C1A3F0.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

class Class_10E98CE0_Member
{
public:
    virtual char Virtual0(int A);
};

class Class_10E98CE0
{
public:
    virtual char FUN_10c1a3f0(int A);

    Class_10E98CE0_Member* Unknown04;
    Class_10E98CE0_Member* Unknown08;
};

// FUNCTION: 0x10C1A3F0 ?FUN_10c1a3f0@Class_10E98CE0@@UAEDH@Z
char Class_10E98CE0::FUN_10c1a3f0(int A)
{
    if (Unknown04->Virtual0(A) == 1)
        return 1;
    return Unknown08->Virtual0(A);
}
