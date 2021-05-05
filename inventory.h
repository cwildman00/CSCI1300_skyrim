//CSCI1300 Fall 2020
//Author: Cassie Wildman
//Recitation: 514 - Chris Gavin
//Project 3 - Inventory Class

/*/Purpose:
    -Organize and manage items
/*/

#include "items.h"
#include <vector>
#include <string>

class inventory
{
private:
    vector<item> weapons;
    vector<item> armor;
    vector<item> potions;

public:
    inventory();

    void addItem(item newItem);
    void removeItem (item remove);

    int viewItems(string category);
    item itemToRemove(string category, int index);

    int getVectSize(string category);
    void saveInventory(inventory playerInv);
};