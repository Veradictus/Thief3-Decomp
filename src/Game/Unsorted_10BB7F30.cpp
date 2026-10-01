// Game/Unsorted_10BB7F30.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

extern float DAT_10eafbdc;

float appFrand();

class Class_10BB7F60
{
public:
    float FUN_10bb7f60();

    char Unknown00[0x29C];
    float Unknown29C;
};

// FUNCTION: 0x10BB7F60 ?FUN_10bb7f60@Class_10BB7F60@@QAEMXZ
float Class_10BB7F60::FUN_10bb7f60()
{
    if (Unknown29C == DAT_10eafbdc)
        Unknown29C = appFrand();
    return Unknown29C;
}
