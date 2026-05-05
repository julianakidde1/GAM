// Fill out your copyright notice in the Description page of Project Settings.


#include "GAM_V1/HUDWidget.h"

void UHUDWidget::SetHealthBarPercent(float NewPercent)
{
    if (NewPercent >= 0.0f && NewPercent <= 1.0f)
    {
        HealthBar->SetPercent(NewPercent);
    }
}
