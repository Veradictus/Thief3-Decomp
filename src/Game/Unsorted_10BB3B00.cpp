// Game/Unsorted_10BB3B00.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

class Class_10905A90_Member
{
public:
    virtual void Virtual0();
    virtual void Virtual1();
    virtual void Virtual2();
    virtual void Virtual3();
    virtual void Virtual4();
    virtual void Virtual5(void* Block);
};

Class_10905A90_Member* FUN_10905aa0();

// Ion Storm's string (0x109081E0): a char pointer to a block allocated 4 bytes before it.
class Class_109081E0
{
public:
    ~Class_109081E0()
    {
        if (Unknown00)
        {
            char* Block = Unknown00 - 4;
            FUN_10905aa0()->Virtual5(Block);
            Unknown00 = 0;
        }
    }

    char* Unknown00;
};

class Class_10E50610
{
public:
    virtual ~Class_10E50610() {}
};

class Class_10BB43E0
{
public:
    ~Class_10BB43E0();

    Class_10E50610 Unknown00;
    Class_109081E0 Unknown04;
};

// FUNCTION: 0x10BB43E0 ??1Class_10BB43E0@@QAE@XZ
Class_10BB43E0::~Class_10BB43E0()
{
}
