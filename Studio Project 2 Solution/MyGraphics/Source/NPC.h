#ifndef NPC_H
#define NPC_H

#include "Vector3.h"
#include "Object.h"

// Type of NPC
enum NPC_TYPE
{
	NPC_RACING,
	NPC_LORE,
	NPC_JOKER,
	NPC_FACTION_SPEED,
	NPC_FACTION_GIANT,
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

// Axis of possible movement
enum MOVE_AXIS
{
	MOVEAXIS_X,	// Movement in the X axis
	MOVEAXIS_Z,	// Movement in the Z axis

	MOVEAXIS_TOTAL,
};

class NPC
{
public:
	static const int maxMoveAmt = 10;					// Maximum movement amount in a certain axis
	static const int minMoveAmt = -10;					// Minimum movement amount in a certain axis
	static const int movementSpeed = 2;					// Movement speed
	static const int sizeOfBoxMove = 10;				// Size of box for movement collision
	static const int sizeOfTextMove = 20;				// Size of box for text collision
	static const int numberOfNPCs = NPC_TOTAL;			// Total number of NPCs

	Object NPCS[NPC_TOTAL];								// Array containing position and box data for each NPC
	int moveDirX[NPC_TOTAL];							// Array containing possible movement in the X axis for each NPC
	int moveDirZ[NPC_TOTAL];							// Array containing possible movement in the Z axis for each NPC 
	bool canMove[NPC_TOTAL];							// Array that determines if each NPC can move
	int npcMoveDelay[NPC_TOTAL];						// Array containing the delay such that each NPC has to wait before moving
	int npcFacingRotaion[NPC_TOTAL];					// Array containing the rotation of each NPC
	int moveAmt[NPC_TOTAL][MOVEAXIS_TOTAL];				// Double array containing the MinMax movement amount for all the axis for each NPC
	int npcDirectionDelay[NPC_TOTAL][MOVEAXIS_TOTAL];	// Dobule array containing the direction and the delay such that each NPC has to travel in a direction before it can switch

	// Get the coord of the requested NPC type
	Vector3 GetCoord(int);

	// Update functions
	void Update(double dt);
	void RotationUpdate(int i, int angle);
	void CheckForCollision(int i);
	void CheckForMinMaxMovement(int i);


	NPC();
	~NPC();
};

/*
To add NPCs,
1. Add the NPC type under the NPC_TYPE enum
2. Add the NPC coords under the default constructor
 */

#endif