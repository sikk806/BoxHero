// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/DSWidgetComponent.h"
#include "UI/DSUserWidget.h"


void UDSWidgetComponent::InitWidget()
{
    Super::InitWidget();

    UDSUserWidget* UserWidget = Cast<UDSUserWidget>(GetWidget());
    if(UserWidget)
    {
        UserWidget->SetOwningActor(GetOwner());
    }

    
}