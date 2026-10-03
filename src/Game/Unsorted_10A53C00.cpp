// Game/Unsorted_10A53C00.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
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
};

extern const char DAT_10e47660[];

class Class_10A53C00
{
public:
    Class_109081E0 FUN_10a53c00(int State);
};

// FUNCTION: 0x10A53C00 ?FUN_10a53c00@Class_10A53C00@@QAE?AVClass_109081E0@@H@Z
Class_109081E0 Class_10A53C00::FUN_10a53c00(int State)
{
    switch (State)
    {
    case 0:
        return Class_109081E0("Normal");
    case 1:
        return Class_109081E0("Selected");
    case 2:
        return Class_109081E0("Pressed");
    case 3:
        return Class_109081E0("Disabled");
    }
    return Class_109081E0(DAT_10e47660);
}
