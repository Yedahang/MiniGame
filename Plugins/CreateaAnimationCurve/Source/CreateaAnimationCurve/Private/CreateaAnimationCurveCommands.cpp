// Copyright Epic Games, Inc. All Rights Reserved.

#include "CreateaAnimationCurveCommands.h"

#define LOCTEXT_NAMESPACE "FCreateaAnimationCurveModule"

void FCreateaAnimationCurveCommands::RegisterCommands()
{
	UI_COMMAND(PluginAction, "CreateaAnimationCurve", "Execute CreateaAnimationCurve action", EUserInterfaceActionType::Button, FInputChord());
}

#undef LOCTEXT_NAMESPACE
