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


//std::vector<double> vec;
//// ... fill vec with values
//double average = std::accumulate(vec.begin(), vec.end(), 0) / vec.size();

namespace HOO{

	template<class T> float getWeight(T item);

	/**
	 * class Item: this class is the basic implementation of an Item.
	 * It sets the min-max prices for the item, its unit weight, and name.
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
		/**
		 * this methodd simply computes the mean price of the item, in
		 * the constructor only the min and max price are given
		 */
		void computeMeanValue(void);
		/**
		 * this method returns the min/average/max prices ot the item
		 * @return Vector3 = (min, avg, max)
		 */
		Vector3 getPrices(void);
		/**
		 * this method returns the name of the object
		 * @return String name
		 */
		String getName(void);
		/**
		 * get the unit weight of an Item
		 */
		float getWeight(void);
	};

	/**
	 * Goods class: this class is a mapping between a given item and its
	 * stored quantity. The class provides basic functions to get rapidly
	 * those useful variables.
	 */
	class Goods{
	private:
		Item * _item;
		HOO::uint32 _itemUID;
		float _quantity;
		float _weight;

		/**
		 * this method computes the total weight of the stored goods
		 * @see getWeight
		 */
		void computeWeight(void);

	public:
		Goods(std::map<HOO::uint32,Item*> * ItemMap ,HOO::uint32 ItemID, float qty);
		~Goods(void);
		/**
		 * this method returns the total weight of the goods
		 * @see computeWeight
		 */
		float getWeight(void);
		/**
		 * this method returns the quantity of items
		 * @return int qty
		 */
		float getQty(void);
		/**
		 * this method sets the quantity of Items
		 * @param float qty
		 */
		void setQty(float);
		/**
		 * this method removes a certain quantity of items, if the resulting
		 * _quantity is below 0, it sets quantity = 0 and returns the quantity
		 * it could not remove.
		 * @param float qty
		 * @return float rest
		 */
		float removeQty(float);
		/**
		 * this method adds a given quantity of item
		 * @param float qty
		 */
		void addQty(float);
		/**
		 * this method sets the item that the goods instance is representing.
		 * The Item is identified by its UID
		 * @param uint32 ItemID
		 */
		void setItem(std::map<HOO::uint32,Item*> * ItemMap, HOO::uint32 ItemID);
		/**
		 * This method return the UID of the Item the instance is representing
		 * @return uint32 ItemID
		 */
		HOO::uint32 getItem(void);
	};

	/**
	 * a basic inventory class. This is only a class where the goods are
	 * stored, nothing related to graphical output or representation of the
	 * inventory.
	 */
	class Inventory{
	private:
		float _goldAmount;
		std::vector<Goods> _goods;
		float _maxWeight;
		float _currentWeight;
		std::map<HOO::uint32,int> _goodsList;

		/**
		 * this method computes the goods list
		 */
		void computeGoodsList(void);
		/**
		 * computes the sum of the weight of all stored goods
		 * together
		 */
		void computeTotalWeight(void);

	public:
		Inventory(float gold = 0.0f);
		Inventory(float gold, std::vector<Goods> goodsVector);
		~Inventory();
		/**
		 * get the gold amount that is stored in the inventory
		 * @return float amount
		 */
		float getGoldAmount(void);
		/**
		 * get the list of the stored goods and their
		 * respective quantity
		 * @return std::map<uint32 UID, int amount>
		 */
		std::map<uint32,int> getGoodsList(void);
		/**
		 * get the sum of the weight of all stored goods
		 * toghether
		 * @return float total_weight
		 */
		float getTotalWeight(void);
		/**
		 * add gold to the inventory
		 * @param float goldAmount
		 * @return int sucessStatus
		 */
		int addGold(float gold);
		/**
		 * remove gold from the inventory
		 * @param float goldAmount
		 * @return int sucessStatus
		 */
		int removeGold(float gold);
		/**
		 * add one good to the inventory
		 * @param Goods goods
		 * @return int sucessStatus
		 */
		int addStuff(Goods goods);
		/**
		 * add a vector of goods to the inventory
		 * @param std::vector<Goods> goodsVector
		 * @return int sucessStatus
		 */
		int addStuff(std::vector<Goods> goodsVector);
		/**
		 * remove one good from the inventory
		 * @param Goods goods
		 * @return int sucessStatus
		 */
		int removeStuff(Goods goods);
		/**
		 * remove one vector of goods from the inventory
		 * @param std::vector<Goods> goodsVector
		 * @return int sucessStatus
		 */
		int removeStuff(std::vector<Goods> goodsVector);

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



//class Item
inline HOO::Item::Item(String Name,float unitWeight, float minPrice, float maxPrice){
	_minUnitPrice=minPrice;
	_maxUnitPrice=maxPrice;
	_unitWeight=unitWeight;
	_name=Name;
	computeMeanValue();
	return;
}
inline HOO::Item::~Item(void){
	return;
}
inline void HOO::Item::computeMeanValue(void){
	_meanUnitPrice=(_minUnitPrice+_maxUnitPrice)/2;
	return;
}
inline HOO::Vector3 HOO::Item::getPrices(void){
	return HOO::Vector3(_minUnitPrice,_meanUnitPrice,_maxUnitPrice);
}
inline HOO::String HOO::Item::getName(void){
	return _name;
}

inline float HOO::Item::getWeight(void){
	return _unitWeight;
}


// class Goods
inline void HOO::Goods::computeWeight(void){
	_weight=_quantity * _item->getWeight();
	return;
}
inline float HOO::Goods::getWeight(void){return _weight;}
inline float HOO::Goods::getQty(void){return _quantity;}
inline void HOO::Goods::setQty(float qty){
	_quantity=qty;
	return;
}
inline float HOO::Goods::removeQty(float qty){
	_quantity-=qty;
	float rest = 0.0f;
	if (_quantity < 0){
		rest = -_quantity;
		_quantity = 0.0f;
	}
	return rest;
}
inline void HOO::Goods::addQty(float qty){
	_quantity+=qty;
	return;
}
inline HOO::uint32 HOO::Goods::getItem(void){return _itemUID;}
inline float HOO::Inventory::getGoldAmount(void){return _goldAmount;}
inline float HOO::Inventory::getTotalWeight(void){return _currentWeight;}


#endif
