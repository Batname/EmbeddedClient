// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#include "EmbeddedClientApp.h"
#include "Misc/Parse.h"
#include "Misc/CommandLine.h"
#include "Misc/QueuedThreadPool.h"
#include "Internationalization/Internationalization.h"
#include "Misc/ConfigCacheIni.h"
#include "GenericPlatform/GenericApplication.h"
#include "Misc/App.h"
#include "Modules/ModuleManager.h"
#include "HAL/PlatformApplicationMisc.h"
#include "HAL/PlatformCrashContext.h"
#include "RequiredProgramMainCPPInclude.h"
#include "Dom/JsonObject.h"

#include "PlatformInfo.h"

#define LOCTEXT_NAMESPACE "RunEmbeddedClientApp"

IMPLEMENT_APPLICATION(EmbeddedClientApp, "EmbeddedClientApp");
DEFINE_LOG_CATEGORY(EmbeddedClienLog);


void RunEmbeddedClientApp(const TCHAR* CommandLine) {
    // Override the stack size for the thread pool.
    FQueuedThreadPool::OverrideStackSize = 256 * 1024;

    // Increase the HttpSendTimeout to 5 minutes
    GConfig->SetFloat(TEXT("HTTP"), TEXT("HttpSendTimeout"), 5 * 60.0f, GEngineIni);

    // Initialize the engine. -Messaging enables MessageBus transports required by Concert (Recovery Service).
    FString FinalCommandLine(CommandLine);
    FinalCommandLine.Append(TEXT(" -Messaging"));
    GEngineLoop.PreInit(*FinalCommandLine);
    check(GConfig && GConfig->IsReadyForUse());

    // Make sure all UObject classes are registered and default properties have been initialized
    ProcessNewlyLoadedUObjects();

    // Tell the module manager is may now process newly-loaded UObjects when new C++ modules are loaded
    FModuleManager::Get().StartProcessingNewlyLoadedObjects();

    // Load modules
    FModuleManager::Get().LoadModule(TEXT("UdpMessaging"));
    FModuleManager::Get().LoadModule(TEXT("TcpMessaging"));

    // Load internal Concert plugins in the pre-default phase
    IPluginManager::Get().LoadModulesForEnabledPlugins(ELoadingPhase::PreDefault);

    // Load Concert Sync plugins in default phase
    IPluginManager::Get().LoadModulesForEnabledPlugins(ELoadingPhase::Default);

    // loop while the server does the rest
    while (!IsEngineExitRequested())
    {
        UE_LOG(EmbeddedClienLog, Warning, TEXT("Hello UE4 embedded"));
        FTicker::GetCoreTicker().Tick(FApp::GetDeltaTime());
        FPlatformProcess::Sleep(0.4f);
    }

    FEngineLoop::AppPreExit();
    FModuleManager::Get().UnloadModulesAtShutdown();
    FTaskGraphInterface::Shutdown();

    FEngineLoop::AppExit();
}

#undef LOCTEXT_NAMESPACE
