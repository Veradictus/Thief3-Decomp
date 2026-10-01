// Game/Unsorted_10C4A180.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

class Class_1090A780
{
public:
    Class_1090A780(const Class_1090A780& Other);
    ~Class_1090A780();

    char* Unknown00;
};

class Class_109F6F40
{
public:
    Class_1090A780 FUN_109f6f40();

    char Unknown00[0xC];
};

class Class_10C4C200
{
public:
    Class_1090A780 FUN_10c4c200();

    char Unknown00[0xC];
    Class_109F6F40 Unknown0C;
};

// FUNCTION: 0x10C4C200 ?FUN_10c4c200@Class_10C4C200@@QAE?AVClass_1090A780@@XZ
Class_1090A780 Class_10C4C200::FUN_10c4c200()
{
    return Unknown0C.FUN_109f6f40();
}
