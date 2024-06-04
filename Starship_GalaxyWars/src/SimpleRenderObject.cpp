#include "SimpleRenderObject.h"
#include "Texture.h"
#include "ST7735SClient.h"

SimpleRenderObject::SimpleRenderObject(BaseRenderObject* parent)
{
	m_parent = parent;
}

SimpleRenderObject::~SimpleRenderObject() 
{}

SimpleRenderObject::SimpleRenderObject(Texture& texture)
{
	SetTexture(texture);
}

void SimpleRenderObject::SetTexture(Texture& newTexture)
{
	m_width 		  = newTexture.width;
	m_height 		  = newTexture.height;
	m_textureData 	  = newTexture.data;
	m_textureDataSize = newTexture.dataSize;
	m_textureFormat   = newTexture.textureFormat;

	SetRenderDirty(true);
}

void SimpleRenderObject::Render(bool clearLastPosition)
{
	if(!GetRenderDirty()) {return;}

	ST7735SClient& renderer = ST7735SClient::Get();
	
	if(clearLastPosition)
	{
		// Render over previous position with background color.
		ScreenRegion lastRegion = GetLastRenderRegion();
		renderer.SetRegion(lastRegion);
		renderer.FillCurrentScreenRegionPacked16(renderer.m_backgroundColor);
	}

	// Render new position
	ScreenRegion newRegion = GetRenderRegion();

	#if DEBUG_REGIONS
	Debug_PrintLine("Region - x=[%d,%d], y=[%d,%d]", 
		newRegion.m_startX, newRegion.m_endX,
		newRegion.m_startY, newRegion.m_endY);
	#endif

	renderer.SetRegion(newRegion);
	renderer.FillCurrentScreenRegionTexture(m_textureData, m_textureDataSize, m_textureFormat, m_width, m_height);

	SetRenderDirty(false);
}
