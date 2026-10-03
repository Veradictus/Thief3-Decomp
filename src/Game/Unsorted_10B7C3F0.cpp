// Game/Unsorted_10B7C3F0.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

#include <float.h>

class Class_10B7C4A0
{
public:
    Class_10B7C4A0* FUN_10b7c4a0();

    int Unknown00;
    int Unknown04;
    int Unknown08;
    int Unknown0C;
    float Unknown10[5][4];
    float Unknown60[3][4];
    float Unknown90;
    float Unknown94;
    int Unknown98;
};

class Class_10B7C3F0_Member
{
public:
    virtual ~Class_10B7C3F0_Member();

    char Unknown04[2];
    unsigned short Unknown06;
};

class Class_10B7C3F0
{
public:
    void FUN_10b7c3f0(Class_10B7C3F0_Member* New);

    char Unknown00[0x54];
    Class_10B7C3F0_Member* Unknown54;
};

// FUNCTION: 0x10B7C3F0 ?FUN_10b7c3f0@Class_10B7C3F0@@QAEXPAVClass_10B7C3F0_Member@@@Z
void Class_10B7C3F0::FUN_10b7c3f0(Class_10B7C3F0_Member* New)
{
    if (New)
        New->Unknown06++;
    Class_10B7C3F0_Member* Old = Unknown54;
    if (Old)
    {
        Old->Unknown06--;
        if (Old->Unknown06 == 0)
            delete Old;
    }
    Unknown54 = New;
}

// FUNCTION: 0x10B7C4A0 ?FUN_10b7c4a0@Class_10B7C4A0@@QAEPAV1@XZ
Class_10B7C4A0* Class_10B7C4A0::FUN_10b7c4a0()
{
    Unknown00 = 0;
    Unknown04 = 0;
    Unknown08 = 0;
    Unknown10[0][0] = Unknown10[0][1] = Unknown10[0][2] = Unknown10[0][3] = 0.0f;
    Unknown10[1][0] = Unknown10[1][1] = Unknown10[1][2] = Unknown10[1][3] = 0.0f;
    Unknown10[2][0] = Unknown10[2][1] = Unknown10[2][2] = Unknown10[2][3] = 0.0f;
    Unknown10[3][0] = Unknown10[3][1] = Unknown10[3][2] = Unknown10[3][3] = 0.0f;
    Unknown10[4][0] = Unknown10[4][1] = Unknown10[4][2] = Unknown10[4][3] = 0.0f;
    for (int i = 0; i < 3; i++)
        Unknown60[i][0] = Unknown60[i][1] = Unknown60[i][2] = Unknown60[i][3] = 0.0f;
    Unknown60[0][0] = 1.0f;
    Unknown60[1][1] = 1.0f;
    Unknown60[2][2] = 1.0f;
    Unknown90 = -FLT_MAX;
    Unknown94 = FLT_MAX;
    Unknown98 = 0;
    return this;
}
