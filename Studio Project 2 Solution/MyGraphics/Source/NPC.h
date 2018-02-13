#ifndef NPCS_H
#define NPCS_H

#include "Vector3.h"

// Type of NPC
enum NPC_TYPE
{
	NPC_WEATHER,
	NPC_LORE,
	NPC_HUNTING,
	NPC_RAISING,
	NPC_RACING,

	NPC_TOTAL,
};

class NPC
{
public:
	const static int numberOfNPCs = NPC_TOTAL;
	Vector3 NPCS[numberOfNPCs];
	
	// Get the coord of the requested NPC type
	Vector3 getCoord(NPC_TYPE);

	NPC();
	~NPC();
};

/*
To add NPCs,
1. Add the NPC type under the NPC_TYPE enum
2. Add the NPC coords under the default constructor
 */

#endif