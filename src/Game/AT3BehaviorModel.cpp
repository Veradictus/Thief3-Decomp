// Game/AT3BehaviorModel.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

enum EInternal { EC_Internal };

inline void* operator new(unsigned int, EInternal* Mem)
{
    return Mem;
}

class AT3BehaviorModel
{
public:
    AT3BehaviorModel();
    static void InternalConstructor(void* X);
};

// FUNCTION: 0x109644F0 ?InternalConstructor@AT3BehaviorModel@@SAXPAX@Z
void AT3BehaviorModel::InternalConstructor(void* X)
{
    new ((EInternal*)X) AT3BehaviorModel();
}
