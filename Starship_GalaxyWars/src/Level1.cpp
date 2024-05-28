#include "Levels/Level1.h"
#include "GameState.h"
#include "XYCoord.h"
#include "Entity.h"

void Level1::InitializeEnemies()
{
    const uint8_t numEnemies = 8;
    m_numEnemies = numEnemies;

    EntityType enemyList[numEnemies] = 
    { 
        EntityType_Fly, EntityType_Fly, EntityType_Fly, EntityType_Fly,
        EntityType_Crab, EntityType_Crab, EntityType_Crab, EntityType_Crab
    };

    m_enemies = new Enemy*[numEnemies];

    // Go through each entity type and lay them out on the screen 1 by 1.
    for (uint8_t i = 0; i < numEnemies; i++)
    {
        m_enemies[i] = CreateEnemyFromType(enemyList[i]);
    }

    m_initialized = true;
}
