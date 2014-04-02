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

	/**
	 * class Item: this class is the basic implementation of an Item
	 */
	class Item{
	private:
		String _name;
		float _unitWeight;
		float _minUnitPrice;
		float _meanUnitPrice;
		float _maxUnitPrice;
	public:
		Item(String Name,float unitWeight, float minPrice, float maxPrice);
		~Item(void);
		void computeMeanValue(void);
		Vector3 getPrices(void);
		String getName(void);
	};

	/**
	 * Goods class: this class is a mapping between a given item and its
	 * stored quantity. The class provides basic funtions to get rapidely
	 * those useful variables.
	 */
	class Goods{
	private:
		Item _item;
		int _quantity;
		float _weigth;
	public:
		Goods(std::map<uint32,Item> * ItemMap ,uint32 ItemID, int qty);
		~Goods(void);
		void computeWeigth(void);
		float getWeigth(void);
		int getQty(void);
		void setQty(int);
		void setItem(uint32 ItemID);
	};

	/**
	 * a basic inventory class. This is only a class where the goods are
	 * stored, nothing related to graphical output or representation of the
	 * inventory.
	 */
	class Inventory{
	private:
		float _goldAmount;
		vector<Goods> _goods;
	public:
		void addStuff(Goods goods);
		void addGold(float gold);
		float getGoldAmount(void);
		std::vector<String> getGoodsList(void);

	};

//	class Cloth : public Item{
//
//	};
//
//	class Weapon : public Item{
//
//	};
//
//	class Armor : public Cloth{
//
//	};
//
//
//	class Ship{
//	private:
//		Inventory * _inventory;
//		CannonList * _cannonList;
//	};
//
//	class CannonList{
//
//	};
//
//
//	class StaticWeapon{
//
//	};
//
//	class Cannon : public StaticWeapon{
//
//	};

} // end namespace


#endif
