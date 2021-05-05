//CSCI1300 Fall 2020
//Author: Cassie Wildman
//Recitation: 514 - Chris Gavin
//Project 3 - Player Class

#include "player.h"
#include <iomanip>
#include <cstdlib>
#include <ctime>

using namespace std;

player::player() //Default//
{
    name = "Prisoner";
    race = "Nord";
    gender = "M";
    health = 100.0;
}

player::player(string playerName, string playerRace, string playerGender)
{
    name = playerName;
    race = playerRace;
    gender = playerGender;
    health = 100.0;
}

string player::getPlayerName()
{
    return name;
}

void player::setPlayerName(string playerName)
{
    name = playerName;
}

string player::getPlayerRace()
{
    return race;
}

void player::setPlayerRace(string playerRace)
{
    race = playerRace;
}

string player::getPlayerGender()
{
    return gender;
}

void player::setPlayerGender(string playerGender)
{
    gender = playerGender;
}

int player::getHealth()
{
    return health;
}
void player::setHealth(int newHealth) // Used for resetting health back to 100 at the end of battles
{
    health = newHealth;
}


double player::takeDamage(item attackWeapon, item receivingArmor) // Damage calculator factoring in armor
{
    srand(time(NULL));
    int timesHit = (rand() % 10) + 1; // Randomized number of potential attack hits
    double damageReductionPer = (.12 * (receivingArmor.getRating() + 100)  / 100); // Find percentage of damage to reduce. Equation adapted from the original game - formula can be found here: https://en.uesp.net/wiki/Skyrim:Armor
    double totalDamage = (attackWeapon.getRating() * damageReductionPer) * timesHit; // Apply damage reduction and multiply the damage by number of hits
    
    health -= totalDamage;
    return totalDamage ;
}

void player::usePotion(item potion) // Use and remove potion from the inventory
{
    health += potion.getRating();
    playerInventory.removeItem(potion);
}

bool player::alive() // Check if the player is alive
{
    if (health > 0)
    {
        return true;
    }
    else
    {
        return false;
    }
}

void player::setEquipedWeapon(item newWeapon)
{
    newWeapon.setEquipped("Y");
    equipedWeapon.setEquipped("N");
    equipedWeapon = newWeapon;
}

item player::getEquippedWeapon()
{
    return equipedWeapon;
}

void player::setEquipedArmor(item newArmor)
{
    equipedArmor = newArmor;
}

item player::getEquippedArmor()
{
    return equipedArmor;
}