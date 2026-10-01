// Game/Unsorted_10ABF200.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

struct Struct_10ABF1B0
{
    char Unknown00[0x20];
    char Unknown20;
};

Struct_10ABF1B0* __stdcall FUN_10abf1b0(int A);

// FUNCTION: 0x10ABF200 ?FUN_10abf200@@YGXHD@Z
void __stdcall FUN_10abf200(int A, char B)
{
    FUN_10abf1b0(A)->Unknown20 = B;
}
