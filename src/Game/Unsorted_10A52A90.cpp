// Game/Unsorted_10A52A90.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

class WindowManager
{
public:
    void FUN_109e8ae0(void* Window);
};

extern WindowManager* GWindowManager;

class Class_10A52B30
{
public:
    void FUN_10a52b30();

    char Unknown00[0xB8];
    int UnknownB8;
    char UnknownBC[4];
    void** UnknownC0;
};

// FUNCTION: 0x10A52B30 ?FUN_10a52b30@Class_10A52B30@@QAEXXZ
void Class_10A52B30::FUN_10a52b30()
{
    for (int i = 0; i < UnknownB8; i++)
    {
        if (UnknownC0[i])
            GWindowManager->FUN_109e8ae0(UnknownC0[i]);
    }
    UnknownB8 = 0;
}
