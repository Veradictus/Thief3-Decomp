// Game/Unsorted_10A242E0_3.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

class Class_10A357C0
{
public:
    void FUN_10a357c0(unsigned char A);
};

struct Static_10A35EA0 : public Class_10A357C0
{
    char Unknown0C;
};

Static_10A35EA0* FUN_10a35ea0();

class Class_10A24300
{
public:
    void FUN_10a24300(unsigned char A);

    char Unknown00[0x55];
    unsigned char Unknown55;
};

// FUNCTION: 0x10A24300 ?FUN_10a24300@Class_10A24300@@QAEXE@Z
void Class_10A24300::FUN_10a24300(unsigned char A)
{
    FUN_10a35ea0()->FUN_10a357c0(A);
    Unknown55 = A;
}
