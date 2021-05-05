//CSCI1300 Fall 2020
//Author: Cassie Wildman
//Recitation: 514 - Chris Gavin
//Project 3 - Inventory Class

#include <iostream>
#include <fstream>
#include "inventory.h"

using namespace std;

inventory::inventory() // Create the category vectors
{
    vector<item> weapons;
    vector<item> armor;
    vector<item> potions;
}

void inventory::addItem(item newItem) // Sort item into correct inventory section by checking item type
{
    if (newItem.getType() == "One Handed" || newItem.getType() == "Two Handed")
    {
        weapons.push_back(newItem);
    }

    if (newItem.getType() == "Light" || newItem.getType() == "Heavy" || newItem.getType() == "Clothing")
    {
        armor.push_back(newItem);
    }

    if (newItem.getType() == "Healing Potion")
    {
        potions.push_back(newItem);
    }
}

void inventory::removeItem(item remove) // Get the type of the item to be removed, go into the respective vector, then erase it.
{
    if (remove.getType() == "One Handed" || remove.getType() == "Two Handed")
    {
        for (int i = 0; i < weapons.size(); i++)
        {
            if (remove.getName() == weapons[i].getName())
            {
                weapons.erase(weapons.begin() + i);
                break;
            }
        }
    }

    if (remove.getType() == "Light" || remove.getType() == "Heavy" || remove.getType() == "Clothing")
    {
        for (int i = 0; i < armor.size(); i++)
        {
            if (remove.getName() == armor[i].getName())
            {
                armor.erase(armor.begin() + i);
                break;
            }
        }
    }

    if (remove.getType() == "Healing Potion")
    {
        for (int i = 0; i < potions.size(); i++)
        {
            if (remove.getName() == potions[i].getName())
            {
                potions.erase(potions.begin() + i);
                break;
            }
        }
    }
}

int inventory::viewItems(string category) // Print everything in the given category along with positon numbers for menu selection by the user
{
    int count = 0;

    if (category == "weapons")
    {
        for (int k = 0; k < weapons.size(); k++)
        {
            cout << (k+1) << ": " << weapons[k].getName() << endl;
            cout << "Damge: " << weapons[k].getRating() << " | Weight: " << weapons[k].getWeight() << " | Value: " << weapons[k].getValue() << endl << endl;
            count++;
        }
    }
    
    else if (category == "armor")
    {
        for (int k = 0; k < armor.size(); k++)
        {
            cout << (k+1) << ": " << armor[k].getName() << endl;
            cout << "Armor: " << armor[k].getRating() << " | Weight: " << armor[k].getWeight() << " | Value: " << armor[k].getValue() << endl <<endl;
            count++;
        }
    }

    else if (category == "potions")
    {
        for (int k = 0; k < potions.size(); k++)
        {
            cout << (k+1) << ": " <<  potions[k].getName() << endl;
            cout << "Heal: " << potions[k].getRating() << " | Weight: " << potions[k].getWeight() << " | Value: " << potions[k].getValue() << endl << endl;
            count++;
        }
    }

    if (count > 0)
    {
        return count;
    }
    else
    {
        return -2; // If the inventory category is empty, return -2
    }
    
}

item inventory::itemToRemove(string category, int index) // Get the number for a desired item, use that number as an index to get the item. Used mostly for removing items
    {
        if (category == "weapons")
        {
            index -= 1; // Subtract 1 because the user is seeing the wrong numbers
            return weapons[index];
        }

        else if (category == "armor")
        {
            index -= 1;
            return armor[index];
        }

        else if (category == "potions")
        {
            index -= 1;
            return potions[index];
        }
        
        return weapons[0]; // control return
    }

int inventory::getVectSize(string category) // Get number of items stored in the given inventory category
{
    return category.size();
}

void inventory::saveInventory(inventory playerInv) // Write the player's inventory to a .txt file for save purposes.
{
    ofstream inventoryFile;
    inventoryFile.open("playerInventory.txt");
    for (int i = 0; i < weapons.size(); i++)
    {
        inventoryFile << weapons[i].getName() << "," << weapons[i].getType() << "," << weapons[i].getRating() << "," << weapons[i].getWeight() << "," << weapons[i].getValue() << "," <<weapons[i].getEquipped() << "\n";
    }
    for (int i = 0; i < armor.size(); i++)
    {
        inventoryFile << armor[i].getName() << "," << armor[i].getType() << "," << armor[i].getRating() << "," << armor[i].getWeight() << "," << armor[i].getValue() << "," << armor[i].getEquipped() << "\n";
    }
    for (int i = 0; i < potions.size(); i++)
    {
        inventoryFile << potions[i].getName() << "," << potions[i].getType() << "," << potions[i].getRating() << "," << potions[i].getWeight() << "," << potions[i].getValue() << "\n";
    }
    inventoryFile.close();
}
