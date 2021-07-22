// Fill out your copyright notice in the Description page of Project Settings.


#include "WeaponElementData.h"

float UWeaponElementData::ScaleDamage(float damageAmount, UWeaponElementData* elementType) {
	if (elementType->strength != NULL && elementType->strength->elementName.Equals(elementName)) {
		return 2.f;
	} else if (elementType->weakness != NULL && elementType->weakness->elementName.Equals(elementName)) {
		return 0.5f;
	} else {
		return 1.f;
	}
}

