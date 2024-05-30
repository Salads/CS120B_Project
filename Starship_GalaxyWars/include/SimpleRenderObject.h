#pragma once

#include "BaseRenderObject.h"
#include "Texture.h"
#include <stdint.h>

class SimpleRenderObject : public BaseRenderObject
{
public:
    SimpleRenderObject();
    SimpleRenderObject(Texture& texture);
    void Render();
protected:
    const uint16_t* m_texture;
    uint16_t  m_textureSize;
};
