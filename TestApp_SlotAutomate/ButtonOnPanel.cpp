#include "ButtonOnPanel.h"
#include <iostream>

ButtonOnPanel::ButtonOnPanel()
	: Position(0, 0), Size(1, 1), Velocity(0.0f), Color(1.0f), Rotation(0.0f), SpriteUp(), SpriteDown(), buttonIsUp(true)//, pushed(false)
{ 
}

ButtonOnPanel::ButtonOnPanel(glm::vec2 pos, glm::vec2 size, Texture2D sprite_up, Texture2D sprite_down, glm::vec3 color = glm::vec3(1.0f), glm::vec2 velocity = glm::vec2(0.0f, 0.0f))
	: Position(pos), Size(size), Velocity(velocity), Color(color), Rotation(0.0f), SpriteUp(sprite_up), SpriteDown(sprite_down), buttonIsUp(true)//, pushed(false)
{
}

ButtonOnPanel::ButtonOnPanel(glm::vec2 pos, glm::vec2 size, Texture2D sprite_up, Texture2D sprite_down)
	: Position(pos), Size(size), Rotation(0.0f), SpriteUp(sprite_up), SpriteDown(sprite_down), buttonIsUp(true), Color(glm::vec3(1.0f)), Velocity(glm::vec2(0.0f, 0.0f))//, pushed(false)
{
}

//ButtonOnPanel::~ButtonOnPanel() {}
//void ButtonOnPanel::Update(GLfloat dt) {}

void ButtonOnPanel::Draw(SpriteRenderer &renderer)
{
	if (buttonIsUp) renderer.DrawSprite(this->SpriteUp, this->Position, this->Size, this->Rotation, this->Color);
	else renderer.DrawSprite(this->SpriteDown, this->Position, this->Size, this->Rotation, this->Color);
}

bool ButtonOnPanel::ProcessInput(GLfloat dt, glm::vec2 *mousePos, GLboolean pressed) {
	if (pressed) {
		if ((mousePos->x > Position.x) && (mousePos->x < (Position.x + Size.x)) &&
			(mousePos->y > Position.y) && (mousePos->y < (Position.y + Size.y))) {
			buttonIsUp = false;
		}
	}
	else {
		if (!buttonIsUp) {
			buttonIsUp = true;
			//std::cout << "Button UP" << std::endl;
			return true;
		}
	}
	return false;
}