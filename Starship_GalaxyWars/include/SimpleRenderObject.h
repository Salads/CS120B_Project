#pragma once

#include "BaseRenderObject.h"
#include "Texture.h"
#include <stdint.h>

class SimpleRenderObject : public BaseRenderObject
{
public:
    SimpleRenderObject(BaseRenderObject* parent = nullptr);
    virtual ~SimpleRenderObject();
    SimpleRenderObject(Texture& texture);
    void SetTexture(Texture& newTexture);
    void Render(bool clearLastPosition = true);
protected:
    const uint8_t* m_textureData;
    uint16_t       m_textureDataSize;
    TextureFormat  m_textureFormat;
};
