// Game/Unsorted_10A74B20.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

class Class_10E6BBD0
{
public:
    virtual void FUN_10a756f0(int Event, int A, int B, int C);

    void FUN_10a74c10(int A);
    void FUN_10a75190(int A, int B, int C);
    void FUN_10a75560(int A, bool B);
    void FUN_10a75680(int A, int B, int C);
};

// FUNCTION: 0x10A756F0 ?FUN_10a756f0@Class_10E6BBD0@@UAEXHHHH@Z
void Class_10E6BBD0::FUN_10a756f0(int Event, int A, int B, int C)
{
    switch (Event)
    {
    case 42:
    case 43:
        FUN_10a75680(A, B, C);
        break;
    case 36:
    case 37:
        FUN_10a75560(A, Event == 36);
        break;
    case 39:
        FUN_10a74c10(A);
        break;
    case 1:
        FUN_10a75190(A, B, C);
        break;
    }
}
