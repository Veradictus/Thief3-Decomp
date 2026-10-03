// Game/Unsorted_10A51140.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

class WindowManager
{
public:
    void FUN_109e3d60(void* Window);
};

extern WindowManager* GWindowManager;

class Class_10E67BD8
{
public:
    void FUN_10a514e0(int Index);

    char Unknown00[0x11C];
    void* Unknown11C;
    char Unknown120[8];
    void** Unknown128;
};

class Class_10E7EDB8
{
public:
    virtual void FUN_10a51530(int A, void* B, int C, int D);

    void* Unknown04;
    int Unknown08;
    int Unknown0C;
    void** Unknown10;
};

// FUNCTION: 0x10A514E0 ?FUN_10a514e0@Class_10E67BD8@@QAEXH@Z
void Class_10E67BD8::FUN_10a514e0(int Index)
{
    if (Unknown128[Index])
    {
        if (Unknown11C == Unknown128[Index])
            Unknown11C = 0;
        GWindowManager->FUN_109e3d60(Unknown128[Index]);
        Unknown128[Index] = 0;
    }
}

// FUNCTION: 0x10A51530 ?FUN_10a51530@Class_10E7EDB8@@UAEXHPAXHH@Z
void Class_10E7EDB8::FUN_10a51530(int A, void* B, int C, int D)
{
    if (A == 0x26)
    {
        for (int i = 0; i < Unknown08; i++)
        {
            if (Unknown10[i] && Unknown10[i] == B)
            {
                if (Unknown04 == Unknown10[i])
                    Unknown04 = 0;
                Unknown10[i] = 0;
            }
        }
    }
}
