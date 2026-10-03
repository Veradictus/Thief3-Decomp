// Game/Unsorted_10B369B0.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

class Class_10B1B8A0
{
public:
    bool FUN_10b1b7f0(int A);
};

Class_10B1B8A0* FUN_10b1b600();

class WindowManager
{
public:
    void FUN_10b16110(int A, int B);
};

extern WindowManager* GWindowManager;

class Class_10B374A0
{
public:
    void FUN_10b374a0(int A, Class_10B374A0* B, int C);

    char Unknown00[0x4];
    int Unknown04;
};

// FUNCTION: 0x10B374A0 ?FUN_10b374a0@Class_10B374A0@@QAEXHPAV1@H@Z
void Class_10B374A0::FUN_10b374a0(int A, Class_10B374A0* B, int C)
{
    if (B->Unknown04 == Unknown04)
    {
        if (FUN_10b1b600()->FUN_10b1b7f0(A) && GWindowManager)
            GWindowManager->FUN_10b16110(A, 1);
    }
}
