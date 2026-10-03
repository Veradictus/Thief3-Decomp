// Game/AAIPathPoint.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

class UObject
{
public:
    virtual void Unknown00();
    virtual void Unknown04();
    virtual ~UObject();

    int Index;
    char Unknown08[0x24];
};

class AActor : public UObject
{
public:
    AActor();
    virtual ~AActor();

    char Unknown2C[0x94];
};

class AMarker : public AActor
{
public:
    virtual ~AMarker();
};

class Class_10BC00A0
{
public:
    Class_10BC00A0();

    int Unknown00;
};

class AAIPathPoint : public AMarker
{
public:
    AAIPathPoint();
    virtual ~AAIPathPoint();

    virtual void Unknown00();

    Class_10BC00A0 Unknown0C0;
};

// FUNCTION: 0x10B93860 ??0AAIPathPoint@@QAE@XZ
AAIPathPoint::AAIPathPoint()
{
}
