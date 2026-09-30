// Engine/FFrame.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

// Handoff (not compiled by the worker): needs include/Core/Core.h to declare
//   FFrame::FFrame(UObject* InObject, UStruct* InNode, INT CodeOffset, void* InLocals);
//   UStruct: BYTE Unknown34[0x14]; TArray<BYTE> Script;   // 0x48
//   template <class T> class TArray : public FArray { T& operator()(INT i) { return ((T*)Data)[i]; } };
// v5.cpp is the same constructor with those declarations local to the file: 100.0.
#include "Core/Core.h"

// FUNCTION: 0x10B0FCA0 ??0FFrame@@QAE@PAVUObject@@PAVUStruct@@HPAX@Z
FFrame::FFrame(UObject* InObject, UStruct* InNode, INT CodeOffset, void* InLocals)
    : Node(InNode), Object(InObject), Code(&InNode->Script(CodeOffset)), Locals((BYTE*)InLocals)
{
}
