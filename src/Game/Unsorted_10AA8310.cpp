// Game/Unsorted_10AA8310.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

class Class_1090A780
{
public:
    Class_1090A780(const Class_1090A780& Other);
    ~Class_1090A780();

    char* Unknown00;
};

class Class_10AB3800
{
public:
    Class_1090A780 FUN_10ab3800();

    char Unknown00[0xC];
};

class Class_10AA83E0
{
public:
    Class_1090A780 FUN_10aa83e0();

    char Unknown00[0x20];
    Class_10AB3800 Unknown20;
};

class Class_10E65574
{
public:
    virtual void Virtual0();
    virtual Class_1090A780 FUN_10b34b10();

    Class_1090A780 Unknown04;
};

class Class_10AA8400
{
public:
    Class_1090A780 FUN_10aa8400();

    char Unknown00[0x20];
    Class_10E65574 Unknown20;
};

// FUNCTION: 0x10AA83E0 ?FUN_10aa83e0@Class_10AA83E0@@QAE?AVClass_1090A780@@XZ
Class_1090A780 Class_10AA83E0::FUN_10aa83e0()
{
    return Unknown20.FUN_10ab3800();
}

// FUNCTION: 0x10AA8400 ?FUN_10aa8400@Class_10AA8400@@QAE?AVClass_1090A780@@XZ
Class_1090A780 Class_10AA8400::FUN_10aa8400()
{
    return Unknown20.Class_10E65574::FUN_10b34b10();
}
