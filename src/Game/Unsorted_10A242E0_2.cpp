// Game/Unsorted_10A242E0_2.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

class Class_10A357E0
{
public:
    void FUN_10a357e0(unsigned char A);
};

struct Static_10A35EA0 : public Class_10A357E0
{
    char Unknown0C;
};

Static_10A35EA0* FUN_10a35ea0();

class Class_10A242E0
{
public:
    void FUN_10a242e0(unsigned char A);

    char Unknown00[0x57];
    unsigned char Unknown57;
};

// FUNCTION: 0x10A242E0 ?FUN_10a242e0@Class_10A242E0@@QAEXE@Z
void Class_10A242E0::FUN_10a242e0(unsigned char A)
{
    FUN_10a35ea0()->FUN_10a357e0(A);
    Unknown57 = A;
}
