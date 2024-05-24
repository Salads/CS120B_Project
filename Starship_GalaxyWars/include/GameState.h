#pragma once

#include "Globals.h"
#include "Enemy.h"

class GameState
{
public:
    GameState();
private:
    uint8_t  m_score;  
    uint32_t m_timeElapsedMS; 
    //Enemy*   m_enemies;

};
