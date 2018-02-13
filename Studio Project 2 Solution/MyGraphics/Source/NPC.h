#ifndef NPCS_H
#define NPCS_H

#include "Vector3.h"
#include "Box.h"

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
	Box moveCollisions[numberOfNPCs];
	Box textCollisions[numberOfNPCs];
	
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