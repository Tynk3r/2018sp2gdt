#ifndef SHOP_H
#define SHOP_H

#include "Vector3.h"
#include "Object.h"

// Type of SHOP
enum SHOP_ACTION
{	
	SHOP_EXIT,

	SHOP_BUY_START,
	SHOP_BUY_REDFRUIT,
	SHOP_BUY_BLUFRUIT,
	SHOP_BUY_MEAT,
	SHOP_BUY_TRAP,
	SHOP_BUY_INCUBATOR,
	SHOP_BUY_END,

	SHOP_SELL_START,
	SHOP_SELL_REDFRUIT,
	SHOP_SELL_BLUFRUIT,
	SHOP_SELL_MEAT,
	SHOP_SELL_TRAP,
	SHOP_SELL_INCUBATOR,
	SHOP_SELL_END,

	SHOP_AMOUNT_START,
	SHOP_RESET_AMOUNT,
	SHOP_INCREASE_AMOUNT_1,
	SHOP_DECREASE_AMOUNT_1,
	SHOP_INCREASE_AMOUNT_10,
	SHOP_DECREASE_AMOUNT_10,
	SHOP_INCREASE_AMOUNT_100,
	SHOP_DECREASE_AMOUNT_100,
	SHOP_AMOUNT_END,

	SHOP_TOTAL,
};
class SHOP
{
public:
	const static int numberOfSHOPs = SHOP_TOTAL;
	Object coord[numberOfSHOPs];
	int cost[numberOfSHOPs];		// The selling/Buying value of each action
	double supply[numberOfSHOPs];	// This will affect the cost of each action

	// Get the coord of the requested action
	Vector3 GetCoord(int);

	// Update prices based on supply/demand
	void Update();

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