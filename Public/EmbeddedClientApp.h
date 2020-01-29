// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#pragma once

// Pre-compiled header includes
#include "CoreMinimal.h"
#include "Logging/LogMacros.h"


DECLARE_LOG_CATEGORY_EXTERN(EmbeddedClienLog, Log, All)

void RunEmbeddedClientApp(const TCHAR* Commandline);
