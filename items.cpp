//CSCI1300 Fall 2020
//Author: Cassie Wildman
//Recitation: 514 - Chris Gavin
//Project 3 - Item Class

#include <iostream>
#include "items.h"

using namespace std;
item::item()
{
    name = "";
    type = "";
    rating = 0;
    weight = 0;
    value = 0;
    bool equipped = false;

}
item::item(string newName, string newType, int newRating, int newWeight, int newValue)
{
    name = newName;
    type = newType;
    rating = newRating;
    weight = newWeight;
    value = newValue;
}

string item::getName()
{
    return name;
}

void item::setName(string itemName)
{
    name = itemName;
}

string item::getType()
{
    return type;
}

void item::setType(string itemType)
{
    type = itemType;
}

int item::getRating()
{
    return rating;
}

void item::setRating(int itemRating)
{
    rating = itemRating;
}

int item::getWeight()
{
    return weight;
}

void item::setWeight(int itemWeight)
{
    weight = itemWeight;
}

int item::getValue()
{
    return value;
}

void item::setValue(int itemValue)
{
    value = itemValue;
}

bool item::getEquipped()
{
    if (equipped == true)
    {
        return true;
    }
    else
    {
        return false;
    }
    
}

void item::setEquipped(bool status)
{
    if (status == 1)
    {
        equipped = true;
    }
    else
    {
        equipped = false;
    }
}
