// Game/AT3PlayerController_3.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

#include "Engine/EngineClasses.h"

class Class_10B1D190
{
public:
    ~Class_10B1D190();

    void* Unknown00;
};

class AT3PlayerController : public APlayerController
{
    DECLARE_CLASS(AT3PlayerController, APlayerController, 0x4, T3Player)

public:
    virtual ~AT3PlayerController();

    BITFIELD bIsActive:1;
    Class_10B1D190 Unknown2C4;
};

// FUNCTION: 0x10B121F0 ??1AT3PlayerController@@UAE@XZ
AT3PlayerController::~AT3PlayerController()
{
    ConditionalDestroy();
}
