// Game/AAIPathPoint_7.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

#include "Engine/EngineClasses.h"

class Class_10BBFF10;

class Class_10BC0F30
{
public:
    ~Class_10BC0F30();

    Class_10BBFF10* Unknown00;
};

class AAIPathPoint : public AMarker
{
    DECLARE_CLASS(AAIPathPoint, AMarker, 0x0, AICore)

public:
    virtual void Destroy();
    virtual ~AAIPathPoint();
    virtual void Modify();
    virtual void PostLoad();
    virtual void Serialize(FArchive& Ar);

public:
    Class_10BC0F30 Unknown0C0;
};

// FUNCTION: 0x10B937D0 ??1AAIPathPoint@@UAE@XZ
AAIPathPoint::~AAIPathPoint()
{
    ConditionalDestroy();
}
