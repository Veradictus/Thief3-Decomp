// Game/AT3MovementModel.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

enum EInternal { EC_Internal };

inline void* operator new(unsigned int, EInternal* Mem)
{
    return Mem;
}

class AT3MovementModel
{
public:
    AT3MovementModel();
    static void InternalConstructor(void* X);
};

// FUNCTION: 0x10964520 ?InternalConstructor@AT3MovementModel@@SAXPAX@Z
void AT3MovementModel::InternalConstructor(void* X)
{
    new ((EInternal*)X) AT3MovementModel();
}
