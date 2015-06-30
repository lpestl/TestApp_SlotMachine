#pragma once

#include "texture.h"
#include "sprite_renderer.h"
#include <vector>

// Class describes a line, check an item is located on the line and says winning
class Line
{
public:
	// Constructor
	Line(Texture2D line, glm::vec2 pos, glm::vec2 size);
	//~Line();
	//void Init();
	//void Update(GLfloat dt);
	virtual void Draw(SpriteRenderer &renderer);
	// Check winning
	int CheckWin(int bet);

	// public current names items
	std::vector<std::string>	items;
	// flag visibiliti
	bool						visible;
private:
	glm::vec2					Pos, Size;
	Texture2D					m_line;
};

