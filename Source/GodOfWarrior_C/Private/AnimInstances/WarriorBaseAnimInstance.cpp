// Jackie Lee .All Rights Reserved


#include "AnimInstances/WarriorBaseAnimInstance.h"

#include "BlueprintFunctionLibrary/WarriorBlueprintFunctionLibrary.h"

bool UWarriorBaseAnimInstance::DoseOwnerHaveTag(FGameplayTag TagToCheck) const
{
	if (APawn* OwningPawn = TryGetPawnOwner())
	{
		return UWarriorBlueprintFunctionLibrary::NativeIsActorHasTag(OwningPawn, TagToCheck);
	}
	return false;
}
