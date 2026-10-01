// Game/Unsorted_10C61CF0.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

extern void* DAT_10e9ca9c[];

void* FUN_10905c10(int Kind, int* Arg, int A, int B, int C, int D);

class Class_10E9CA9C
{
public:
    void** Unknown00;
    char Unknown04;
};

// FUNCTION: 0x10C61D10 ?FUN_10c61d10@@YAPAVClass_10E9CA9C@@XZ
Class_10E9CA9C* FUN_10c61d10()
{
    int Value = 0;
    Class_10E9CA9C* Object = (Class_10E9CA9C*)FUN_10905c10(8, &Value, 0, 0, 0, 0);
    if (Object)
    {
        Object->Unknown00 = DAT_10e9ca9c;
        Object->Unknown04 = 1;
        return Object;
    }
    return 0;
}
