#include "Level.h"

struct MenuLevel : public Level
{
public:
	MenuLevel();
	virtual void Update();
	virtual void Render();
};
