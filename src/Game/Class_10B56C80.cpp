// Game/Class_10B56C80.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

class Class_1090A780
{
public:
    Class_1090A780(const Class_1090A780& Other);
    ~Class_1090A780();

    char* Unknown00;
};

class Class_10B56C80
{
public:
    Class_1090A780 FUN_10b56c80();

    char Unknown00[0x1BC];
    Class_1090A780 Unknown1BC;
};

// FUNCTION: 0x10B56C80 ?FUN_10b56c80@Class_10B56C80@@QAE?AVClass_1090A780@@XZ
Class_1090A780 Class_10B56C80::FUN_10b56c80()
{
    return Class_1090A780(Unknown1BC);
}
