// -----------------------------------------------------------------------------
//  Filename:    HOO_gameObjects.h
// -----------------------------------------------------------------------------
//  This source file is part of the
//                         _                __     ___      _
//    /\  /\___  __ _ _ __| |_ ___    ___  / _|   /___\__ _| | __
//   / /_/ / _ \/ _` | '__| __/ __|  / _ \| |_   //  // _` | |/ /
//  / __  /  __/ (_| | |  | |_\__ \ | (_) |  _| / \_// (_| |   <
//  \/ /_/ \___|\__,_|_|   \__|___/  \___/|_|   \___/ \__,_|_|\_\
//
//     __            _
//    /__\ __   __ _(_)_ __   ___
//   /_\| '_ \ / _` | | '_ \ / _ \
//  //__| | | | (_| | | | | |  __/
//  \__/|_| |_|\__, |_|_| |_|\___|
//             |___/
//
// -----------------------------------------------------------------------------
//
//  License
//  This work is free. You can redistribute it and/or modify it under the
//  terms of the "Do What The Fuck You Want To Public License", Version 2,
//  as published by Sam Hocevar. See the file "LICENSE" in the root folder
//  of the project or visit http://www.wtfpl.net/about for more details.
//
//
//  Author
//  Danduk82, alias Andrea Borghi
//
//  Creation date
//  02/04/2014

#ifndef HOO_GAMEOBJECTS_H
#define HOO_GAMEOBJECTS_H

// HOO specific headers
#include "HOO_definitions.h"


namespace HOO{

class Item{
private:
	String _name;
	float _unitWeight;
	float _minUnitValue;
	float _meanUnitValue;
	float _maxUnitValue;
public:
	Item(String Name,float unitWeight, float minValue, float maxValue);
	~Item(void);
	void computeMeanValue(void);
	Vector3 getValues(void);
	String getName(void);
};

class Goods{
private:
	Item _item;
	int _quantity;
	float _weigth;
public:
	Goods(map<uint32,Item> * ItemMap ,uint32 ItemID, int qty);
	~Goods(void);
	void computeWeigth(void);
	float getWeigth(void);
	int getQty(void);
	void setQty(int);
	void setItem(uint32 ItemID);
};

class Inventory{
private:
	float * _goldAmount;
	vector<Goods> * _goods;
};

class Cloth : public Item{

};

class Weapon : public Item{

};

class Armor : public Cloth{

};

class ManualGun : public Weapon{

};

class MeleeWeapon : public Weapon{

};

class Ship{
private:
	Inventory * _inventory;
	CannonList * _cannonList;
};

class CannonList{

};

class Character{

};

class StaticWeapon{

};

class Cannon : public StaticWeapon{

};

class PlayerCharacter : public Character{

};

} // end namespace


#endif
