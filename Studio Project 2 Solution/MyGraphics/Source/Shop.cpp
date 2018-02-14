#include "SHOP.h"

SHOP::SHOP()
{
	SHOPS[SHOP_EXIT].setBox(Vector3(60, 612.5, 0), 25, 40, 1);
	SHOPS[SHOP_BUY_FRUIT].setBox(Vector3(1042.5, 201, 0), 135, 53, 1);
//	SHOPS[SHOP_BUY_MEAT].setBox(Vector3(60, 0, 80), sizeOfBox);
//	SHOPS[SHOP_BUY_TRAP].setBox(Vector3(60, 0, 80), sizeOfBox);
//	SHOPS[SHOP_SELL_FRUIT].setBox(Vector3(60, 0, 80), sizeOfBox);
//	SHOPS[SHOP_SELL_MEAT].setBox(Vector3(60, 0, 80), sizeOfBox);
//	SHOPS[SHOP_SELL_TRAP].setBox(Vector3(60, 0, 80), sizeOfBox);
//	SHOPS[SHOP_RESET_QUANTITY].setBox(Vector3(60, 0, 80), sizeOfBox);
//	SHOPS[SHOP_INCREASE_QUANTITY_1].setBox(Vector3(60, 0, 80), sizeOfBox);
//	SHOPS[SHOP_DECREASE_QUANTITY_1].setBox(Vector3(60, 0, 80), sizeOfBox);
//	SHOPS[SHOP_INCREASE_QUANTITY_10].setBox(Vector3(60, 0, 80), sizeOfBox);
//	SHOPS[SHOP_DECREASE_QUANTITY_10].setBox(Vector3(60, 0, 80), sizeOfBox);
//	SHOPS[SHOP_INCREASE_QUANTITY_100].setBox(Vector3(60, 0, 80), sizeOfBox);
//	SHOPS[SHOP_DECREASE_QUANTITY_100].setBox(Vector3(60, 0, 80), sizeOfBox);
}

//maxX : 1110 maxY 225 
//minX : 975 minY 175
//135 50

Vector3 SHOP::getCoord(SHOP_TYPE type)
{
	return SHOPS[type].getPos();
}

Vector3 SHOP::getCoord(int i)
{
	return SHOPS[i].getPos();
}
SHOP::~SHOP()
{
}
