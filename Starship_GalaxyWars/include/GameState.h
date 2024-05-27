#ifndef GAMESTATE_H
#define GAMESTATE_H

#include "Enemy.h"
#include "Player.h"
#include "Bullet.h"

class GameState
{
public:
    GameState();
    FORCE_INLINE static GameState& Get();

    FORCE_INLINE void Initialize();
    FORCE_INLINE double GetDeltaTime();

public:
    bool      m_initialized = false;
    uint8_t   m_score;  
    Enemy**   m_enemies; // An array of POINTERS, to Enemies.
    uint8_t   m_numEnemies = 0;
 
    Player*   m_player;
 
    bool      m_fireButton = false;
    Bullet**  m_bullets;
    uint8_t   m_numBullets;

    uint32_t  m_lastFrameMS = 0;
    uint32_t  m_timeMS = 0;
};

#include "GameState.inl"

#endif
