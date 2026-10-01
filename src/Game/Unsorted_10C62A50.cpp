// Game/Unsorted_10C62A50.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

class Class_10C3F110 {
public:
    int FUN_10c3f110(int p1);
};

Class_10C3F110* FUN_10c3fb10();

class Class_10C62A50 {
public:
    char Unknown00[0x40];
    int Unknown40;

    int FUN_10c62a50(int A);
};

// FUNCTION: 0x10C62A50 ?FUN_10c62a50@Class_10C62A50@@QAEHH@Z
int Class_10C62A50::FUN_10c62a50(int A)
{
    return FUN_10c3fb10()->FUN_10c3f110(Unknown40) + A;
}
