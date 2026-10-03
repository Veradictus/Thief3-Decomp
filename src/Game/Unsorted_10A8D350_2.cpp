// Game/Unsorted_10A8D350_2.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

class Class_1090A780
{
public:
    Class_1090A780(const Class_1090A780& Other);
    ~Class_1090A780();

    char* Unknown00;
};

class Class_109081E0 : public Class_1090A780
{
public:
    Class_109081E0(const char* In);
    Class_109081E0(const Class_1090A780& Other) : Class_1090A780(Other) {}
};

extern Class_1090A780 DAT_10f3a1f8[];

extern const char DAT_10e6c7ec[];

class Class_10E6C7B4
{
public:
    virtual void Virtual0();
    virtual void Virtual1();
    virtual void Virtual2();
    virtual Class_109081E0 FUN_10a8d490();

    int Unknown04;
};

// FUNCTION: 0x10A8D490 ?FUN_10a8d490@Class_10E6C7B4@@UAE?AVClass_109081E0@@XZ
Class_109081E0 Class_10E6C7B4::FUN_10a8d490()
{
    if (Unknown04 >= 0 && Unknown04 < 4)
        return Class_109081E0(DAT_10f3a1f8[Unknown04]);
    return Class_109081E0(DAT_10e6c7ec);
}
