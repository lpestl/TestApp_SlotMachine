#ifndef BUTTON_ON_PANEL
#define BUTTON_ON_PANEL

//#include "Game.h"
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include "texture.h"
#include "sprite_renderer.h"

// class describes the behavior of a button. reaction to the press
class ButtonOnPanel
{
public:
	// Constructors
	ButtonOnPanel();
	ButtonOnPanel(glm::vec2 pos, glm::vec2 size, Texture2D sprite_up, Texture2D sprite_down, glm::vec3 color, glm::vec2 velocity);
	ButtonOnPanel(glm::vec2 pos, glm::vec2 size, Texture2D sprite_up, Texture2D sprite_down);
	//~ButtonOnPanel();
	//void Init();
	bool ProcessInput(GLfloat dt, glm::vec2 *mousePos, GLboolean pressed);
	//void Update(GLfloat dt);
	//void Render();
	// Draw sprite
	virtual void Draw(SpriteRenderer &renderer);

private:
	// Object state
	glm::vec2   Position, Size, Velocity;
	glm::vec3   Color;
	GLfloat     Rotation;
	// Render state
	Texture2D   SpriteUp;
	Texture2D   SpriteDown;
	// Flag pressing
	bool		buttonIsUp;
};

#endif;