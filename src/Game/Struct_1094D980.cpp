// Game/Struct_1094D980.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

class Struct_1094D980
{
public:
    void SetValues(int Param1, int Param2, int Param3);

    int Unknown00;
    int Unknown04;
    int Unknown08;
    int Unknown0C;
    char Unknown10;
    char Unknown11;
};

// FUNCTION: 0x1094D980 ?SetValues@Struct_1094D980@@QAEXHHH@Z
void Struct_1094D980::SetValues(int Param1, int Param2, int Param3)
{
    Unknown0C = Param3;
    Unknown10 = (char)Param1;
    Unknown11 = (char)Param2;
    Unknown04 = 0;
    Unknown08 = 0;
}
