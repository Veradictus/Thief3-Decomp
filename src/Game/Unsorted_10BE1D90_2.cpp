// Game/Unsorted_10BE1D90_2.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

class Class_10C08940
{
public:
    int FUN_10c08940();
};

class Class_10978090
{
public:
    Class_10C08940* FUN_10978090();
};

class Class_10FF667C
{
public:
    char Unknown00[0x24];
    Class_10978090* Unknown24;
};

extern Class_10FF667C* DAT_10ff667c;

// FUNCTION: 0x10BE1D90 ?FUN_10be1d90@@YAHXZ
int FUN_10be1d90()
{
    if (!DAT_10ff667c->Unknown24->FUN_10978090())
        return 0;
    return DAT_10ff667c->Unknown24->FUN_10978090()->FUN_10c08940();
}
