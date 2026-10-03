// Game/Unsorted_10918260_2.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

class Class_10924E80
{
public:
    void FUN_10925060();
};

class Class_10924100
{
public:
    ~Class_10924100();
};

extern Class_10924E80* DAT_10f2c734;

extern Class_10924100* DAT_10f2c740;

extern int DAT_10efef54;

extern char DAT_10f2c724;

void FUN_1092f190();

// FUNCTION: 0x10918260 ?FUN_10918260@@YAXXZ
void FUN_10918260()
{
    if (DAT_10f2c734)
        DAT_10f2c734->FUN_10925060();
    DAT_10efef54 = -1;
    DAT_10f2c724 = 0;
    if (DAT_10f2c740)
    {
        delete DAT_10f2c740;
        DAT_10f2c740 = 0;
    }
    FUN_1092f190();
}
