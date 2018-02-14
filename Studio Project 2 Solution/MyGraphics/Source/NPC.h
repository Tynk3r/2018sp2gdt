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

class NPC
{
public:
	const static int numberOfNPCs = NPC_TOTAL;
	static const int sizeOfBoxMove = 10;
	static const int sizeOfTextMove = 20;


	Object NPCS[numberOfNPCs];
	
	// Get the coord of the requested NPC type using the NPC_TYPE
	Vector3 getCoord(NPC_TYPE);

	// Get the coord of the requested NPC type using an integer
	Vector3 getCoord(int);

	NPC();
	~NPC();
};

/*
To add NPCs,
1. Add the NPC type under the NPC_TYPE enum
2. Add the NPC coords under the default constructor
 */

#endif