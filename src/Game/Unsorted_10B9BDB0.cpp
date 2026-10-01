// Game/Unsorted_10B9BDB0.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

class Class_10B9C9C0
{
public:
    void FUN_10b9c9c0(void* A);

    char Unknown00[0x38];
    void* Unknown38;
};

// FUNCTION: 0x10B9C9C0 ?FUN_10b9c9c0@Class_10B9C9C0@@QAEXPAX@Z
void Class_10B9C9C0::FUN_10b9c9c0(void* A)
{
    if (Unknown38)
        ::operator delete(Unknown38);
    Unknown38 = A;
}
