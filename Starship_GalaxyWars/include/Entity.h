#pragma once

#include "Types.h"
#include "XYCoord.h"
#include "ScreenRegion.h"

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

class Entity
{
public:
	Entity();
	~Entity();
	bool GetCollides(Entity &other);
	uint16_t* GetTextureData();
	uint16_t GetTextureDataSize();

	void SetPosition(int16_t x, int16_t y);
	void SetPosition(XYCoord newPosition);
	void SetLastRenderedPosition(ScreenRegion region);
	void SetRenderDirty(bool dirty);
	bool GetRenderDirty() {return m_renderDirty;}
	void ClearFromDisplay();
	ScreenRegion GetLastRenderRegion();
	ScreenRegion GetRenderRegion();

	uint8_t GetWidth();
	uint8_t GetHeight();

	XYCoord GetPosition();
	bool    GetIsMarkedForDeletion();
	void    SetIsMarkedForDeletion(bool shouldDelete);
	
protected:

	bool m_renderDirty = false;

	uint8_t m_width = 25;
	uint8_t m_height = 25;

	XYCoord m_position;
	XYCoord m_lastRenderedPosition;

	// There's no data integrity checking between texture data and
	// entity size. There's also no texture stretching.
	// Will probably crash if you mismatch texture data size with entity size.
	uint16_t* m_textureData;
	uint16_t  m_textureDataSize;

	bool      m_markedForDelete = false;
	bool      m_lastRenderInitialized = false;

	// Working with integers at faster update rates, we end up with
	// "move" deltas like .10 pixels and so on. This is used to accumulate 
	// the updating if we aren't able to represent a change.
	uint32_t  m_timeSinceLastUpdate = 0;
};
