// Game/Unsorted_10C5F470.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

struct Info_10C5F470
{
    int Unknown00;
    int Unknown04;
    int Unknown08;
};

struct Class_10C5F470_Member
{
    char Unknown00[0x18];
    Info_10C5F470 Unknown18;
};

class Class_10C5F470
{
public:
    void FUN_10c5f470(const Info_10C5F470* In);

    Class_10C5F470_Member* Unknown00;
};

// FUNCTION: 0x10C5F470 ?FUN_10c5f470@Class_10C5F470@@QAEXPBUInfo_10C5F470@@@Z
void Class_10C5F470::FUN_10c5f470(const Info_10C5F470* In)
{
    Unknown00->Unknown18 = *In;
}
