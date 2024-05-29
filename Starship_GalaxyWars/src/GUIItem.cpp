#include "GUIItem.h"

GUIItem::GUIItem(TextTexture *texture)
{
	m_textureData = (uint16_t*)texture->data;
	m_textureDataSize = texture->dataSize;
	m_width = texture->width;
	m_height = texture->height;
}
