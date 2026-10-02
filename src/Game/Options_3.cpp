// Game/Options_3.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

class Options
{
public:
    void Save();
    void FUN_10ab66e0();

    int Unknown00;
    int Values[21];
    char Unknown58;
    char Unknown59;
};

// FUNCTION: 0x10AB66E0 ?FUN_10ab66e0@Options@@QAEXXZ
void Options::FUN_10ab66e0()
{
    Save();
    Unknown59 = 0;
}
