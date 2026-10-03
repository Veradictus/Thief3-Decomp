// Game/Unsorted_10A300C0.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

struct Item_10A304C0
{
    int Unknown00;
    int Unknown04;
    int Unknown08;
    int Unknown0C;
};

class Class_10A304C0
{
public:
    void FUN_10a304c0(int A, int B);

    int Unknown00;
    int Unknown04;
    Item_10A304C0* Unknown08;
};

// FUNCTION: 0x10A304C0 ?FUN_10a304c0@Class_10A304C0@@QAEXHH@Z
void Class_10A304C0::FUN_10a304c0(int A, int B)
{
    Item_10A304C0 Temp = Unknown08[A];
    Unknown08[A] = Unknown08[B];
    Unknown08[B] = Temp;
}
