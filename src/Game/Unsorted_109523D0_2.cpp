// Game/Unsorted_109523D0_2.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

struct Info_10952690
{
    int Unknown00;
    int Unknown04;
    int Unknown08;
    int Unknown0C;
};

class Class_10936AC0
{
public:
    void FUN_10937280(int A, Info_10952690* Info);
};

extern Class_10936AC0* DAT_10f31be0;

class Class_10952690
{
public:
    void FUN_10952690();

    char Unknown00[0x80];
    int Unknown80;
    int Unknown84;
    int Unknown88;
};

// FUNCTION: 0x10952690 ?FUN_10952690@Class_10952690@@QAEXXZ
void Class_10952690::FUN_10952690()
{
    Info_10952690 Info;
    Info.Unknown00 = Unknown80;
    Info.Unknown04 = Unknown84;
    Info.Unknown08 = Unknown88;
    Info.Unknown0C = 0;
    DAT_10f31be0->FUN_10937280(0, &Info);
}
