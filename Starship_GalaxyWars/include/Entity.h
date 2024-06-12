#pragma once

#include "Types.h"
#include "XYCoord.h"
#include "ScreenRegion.h"
#include "SimpleRenderObject.h"

// To easily identify what entity type we're looking at.
enum EntityType : uint8_t
{
	EntityType_None, // Not initialized!
	EntityType_Fly,
	EntityType_GreenMonster,
	EntityType_Crab,
	EntityType_Player,
	EntityType_Bullet,
};

class Entity : public SimpleRenderObject
{
public:
	Entity();
	Entity(Texture& texture);
	~Entity();
	bool GetCollides(Entity &other);
	
	bool    GetIsMarkedForDeletion();
	void    SetIsMarkedForDeletion(bool shouldDelete);
	bool	GetMoveDebtPaid(float moveSpeed);
	void	UpdateLastMoveTime();
	void	UpdateMoveTimeDebt(uint32_t dt);
	
protected:

	// Working with integers at faster update rates, we end up with
	// "move" deltas like .10 pixels and so on. This is used to accumulate 
	// the updating if we aren't able to represent a change.
	uint32_t  m_lastMoveTime = 0;
	uint32_t  m_timeSinceLastMove = 0;
	bool      m_markedForDelete = false;


};
