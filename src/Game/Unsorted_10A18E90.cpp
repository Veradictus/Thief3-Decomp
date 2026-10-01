// Game/Unsorted_10A18E90.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

class Class_10A88A50
{
public:
    bool FUN_10a88a50(int p1);
};

class Class_10A18F80
{
public:
    bool FUN_10a18f80(int p1);

    int Unknown00;
    Class_10A88A50* Unknown04;
};

struct Info_10A18FA0
{
    int Unknown00;
    int Unknown04;
    int Unknown08;
};

class Class_10A18FA0
{
public:
    bool FUN_10a18fa0(int Index);

    char Unknown00[0x320];
    Info_10A18FA0 Unknown320[1];
};

// FUNCTION: 0x10A18F80 ?FUN_10a18f80@Class_10A18F80@@QAE_NH@Z
bool Class_10A18F80::FUN_10a18f80(int p1)
{
    if (!Unknown04)
        return false;
    return Unknown04->FUN_10a88a50(p1);
}

// FUNCTION: 0x10A18FA0 ?FUN_10a18fa0@Class_10A18FA0@@QAE_NH@Z
bool Class_10A18FA0::FUN_10a18fa0(int Index)
{
    return Unknown320[Index].Unknown00 > 0;
}
