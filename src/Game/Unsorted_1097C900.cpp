// Game/Unsorted_1097C900.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

class Class_1097B320
{
public:
    void FUN_1097b320();

    char Unknown00[0x28];
};

class Class_10AF4BB0
{
public:
    void FUN_10af3bd0(int A, int B, int C);

    void* Unknown00;
    int Unknown04;
    int Unknown08;
};

class Class_1097C980 : public Class_10AF4BB0
{
public:
    void FUN_1097c980(int Index, int Count);
};

// FUNCTION: 0x1097C980 ?FUN_1097c980@Class_1097C980@@QAEXHH@Z
void Class_1097C980::FUN_1097c980(int Index, int Count)
{
    for (int i = Index; i < Index + Count; i++)
        ((Class_1097B320*)Unknown00)[i].FUN_1097b320();
    FUN_10af3bd0(Index, Count, 0x28);
}
