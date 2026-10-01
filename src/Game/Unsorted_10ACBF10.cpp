// Game/Unsorted_10ACBF10.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

extern void* DAT_10e70020[];

class Class_10E67938
{
public:
    Class_10E67938();

    void** Unknown00;
};

class Class_10E70020 : public Class_10E67938
{
public:
    Class_10E70020* FUN_10acc050();
};

// FUNCTION: 0x10ACC050 ?FUN_10acc050@Class_10E70020@@QAEPAV1@XZ
Class_10E70020* Class_10E70020::FUN_10acc050()
{
    this->Class_10E67938::Class_10E67938();
    Unknown00 = DAT_10e70020;
    return this;
}
