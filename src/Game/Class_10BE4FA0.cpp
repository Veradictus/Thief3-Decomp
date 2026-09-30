// Game/Class_10BE4FA0.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

extern const char DAT_10e47660[];

class Class_109081E0
{
public:
    Class_109081E0(const char* In);
    ~Class_109081E0();

    char* Unknown00;
};

class Class_10E97B00
{
public:
    Class_10E97B00(const char* In);

    void** Unknown00;
    Class_109081E0 Unknown04;
};

class Class_10BE4FA0
{
public:
    Class_10E97B00 FUN_10be4fa0();
};

// FUNCTION: 0x10BE4FA0 ?FUN_10be4fa0@Class_10BE4FA0@@QAE?AVClass_10E97B00@@XZ
Class_10E97B00 Class_10BE4FA0::FUN_10be4fa0()
{
    return Class_10E97B00(DAT_10e47660);
}
