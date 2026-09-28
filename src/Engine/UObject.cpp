// Engine/UObject.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

#include "Core/Core.h"

float appFrand();

FVector appVRand();

// FUNCTION: 0x10AFD470 ?execDynArrayLength@UObject@@QAEXAAVFFrame@@QAX@Z
void UObject::execDynArrayLength(FFrame& Stack, RESULT_DECL)
{
    GProperty = NULL;
    Stack.Step(this, NULL);
    if (!GPropAddr)
        return;
    FArray* Array = (FArray*)GPropAddr;
    if (!Result)
        GRuntimeUCFlags |= RUC_ArrayLengthSet;
    else
        *(INT*)Result = Array->Num();
}

// FUNCTION: 0x10AFD550 ?execEndFunctionParms@UObject@@QAEXAAVFFrame@@QAX@Z
void UObject::execEndFunctionParms(FFrame& Stack, RESULT_DECL)
{
    Stack.Code--;
}

// FUNCTION: 0x10AFD560 ?execStop@UObject@@QAEXAAVFFrame@@QAX@Z
void UObject::execStop(FFrame& Stack, RESULT_DECL)
{
    Stack.Code = NULL;
}

// FUNCTION: 0x10AFD810 ?execSelf@UObject@@QAEXAAVFFrame@@QAX@Z
void UObject::execSelf(FFrame& Stack, RESULT_DECL)
{
    *(UObject**)Result = this;
}

// FUNCTION: 0x10AFD900 ?execFinalFunction@UObject@@QAEXAAVFFrame@@QAX@Z
void UObject::execFinalFunction(FFrame& Stack, RESULT_DECL)
{
    CallFunction(Stack, Result, (UFunction*)Stack.ReadObject());
}

// FUNCTION: 0x10AFDB70 ?execFloatConst@UObject@@QAEXAAVFFrame@@QAX@Z
void UObject::execFloatConst(FFrame& Stack, RESULT_DECL)
{
    *(FLOAT*)Result = Stack.ReadFloat();
}

// FUNCTION: 0x10AFDBB0 ?execNameConst@UObject@@QAEXAAVFFrame@@QAX@Z
void UObject::execNameConst(FFrame& Stack, RESULT_DECL)
{
    *(FName*)Result = Stack.ReadName();
}

// FUNCTION: 0x10AFDBD0 ?execByteConst@UObject@@QAEXAAVFFrame@@QAX@Z
void UObject::execByteConst(FFrame& Stack, RESULT_DECL)
{
    *(BYTE*)Result = *Stack.Code++;
}

// FUNCTION: 0x10AFDC10 ?execIntConstByte@UObject@@QAEXAAVFFrame@@QAX@Z
void UObject::execIntConstByte(FFrame& Stack, RESULT_DECL)
{
    *(INT*)Result = *Stack.Code;
    Stack.Code++;
}

// FUNCTION: 0x10AFDC90 ?execPrimitiveCast@UObject@@QAEXAAVFFrame@@QAX@Z
void UObject::execPrimitiveCast(FFrame& Stack, RESULT_DECL)
{
    INT B = *Stack.Code++;
    (Stack.Object->*GCasts[B])(Stack, Result);
}

// FUNCTION: 0x10AFDCB0 ?execByteToInt@UObject@@QAEXAAVFFrame@@QAX@Z
void UObject::execByteToInt(FFrame& Stack, RESULT_DECL)
{
    P_GET_BYTE(V);
    *(INT*)Result = V;
}

// FUNCTION: 0x10AFDCE0 ?execByteToBool@UObject@@QAEXAAVFFrame@@QAX@Z
void UObject::execByteToBool(FFrame& Stack, RESULT_DECL)
{
    P_GET_BYTE(V);
    *(UBOOL*)Result = (V != 0);
}

// FUNCTION: 0x10AFDD10 ?execByteToFloat@UObject@@QAEXAAVFFrame@@QAX@Z
void UObject::execByteToFloat(FFrame& Stack, RESULT_DECL)
{
    P_GET_BYTE(V);
    *(FLOAT*)Result = V;
}

// FUNCTION: 0x10AFDDC0 ?execIntToByte@UObject@@QAEXAAVFFrame@@QAX@Z
void UObject::execIntToByte(FFrame& Stack, RESULT_DECL)
{
    P_GET_INT(A);
    *(BYTE*)Result = (BYTE)A;
}

// FUNCTION: 0x10AFDDF0 ?execIntToFloat@UObject@@QAEXAAVFFrame@@QAX@Z
void UObject::execIntToFloat(FFrame& Stack, RESULT_DECL)
{
    P_GET_INT(V);
    *(FLOAT*)Result = V;
}

// FUNCTION: 0x10AFDEA0 ?execBoolToByte@UObject@@QAEXAAVFFrame@@QAX@Z
void UObject::execBoolToByte(FFrame& Stack, RESULT_DECL)
{
    P_GET_UBOOL(A);
    *(BYTE*)Result = A & 1;
}

// FUNCTION: 0x10AFDED0 ?execBoolToInt@UObject@@QAEXAAVFFrame@@QAX@Z
void UObject::execBoolToInt(FFrame& Stack, RESULT_DECL)
{
    P_GET_UBOOL(V);
    *(INT*)Result = V & 1;
}

// FUNCTION: 0x10AFDF00 ?execBoolToFloat@UObject@@QAEXAAVFFrame@@QAX@Z
void UObject::execBoolToFloat(FFrame& Stack, RESULT_DECL)
{
    P_GET_UBOOL(A);
    *(FLOAT*)Result = (INT)(A & 1);
}

// FUNCTION: 0x10AFDF40 ?execBoolToString@UObject@@QAEXAAVFFrame@@QAX@Z
void UObject::execBoolToString(FFrame& Stack, RESULT_DECL)
{
    P_GET_UBOOL(A);
    *(FString*)Result = A ? "True" : "False";
}

// FUNCTION: 0x10AFDF80 ?execFloatToByte@UObject@@QAEXAAVFFrame@@QAX@Z
void UObject::execFloatToByte(FFrame& Stack, RESULT_DECL)
{
    P_GET_FLOAT(V);
    *(BYTE*)Result = (BYTE)V;
}

// FUNCTION: 0x10AFDFB0 ?execFloatToInt@UObject@@QAEXAAVFFrame@@QAX@Z
void UObject::execFloatToInt(FFrame& Stack, RESULT_DECL)
{
    P_GET_FLOAT(V);
    *(INT*)Result = (INT)V;
}

// FUNCTION: 0x10AFE360 ?execNot_PreBool@UObject@@QAEXAAVFFrame@@QAX@Z
void UObject::execNot_PreBool(FFrame& Stack, RESULT_DECL)
{
    P_GET_UBOOL(A);
    P_FINISH;
    *(DWORD*)Result = !A;
}

// FUNCTION: 0x10AFE9C0 ?execComplement_PreInt@UObject@@QAEXAAVFFrame@@QAX@Z
void UObject::execComplement_PreInt(FFrame& Stack, RESULT_DECL)
{
    P_GET_INT(A);
    P_FINISH;
    *(INT*)Result = ~A;
}

// FUNCTION: 0x10AFEA60 ?execSubtract_PreInt@UObject@@QAEXAAVFFrame@@QAX@Z
void UObject::execSubtract_PreInt(FFrame& Stack, RESULT_DECL)
{
    P_GET_INT(A);
    P_FINISH;
    *(INT*)Result = -A;
}

// FUNCTION: 0x10AFEB60 ?execAdd_IntInt@UObject@@QAEXAAVFFrame@@QAX@Z
void UObject::execAdd_IntInt(FFrame& Stack, RESULT_DECL)
{
    P_GET_INT(A);
    P_GET_INT(B);
    P_FINISH;
    *(INT*)Result = A + B;
}

// FUNCTION: 0x10AFF490 ?execMultiply_FloatFloat@UObject@@QAEXAAVFFrame@@QAX@Z
void UObject::execMultiply_FloatFloat(FFrame& Stack, RESULT_DECL)
{
    P_GET_FLOAT(A);
    P_GET_FLOAT(B);
    P_FINISH;
    *(FLOAT*)Result = A * B;
}

// FUNCTION: 0x10AFFCE0 ?execFRand@UObject@@QAEXAAVFFrame@@QAX@Z
void UObject::execFRand(FFrame& Stack, RESULT_DECL)
{
    P_FINISH;
    *(FLOAT*)Result = appFrand();
}

// FUNCTION: 0x10AFFE10 ?execRotationConst@UObject@@QAEXAAVFFrame@@QAX@Z
void UObject::execRotationConst(FFrame& Stack, RESULT_DECL)
{
    ((FRotator*)Result)->Pitch = Stack.ReadInt();
    ((FRotator*)Result)->Yaw = Stack.ReadInt();
    ((FRotator*)Result)->Roll = Stack.ReadInt();
}

// FUNCTION: 0x10AFFE40 ?execVectorConst@UObject@@QAEXAAVFFrame@@QAX@Z
void UObject::execVectorConst(FFrame& Stack, RESULT_DECL)
{
    *(FVector*)Result = *(FVector*)Stack.Code;
    Stack.Code += sizeof(FVector);
}

// FUNCTION: 0x10B00580 ?execAdd_VectorVector@UObject@@QAEXAAVFFrame@@QAX@Z
void UObject::execAdd_VectorVector(FFrame& Stack, RESULT_DECL)
{
    P_GET_VECTOR(A);
    P_GET_VECTOR(B);
    P_FINISH;
    *(FVector*)Result = A + B;
}

// FUNCTION: 0x10B00F30 ?execVRand@UObject@@QAEXAAVFFrame@@QAX@Z
void UObject::execVRand(FFrame& Stack, RESULT_DECL)
{
    P_FINISH;
    *(FVector*)Result = appVRand();
}

// FUNCTION: 0x10B014C0 ?execAdd_RotatorRotator@UObject@@QAEXAAVFFrame@@QAX@Z
void UObject::execAdd_RotatorRotator(FFrame& Stack, RESULT_DECL)
{
    P_GET_ROTATOR(A);
    P_GET_ROTATOR(B);
    P_FINISH;
    *(FRotator*)Result = A + B;
}

// FUNCTION: 0x10B02200 ?execLen@UObject@@QAEXAAVFFrame@@QAX@Z
void UObject::execLen(FFrame& Stack, RESULT_DECL)
{
    P_GET_STR(S);
    P_FINISH;
    *(INT*)Result = S.Len();
}

// FUNCTION: 0x10B028B0 ?execHighNative0@UObject@@QAEXAAVFFrame@@QAX@Z
void UObject::execHighNative0(FFrame& Stack, RESULT_DECL)
{
    BYTE B = *Stack.Code++;
    (this->*GNatives[0 * 256 + B])(Stack, Result);
}

// FUNCTION: 0x10B028E0 ?execHighNative1@UObject@@QAEXAAVFFrame@@QAX@Z
void UObject::execHighNative1(FFrame& Stack, RESULT_DECL)
{
    BYTE B = *Stack.Code++;
    (this->*GNatives[1 * 256 + B])(Stack, Result);
}

// FUNCTION: 0x10B02910 ?execHighNative2@UObject@@QAEXAAVFFrame@@QAX@Z
void UObject::execHighNative2(FFrame& Stack, RESULT_DECL)
{
    BYTE B = *Stack.Code++;
    (this->*GNatives[2 * 256 + B])(Stack, Result);
}

// FUNCTION: 0x10B02940 ?execHighNative3@UObject@@QAEXAAVFFrame@@QAX@Z
void UObject::execHighNative3(FFrame& Stack, RESULT_DECL)
{
    BYTE B = *Stack.Code++;
    (this->*GNatives[3 * 256 + B])(Stack, Result);
}

// FUNCTION: 0x10B02970 ?execHighNative4@UObject@@QAEXAAVFFrame@@QAX@Z
void UObject::execHighNative4(FFrame& Stack, RESULT_DECL)
{
    BYTE B = *Stack.Code++;
    (this->*GNatives[4 * 256 + B])(Stack, Result);
}

// FUNCTION: 0x10B029A0 ?execHighNative5@UObject@@QAEXAAVFFrame@@QAX@Z
void UObject::execHighNative5(FFrame& Stack, RESULT_DECL)
{
    BYTE B = *Stack.Code++;
    (this->*GNatives[5 * 256 + B])(Stack, Result);
}

// FUNCTION: 0x10B029D0 ?execHighNative6@UObject@@QAEXAAVFFrame@@QAX@Z
void UObject::execHighNative6(FFrame& Stack, RESULT_DECL)
{
    BYTE B = *Stack.Code++;
    (this->*GNatives[6 * 256 + B])(Stack, Result);
}

// FUNCTION: 0x10B02A00 ?execHighNative7@UObject@@QAEXAAVFFrame@@QAX@Z
void UObject::execHighNative7(FFrame& Stack, RESULT_DECL)
{
    BYTE B = *Stack.Code++;
    (this->*GNatives[7 * 256 + B])(Stack, Result);
}

// FUNCTION: 0x10B02A30 ?execHighNative8@UObject@@QAEXAAVFFrame@@QAX@Z
void UObject::execHighNative8(FFrame& Stack, RESULT_DECL)
{
    BYTE B = *Stack.Code++;
    (this->*GNatives[8 * 256 + B])(Stack, Result);
}

// FUNCTION: 0x10B02A60 ?execHighNative9@UObject@@QAEXAAVFFrame@@QAX@Z
void UObject::execHighNative9(FFrame& Stack, RESULT_DECL)
{
    BYTE B = *Stack.Code++;
    (this->*GNatives[9 * 256 + B])(Stack, Result);
}

// FUNCTION: 0x10B02A90 ?execHighNative10@UObject@@QAEXAAVFFrame@@QAX@Z
void UObject::execHighNative10(FFrame& Stack, RESULT_DECL)
{
    BYTE B = *Stack.Code++;
    (this->*GNatives[10 * 256 + B])(Stack, Result);
}

// FUNCTION: 0x10B02AC0 ?execHighNative11@UObject@@QAEXAAVFFrame@@QAX@Z
void UObject::execHighNative11(FFrame& Stack, RESULT_DECL)
{
    BYTE B = *Stack.Code++;
    (this->*GNatives[11 * 256 + B])(Stack, Result);
}

// FUNCTION: 0x10B02AF0 ?execHighNative12@UObject@@QAEXAAVFFrame@@QAX@Z
void UObject::execHighNative12(FFrame& Stack, RESULT_DECL)
{
    BYTE B = *Stack.Code++;
    (this->*GNatives[12 * 256 + B])(Stack, Result);
}

// FUNCTION: 0x10B02B20 ?execHighNative13@UObject@@QAEXAAVFFrame@@QAX@Z
void UObject::execHighNative13(FFrame& Stack, RESULT_DECL)
{
    BYTE B = *Stack.Code++;
    (this->*GNatives[13 * 256 + B])(Stack, Result);
}

// FUNCTION: 0x10B02B50 ?execHighNative14@UObject@@QAEXAAVFFrame@@QAX@Z
void UObject::execHighNative14(FFrame& Stack, RESULT_DECL)
{
    BYTE B = *Stack.Code++;
    (this->*GNatives[14 * 256 + B])(Stack, Result);
}

// FUNCTION: 0x10B02B80 ?execHighNative15@UObject@@QAEXAAVFFrame@@QAX@Z
void UObject::execHighNative15(FFrame& Stack, RESULT_DECL)
{
    BYTE B = *Stack.Code++;
    (this->*GNatives[15 * 256 + B])(Stack, Result);
}

// FUNCTION: 0x10B02C90 ?execSaveConfig@UObject@@QAEXAAVFFrame@@QAX@Z
void UObject::execSaveConfig(FFrame& Stack, RESULT_DECL)
{
    P_FINISH;
    SaveConfig(0, NULL);
}

// FUNCTION: 0x10B02CB0 ?execResetConfig@UObject@@QAEXAAVFFrame@@QAX@Z
void UObject::execResetConfig(FFrame& Stack, RESULT_DECL)
{
    P_FINISH;
    ResetConfig(GetClass());
}

// FUNCTION: 0x10B02E50 ?execIsA@UObject@@QAEXAAVFFrame@@QAX@Z
void UObject::execIsA(FFrame& Stack, RESULT_DECL)
{
    P_GET_NAME(ClassName);
    P_FINISH;
    UClass* TempClass;
    for (TempClass = GetClass(); TempClass; TempClass = (UClass*)TempClass->SuperField)
        if (TempClass->GetFName() == ClassName)
            break;
    *(DWORD*)Result = TempClass != NULL;
}

// FUNCTION: 0x10B04810 ?execStaticSaveConfig@UObject@@QAEXAAVFFrame@@QAX@Z
void UObject::execStaticSaveConfig(FFrame& Stack, RESULT_DECL)
{
    P_FINISH;
    GetClass()->ClassDefaultObject->SaveConfig(0, NULL);
}
