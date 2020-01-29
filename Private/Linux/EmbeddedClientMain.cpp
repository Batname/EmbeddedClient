// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#include "CoreMinimal.h"
#include "Containers/StringConv.h"
#include "Containers/UnrealString.h"
#include "CoreGlobals.h"
#include <locale.h>

/**
 * main(), called when the application is started
 */
int main(int argc, const char *argv[])
{
    FString SavedCommandLine;

    for (int32 Option = 1; Option < argc; Option++)
    {
        SavedCommandLine += TEXT(" ");
        SavedCommandLine += UTF8_TO_TCHAR(argv[Option]);	// note: technically it depends on locale
    }

    // assume unattended if we don't have X11 display
    if (getenv("DISPLAY") == nullptr)
    {
        SavedCommandLine += TEXT(" -unattended");
    }

    // Run the app
    RunEmbeddedClientApp(*SavedCommandLine);

    return 0;
}
