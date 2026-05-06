// Copyright Juliana Kidde


#include "Character/GAM_V2CharacterBase.h"

AGAM_V2CharacterBase::AGAM_V2CharacterBase()
{
	PrimaryActorTick.bCanEverTick = false;
	
	Weapon = CreateDefaultSubobject<USkeletalMeshComponent>("Weapon");
	Weapon->SetupAttachment(GetMesh(), FName("WeaponHandSocket"));
	Weapon->SetCollisionEnabled(ECollisionEnabled::NoCollision);

}

void AGAM_V2CharacterBase::BeginPlay()
{
	Super::BeginPlay();
	
}

