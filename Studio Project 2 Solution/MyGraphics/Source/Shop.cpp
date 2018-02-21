#include "SHOP.h"

SHOP::SHOP()
{
	coord[SHOP_EXIT					].setBox(Vector3(150, 603, 0), 120, 60, 1);
	coord[SHOP_BUY_REDFRUIT			].setBox(Vector3(150, 331, 0), 120, 60, 1);
	coord[SHOP_BUY_BLUFRUIT			].setBox(Vector3(300, 331, 0), 120, 60, 1);
	coord[SHOP_BUY_MEAT				].setBox(Vector3(450, 331, 0), 120, 60, 1);
	coord[SHOP_BUY_TRAP				].setBox(Vector3(600, 331, 0), 120, 60, 1);
	coord[SHOP_BUY_INCUBATOR		].setBox(Vector3(750, 331, 0), 120, 60, 1);

	coord[SHOP_SELL_REDFRUIT		].setBox(Vector3(150, 467, 0), 120, 60, 1);
	coord[SHOP_SELL_BLUFRUIT		].setBox(Vector3(300, 467, 0), 120, 60, 1);
	coord[SHOP_SELL_MEAT			].setBox(Vector3(450, 467, 0), 120, 60, 1);
	coord[SHOP_SELL_TRAP			].setBox(Vector3(600, 467, 0), 120, 60, 1);
	coord[SHOP_SELL_INCUBATOR		].setBox(Vector3(750, 467, 0), 120, 60, 1);
	
	coord[SHOP_RESET_AMOUNT			].setBox(Vector3(1050, 399, 0), 120, 60, 1);
	coord[SHOP_INCREASE_AMOUNT_1	].setBox(Vector3(900, 331, 0), 120, 60, 1);
	coord[SHOP_DECREASE_AMOUNT_1	].setBox(Vector3(900, 467, 0), 120, 60, 1);
	coord[SHOP_INCREASE_AMOUNT_10	].setBox(Vector3(900, 263, 0), 120, 60, 1);
	coord[SHOP_DECREASE_AMOUNT_10	].setBox(Vector3(900, 535, 0), 120, 60, 1);
	coord[SHOP_INCREASE_AMOUNT_100	].setBox(Vector3(900, 195, 0), 120, 60, 1);
	coord[SHOP_DECREASE_AMOUNT_100	].setBox(Vector3(900, 603, 0), 120, 60, 1);

	cost[SHOP_BUY_REDFRUIT			] = 200;
	cost[SHOP_BUY_BLUFRUIT			] = 2;
	cost[SHOP_BUY_MEAT				] = 2;
	cost[SHOP_BUY_TRAP				] = 2;
	cost[SHOP_BUY_INCUBATOR			] = 2;

	cost[SHOP_SELL_REDFRUIT			] = (cost[SHOP_BUY_REDFRUIT	] / 2);
	cost[SHOP_SELL_BLUFRUIT			] = (cost[SHOP_BUY_BLUFRUIT	] / 2);
	cost[SHOP_SELL_MEAT				] = (cost[SHOP_BUY_MEAT		] / 2);
	cost[SHOP_SELL_TRAP				] = (cost[SHOP_BUY_TRAP		] / 2);
	cost[SHOP_SELL_INCUBATOR		] = (cost[SHOP_BUY_INCUBATOR] / 2);

	supply[SHOP_BUY_REDFRUIT		] = 45;
	supply[SHOP_BUY_BLUFRUIT		] = 45;
	supply[SHOP_BUY_MEAT			] = 45;
	supply[SHOP_BUY_TRAP			] = 45;
	supply[SHOP_BUY_INCUBATOR		] = 45;
}

void SHOP::Update()
{
	for (int i = (SHOP_BUY_START + 1); i <= SHOP_BUY_END; i++)
	{
		if (supply[i] >= 45)
		{
			supply[i] = 45;
		}
		else if (supply[i] <= 0)
		{
			supply[i] = 1;
		}

		// Supply - Demand equation
		cost[i] = ((999 / (supply[i] / 2)) - ((supply[i] - 1) / (supply[i] / 40)));

		// Fail safes such that there will always be a price
		if (cost[i] >= 999)
		{
			cost[i] = 999;
		}
		else if (cost[i] < 0)
		{
			cost[i] = 1;
		}
	}

	cost[SHOP_SELL_REDFRUIT	] = (cost[SHOP_BUY_REDFRUIT	] / 2);
	cost[SHOP_SELL_BLUFRUIT	] = (cost[SHOP_BUY_BLUFRUIT	] / 2);
	cost[SHOP_SELL_MEAT		] = (cost[SHOP_BUY_MEAT		] / 2);
	cost[SHOP_SELL_TRAP		] = (cost[SHOP_BUY_TRAP		] / 2);
	cost[SHOP_SELL_INCUBATOR] = (cost[SHOP_BUY_INCUBATOR] / 2);
}

Vector3 SHOP::GetCoord(int i)
{
	return coord[i].getPos();
}
SHOP::~SHOP()
{
}
