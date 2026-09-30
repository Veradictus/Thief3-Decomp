// Game/Class_10AAA130.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

class Class_1090A780
{
public:
    Class_1090A780(const Class_1090A780& Other);
    ~Class_1090A780();

    char* Unknown00;
};

class Class_10AAA130
{
public:
    Class_1090A780 FUN_10aaa130();

    char Unknown00[0x20];
    Class_1090A780 Unknown20;
};

// FUNCTION: 0x10AAA130 ?FUN_10aaa130@Class_10AAA130@@QAE?AVClass_1090A780@@XZ
Class_1090A780 Class_10AAA130::FUN_10aaa130()
{
    return Class_1090A780(Unknown20);
}
