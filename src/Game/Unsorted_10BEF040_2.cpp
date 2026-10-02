// Game/Unsorted_10BEF040_2.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

double FUN_10c00480();

class Class_10E975A0
{
public:
    virtual void FUN_10bef040();
    void FUN_10beec50(int A);

    char Unknown04[0x64];
    bool Unknown68;
    float Unknown6C;
};

// FUNCTION: 0x10BEF040 ?FUN_10bef040@Class_10E975A0@@UAEXXZ
void Class_10E975A0::FUN_10bef040()
{
    Unknown68 = true;
    Unknown6C = (float)FUN_10c00480();
    FUN_10beec50(0);
}
