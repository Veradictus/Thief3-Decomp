// Game/Unsorted_1092BB80.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

struct Node_10F31AFC
{
    Node_10F31AFC* Unknown00;
    Node_10F31AFC* Unknown04;
    Node_10F31AFC* Unknown08;
};

class Class_1092C160
{
public:
    void FUN_1092c160(Node_10F31AFC* Root);
};

extern bool DAT_10ffc855;

extern Class_1092C160 DAT_10f31ae0;

extern Node_10F31AFC* DAT_10f31afc;

extern int DAT_10f31b00;

// FUNCTION: 0x1092C290 ?FUN_1092c290@@YAXXZ
void FUN_1092c290()
{
    if (!DAT_10ffc855)
    {
        DAT_10f31ae0.FUN_1092c160(DAT_10f31afc->Unknown04);
        DAT_10f31afc->Unknown04 = DAT_10f31afc;
        DAT_10f31b00 = 0;
        DAT_10f31afc->Unknown00 = DAT_10f31afc;
        DAT_10f31afc->Unknown08 = DAT_10f31afc;
    }
}
