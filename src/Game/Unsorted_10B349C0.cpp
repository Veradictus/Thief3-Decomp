// Game/Unsorted_10B349C0.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

class Class_1090A780
{
public:
    Class_1090A780(const Class_1090A780& Other);
    ~Class_1090A780();

    int* Unknown00;
};

class Class_109081E0 : public Class_1090A780
{
public:
    Class_109081E0(const char* In);
};

extern const char DAT_10e795b0[];

class Class_10E7C178
{
public:
    virtual void Virtual0();
    virtual void Virtual1();
    virtual void Virtual2();
    virtual Class_109081E0 FUN_10b34a30();

    Class_109081E0 Unknown04;
};

// FUNCTION: 0x10B34A30 ?FUN_10b34a30@Class_10E7C178@@UAE?AVClass_109081E0@@XZ
Class_109081E0 Class_10E7C178::FUN_10b34a30()
{
    if (Unknown04.Unknown00 && Unknown04.Unknown00[-1] > 0)
        return Unknown04;
    return Class_109081E0(DAT_10e795b0);
}
