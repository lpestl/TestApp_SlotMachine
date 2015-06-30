#ifndef GAME_H
#define GAME_H
// GLEW
#include <GL/glew.h>
// GLFW
#include <GLFW/glfw3.h>
// Need .h files:
// for resource manager,
#include "resource_manager.h"
// for sprite rendering,
#include "sprite_renderer.h"
// for rendering buttons ("Start" & "Lines"),
#include "ButtonOnPanel.h"
// for rotating drums,
#include "rotating_drum.h"
// for text rendering
#include "text_renderer.h"
// for read lines wins;
#include "Line.h"

// Represents the current state of the game
enum GameState {
	GAME_EXPECTATION,
	GAME_ACTIVE,
	GAME_SHOW_LINES,
	GAME_STOPPING
};

// Game holds all game-related state and functionality.
// Combines all game-related data into a single class for
// easy access to each of the components and manageability.
class Game
{
public:
	// Game state
	GameState              State;
	GLboolean              Keys[1024];
	GLuint                 Width, Height;
	glm::vec2			   *MousePos;
	// Constructor/Destructor
	Game(GLuint width, GLuint height);
	~Game();
	// Initialize game state (load all shaders/textures/levels)
	void Init();
	// GameLoop
	void ProcessInput(GLfloat dt);
	void Update(GLfloat dt);
	void Render();
	// Function for calculate FPS;
	void CalculateFrameRate();
private:
	// Button "Start"
	ButtonOnPanel				*m_startButton;
	// Button "Select Lines"
	ButtonOnPanel				*m_selectLines;
	// Vector drums
	std::vector<rotating_drum *> m_drums;
	// Time contrllers
	double						curentTime;
	double						timeRotation;
	// For render text
	TextRenderer				*fpsTEXT;
	// FPS
	float						FPS;
	// Current count lines and vector lines
	int							countLines;
	std::vector<Line *>			lines;
	// The size of bets and winnings
	int							bet;
	int							winsPoints;
};

#endif

