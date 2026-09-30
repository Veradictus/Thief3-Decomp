// Game/Unsorted_10A54D50_2.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

class Class_1090A780
{
public:
    Class_1090A780(const Class_1090A780& Other);
    ~Class_1090A780();

    char* Unknown00;
};

class Class_10A54E80
{
public:
    Class_1090A780 FUN_10a54e80();

    char Unknown00[0x11C];
    Class_1090A780 Unknown11C;
};

// FUNCTION: 0x10A54E80 ?FUN_10a54e80@Class_10A54E80@@QAE?AVClass_1090A780@@XZ
Class_1090A780 Class_10A54E80::FUN_10a54e80()
{
    return Class_1090A780(Unknown11C);
}
