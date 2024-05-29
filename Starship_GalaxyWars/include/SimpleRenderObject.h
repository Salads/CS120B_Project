#pragma once

#include "BaseRenderObject.h"
#include <stdint.h>

class SimpleRenderObject : public BaseRenderObject
{
protected:
private:
    uint16_t* m_texture;
    uint16_t  m_textureSize;
};
