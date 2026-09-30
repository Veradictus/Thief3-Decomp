// Game/Unsorted_10BD1EA0.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

extern void* DAT_10e934d0[];

class Class_10E90D70
{
public:
    Class_10E90D70(int A, int B);

    void** Unknown00;
};

class Class_10E934D0 : public Class_10E90D70
{
public:
    Class_10E934D0* FUN_10bd1ec0(int A, int B);

    char Unknown04[0x3C];
    char Unknown40;
};

// FUNCTION: 0x10BD1EC0 ?FUN_10bd1ec0@Class_10E934D0@@QAEPAV1@HH@Z
Class_10E934D0* Class_10E934D0::FUN_10bd1ec0(int A, int B)
{
    this->Class_10E90D70::Class_10E90D70(A, B);
    Unknown40 = 0;
    Unknown00 = DAT_10e934d0;
    return this;
}
