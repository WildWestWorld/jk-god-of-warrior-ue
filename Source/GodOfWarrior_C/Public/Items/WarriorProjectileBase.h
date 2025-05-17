// Jackie Lee .All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
//得导入Niagara插件才能用
#include "GameplayEffectTypes.h"
#include "NiagaraComponent.h"
#include "Abilities/GameplayAbilityTypes.h"
#include "WarriorProjectileBase.generated.h"

class UProjectileMovementComponent;
class UBoxComponent;


UENUM(BlueprintType)
enum class EProjectileDamagePolicy : uint8
{
	OnHit,
	OnBeginOverlap,
};

UCLASS()
class GODOFWARRIOR_C_API AWarriorProjectileBase : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AWarriorProjectileBase();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category="Projectile")
	UBoxComponent* ProjectileCollisionBox;
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category="Projectile")
	UNiagaraComponent* ProjectileNiagaraComponent;
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category="Projectile")
	UProjectileMovementComponent* ProjectileMovementComponent;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Projectile")
	EProjectileDamagePolicy ProjectileDamagePolicy = EProjectileDamagePolicy::OnHit;

	UPROPERTY(BlueprintReadOnly, Category="Projectile", meta = (ExposeOnSpawn = "true"))
	FGameplayEffectSpecHandle ProjectileDamageEffectSpecHandle;

	UFUNCTION()
	virtual void OnProjectileHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
	                             FVector NormalImpulse, const FHitResult& Hit);


	UFUNCTION()
	virtual void OnProjectileBeginOverlap(UPrimitiveComponent*
	                                      OverlappedComponent, AActor* OtherActor, UPrimitiveComponent*
	                                      OtherComp, int32 OtherBodyIndex, bool bFromSweep,
	                                      const FHitResult& SweepResult);
	UFUNCTION(BlueprintImplementableEvent, meta=(DisplayName="On Spawn Projectile Hit FX"))
	void BP_OnSpawnProjectileHitFX(const FVector& HitLocation);

private:
	void HandleApplyProjectileDamage(APawn* InHitPawn, const FGameplayEventData& InPayload);
};
