// Game/Unsorted_10C56D00.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

class Class_10C56E40_Field00
{
public:
    virtual void Virtual0();
    virtual void Virtual1();
    virtual void Virtual2();
};

class Class_10C56E40
{
public:
    ~Class_10C56E40();

    Class_10C56E40_Field00* Unknown00;
};

// FUNCTION: 0x10C56E40 ??1Class_10C56E40@@QAE@XZ
Class_10C56E40::~Class_10C56E40()
{
    if (Unknown00)
        Unknown00->Virtual2();
}
