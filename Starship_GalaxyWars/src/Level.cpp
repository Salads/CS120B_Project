#include "Level.h"
#include "ST7735SClient.h"

Level::Level()
{
	ST7735SClient& renderer = ST7735SClient::Get();
	ScreenRegion fullScreen;
	renderer.SetRegion(fullScreen);
	renderer.FillCurrentScreenRegionPacked16(renderer.m_backgroundColor);
}

Level::~Level()
{}

void Level::Update()
{

}

void Level::Render()
{

}

DoneReason Level::GetDoneReason()
{
	return DoneReason_None;
}
