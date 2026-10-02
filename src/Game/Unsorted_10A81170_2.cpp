// Game/Unsorted_10A81170_2.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

extern void* DAT_10e6c14c[];

class Class_10E6C104
{
public:
    Class_10E6C104();

    void** Unknown00;
};

class Class_10E6C14C : public Class_10E6C104
{
public:
    Class_10E6C14C* FUN_10a81170();

    char Unknown04[4];
    int Unknown08;
};

// FUNCTION: 0x10A81170 ?FUN_10a81170@Class_10E6C14C@@QAEPAV1@XZ
Class_10E6C14C* Class_10E6C14C::FUN_10a81170()
{
    this->Class_10E6C104::Class_10E6C104();
    Unknown00 = DAT_10e6c14c;
    Unknown08 = 0;
    return this;
}
