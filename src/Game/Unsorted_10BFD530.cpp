// Game/Unsorted_10BFD530.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

class Class_10991270
{
public:
    ~Class_10991270();

    char Unknown00[0xC];
};

class Class_10BFD4E0
{
public:
    ~Class_10BFD4E0();

    char Unknown00[0x18];
    Class_10991270 Unknown18;
    Class_10991270 Unknown24;
    char Unknown30[0xC];
};

class Class_10AF4BB0
{
public:
    void FUN_10af3bd0(int A, int B, int C);

    void* Unknown00;
    int Unknown04;
    int Unknown08;
};

class Class_10BFE6B0 : public Class_10AF4BB0
{
public:
    void FUN_10bfe6b0(int Index, int Count);
};

// FUNCTION: 0x10BFE6B0 ?FUN_10bfe6b0@Class_10BFE6B0@@QAEXHH@Z
void Class_10BFE6B0::FUN_10bfe6b0(int Index, int Count)
{
    for (int i = Index; i < Index + Count; i++)
        ((Class_10BFD4E0*)Unknown00)[i].~Class_10BFD4E0();
    FUN_10af3bd0(Index, Count, 0x3C);
}
