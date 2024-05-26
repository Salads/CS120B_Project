#ifndef GAMESTATE_H
#define GAMESTATE_H

#include "Enemy.h"
#include "Player.h"

class GameState
{
public:
    GameState();
    FORCE_INLINE static GameState& Get();

    FORCE_INLINE void Initialize();

public:
    bool     m_initialized = false;
    uint8_t  m_score;  
    uint32_t m_timeElapsedMS; 
    Enemy**  m_enemies; // An array of POINTERS, to Enemies.
    uint8_t  m_numEnemies = 0;

    Player*  m_player;
};

#include "GameState.inl"

#endif
