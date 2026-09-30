// Game/Unsorted_109CDCA0.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

class Class_1098E160
{
public:
    int FUN_1098e160(int& Item, int& Index);

    int* Unknown00;
    int Unknown04;
    int Unknown08;
};

struct Struct_109CE1F0
{
    int Unknown00;
    Class_1098E160 Unknown04;
};

// FUNCTION: 0x109CE1F0 ?FUN_109ce1f0@@YGHPAUStruct_109CE1F0@@H@Z
int __stdcall FUN_109ce1f0(Struct_109CE1F0* Obj, int Item)
{
    int Index = 0;
    return Obj->Unknown04.FUN_1098e160(Item, Index);
}
