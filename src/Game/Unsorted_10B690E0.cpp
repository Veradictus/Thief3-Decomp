// Game/Unsorted_10B690E0.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
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

class Class_10E858D0 : public Class_10E88900
{
public:
    Class_10E858D0();

    virtual ~Class_10E858D0();

    int Unknown2CC;
    int Unknown2D0;
    int Unknown2D4;
    int Unknown2D8;
    int Unknown2DC;
    int Unknown2E0;
    int Unknown2E4;
    int Unknown2E8;
    int Unknown2EC;
    int Unknown2F0;
    int Unknown2F4;
    Class_10B59F20_Member Unknown2F8;
};

// FUNCTION: 0x10B69200 ??0Class_10E858D0@@QAE@XZ
Class_10E858D0::Class_10E858D0()
    : Unknown2CC(0), Unknown2D0(0), Unknown2D4(0), Unknown2D8(0), Unknown2DC(0), Unknown2E0(0),
      Unknown2E4(0), Unknown2E8(0), Unknown2EC(0), Unknown2F0(0), Unknown2F4(0)
{
}
