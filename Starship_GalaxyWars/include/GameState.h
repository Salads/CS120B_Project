#ifndef GAMESTATE_H
#define GAMESTATE_H

#include "Enemy.h"
#include "Player.h"
#include "Bullet.h"
#include "JoystickDirection.h"
#include "GameLevel.h"
#include "MenuLevel.h"

class GameState
{
public:
    FORCE_INLINE GameState();
    FORCE_INLINE static GameState& Get();

    FORCE_INLINE void Initialize();
    FORCE_INLINE void UpdateDeltaTime();

public:
    bool              m_initialized = false;
    Enemy**           m_enemies; // An array of POINTERS, to Enemies.
    uint8_t           m_numEnemies = 0;

    Level*            m_currentLevel;
 
    Player*           m_player;
    uint8_t           m_score = 0;
 
    bool              m_fireButton = false;
    JoystickDirection m_joystickDirection = JD_CENTER;

    Bullet**          m_bullets;
    uint8_t           m_numBullets;
    
    // Timing
    uint32_t          m_lastFrameTimeMS = 0;
    uint32_t          m_currentTimeMS   = 0;
    uint32_t          m_deltaTimeMS     = 0;
    uint32_t          m_timeSinceLastFireMS = 0;
};

#include "GameState.inl"

#endif
