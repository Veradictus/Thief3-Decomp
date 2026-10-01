// Game/Unsorted_10A243F0_2.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

class Class_10A35870
{
public:
    void FUN_10a35870(const int* A);
};

struct Static_10A35EA0 : public Class_10A35870
{
    char Unknown0C;
};

Static_10A35EA0* FUN_10a35ea0();

class Class_10A258B0
{
public:
    void FUN_10a25a60(int A);
    const int* FUN_10a258b0(int* P, int V);
};

// FUNCTION: 0x10A25A60 ?FUN_10a25a60@Class_10A258B0@@QAEXH@Z
void Class_10A258B0::FUN_10a25a60(int A)
{
    FUN_10a35ea0()->FUN_10a35870(FUN_10a258b0(&A, A));
}
