// Game/Class_10CFB350.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

class Class_10CFB350
{
public:
    Class_10CFB350* FUN_10cfb350(const Class_10CFB350* Src, int B);

    int Unknown00[4];
};

// FUNCTION: 0x10CFB350 ?FUN_10cfb350@Class_10CFB350@@QAEPAV1@PBV1@H@Z
Class_10CFB350* Class_10CFB350::FUN_10cfb350(const Class_10CFB350* Src, int B)
{
    for (int i = 0; i < 4; i++)
        Unknown00[i] = Src->Unknown00[i];
    Unknown00[3] = B;
    return this;
}
