// Game/Unsorted_10B559E0.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

class WindowManager
{
public:
    void FUN_109e8ae0(void* A);
};

extern WindowManager* GWindowManager;

struct Struct_10E81DD4_Unknown08
{
    void* Unknown00;
    int Unknown04;
};

class Class_10E81DD4
{
public:
    virtual ~Class_10E81DD4();

    void* Unknown04;
    Struct_10E81DD4_Unknown08 Unknown08[2];
};

// FUNCTION: 0x10B561D0 ??1Class_10E81DD4@@UAE@XZ
Class_10E81DD4::~Class_10E81DD4()
{
    if (Unknown04)
        GWindowManager->FUN_109e8ae0(Unknown04);
    for (int i = 0; i < 2; i++)
    {
        if (Unknown08[i].Unknown00)
            GWindowManager->FUN_109e8ae0(Unknown08[i].Unknown00);
    }
}
