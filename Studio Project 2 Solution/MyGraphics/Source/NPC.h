#ifndef NPC_H
#define NPC_H

#include "Vector3.h"
#include "Object.h"

// Type of NPC
enum NPC_TYPE
{
	NPC_WEATHER,
	NPC_LORE,
	NPC_HUNTING,
	NPC_RAISING,
	NPC_RACING,
	NPC_SHOP,

	NPC_TOTAL,
};

// Direction of possible movement
enum MOVE_DIRECTION
{
	MOVEDIR_POS,	// Can move in the positive direction
	MOVEDIR_NEG,	// Can move in the negative direction
	MOVEDIR_BOTH,	// Can move in both of the directions
	MOVEDIR_NONE,	// Can move in none of the directions

	MOVEDIR_TOTAL,
};

class NPC
{
public:
	const static int numberOfNPCs = NPC_TOTAL;
	static const int sizeOfBoxMove = 10;
	static const int sizeOfTextMove = 20;

	Object NPCS[numberOfNPCs];
	MOVE_DIRECTION moveDirX[numberOfNPCs];
	MOVE_DIRECTION moveDirZ[numberOfNPCs];
	bool canMove[numberOfNPCs];
	int moveAmt[numberOfNPCs][2];

	// Get the coord of the requested NPC type using the NPC_TYPE
	Vector3 GetCoord(NPC_TYPE);

	// Get the coord of the requested NPC type using an integer
	Vector3 GetCoord(int);

	// Update all NPCs
	void Update(double dt);

	NPC();
	~NPC();
};

/*
To add NPCs,
1. Add the NPC type under the NPC_TYPE enum
2. Add the NPC coords under the default constructor
 */

#endif