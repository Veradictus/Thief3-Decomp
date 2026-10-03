// Game/Unsorted_10C38F70.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

struct Struct_10C39220
{
    int Unknown00;
    int Unknown04;
    int Unknown08;
};

class Class_10C39220
{
public:
    bool FUN_10c39220(int A);

    char Unknown00[0x28];
    Struct_10C39220 Unknown28;
    char Unknown34[0x6C];
    int UnknownA0;
    char UnknownA4[4];
    Struct_10C39220* UnknownA8;
    int UnknownAC;
    char UnknownB0[0x4C];
    int UnknownFC;
};

// FUNCTION: 0x10C39220 ?FUN_10c39220@Class_10C39220@@QAE_NH@Z
bool Class_10C39220::FUN_10c39220(int A)
{
    Struct_10C39220* Out = (Struct_10C39220*)A;
    if (UnknownAC >= UnknownA0)
        return false;
    if (UnknownFC == 1 || UnknownFC == 7)
        *Out = Unknown28;
    else
        *Out = UnknownA8[UnknownAC];
    return true;
}
