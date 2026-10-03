// Game/Unsorted_10B59E30.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

class Class_10E88900
{
public:
    Class_10E88900();

    virtual ~Class_10E88900();

    char Unknown04[0x2C8];
};

class Class_10B59FA0_Member
{
public:
    virtual void Virtual0();
    virtual void Virtual1();
    virtual void Virtual2();
};

class Class_10B59F20_Member
{
public:
    Class_10B59F20_Member(Class_10B59FA0_Member* In = 0) : Unknown00(In)
    {
        if (Unknown00)
            Unknown00->Virtual1();
    }
    ~Class_10B59F20_Member()
    {
        if (Unknown00)
            Unknown00->Virtual2();
    }

    Class_10B59FA0_Member* Unknown00;
};

class Class_10E82480 : public Class_10E88900
{
public:
    Class_10E82480();

    virtual ~Class_10E82480();

    int Unknown2CC;
    int Unknown2D0;
    int Unknown2D4;
    Class_10B59F20_Member Unknown2D8;
};

// FUNCTION: 0x10B59F20 ??0Class_10E82480@@QAE@XZ
Class_10E82480::Class_10E82480()
    : Unknown2CC(0), Unknown2D0(0), Unknown2D4(0)
{
}
