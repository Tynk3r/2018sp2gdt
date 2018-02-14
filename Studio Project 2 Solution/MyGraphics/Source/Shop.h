#ifndef SHOP_H
#define SHOP_H

#include "Vector3.h"
#include "Object.h"

// Type of SHOP
enum SHOP_TYPE
{
	SHOP_EXIT,
	SHOP_BUY_FRUIT,
//	SHOP_BUY_MEAT,
//	SHOP_BUY_TRAP,
//	SHOP_SELL_FRUIT,
//	SHOP_SELL_MEAT,
//	SHOP_SELL_TRAP,
//	SHOP_RESET_QUANTITY,
//	SHOP_INCREASE_QUANTITY_1,
//	SHOP_DECREASE_QUANTITY_1,
//	SHOP_INCREASE_QUANTITY_10,
//	SHOP_DECREASE_QUANTITY_10,
//	SHOP_INCREASE_QUANTITY_100,
//	SHOP_DECREASE_QUANTITY_100,

	SHOP_TOTAL,
};
class SHOP
{
public:
	const static int numberOfSHOPs = SHOP_TOTAL;
	Object SHOPS[numberOfSHOPs];
	
	// Get the coord of the requested SHOP type using the SHOP_TYPE
	Vector3 getCoord(SHOP_TYPE);

	// Get the coord of the requested SHOP type using an integer
	Vector3 getCoord(int);

	SHOP();
	~SHOP();
};

/*
To add SHOPs,
1. Add the SHOP type under the SHOP_TYPE enum
2. Add the SHOP coords under the default constructor
 */

#endif