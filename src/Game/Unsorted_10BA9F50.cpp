// Game/Unsorted_10BA9F50.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

struct Struct_10BA9F50
{
    int Unknown00;
    int Unknown04;
    int Unknown08;
};

class Class_10BA9F50_Member
{
public:
    void GetPosition(Struct_10BA9F50* Out) { *Out = Unknown38; }

    char Unknown00[0x38];
    Struct_10BA9F50 Unknown38;
};

class Class_10BA9F50
{
public:
    bool FUN_10ba9f50(Struct_10BA9F50* Out);

    char Unknown00[0x34];
    Class_10BA9F50_Member* Unknown34;
};

// FUNCTION: 0x10BA9F50 ?FUN_10ba9f50@Class_10BA9F50@@QAE_NPAUStruct_10BA9F50@@@Z
bool Class_10BA9F50::FUN_10ba9f50(Struct_10BA9F50* Out)
{
    Unknown34->GetPosition(Out);
    return true;
}
