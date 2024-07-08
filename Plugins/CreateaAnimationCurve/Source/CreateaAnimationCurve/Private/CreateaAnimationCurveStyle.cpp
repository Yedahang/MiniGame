// Copyright Epic Games, Inc. All Rights Reserved.

#include "CreateaAnimationCurveStyle.h"
#include "CreateaAnimationCurve.h"
#include "Framework/Application/SlateApplication.h"
#include "Styling/SlateStyleRegistry.h"
#include "Slate/SlateGameResources.h"
#include "Interfaces/IPluginManager.h"
#include "Styling/SlateStyleMacros.h"

#define RootToContentDir Style->RootToContentDir

TSharedPtr<FSlateStyleSet> FCreateaAnimationCurveStyle::StyleInstance = nullptr;

void FCreateaAnimationCurveStyle::Initialize()
{
	if (!StyleInstance.IsValid())
	{
		StyleInstance = Create();
		FSlateStyleRegistry::RegisterSlateStyle(*StyleInstance);
	}
}

void FCreateaAnimationCurveStyle::Shutdown()
{
	FSlateStyleRegistry::UnRegisterSlateStyle(*StyleInstance);
	ensure(StyleInstance.IsUnique());
	StyleInstance.Reset();
}

FName FCreateaAnimationCurveStyle::GetStyleSetName()
{
	static FName StyleSetName(TEXT("CreateaAnimationCurveStyle"));
	return StyleSetName;
}


const FVector2D Icon16x16(16.0f, 16.0f);
const FVector2D Icon20x20(20.0f, 20.0f);

TSharedRef< FSlateStyleSet > FCreateaAnimationCurveStyle::Create()
{
	TSharedRef< FSlateStyleSet > Style = MakeShareable(new FSlateStyleSet("CreateaAnimationCurveStyle"));
	Style->SetContentRoot(IPluginManager::Get().FindPlugin("CreateaAnimationCurve")->GetBaseDir() / TEXT("Resources"));

	Style->Set("CreateaAnimationCurve.PluginAction", new IMAGE_BRUSH_SVG(TEXT("PlaceholderButtonIcon"), Icon20x20));
	return Style;
}

void FCreateaAnimationCurveStyle::ReloadTextures()
{
	if (FSlateApplication::IsInitialized())
	{
		FSlateApplication::Get().GetRenderer()->ReloadTextureResources();
	}
}

const ISlateStyle& FCreateaAnimationCurveStyle::Get()
{
	return *StyleInstance;
}
