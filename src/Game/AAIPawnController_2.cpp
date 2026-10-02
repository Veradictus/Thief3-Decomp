// Game/AAIPawnController_2.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

class Class_10B9B8D0
{
public:
    Class_10B9B8D0();

    int Unknown00;
};

class AAIController
{
public:
    AAIController();
    ~AAIController();

    virtual void Virtual0();

    char Unknown04[0x110];
};

class AAIPawnController : public AAIController
{
public:
    AAIPawnController();

    virtual void Virtual0();

    unsigned int initialized : 1;
    Class_10B9B8D0 Unknown118;
};

// FUNCTION: 0x109627C0 ??0AAIPawnController@@QAE@XZ
AAIPawnController::AAIPawnController()
{
}
