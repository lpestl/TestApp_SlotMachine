#ifndef ROTATION_DRUM_H
#define ROTATION_DRUM_H

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include "texture.h"
#include "sprite_renderer.h"
#include <vector>
//#include <stdlib.h>

class drums_item {
public:
	drums_item();
	drums_item(glm::vec2 pos, glm::vec2 size, glm::vec2 velocity, Texture2D	txture);
	void Init();
	void Update(GLfloat dt);
	virtual void Draw(SpriteRenderer &renderer);
	void SetPosition(glm::vec2 pos);
	void CorrectPosition();
	glm::vec2 GetPosition();
	glm::vec2 GetSize();
private:
	glm::vec2   Position, Size, Velocity;
	Texture2D	texture;
};

class rotating_drum
{
public:
	rotating_drum();
	rotating_drum(glm::vec2 pos, glm::vec2 size, glm::vec2 velocity);
	void addItem(Texture2D item, std::string name);
	void Init();
	void Update(GLfloat dt);
	virtual void Draw(SpriteRenderer &renderer);
	void StartRotation(double time);
	std::vector<std::string> GetVisible();
private:
	glm::vec2					Position, Size, Velocity;
	std::vector<drums_item *>	items;
	std::vector<std::string>	names;
	double						curentTime;
	double						timeRotation;
	int							n_min;
};

#endif