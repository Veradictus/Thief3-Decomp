// Game/Unsorted_10BAA000.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

struct Struct_10C05A80
{
    float Unknown00;
    float Unknown04;
    float Unknown08;
};

float FUN_10c05a80(const Struct_10C05A80* A, const Struct_10C05A80* B);

struct Struct_10BAA000
{
    char Unknown00[0x2C];
    Struct_10C05A80 Unknown2C;
};

struct Struct_10AA3520
{
    char Unknown00[8];
    Struct_10BAA000* Unknown08;
};

extern Struct_10AA3520* DAT_10f35dec;

extern float DAT_10eafbdc;

extern float DAT_10e49684;

class Class_10BAA000
{
public:
    float FUN_10baa000();

    char Unknown00[0x34];
    Struct_10BAA000* Unknown34;
};

// FUNCTION: 0x10BAA000 ?FUN_10baa000@Class_10BAA000@@QAEMXZ
float Class_10BAA000::FUN_10baa000()
{
    if (DAT_10f35dec && DAT_10f35dec->Unknown08)
    {
        Struct_10BAA000* Mine = Unknown34;
        float Dist = FUN_10c05a80(&Mine->Unknown2C, &DAT_10f35dec->Unknown08->Unknown2C);
        if (Dist > 1048576.0f)
            return DAT_10eafbdc;
        return DAT_10e49684 - Dist * 9.536743e-07f;
    }
    return DAT_10eafbdc;
}
