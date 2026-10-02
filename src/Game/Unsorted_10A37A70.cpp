// Game/Unsorted_10A37A70.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

class Class_109081E0;

class Class_1090FD40
{
public:
    void FUN_1090f2c0(int Count);
    void FUN_10a37f80(int A, int B, int C);
    void FUN_10a39200(int Index);

    int Unknown00;
    int Unknown04;
    Class_109081E0* Unknown08;
};

// FUNCTION: 0x10A39200 ?FUN_10a39200@Class_1090FD40@@QAEXH@Z
void Class_1090FD40::FUN_10a39200(int Index)
{
    if (Index != Unknown00 - 1)
        FUN_10a37f80(Index + 1, Index, Unknown00 - Index - 1);
    FUN_1090f2c0(Unknown00 - 1);
}
