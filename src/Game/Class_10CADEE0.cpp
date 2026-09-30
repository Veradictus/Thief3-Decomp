// Game/Class_10CADEE0.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

#include "Core/Core.h"

struct InputData_10CADEE0
{
    int field0;
    int field4;
    int field8;
    int fieldC;
};

class Class_10CADEE0
{
public:
    char Unknown000[0xE0];
    int fieldE0;
    int fieldE4;
    int fieldE8;
    int fieldEC;

    void FUN_10cadee0(InputData_10CADEE0* In);
};

// FUNCTION: 0x10CADEE0 ?FUN_10cadee0@Class_10CADEE0@@QAEXPAUInputData_10CADEE0@@@Z
void Class_10CADEE0::FUN_10cadee0(InputData_10CADEE0* In)
{
    this->fieldE0 = In->field0;
    this->fieldE4 = In->field4;
    this->fieldE8 = In->field8;
    this->fieldEC = In->fieldC;
}
