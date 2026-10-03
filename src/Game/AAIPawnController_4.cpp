// Game/AAIPawnController_4.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

#include "Engine/EngineClasses.h"

class Class_10B9C9A0
{
public:
    ~Class_10B9C9A0();

    void* Unknown00;
};

class AAIPawnController : public AAIController
{
    DECLARE_CLASS(AAIPawnController, AAIController, 0x0, AICore)

public:
    virtual void Destroy();
    virtual ~AAIPawnController();
    virtual void Serialize(FArchive& Ar);

public:
    BITFIELD initialized:1;
    Class_10B9C9A0 Unknown118;
};

// FUNCTION: 0x10962730 ??1AAIPawnController@@UAE@XZ
AAIPawnController::~AAIPawnController()
{
    ConditionalDestroy();
}
