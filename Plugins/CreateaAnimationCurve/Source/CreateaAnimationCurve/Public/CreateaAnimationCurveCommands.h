// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Framework/Commands/Commands.h"
#include "CreateaAnimationCurveStyle.h"

class FCreateaAnimationCurveCommands : public TCommands<FCreateaAnimationCurveCommands>
{
public:

	FCreateaAnimationCurveCommands()
		: TCommands<FCreateaAnimationCurveCommands>(TEXT("CreateaAnimationCurve"), NSLOCTEXT("Contexts", "CreateaAnimationCurve", "CreateaAnimationCurve Plugin"), NAME_None, FCreateaAnimationCurveStyle::GetStyleSetName())
	{
	}

	// TCommands<> interface
	virtual void RegisterCommands() override;

public:
	TSharedPtr< FUICommandInfo > PluginAction;
};
