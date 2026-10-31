// Game/AIContextScalarUpdate.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

#include "Game/Class_10C7D570.h"
#include "Game/Class_10BBDB40.h"

float GetFrameDeltaTime();

extern float DAT_10eafbdc;

// Limited view of fields observed in this method; no total class size asserted.
class Class_10BBB410 {
public:
    void FUN_10bb8ae0();
    char Unknown00[8];
    Class_10C7D570* Owner;
    char Unknown0C[0x254];
    float Scalar;
};

// FUNCTION: 0x10BB8AE0 ?FUN_10bb8ae0@Class_10BBB410@@QAEXXZ
void Class_10BBB410::FUN_10bb8ae0()
{
    double oldValue = Scalar;
    double rate = Owner->FUN_10dbd510()->GetFloat(0x001004B7);
    Scalar = oldValue - rate * GetFrameDeltaTime();
    Scalar = DAT_10eafbdc >= Scalar ? 0.0f : Scalar;
}
