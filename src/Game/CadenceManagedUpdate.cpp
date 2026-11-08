// Game/CadenceManagedUpdate.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

#include "Game/CadenceReceiverView.h"

Class_10C41420* GetSoundBufferPool();

// FUNCTION: 0x10C5DC60 ?FUN_10c5dc60@Class_10C80360@@QAEXM@Z
void Class_10C80360::FUN_10c5dc60(float A)
{
    if (m_Guard0D)
    {
        for (int Channel = 0; Channel < 4; ++Channel)
        {
            if (Channel != m_SelectedIndex3C)
                m_Flags38[Channel] = 1;
        }

        for (int Index = GetSoundBufferPool()->GetItemCount() - 1; Index >= 0; --Index)
        {
            cRefPtr Object = GetSoundBufferPool()->GetItem(Index);
            if (Object.m_Object && !Object.m_Object->FUN_10c63d50() && Object.m_Object->FUN_10c63dc0())
                Object.m_Object->FUN_10c63f40();
        }
    }
}
