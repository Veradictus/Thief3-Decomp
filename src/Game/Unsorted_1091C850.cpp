// Game/Unsorted_1091C850.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

class Class_1091c710
{
public:
    unsigned char FUN_1091c710(int* p1);
};

class Class_1091ca00
{
public:
    bool FUN_1091ca00(int p1);

    char Unknown00[0x30];
    Class_1091c710 Unknown30;
};

// FUNCTION: 0x1091CA00 ?FUN_1091ca00@Class_1091ca00@@QAE_NH@Z
bool Class_1091ca00::FUN_1091ca00(int p1)
{
    return Unknown30.FUN_1091c710(&p1);
}
