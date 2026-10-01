// Game/FieldClass_A89060.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

extern float DAT_10e499a0;

class FieldClass_A89060
{
public:
    void FUN_10aae870(int A, int B);

    char Unknown00[0x828];
    int Unknown828;
    int Unknown82c;
};

// FUNCTION: 0x10AAE870 ?FUN_10aae870@FieldClass_A89060@@QAEXHH@Z
void FieldClass_A89060::FUN_10aae870(int A, int B)
{
    Unknown828 = (int)(A * DAT_10e499a0);
    Unknown82c = (int)(B * DAT_10e499a0);
}
