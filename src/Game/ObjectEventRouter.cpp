// Game/ObjectEventRouter.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

struct RoutedObject;

struct RoutedOwner
{
    char Unknown00[0xE8];
    RoutedObject* SuppressedObject;
};

struct RoutedObject
{
    char Unknown00[0x24];
    RoutedOwner* Owner;
};

struct RoutedEvent { int Unknown00; unsigned Id; };

struct RoutedPayload { int Unknown00; int* Value; };

// Physical target-local dispatch and input-manager views; global identities
// are already canonical. No additional virtual semantics are asserted.
class Class_10F46DA0
{
public:
    virtual void Virtual0();
    virtual void Virtual1(void* Signal, int Code, RoutedObject* Object, int Value);
    virtual void Virtual2();
    virtual void Virtual3(void* Signal, int Code, RoutedObject* Object, int Value);
};

class Class_10F3A3D8
{
public:
    char Unknown00[0xDC];
    void* SignalDC;
    void* SignalE0;
    void* SignalE4;
    void* UnknownE8;
    void* SignalEC;
    void* SignalF0;
};

extern Class_10F46DA0* DAT_10f46da0;

extern Class_10F3A3D8* DAT_10f3a3d8;

// FUNCTION: 0x10AC8310 ?RouteObjectEvent@@YGXPAXPAURoutedObject@@PAURoutedEvent@@PAURoutedPayload@@@Z
void __stdcall RouteObjectEvent(void* Unused, RoutedObject* Object, RoutedEvent* Event, RoutedPayload* Payload)
{
    if (Object == Object->Owner->SuppressedObject)
        return;
    switch (Event->Id)
    {
    case 0x2000BA:
        if (Payload->Value && *Payload->Value > 0)
            DAT_10f46da0->Virtual1(DAT_10f3a3d8->SignalEC, 0x10, Object, -1);
        break;
    case 0x803B9:
        if (Payload->Value)
            DAT_10f46da0->Virtual1(DAT_10f3a3d8->SignalE4, 0x10, Object, -1);
        else
            DAT_10f46da0->Virtual3(DAT_10f3a3d8->SignalE4, 0x10, Object, -1);
        break;
    case 0x8001F3:
        if (Payload->Value && *Payload->Value)
            DAT_10f46da0->Virtual1(DAT_10f3a3d8->SignalDC, 0x3C, Object, -1);
        break;
    case 0x80026E:
        if (Payload->Value && *Payload->Value)
            DAT_10f46da0->Virtual1(DAT_10f3a3d8->SignalF0, 0x11, Object, -1);
        break;
    case 0x8001FE:
        if (Payload->Value && *Payload->Value)
            DAT_10f46da0->Virtual1(DAT_10f3a3d8->SignalE0, 0x10, Object, -1);
        break;
    }
}
