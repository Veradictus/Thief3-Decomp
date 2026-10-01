// Game/UT3GameEngine.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

extern void* DAT_10e78910[];

extern void* DAT_10e7890c[];

class UGameEngine
{
public:
    UGameEngine();

    void** Unknown00;
    char Unknown04[0x28];
    void** Unknown2C;
};

class UT3GameEngine : public UGameEngine
{
public:
    UT3GameEngine();
};

// FUNCTION: 0x10B13630 ??0UT3GameEngine@@QAE@XZ
UT3GameEngine::UT3GameEngine()
{
    Unknown00 = DAT_10e78910;
    Unknown2C = DAT_10e7890c;
}
