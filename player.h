//CSCI1300 Fall 2020
//Author: Cassie Wildman
//Recitation: 514 - Chris Gavin
//Project 3 - Player Class

/*/Purpose:
    -Create character
    -Manage health
    -Manage equipped items
/*/

#include <string>
#include "inventory.h"
using namespace std;

class player
{
private:
    string name;
    string race;
    string gender;
    double health;
    item equipedWeapon;
    item equipedArmor;

public:
    player();
    player(string playerName, string playerRace, string playerGender);

    inventory playerInventory;

    string getPlayerName();
    void setPlayerName(string playerName);

    string getPlayerRace();
    void setPlayerRace(string playerRace);

    string getPlayerGender();
    void setPlayerGender(string playerGender);

    int getHealth();
    void setHealth(int newHealth);


    double takeDamage(item attackWeapon, item receivingArmor); //Pull opponent weapon and find the damage, then subtract from health. Return new health.
    void usePotion(item potion); //Pull potion and find the healing rating, add to health. Delete from vector, return new health.
    
    bool alive(); //Check health status

    void setEquipedWeapon(item newWeapon);
    item getEquippedWeapon();

    void setEquipedArmor(item newArmor);
    item getEquippedArmor();
};