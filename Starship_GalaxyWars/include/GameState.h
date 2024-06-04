#ifndef GAMESTATE_H
#define GAMESTATE_H

#include "Enemy.h"
#include "Player.h"
#include "Bullet.h"
#include "JoystickDirection.h"
#include "GameLevel.h"

class GameState
{
public:
    FORCE_INLINE GameState();
    FORCE_INLINE static GameState& Get();

    FORCE_INLINE void Initialize();
    FORCE_INLINE void UpdateDeltaTime();

public:
    bool              m_initialized = false;

    Level*            m_currentLevel = nullptr;
 
    uint8_t           m_score = 0;
 
    bool              m_fireButton = false;
    // We have two different joystick axis here because I only want to check two directions
    // when handling ui/gameplay. I'm lazy. :)
    JoystickDirection m_joystickDirectionY = JD_CENTER;
    JoystickDirection m_joystickDirectionX = JD_CENTER;
    
    // Timing
    uint32_t          m_lastFrameTimeMS = 0;
    uint32_t          m_currentTimeMS   = 0;
    uint32_t          m_deltaTimeMS     = 0;
    uint32_t          m_timeNextFireMS    = 0;
    uint32_t          m_timeSinceLastFireMS = 0;
};

#include "GameState.inl"

#endif
