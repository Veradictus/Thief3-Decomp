// Game/Unsorted_10C3FBE0.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

#include <vector>

class Class_10C3FF10
{
public:
    void FUN_10c3ff10(int Value);

    char Unknown00[0xF0];
    int UnknownF0;
    char UnknownF4[0x34];
    int Unknown128;
};

struct Struct_10C40590_Item
{
    int Unknown00;
    int Unknown04;
    int Unknown08;
};

class Class_10C40590
{
public:
    int FUN_10c40590();

    char Unknown00[0xBC];
    std::vector<Struct_10C40590_Item> Unknown0BC;
};

struct Struct_10C63E90
{
    int Unknown00;
    int Unknown04;
    int Unknown08;
};

class Class_10C63E90
{
public:
    Struct_10C63E90 FUN_10c63e90();
};

struct Struct_10C41500
{
    Class_10C63E90* Unknown00;
    int Unknown04;
    int Unknown08;
};

class Class_10C41500
{
public:
    Struct_10C63E90 FUN_10c41500(int Index);

    char Unknown00[0xBC];
    std::vector<Struct_10C41500> UnknownBC;
};

// FUNCTION: 0x10C3FF10 ?FUN_10c3ff10@Class_10C3FF10@@QAEXH@Z
void Class_10C3FF10::FUN_10c3ff10(int Value)
{
    if (Unknown128 != -1)
    {
        if (Value != -1)
        {
            Unknown128 = Value;
        }
        UnknownF0 = Unknown128;
        Unknown128 = -1;
    }
}

// FUNCTION: 0x10C40590 ?FUN_10c40590@Class_10C40590@@QAEHXZ
int Class_10C40590::FUN_10c40590()
{
    return Unknown0BC.size();
}

// FUNCTION: 0x10C41500 ?FUN_10c41500@Class_10C41500@@QAE?AUStruct_10C63E90@@H@Z
Struct_10C63E90 Class_10C41500::FUN_10c41500(int Index)
{
    return UnknownBC[Index].Unknown00->FUN_10c63e90();
}
