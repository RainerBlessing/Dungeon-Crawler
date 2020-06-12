#include "pch.h"
#include "GameCharacter.h"

int GameCharacter::takeDamage(int amount)
{
    int damage = amount - defence;
    
    if (damage > amount || damage < 0)
        damage = 0;
    
    currentHealth -= damage;

    if (currentHealth < 0) {
        currentHealth = 0;
    }

    return damage;
}
