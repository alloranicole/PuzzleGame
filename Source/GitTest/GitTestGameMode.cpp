// Copyright 1998-2015 Epic Games, Inc. All Rights Reserved.

#include "GitTest.h"
#include "GitTestGameMode.h"
#include "GitTestPlayerController.h"

AGitTestGameMode::AGitTestGameMode()
{
	// no pawn by default
	DefaultPawnClass = NULL;
	// use our own player controller class
	PlayerControllerClass = AGitTestPlayerController::StaticClass();
}
