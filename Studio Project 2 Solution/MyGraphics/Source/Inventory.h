#ifndef INVENTORY_H
#define INVENTORY_H

// List of items in inventory
enum ITEMS
{
	ITEMS_TRAP,
	ITEMS_REDFRUIT,
	ITEMS_BLUFRUIT,
	ITEMS_MEAT,
	ITEMS_INCUBATOR,
	ITEMS_CURRENCY,

	ITEMS_TOTAL,
};
class Inventory
{
private:
	static Inventory *INVENTORY_instance;
	Inventory();

public:
	bool showInventory;
	int items[ITEMS_TOTAL];

	static Inventory* instance(void);
	void Update(double dt);
};

#endif