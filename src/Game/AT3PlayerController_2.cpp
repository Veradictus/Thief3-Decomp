// Game/AT3PlayerController_2.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

class Class_10A03400
{
public:
    Class_10A03400* FUN_10a03400();

    int Unknown00;
};

class UObject
{
public:
    virtual void Unknown00();
    virtual void Unknown04();
    virtual ~UObject();
};

class AController : public UObject
{
public:
    virtual void Unknown00();
};

class APlayerController : public AController
{
public:
    APlayerController();
    virtual ~APlayerController();

    char Unknown04[0x2BC];
};

class AT3PlayerController : public APlayerController
{
public:
    AT3PlayerController();
    virtual ~AT3PlayerController();

    unsigned int bIsActive : 1;
    Class_10A03400 Unknown2C4;
};

// FUNCTION: 0x10B12170 ??0AT3PlayerController@@QAE@XZ
AT3PlayerController::AT3PlayerController()
{
    Unknown2C4.FUN_10a03400();
}
