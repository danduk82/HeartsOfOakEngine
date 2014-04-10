// -----------------------------------------------------------------------------
//  Filename:    gameObjects.cpp
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

// HOO specific headers
#include "HOO_definitions.h"
#include "HOO_gameObjects.h"

template <class T> float HOO::getWeight(T item){
	return item.getWeight();
}


//class Goods
HOO::Goods::Goods(std::map<HOO::uint32,Item*> * ItemMap ,HOO::uint32 ItemID, float qty){
	_item = ItemMap->at(ItemID);
	_quantity=qty;
	computeWeight();
	return;
}
HOO::Goods::~Goods(void){
}

void HOO::Goods::setItem(std::map<HOO::uint32,Item*> * ItemMap, HOO::uint32 ItemID){
	_item = ItemMap->at(ItemID);
	return;
}


// class Inventory
void HOO::Inventory::computeGoodsList(void){
	// init the goods list
	if (! _goodsList.empty()) {
		_goodsList = std::map<HOO::uint32,int>();
	};
	for (int i = 0; i <= _goods.size(); ++i){
		_goodsList.insert(std::pair<HOO::uint32,int>(_goods[i].getItem(),_goods[i].getQty()));
	}
	return;
}
void HOO::Inventory::computeTotalWeight(void){
	_currentWeight=0.0f;
	for (int i = 0 ; i <=_goods.size(); ++i){
		_currentWeight+=_goods[i].getWeight();
	}
	return;
}
HOO::Inventory::Inventory(float gold){
	_goldAmount=gold;
	return;
}
HOO::Inventory::Inventory(float gold, std::vector<Goods> goodsVector){
	_goldAmount=gold;
	_goods=goodsVector;
	return;
}
HOO::Inventory::~Inventory(){
	return;
}
std::map<HOO::uint32,int> HOO::Inventory::getGoodsList(void){
	std::map<HOO::uint32,int> goodsList;
	return goodsList;
}

int HOO::Inventory::addGold(float gold){
	return HOO::SUCCESS;
}
int HOO::Inventory::removeGold(float gold){
	return HOO::SUCCESS;
}
int HOO::Inventory::addStuff(Goods goods){
	return HOO::SUCCESS;
}
int HOO::Inventory::addStuff(std::vector<Goods> goodsVector){
	return HOO::SUCCESS;
}
int HOO::Inventory::removeStuff(Goods goods){
	return HOO::SUCCESS;
}
int HOO::Inventory::removeStuff(std::vector<Goods> goodsVector){
	return HOO::SUCCESS;
}

