// Game/Unsorted_10ACE4B0.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

class Class_10B82390
{
public:
    void FUN_10b82390(int A, void* B);
};

Class_10B82390* __stdcall FUN_10acf690(int A);

// FUNCTION: 0x10ACFB10 ?FUN_10acfb10@@YGXHPAX@Z
void __stdcall FUN_10acfb10(int A, void* B)
{
    Class_10B82390* Obj = FUN_10acf690(A);
    if (Obj)
        Obj->FUN_10b82390(0x8056b, B);
}
