// Game/Unsorted_1097D350.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.


class Class_1097D530
{
public:
    void FUN_1097d530();
    void FUN_1097cc10();

    char Unknown00[0xC];
    void* Unknown0C;
    int Unknown10;
};

// FUNCTION: 0x1097D530 ?FUN_1097d530@Class_1097D530@@QAEXXZ
void Class_1097D530::FUN_1097d530()
{
    if (Unknown0C)
        ::operator delete(Unknown0C);
    Unknown0C = 0;
    Unknown10 = 0;
    FUN_1097cc10();
}
