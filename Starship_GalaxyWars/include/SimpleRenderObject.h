#pragma once

#include "BaseRenderObject.h"
#include "Texture.h"
#include <stdint.h>

class SimpleRenderObject : public BaseRenderObject
{
public:
    SimpleRenderObject();
    virtual ~SimpleRenderObject();
    SimpleRenderObject(Texture& texture);
    void SetTexture(Texture& newTexture);
    void Render(bool clearLastPosition = true);
protected:
    const uint16_t* m_texture;
    uint16_t  m_textureSize;
};
