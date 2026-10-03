// Game/Unsorted_10917F30_2.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

class Class_1091E940;

class Class_10924100;

class Class_10924E80
{
public:
    void FUN_10925290(int A, int B);
};

void FUN_10919240(Class_1091E940* A, int B);

extern Class_1091E940* DAT_10f2c738;

extern Class_10924100* DAT_10f2c740;

extern int DAT_10f2c73c;

extern Class_10924E80* DAT_10f2c734;

extern int DAT_10efef54;

// FUNCTION: 0x10917F30 ?FUN_10917f30@@YAXHH@Z
void FUN_10917f30(int A, int B)
{
    if (DAT_10f2c738 && DAT_10f2c740)
    {
        FUN_10919240(DAT_10f2c738, DAT_10f2c73c);
        DAT_10efef54 = A;
        DAT_10f2c734->FUN_10925290(A, B);
    }
    else
        DAT_10efef54 = -1;
}
