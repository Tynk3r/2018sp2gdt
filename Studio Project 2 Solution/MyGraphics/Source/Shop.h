#ifndef SHOP_H
#define SHOP_H

#include "Vector3.h"
#include "Object.h"

// Type of SHOP
enum SHOP_ACTION
{
	SHOP_EXIT,
	SHOP_BUY_FRUIT,
	SHOP_BUY_MEAT,
	SHOP_BUY_TRAP,
	SHOP_SELL_FRUIT,
	SHOP_SELL_MEAT,
	SHOP_SELL_TRAP,
	SHOP_RESET_QUANTITY,
	SHOP_INCREASE_QUANTITY_1,
	SHOP_DECREASE_QUANTITY_1,
	SHOP_INCREASE_QUANTITY_10,
	SHOP_DECREASE_QUANTITY_10,
	SHOP_INCREASE_QUANTITY_100,
	SHOP_DECREASE_QUANTITY_100,

	SHOP_TOTAL,
};
class SHOP
{
public:
	const static int numberOfSHOPs = SHOP_TOTAL;
	Object coord[numberOfSHOPs];
	int cost[numberOfSHOPs]; // The selling/Buying value of each action

	// Get the coord of the requested action using the SHOP_ACTION enum
	Vector3 getCoord(SHOP_ACTION);

	// Get the coord of the requested action using an integer
	Vector3 getCoord(int);

	SHOP();
	~SHOP();
};

/*
To add SHOP_ACTIONs,
1. Add the SHOP_ACTION under the SHOP_ACTION enum
2. Add the SHOP_ACTION coords under the default constructor
3. Add the SHOP_ACTION value under the default constructor
 */

#endif