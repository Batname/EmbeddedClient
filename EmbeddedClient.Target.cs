// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;
using System.Collections.Generic;

[SupportedPlatforms("Linux", "LinuxAArch64")]
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

		// Epic Games Launcher needs to run on OS X 10.9, so RemoteDeployment needs this as well
		bEnableOSX109Support = true;

		// Need to disable the bundled version of dbghelp so that CrashDebugHelper can load dbgeng.dll.
		WindowsPlatform.bUseBundledDbgHelp = false;
	}
}
