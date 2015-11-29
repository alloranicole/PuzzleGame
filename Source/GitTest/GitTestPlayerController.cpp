// Copyright 1998-2015 Epic Games, Inc. All Rights Reserved.

#include "GitTest.h"
#include "GitTestPlayerController.h"

AGitTestPlayerController::AGitTestPlayerController()
{
	bShowMouseCursor = true;
	bEnableClickEvents = true;
	bEnableTouchEvents = true;
	DefaultMouseCursor = EMouseCursor::Hand;
}
