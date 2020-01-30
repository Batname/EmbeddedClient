// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;
using System.Collections.Generic;

[SupportedPlatforms("LinuxAArch64")]
[SupportedConfigurations(UnrealTargetConfiguration.Debug, UnrealTargetConfiguration.Development, UnrealTargetConfiguration.Shipping)]
public class EmbeddedClientTarget : TargetRules
{
	public EmbeddedClientTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Program;
		LinkType = TargetLinkType.Monolithic;
		UndecoratedConfiguration = UnrealTargetConfiguration.Shipping;

		LaunchModuleName = "EmbeddedClient";

		bLegalToDistributeBinary = true;

		bBuildDeveloperTools = false;

		bCompileAgainstEngine = false;
		bCompileAgainstCoreUObject = true;
		bUseLoggingInShipping = true;

		// the linker.
		bHasExports = false;

		bUseChecksInShipping = true;

		GlobalDefinitions.Add("PLATFORM_DESKTOP=0");
	}
}
