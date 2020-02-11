// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;
using System.IO;

public class EmbeddedClient : ModuleRules
{
	public EmbeddedClient(ReadOnlyTargetRules Target) : base(Target)
	{
		PublicIncludePaths.AddRange
		(
			new string[]
			{
				"Programs/EmbeddedClient/Private",
				"Runtime/Launch/Public",
				"Developer/DesktopPlatform/Public",
			}
		);

		PrivateIncludePathModuleNames.Add("GPIORuntime");
		//PrivateIncludePaths.Add(Path.Combine(EngineDirectory, "Plugins/PaspberryPi/GPIO/Source/GPIORuntime/Public"));

		PrivateDependencyModuleNames.AddRange(
			new string[]
			{
				"Core",
				"CoreUObject",
				"ApplicationCore",
				"HTTP",
				"Projects",
				"LauncherPlatform",
				"MessageLog",
                "Messaging",
                "MessagingCommon",
                "UdpMessaging",
				"TcpMessaging",
				"GPIORuntime",
				"DesktopPlatform"
			}
		);
	}
}
