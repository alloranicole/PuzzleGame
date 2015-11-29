// Copyright 1998-2015 Epic Games, Inc. All Rights Reserved.

#include "GitTest.h"
#include "GitTestBlock.h"
#include "GitTestBlockGrid.h"

AGitTestBlock::AGitTestBlock()
{
	// Structure to hold one-time initialization
	struct FConstructorStatics
	{
		ConstructorHelpers::FObjectFinderOptional<UStaticMesh> PlaneMesh;
		ConstructorHelpers::FObjectFinderOptional<UMaterialInstance> PurpleMaterial;
		ConstructorHelpers::FObjectFinderOptional<UMaterialInstance> GreenMaterial;
		FConstructorStatics()
			: PlaneMesh(TEXT("/Game/Puzzle/Meshes/PuzzleCube.PuzzleCube"))
			, PurpleMaterial(TEXT("/Game/Puzzle/Meshes/PurpleMaterial.PurpleMaterial"))
			, GreenMaterial(TEXT("/Game/Puzzle/Meshes/GreenMaterial.GreenMaterial"))
		{
		}
	};
	static FConstructorStatics ConstructorStatics;

	// Create dummy root scene component
	DummyRoot = CreateDefaultSubobject<USceneComponent>(TEXT("Dummy0"));
	RootComponent = DummyRoot;

	// Create static mesh component
	BlockMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BlockMesh0"));
	BlockMesh->SetStaticMesh(ConstructorStatics.PlaneMesh.Get());
	BlockMesh->SetRelativeScale3D(FVector(1.f,1.f,0.25f));
	BlockMesh->SetRelativeLocation(FVector(0.f,0.f,25.f));
	//Sets the starting material color
	BlockMesh->SetMaterial(0, ConstructorStatics.PurpleMaterial.Get());
	BlockMesh->AttachTo(DummyRoot);
	BlockMesh->OnClicked.AddDynamic(this, &AGitTestBlock::BlockClicked);
	BlockMesh->OnInputTouchBegin.AddDynamic(this, &AGitTestBlock::OnFingerPressedBlock);

	// Save a pointer to the green and purple material
	GreenMaterial = ConstructorStatics.GreenMaterial.Get();
	PurpleMaterial = ConstructorStatics.PurpleMaterial.Get();

}

void AGitTestBlock::BlockClicked(UPrimitiveComponent* ClickedComp)
{
	int count = 0, uncount = 0;
	// Check we are not already active
	if(!bIsActive)
	{
		bIsActive = true;
		if (left){
			if (left->bIsActive == false){
				left->bIsActive = true;
				left->BlockMesh->SetMaterial(0, GreenMaterial);
				count++;
			}
			else if (left->bIsActive == true){
				left->bIsActive = false;
				left->BlockMesh->SetMaterial(0, PurpleMaterial);
				uncount++;
			}
		}
		if (right){
			if (right->bIsActive == false){
				right->bIsActive = true;
				right->BlockMesh->SetMaterial(0, GreenMaterial);
				count++;
			}
			else if (right->bIsActive == true){
				right->bIsActive = false;
				right->BlockMesh->SetMaterial(0, PurpleMaterial);
				uncount++;
			}
		}
		if (up){
			if (up->bIsActive == false){
				up->bIsActive = true;
				up->BlockMesh->SetMaterial(0, GreenMaterial);
				count++;
			}
			else if (up->bIsActive == true){
				up->bIsActive = false;
				up->BlockMesh->SetMaterial(0, PurpleMaterial);
				uncount++;
			}
		}
		if (down){
			if (down->bIsActive == false){
				down->bIsActive = true;
				down->BlockMesh->SetMaterial(0, GreenMaterial);
				count++;
			}
			else if (down->bIsActive == true){
				down->bIsActive = false;
				down->BlockMesh->SetMaterial(0, PurpleMaterial);
				uncount++;
			}
		}
		// Change material
		BlockMesh->SetMaterial(0, GreenMaterial);
		count++;

		// Tell the Grid
		if(OwningGrid != NULL)
		{
			//Counts green blocks
			OwningGrid->greencount += count;
			OwningGrid->greencount -= uncount;
			if (OwningGrid->greencount == 25){
				OwningGrid->win = true;
			}
			OwningGrid->SubtractMoves();
		}
	}
	else if (bIsActive == true){
		bIsActive = false;
		if (left){
			if (left->bIsActive == false){
				left->bIsActive = true;
				left->BlockMesh->SetMaterial(0, GreenMaterial);
				count++;
			}
			else if (left->bIsActive == true){
				left->bIsActive = false;
				left->BlockMesh->SetMaterial(0, PurpleMaterial);
				uncount++;
			}
		}
		if (right){
			if (right->bIsActive == false){
				right->bIsActive = true;
				right->BlockMesh->SetMaterial(0, GreenMaterial);
				count++;
			}
			else if (right->bIsActive == true){
				right->bIsActive = false;
				right->BlockMesh->SetMaterial(0, PurpleMaterial);
				uncount++;
			}
		}
		if (up){
			if (up->bIsActive == false){
				up->bIsActive = true;
				up->BlockMesh->SetMaterial(0, GreenMaterial);
				count++;
			}
			else if (up->bIsActive == true){
				up->bIsActive = false;
				up->BlockMesh->SetMaterial(0, PurpleMaterial);
				uncount++;
			}
		}
		if (down){
			if (down->bIsActive == false){
				down->bIsActive = true;
				down->BlockMesh->SetMaterial(0, GreenMaterial);
				count++;
			}
			else if (down->bIsActive == true){
				down->bIsActive = false;
				down->BlockMesh->SetMaterial(0, PurpleMaterial);
				uncount++;
			}
		}

		

		//Change material
		BlockMesh->SetMaterial(0, PurpleMaterial);
		uncount++;
		//Tell the Grid
		if (OwningGrid != NULL)
		{
			//Counts green blocks
			OwningGrid->greencount += count;
			OwningGrid->greencount -= uncount; 
			if (OwningGrid->greencount == 25){
				OwningGrid->win = true;
			}
			OwningGrid->SubtractMoves();
		}
	}
		
}



void AGitTestBlock::OnFingerPressedBlock(ETouchIndex::Type FingerIndex, UPrimitiveComponent* TouchedComponent)
{
	BlockClicked(TouchedComponent);
}
