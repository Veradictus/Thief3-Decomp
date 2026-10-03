// Game/Unsorted_10C54BB0.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

class Class_10EB7660
{
public:
    Class_10EB7660();

    virtual ~Class_10EB7660();

    int Unknown04;
};

class Class_10C54B70_Object
{
public:
    virtual void Virtual0();
    virtual void Virtual1();
    virtual void Virtual2();
};

class Class_10C54B70_Member
{
public:
    Class_10C54B70_Member(Class_10C54B70_Object* In = 0) : Unknown00(In)
    {
        if (Unknown00)
            Unknown00->Virtual1();
    }
    ~Class_10C54B70_Member()
    {
        if (Unknown00)
            Unknown00->Virtual2();
    }

    Class_10C54B70_Object* Unknown00;
};

class Class_10E9C300 : public Class_10EB7660
{
public:
    Class_10E9C300();

    virtual ~Class_10E9C300();

    Class_10C54B70_Member Unknown08;
};

// FUNCTION: 0x10C54C70 ??1Class_10E9C300@@UAE@XZ
Class_10E9C300::~Class_10E9C300()
{
}
