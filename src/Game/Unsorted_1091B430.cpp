// Game/Unsorted_1091B430.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

class Class_109081E0
{
public:
    Class_109081E0(const Class_109081E0& Other);
    ~Class_109081E0();

    char* Unknown00;
};

struct Struct_1091B430
{
    int Unknown00;
    int Unknown04;
    Class_109081E0 Unknown08;
    int Unknown0C;
    int Unknown10;
    int Unknown14;
    int Unknown18;
};

struct Struct_1091B430_Node
{
    int Unknown00;
    Struct_1091B430 Unknown04;
};

class Class_1091B430
{
public:
    Struct_1091B430 FUN_1091b430();

    Struct_1091B430_Node* Unknown00;
};

// FUNCTION: 0x1091B430 ?FUN_1091b430@Class_1091B430@@QAE?AUStruct_1091B430@@XZ
Struct_1091B430 Class_1091B430::FUN_1091b430()
{
    return Unknown00->Unknown04;
}
