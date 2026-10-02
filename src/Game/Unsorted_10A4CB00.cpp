// Game/Unsorted_10A4CB00.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

#include <vector>

void FUN_10a4c7b0(int A, int B, bool C);

struct Struct_10A4CB00
{
};

class Class_109E5700
{
public:
    ~Class_109E5700()
    {
        FUN_109e5700();
        delete Unknown18;
        Unknown18 = 0;
    }

    void FUN_109e5700();

    char Unknown00[0x18];
    Struct_10A4CB00* Unknown18;
};

class Class_10A4CB00
{
public:
    ~Class_10A4CB00();

    char Unknown00[4];
    Class_109E5700 Unknown04;
    char Unknown20[8];
    std::vector<int> Unknown28;
};

// FUNCTION: 0x10A4CB00 ??1Class_10A4CB00@@QAE@XZ
Class_10A4CB00::~Class_10A4CB00()
{
}

// FUNCTION: 0x10A4CB40 ?FUN_10a4cb40@@YAXHH@Z
void FUN_10a4cb40(int A, int B)
{
    FUN_10a4c7b0(A, B, true);
}

// FUNCTION: 0x10A4CB60 ?FUN_10a4cb60@@YAXHH@Z
void FUN_10a4cb60(int A, int B)
{
    FUN_10a4c7b0(A, B, false);
}
