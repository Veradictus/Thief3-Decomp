// Game/Unsorted_10C55090.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

class Object_10C552D0_Member
{
public:
    virtual void Virtual0();
    virtual void Virtual1();
    virtual void Virtual2();
};

class Class_10C552D0_Member
{
public:
    ~Class_10C552D0_Member()
    {
        if (Unknown00)
            Unknown00->Virtual2();
    }

    Object_10C552D0_Member* Unknown00;
};

class Class_10A04240
{
public:
    ~Class_10A04240();

    char Unknown00[0x4C];
};

class Class_10C552D0 : public Class_10A04240
{
public:
    ~Class_10C552D0();

    Class_10C552D0_Member Unknown4C;
};

// FUNCTION: 0x10C552D0 ??1Class_10C552D0@@QAE@XZ
Class_10C552D0::~Class_10C552D0()
{
}
