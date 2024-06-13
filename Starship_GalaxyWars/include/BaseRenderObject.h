#pragma once

#include <stdint.h>
#include "XYCoord.h"
#include "ScreenRegion.h"

class BaseRenderObject
{
public:
	BaseRenderObject(BaseRenderObject* parent = nullptr);
	virtual ~BaseRenderObject();
	virtual void Render(bool clearLastPosition = true) = 0;
	void SetPosition(int16_t x, int16_t y);
	void SetPosition(XYCoord newPosition);
	void SetRenderDirty(bool dirty);
	bool GetRenderDirty() {return m_renderDirty;}
	void ClearFromDisplay();
	ScreenRegion GetLastRenderRegion();
	ScreenRegion GetRenderRegion();

	// These Initialized functions are for whether we should set the "last position" of render objects.
	// This way, we don't accidentally clear a previous position due to constructor routines.
	void SetInitialized();
	bool GetInitialized();

	uint8_t GetWidth();
	uint8_t GetHeight();

	XYCoord GetPosition();

protected:
	virtual void OnSetPosition();
	virtual void OnSetRenderDirty(bool newDirty);

protected:
	BaseRenderObject* m_parent = nullptr;
    bool 			  m_renderDirty = false;

	uint8_t 		  m_width = 0;
	uint8_t 		  m_height = 0;

	XYCoord 		  m_position;
	XYCoord 		  m_lastRenderedPosition;

private:
	bool              m_initialized = false;

};
