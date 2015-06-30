#include "Line.h"

Line::Line(Texture2D line, glm::vec2 pos, glm::vec2 size) 
	: Pos(pos), Size(size), m_line(line), visible(false)
{
}

//Line::~Line() {}
//void Line::Init() {}
//void Line::Update(GLfloat dt) {}

void Line::Draw(SpriteRenderer &renderer) {
	// Draw Line
	renderer.DrawSprite(this->m_line, this->Pos, this->Size);
}

// Check winning
int Line::CheckWin(int bet) {
	int winPoints = 0;
	// Calculate matches
	std::string str = items[0];
	int count = 1;
	for (int i = 1; i < items.size(); i++) {
		if (items[i] == str) count++;
		else break;
	}

	// Calculate winning
	switch (count)
	{
		// two matches with
	case 2:
		if (str == "Slot02") winPoints = 5;
		if (str == "Slot03") winPoints = 10;
		if (str == "Slot04") winPoints = 5;
		if (str == "Slot05") winPoints = 5;
		break;
		// for three matches
	case 3:
		if (str == "Slot01") winPoints = 20;
		if (str == "Slot02") winPoints = 40;
		if (str == "Slot03") winPoints = 100;
		if (str == "Slot04") winPoints = 30; 
		if (str == "Slot05") winPoints = 30;
		if (str == "Slot06") winPoints = 5;
		if (str == "Slot07") winPoints = 5;
		if (str == "Slot08") winPoints = 5;
		if (str == "Slot09") winPoints = 5;
		if (str == "Slot10") winPoints = 5;
		break;
		// at four coincidences
	case 4:
		if (str == "Slot01") winPoints = 20;
		if (str == "Slot02") winPoints = 400;
		if (str == "Slot03") winPoints = 1000;
		if (str == "Slot04") winPoints = 100;
		if (str == "Slot05") winPoints = 100;
		if (str == "Slot06") winPoints = 40;
		if (str == "Slot07") winPoints = 25;
		if (str == "Slot08") winPoints = 25;
		if (str == "Slot09") winPoints = 25;
		if (str == "Slot10") winPoints = 25;
		break;
		// at five coincidences
	case 5:
		if (str == "Slot01") winPoints = 200;
		if (str == "Slot02") winPoints = 2000;
		if (str == "Slot03") winPoints = 1000;
		if (str == "Slot04") winPoints = 750;
		if (str == "Slot05") winPoints = 750;
		if (str == "Slot06") winPoints = 150;
		if (str == "Slot07") winPoints = 100;
		if (str == "Slot08") winPoints = 100;
		if (str == "Slot09") winPoints = 100;
		if (str == "Slot10") winPoints = 100;
		break;
	default:
		break;
	}
	// if the line is winning, it will show a line
	if (winPoints != 0) visible = true;

	return winPoints;
}