#include "SimpleRenderObject.h"
#include "Texture.h"
#include "ST7735SClient.h"

SimpleRenderObject::SimpleRenderObject()
{}

SimpleRenderObject::SimpleRenderObject(Texture& texture)
{
	m_width = texture.width;
	m_height = texture.height;
	m_texture = texture.data;
	m_textureSize = texture.dataSize;
}

void SimpleRenderObject::Render()
{
	ST7735SClient& renderer = ST7735SClient::Get();
	// Render over previous position with background color.
	ScreenRegion lastRegion = GetLastRenderRegion();
	renderer.SetRegion(lastRegion);
	renderer.FillCurrentScreenRegion(renderer.m_backgroundColor);

	// Render new position
	ScreenRegion newRegion = GetRenderRegion();
	renderer.SetRegion(newRegion);
	renderer.FillCurrentScreenRegion(m_texture, m_textureSize);
}
