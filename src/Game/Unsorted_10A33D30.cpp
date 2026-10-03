// Game/Unsorted_10A33D30.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

class Class_10A33E80
{
public:
    Class_10A33E80* FUN_10a33e80(__int64 A, __int64 B);

    __int64 Unknown00;
    __int64 Unknown08;
};

// FUNCTION: 0x10A33E80 ?FUN_10a33e80@Class_10A33E80@@QAEPAV1@_J0@Z
Class_10A33E80* Class_10A33E80::FUN_10a33e80(__int64 A, __int64 B)
{
    if (A < B)
    {
        Unknown00 = A;
        Unknown08 = B;
    }
    else
    {
        Unknown08 = A;
        Unknown00 = B;
    }
    return this;
}
