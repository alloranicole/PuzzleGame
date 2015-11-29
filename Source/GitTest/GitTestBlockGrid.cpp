// Copyright 1998-2015 Epic Games, Inc. All Rights Reserved.

#include "GitTest.h"
#include "GitTestBlockGrid.h"
#include "GitTestBlock.h"
#include "Components/TextRenderComponent.h"

#define LOCTEXT_NAMESPACE "PuzzleBlockGrid"

AGitTestBlockGrid::AGitTestBlockGrid()
{
	// Create dummy root scene component
	DummyRoot = CreateDefaultSubobject<USceneComponent>(TEXT("Dummy0"));
	RootComponent = DummyRoot;

	// Create static mesh component
	MoveText = CreateDefaultSubobject<UTextRenderComponent>(TEXT("ScoreText0"));
	MoveText->SetRelativeLocation(FVector(200.f,0.f,0.f));
	MoveText->SetRelativeRotation(FRotator(90.f,0.f,0.f));
	MoveText->SetText(FText::Format(LOCTEXT("ScoreFmt", "Moves: {0}"), FText::AsNumber(50)));
	MoveText->AttachTo(DummyRoot);

	// Set defaults
	Size = 5;
	BlockSpacing = 300.f;
}


void AGitTestBlockGrid::BeginPlay()
{
	Super::BeginPlay();

	// Number of blocks
	const int32 NumBlocks = Size * Size;
	AGitTestBlock* Blocks[7][7];

	for(int i = 0; i < Size + 2; i++){
		for (int j = 0; j < Size + 2; j++){
			Blocks[i][j] = NULL;
		}
	}

	// Loop to spawn each block
	for(int32 BlockIndex=0; BlockIndex<NumBlocks; BlockIndex++)
	{
		const float XOffset = (BlockIndex/Size) * BlockSpacing; // Divide by dimension
		const float YOffset = (BlockIndex%Size) * BlockSpacing; // Modulo gives remainder

		// Make postion vector, offset from Grid location
		const FVector BlockLocation = FVector(XOffset, YOffset, 0.f) + GetActorLocation();

		// Spawn a block
		AGitTestBlock* NewBlock = GetWorld()->SpawnActor<AGitTestBlock>(BlockLocation, FRotator(0,0,0));

		// Tell the block about its owner
		if(NewBlock != NULL)
		{
			NewBlock->OwningGrid = this;
		}
	
		Blocks[(BlockIndex/Size)+ 1][(BlockIndex%Size) + 1] = NewBlock;
	}
    
	for (int i = 1; i <= Size; i++){
		for (int j = 1; j <= Size; j++){
			Blocks[i][j]->down = Blocks[i - 1][j];
			Blocks[i][j]->up = Blocks[i + 1][j];
			Blocks[i][j]->right = Blocks[i][j + 1];
			Blocks[i][j]->left = Blocks[i][j - 1];
		}
	}
}


void AGitTestBlockGrid::SubtractMoves()
{
	// Decrement score
	if (Moves != 0){
		Moves--;
		MoveText->SetText(FText::Format(LOCTEXT("ScoreFmt", "Moves: {0}"), FText::AsNumber(Moves)));	
	}
	if (Moves == 0 && !win){
		MoveText->SetText("Game Over! You Lose!");
	} else if (win)
		MoveText->SetText("You Win!");
   
}

#undef LOCTEXT_NAMESPACE
