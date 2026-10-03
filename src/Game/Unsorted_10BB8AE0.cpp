// Game/Unsorted_10BB8AE0.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

class AAIPawn;

class Class_10AA9DA0
{
public:
    void* FUN_10aa9da0();
};

struct Struct_10B9BCA0
{
    char Unknown00[8];
    Class_10AA9DA0* Unknown08;
};

class Class_10B9BCA0
{
public:
    char Unknown00[0x118];
    Struct_10B9BCA0* Unknown118;
};

Class_10B9BCA0* FUN_10baa660(AAIPawn* Pawn);

class Class_10c7d570
{
public:
    void* FUN_10c7d570();
};

struct Struct_10BB8BC0
{
    int Unknown00;
    int Unknown04;
    int* Unknown08;
};

class Class_10BB8BC0
{
public:
    int FUN_10bb8bc0();

    char Unknown00[8];
    Class_10c7d570* Unknown08;
};

// FUNCTION: 0x10BB8BC0 ?FUN_10bb8bc0@Class_10BB8BC0@@QAEHXZ
int Class_10BB8BC0::FUN_10bb8bc0()
{
    Class_10B9BCA0* Controller = FUN_10baa660((AAIPawn*)Unknown08->FUN_10c7d570());
    if (Controller && Controller->Unknown118 && Controller->Unknown118->Unknown08)
    {
        Struct_10BB8BC0* List = (Struct_10BB8BC0*)Controller->Unknown118->Unknown08->FUN_10aa9da0();
        if (List->Unknown00)
            return List->Unknown08[0];
    }
    return 0;
}
