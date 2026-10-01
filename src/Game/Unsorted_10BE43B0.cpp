// Game/Unsorted_10BE43B0.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

class Class_10BBDB40
{
public:
    unsigned char FUN_10bbdb80();
};

class Class_10DBD510
{
public:
    Class_10BBDB40* FUN_10dbd510(int A);
};

struct Struct_10BE4540
{
    char Unknown00[8];
    Class_10DBD510* Unknown08;
};

class Class_10BE4540
{
public:
    bool FUN_10be4540();

    char Unknown00[4];
    Struct_10BE4540* Unknown04;
};

// FUNCTION: 0x10BE4540 ?FUN_10be4540@Class_10BE4540@@QAE_NXZ
bool Class_10BE4540::FUN_10be4540()
{
    switch (Unknown04->Unknown08->FUN_10dbd510(0x42000585)->FUN_10bbdb80())
    {
    case 1:
        return true;
    }
    return false;
}
