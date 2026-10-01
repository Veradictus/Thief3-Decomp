// Game/Unsorted_10AA47C0.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

extern void* DAT_10e6d52c[];

class Class_10EB7660
{
public:
    Class_10EB7660();

    void** VTable;
    int Unknown04;
};

class Class_10E6D52C : public Class_10EB7660
{
public:
    Class_10E6D52C* FUN_10aa4a00();

    int Unknown08;
};

// FUNCTION: 0x10AA4A00 ?FUN_10aa4a00@Class_10E6D52C@@QAEPAV1@XZ
Class_10E6D52C* Class_10E6D52C::FUN_10aa4a00()
{
    this->Class_10EB7660::Class_10EB7660();
    VTable = DAT_10e6d52c;
    Unknown08 = 0;
    return this;
}
