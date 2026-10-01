// Game/Unsorted_10BB81B0.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

extern float DAT_10eafbdc;

class Class_10BB8210
{
public:
    int FUN_10bb8210();

    char Unknown00[0x2BC];
    float Unknown2BC;
};

// FUNCTION: 0x10BB8210 ?FUN_10bb8210@Class_10BB8210@@QAEHXZ
int Class_10BB8210::FUN_10bb8210()
{
    if (Unknown2BC <= DAT_10eafbdc)
        return 1;
    return 0;
}
