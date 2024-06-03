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
	m_width = newTexture.width;
	m_height = newTexture.height;
	m_texture = newTexture.data;
	m_textureSize = newTexture.dataSize;
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
		renderer.FillCurrentScreenRegion(renderer.m_backgroundColor);
	}

	// Render new position
	ScreenRegion newRegion = GetRenderRegion();
	renderer.SetRegion(newRegion);
	renderer.FillCurrentScreenRegion(m_texture, m_textureSize);

	SetRenderDirty(false);
}
