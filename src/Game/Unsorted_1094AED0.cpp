// Game/Unsorted_1094AED0.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

struct Item_1094B600
{
    int Unknown00;
    int Unknown04;
};

class Class_1094B600
{
public:
    void FUN_1094b600(int A, int B);

    int Unknown00;
    int Unknown04;
    Item_1094B600* Unknown08;
};

// FUNCTION: 0x1094B600 ?FUN_1094b600@Class_1094B600@@QAEXHH@Z
void Class_1094B600::FUN_1094b600(int A, int B)
{
    Item_1094B600 Temp = Unknown08[A];
    Unknown08[A] = Unknown08[B];
    Unknown08[B] = Temp;
}
