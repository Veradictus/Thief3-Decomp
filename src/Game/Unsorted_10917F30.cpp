// Game/Unsorted_10917F30.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

class Class_10924E80
{
public:
    void FUN_10926f20(int A, int B);
};

class Class_10924100;

extern int DAT_10f2c738;

extern Class_10924100* DAT_10f2c740;

extern Class_10924E80* DAT_10f2c734;

extern int DAT_10efef54;

// FUNCTION: 0x10917F80 ?FUN_10917f80@@YAXHH@Z
void FUN_10917f80(int A, int B)
{
    if (DAT_10f2c738 && DAT_10f2c740)
    {
        DAT_10efef54 = A;
        DAT_10f2c734->FUN_10926f20(A, B);
    }
    else
        DAT_10efef54 = -1;
}
