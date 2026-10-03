// Game/Unsorted_10A467C0_2.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

class Class_10A462B0
{
public:
    ~Class_10A462B0();

    char Unknown00[0x30];
};

class Class_10AF4BB0
{
public:
    void FUN_10af3bd0(int A, int B, int C);

    void* Unknown00;
    int Unknown04;
    int Unknown08;
};

class Class_10A467C0 : public Class_10AF4BB0
{
public:
    void FUN_10a467c0(int Index, int Count);
};

// FUNCTION: 0x10A467C0 ?FUN_10a467c0@Class_10A467C0@@QAEXHH@Z
void Class_10A467C0::FUN_10a467c0(int Index, int Count)
{
    for (int i = Index; i < Index + Count; i++)
        ((Class_10A462B0*)Unknown00)[i].~Class_10A462B0();
    FUN_10af3bd0(Index, Count, 0x30);
}
