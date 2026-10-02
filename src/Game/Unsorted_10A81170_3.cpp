// Game/Unsorted_10A81170_3.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

extern void* DAT_10e6c170[];

class Class_10E6C104
{
public:
    Class_10E6C104();

    void** Unknown00;
};

class Class_10E6C170 : public Class_10E6C104
{
public:
    Class_10E6C170* FUN_10a81190();

    char Unknown04[4];
    int Unknown08;
};

// FUNCTION: 0x10A81190 ?FUN_10a81190@Class_10E6C170@@QAEPAV1@XZ
Class_10E6C170* Class_10E6C170::FUN_10a81190()
{
    this->Class_10E6C104::Class_10E6C104();
    Unknown00 = DAT_10e6c170;
    Unknown08 = 0;
    return this;
}
