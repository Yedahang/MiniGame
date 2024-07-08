// Copyright Epic Games, Inc. All Rights Reserved.

#include "CreateaAnimationCurve.h"
#include "CreateaAnimationCurveStyle.h"
#include "CreateaAnimationCurveCommands.h"
#include "Misc/MessageDialog.h"
#include "ToolMenus.h"

static const FName CreateaAnimationCurveTabName("CreateaAnimationCurve");

#define LOCTEXT_NAMESPACE "FCreateaAnimationCurveModule"

void FCreateaAnimationCurveModule::StartupModule()
{
	// This code will execute after your module is loaded into memory; the exact timing is specified in the .uplugin file per-module
	
	FCreateaAnimationCurveStyle::Initialize();
	FCreateaAnimationCurveStyle::ReloadTextures();

	FCreateaAnimationCurveCommands::Register();
	
	PluginCommands = MakeShareable(new FUICommandList);

	PluginCommands->MapAction(
		FCreateaAnimationCurveCommands::Get().PluginAction,
		FExecuteAction::CreateRaw(this, &FCreateaAnimationCurveModule::PluginButtonClicked),
		FCanExecuteAction());

	UToolMenus::RegisterStartupCallback(FSimpleMulticastDelegate::FDelegate::CreateRaw(this, &FCreateaAnimationCurveModule::RegisterMenus));
}

void FCreateaAnimationCurveModule::ShutdownModule()
{
	// This function may be called during shutdown to clean up your module.  For modules that support dynamic reloading,
	// we call this function before unloading the module.

	UToolMenus::UnRegisterStartupCallback(this);

	UToolMenus::UnregisterOwner(this);

	FCreateaAnimationCurveStyle::Shutdown();

	FCreateaAnimationCurveCommands::Unregister();
}

void FCreateaAnimationCurveModule::PluginButtonClicked()
{
	// Put your "OnButtonClicked" stuff here
	FText DialogText = FText::Format(
							LOCTEXT("PluginButtonDialogText", "Add code to {0} in {1} to override this button's actions"),
							FText::FromString(TEXT("FCreateaAnimationCurveModule::PluginButtonClicked()")),
							FText::FromString(TEXT("CreateaAnimationCurve.cpp"))
					   );
	FMessageDialog::Open(EAppMsgType::Ok, DialogText);
}

void FCreateaAnimationCurveModule::RegisterMenus()
{
	// Owner will be used for cleanup in call to UToolMenus::UnregisterOwner
	FToolMenuOwnerScoped OwnerScoped(this);

	{
		UToolMenu* Menu = UToolMenus::Get()->ExtendMenu("LevelEditor.MainMenu.Window");
		{
			FToolMenuSection& Section = Menu->FindOrAddSection("WindowLayout");
			Section.AddMenuEntryWithCommandList(FCreateaAnimationCurveCommands::Get().PluginAction, PluginCommands);
		}
	}

	{
		UToolMenu* ToolbarMenu = UToolMenus::Get()->ExtendMenu("LevelEditor.LevelEditorToolBar.PlayToolBar");
		{
			FToolMenuSection& Section = ToolbarMenu->FindOrAddSection("PluginTools");
			{
				FToolMenuEntry& Entry = Section.AddEntry(FToolMenuEntry::InitToolBarButton(FCreateaAnimationCurveCommands::Get().PluginAction));
				Entry.SetCommandList(PluginCommands);
			}
		}
	}
}

#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FCreateaAnimationCurveModule, CreateaAnimationCurve)