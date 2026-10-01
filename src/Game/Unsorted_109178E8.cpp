// Game/Unsorted_109178E8.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

extern char DAT_10f2c75a;

extern char DAT_10f2c75b;

extern float DAT_10efef60;

extern float DAT_10efef64;

extern float DAT_10e49684;

extern int DAT_10f2c6f0;

extern int DAT_10f2c6f4;

extern int DAT_10f2c6f8;

extern int DAT_10f2c6fc;

extern int DAT_10f2c700;

extern int DAT_10f2c704;

extern int DAT_10f2c708;

extern int DAT_10f2c70c;

extern int DAT_10f2c710;

extern int DAT_10f2c714;

extern int DAT_10f2c718;

extern int DAT_10f2c71c;

struct Struct_109179C0
{
    int Unknown00;
    int Unknown04;
    int Unknown08;
    int Unknown0C;
    int Unknown10;
    int Unknown14;
};

class Class_10924100
{
public:
    char Unknown00[0xC];
    int Unknown0C;
};

extern Class_10924100* DAT_10f2c740;

// FUNCTION: 0x10917990 ?FUN_10917990@@YAMXZ
float FUN_10917990()
{
    if (DAT_10f2c75a)
    {
        if (DAT_10f2c75b)
            return DAT_10efef60;
        return DAT_10efef64 * DAT_10efef60;
    }
    return DAT_10e49684;
}

// FUNCTION: 0x109179C0 ?FUN_109179c0@@YAXPAUStruct_109179C0@@@Z
void FUN_109179c0(Struct_109179C0* Out)
{
    if (DAT_10f2c75a)
    {
        Out->Unknown00 = DAT_10f2c6f0;
        Out->Unknown04 = DAT_10f2c6f4;
        Out->Unknown08 = DAT_10f2c6f8;
        Out->Unknown0C = DAT_10f2c6fc;
        Out->Unknown10 = DAT_10f2c700;
        Out->Unknown14 = DAT_10f2c704;
    }
    else
    {
        Out->Unknown00 = DAT_10f2c708;
        Out->Unknown04 = DAT_10f2c70c;
        Out->Unknown08 = DAT_10f2c710;
        Out->Unknown0C = DAT_10f2c714;
        Out->Unknown10 = DAT_10f2c718;
        Out->Unknown14 = DAT_10f2c71c;
    }
}

// FUNCTION: 0x10917C30 ?FUN_10917c30@@YA_NXZ
bool FUN_10917c30()
{
    if (DAT_10f2c740 && DAT_10f2c740->Unknown0C)
        return true;
    return false;
}
