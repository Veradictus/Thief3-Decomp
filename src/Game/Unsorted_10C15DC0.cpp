// Game/Unsorted_10C15DC0.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

class Class_10C16030
{
public:
    void FUN_10c16030(int A);
};

class Class_10C15E60
{
public:
    void FUN_10c15e60(void* Source);
};

struct Struct_10C161F0
{
    char Unknown00[0x10];
    int Unknown10;
};

class Class_10C161F0
{
public:
    void FUN_10c161f0(Struct_10C161F0* Source);

    char Unknown00[4];
    Class_10C16030 Unknown04;
    char Unknown05[0x400F];
    Class_10C15E60 Unknown4014;
};

class Class_10C15EB0_Member
{
public:
    char Unknown00[4];
    int Unknown04;
};

class Class_10C15EB0
{
public:
    int FUN_10c15eb0();

    char Unknown00[0x4018];
    Class_10C15EB0_Member* Unknown4018;
};

// FUNCTION: 0x10C15EB0 ?FUN_10c15eb0@Class_10C15EB0@@QAEHXZ
int Class_10C15EB0::FUN_10c15eb0()
{
    if (Unknown4018)
        return Unknown4018->Unknown04;
    return 0;
}

// FUNCTION: 0x10C161F0 ?FUN_10c161f0@Class_10C161F0@@QAEXPAUStruct_10C161F0@@@Z
void Class_10C161F0::FUN_10c161f0(Struct_10C161F0* Source)
{
    Unknown04.FUN_10c16030(Source->Unknown10);
    Unknown4014.FUN_10c15e60(Source);
}
