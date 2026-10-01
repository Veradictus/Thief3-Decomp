// Game/Unsorted_10A57820.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

class Class_10A57910
{
public:
    void FUN_10a588c0(int p1);
    void FUN_10a57910(int p1);

    char Unknown00[0x1F0];
    int Unknown1F0;
    int Unknown1F4;
};

class Class_10A57930
{
public:
    int FUN_10a5a510(int A, int B);
    int FUN_10a57930(int A, int B);

    char Unknown00[0x1A4];
    bool Unknown1A4;
};

// FUNCTION: 0x10A57910 ?FUN_10a57910@Class_10A57910@@QAEXH@Z
void Class_10A57910::FUN_10a57910(int p1)
{
    FUN_10a588c0(p1);
    Unknown1F4 = Unknown1F0;
}

// FUNCTION: 0x10A57930 ?FUN_10a57930@Class_10A57930@@QAEHHH@Z
int Class_10A57930::FUN_10a57930(int A, int B)
{
    if (A != 2)
    {
        if (B == 2 && Unknown1A4)
            return A;
    }
    else
        A = 1;
    return FUN_10a5a510(A, B);
}
