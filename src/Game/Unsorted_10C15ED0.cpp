// Game/Unsorted_10C15ED0.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

class Class_10C16030
{
public:
    bool FUN_10c15f90(int A, void* B);
};

class Class_10C15E60
{
public:
    bool FUN_10c15dc0(float A, void* B);
};

struct Struct_10C161F0
{
    char Unknown00[4];
    float Unknown04;
    float Unknown08;
    char Unknown0C[4];
    int Unknown10;
};

class Class_10C161F0
{
public:
    bool FUN_10c161b0(Struct_10C161F0* Source);

    char Unknown00[4];
    Class_10C16030 Unknown04;
    char Unknown05[0x400F];
    Class_10C15E60 Unknown4014;
};

// FUNCTION: 0x10C161B0 ?FUN_10c161b0@Class_10C161F0@@QAE_NPAUStruct_10C161F0@@@Z
bool Class_10C161F0::FUN_10c161b0(Struct_10C161F0* Source)
{
    if (!Unknown04.FUN_10c15f90(Source->Unknown10, Source))
        return false;
    return Unknown4014.FUN_10c15dc0(Source->Unknown08 + Source->Unknown04, Source);
}
