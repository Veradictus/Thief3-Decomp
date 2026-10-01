// Game/Unsorted_1094DA70.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

class Class_1094DF60
{
public:
    void FUN_1094df60(int A);

    char Unknown00[0x10C];
    int Unknown10C;
    int Unknown110;
};

struct Info_1094DF40
{
    int Unknown00;
    int Unknown04;
    int Unknown08;
};

class Class_1094DF40
{
public:
    void FUN_1094df40(const Info_1094DF40* In);

    char Unknown00[0x14C];
    Info_1094DF40 Unknown14C;
};

// FUNCTION: 0x1094DF40 ?FUN_1094df40@Class_1094DF40@@QAEXPBUInfo_1094DF40@@@Z
void Class_1094DF40::FUN_1094df40(const Info_1094DF40* In)
{
    Unknown14C = *In;
}

// FUNCTION: 0x1094DF60 ?FUN_1094df60@Class_1094DF60@@QAEXH@Z
void Class_1094DF60::FUN_1094df60(int A)
{
    Unknown110 = A;
    if (Unknown110 >= Unknown10C)
        Unknown110 = Unknown10C - 1;
    if (Unknown110 < 0)
        Unknown110 = 0;
}
