// Game/Unsorted_10B7ACC0.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

class Class_10B7AD00
{
public:
    int FUN_10b7ad00(int Index);

    char Unknown00[0x28];
    int Unknown28;
    int Unknown2C;
    int* Unknown30;
};

// FUNCTION: 0x10B7AD00 ?FUN_10b7ad00@Class_10B7AD00@@QAEHH@Z
int Class_10B7AD00::FUN_10b7ad00(int Index)
{
    if (Unknown28 > Index)
        return Unknown30[Index];
    return 0x101;
}
