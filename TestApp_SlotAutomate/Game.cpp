#include "game.h"
// Standart .h files
#include <stdlib.h>
#include <iostream>
#include <time.h>

// Renderer for all sprites
SpriteRenderer  *Renderer;

// Function for calculate FPS
void Game::CalculateFrameRate()
{
	static float framesPerSecond = 0.0f;    
	static float lastTime = 0.0f;           
	static char strFrameRate[50] = { 0 };    

	float currentTime = glfwGetTime();// *0.001f;

	++framesPerSecond;

	if (currentTime - lastTime > 1.0f)
	{
		lastTime = currentTime;
		FPS = framesPerSecond;
		framesPerSecond = 0;
	}
}

// Constructor
Game::Game(GLuint width, GLuint height)
	: State(GAME_EXPECTATION), Keys(), Width(width), Height(height), curentTime(0.0f), timeRotation(-1.0), countLines(1), bet(1)
{
	MousePos = new glm::vec2(0.0f, 0.0f);
}

// Destructor
Game::~Game()
{
	delete MousePos;
	delete m_startButton;
	delete Renderer;
}

// Initializing all game resources
void Game::Init()
{
	// Load shaders
	ResourceManager::LoadShader("data/shaders/sprite.vs", "data/shaders/sprite.frag", nullptr, "sprite");
	// Configure shaders
	glm::mat4 projection = glm::ortho(0.0f, static_cast<GLfloat>(this->Width), static_cast<GLfloat>(this->Height), 0.0f, -1.0f, 1.0f);
	ResourceManager::GetShader("sprite").Use().SetInteger("image", 0);
	ResourceManager::GetShader("sprite").SetMatrix4("projection", projection);
	
	// Load font
	fpsTEXT = new TextRenderer(this->Width, this->Height);
	fpsTEXT->Load("data/fonts/tahomabd.ttf", 14);

	// Load textures
	// for background,
	ResourceManager::LoadTexture("data/textures/texture01.png", GL_TRUE, "face");
	ResourceManager::LoadTexture("data/textures/texture02.png", GL_TRUE, "Book_Of_Ra");
	// for buttons,
	ResourceManager::LoadTexture("data/textures/Start_button_up.png", GL_TRUE, "StartUp");
	ResourceManager::LoadTexture("data/textures/Start_button_down.png", GL_TRUE, "StartDown");
	ResourceManager::LoadTexture("data/textures/lines_button_up.png", GL_TRUE, "LinesUp");
	ResourceManager::LoadTexture("data/textures/lines_button_down.png", GL_TRUE, "LinesDown");
	// for items,
	ResourceManager::LoadTexture("data/textures/slot01.png", GL_TRUE, "Slot01");
	ResourceManager::LoadTexture("data/textures/slot02.png", GL_TRUE, "Slot02");
	ResourceManager::LoadTexture("data/textures/slot03.png", GL_TRUE, "Slot03");
	ResourceManager::LoadTexture("data/textures/slot04.png", GL_TRUE, "Slot04");
	ResourceManager::LoadTexture("data/textures/slot05.png", GL_TRUE, "Slot05");
	ResourceManager::LoadTexture("data/textures/slot06.png", GL_TRUE, "Slot06");
	ResourceManager::LoadTexture("data/textures/slot07.png", GL_TRUE, "Slot07");
	ResourceManager::LoadTexture("data/textures/slot08.png", GL_TRUE, "Slot08");
	ResourceManager::LoadTexture("data/textures/slot09.png", GL_TRUE, "Slot09");
	ResourceManager::LoadTexture("data/textures/slot10.png", GL_TRUE, "Slot10");
	// for lines,
	ResourceManager::LoadTexture("data/textures/line01.png", GL_TRUE, "line01");
	ResourceManager::LoadTexture("data/textures/line02.png", GL_TRUE, "line02");
	ResourceManager::LoadTexture("data/textures/line03.png", GL_TRUE, "line03");
	ResourceManager::LoadTexture("data/textures/line04.png", GL_TRUE, "line04");
	ResourceManager::LoadTexture("data/textures/line05.png", GL_TRUE, "line05");
	ResourceManager::LoadTexture("data/textures/line06.png", GL_TRUE, "line06");
	ResourceManager::LoadTexture("data/textures/line07.png", GL_TRUE, "line07");
	ResourceManager::LoadTexture("data/textures/line08.png", GL_TRUE, "line08");
	ResourceManager::LoadTexture("data/textures/line09.png", GL_TRUE, "line09");

	// Set render-specific controls
	Renderer = new SpriteRenderer(ResourceManager::GetShader("sprite"));
	// Set buttons
	// ;) Sorry for the "magic numbers". I'm just in a hurry
	glm::vec2 pos(static_cast<GLfloat>(this->Width - 2 * this->Width / 6), 
		static_cast<GLfloat>(this->Height - this->Height / 6));
	glm::vec2 size(static_cast<GLfloat>(this->Width / (2*2.27f)), 
				   static_cast<GLfloat>(this->Height / (2*2.6f)));
	m_startButton = new ButtonOnPanel(pos, size, ResourceManager::GetTexture("StartUp"), ResourceManager::GetTexture("StartDown")/*, color, vel*/);
	
	// Set button LINES
	// Sorry again for the "magic numbers"
	glm::vec2 pos2(static_cast<GLfloat>(this->Width / 6),
		static_cast<GLfloat>(this->Height - this->Height / 7));
	glm::vec2 size2(static_cast<GLfloat>(this->Width / (2.5f * 2.27f)),
		static_cast<GLfloat>(this->Height / (2.5f * 2.6f)));
	m_selectLines = new ButtonOnPanel(pos2, size2, ResourceManager::GetTexture("LinesUp"), ResourceManager::GetTexture("LinesDown")/*, color, vel*/);

	// Set drums
	srand((unsigned)time(NULL));
	for (int i = 0; i < 5/*COUNT DRUMS*/; i++) {
		glm::vec2 posDrum(Width / 6.54f + i * Width / 7.21f, (-1.0f) * Height / 6.02f);
		glm::vec2 sizeItem(Width / 7.21f, Height / 6.02f);
		glm::vec2 vel(0.0f, rand() % 2000 + 2000);
		m_drums.push_back(new rotating_drum(posDrum, sizeItem, vel));
		// Add all items
		m_drums[i]->addItem(ResourceManager::GetTexture("Slot01"), "Slot01");
		m_drums[i]->addItem(ResourceManager::GetTexture("Slot02"), "Slot02");
		m_drums[i]->addItem(ResourceManager::GetTexture("Slot03"), "Slot03");
		m_drums[i]->addItem(ResourceManager::GetTexture("Slot04"), "Slot04");
		m_drums[i]->addItem(ResourceManager::GetTexture("Slot05"), "Slot05");
		m_drums[i]->addItem(ResourceManager::GetTexture("Slot06"), "Slot06");
		m_drums[i]->addItem(ResourceManager::GetTexture("Slot07"), "Slot07");
		m_drums[i]->addItem(ResourceManager::GetTexture("Slot08"), "Slot08");
		m_drums[i]->addItem(ResourceManager::GetTexture("Slot09"), "Slot09");
		m_drums[i]->addItem(ResourceManager::GetTexture("Slot10"), "Slot10");
		// Mix all items
		m_drums[i]->Init();
	}

	// Set lines
	glm::vec2 pos3(0,0);
	glm::vec2 size3(Width, Height);
	lines.push_back(new Line(ResourceManager::GetTexture("line01"), pos3, size3));
	lines.push_back(new Line(ResourceManager::GetTexture("line02"), pos3, size3));
	lines.push_back(new Line(ResourceManager::GetTexture("line03"), pos3, size3));
	lines.push_back(new Line(ResourceManager::GetTexture("line04"), pos3, size3));
	lines.push_back(new Line(ResourceManager::GetTexture("line05"), pos3, size3));
	lines.push_back(new Line(ResourceManager::GetTexture("line06"), pos3, size3));
	lines.push_back(new Line(ResourceManager::GetTexture("line07"), pos3, size3));
	lines.push_back(new Line(ResourceManager::GetTexture("line08"), pos3, size3));
	lines.push_back(new Line(ResourceManager::GetTexture("line09"), pos3, size3));
}

// Game update fuction
void Game::Update(GLfloat dt)
{
	for (int i = 0; i < 5/*COUNT DRUMS*/; i++) {
		m_drums[i]->Update(dt);
	}

	// If game active
	if (State == GAME_ACTIVE) {
		// We think time
		curentTime += dt;
		// If the rotation time of the left
		if (curentTime >= timeRotation) {
			// Change state
			State = GAME_STOPPING;

			curentTime = 0.0f;
			timeRotation = -1.0f;
		}
	}

	// if after rotation mode
	if (State == GAME_STOPPING) {
		// Clear lines
		for (int i = 0; i < countLines; i++) {
			lines[i]->items.clear();
		}
		// Get specific values in lines
		for (int i = 0; i < m_drums.size(); i++) {
			std::vector<std::string> names = m_drums[i]->GetVisible();			
			
			lines[0]->items.push_back(names[1]);
			lines[1]->items.push_back(names[0]);
			lines[2]->items.push_back(names[2]);
		}
		// Get specific values in lines
		std::vector<std::string> names = m_drums[0]->GetVisible();
		lines[3]->items.push_back(names[2]);
		lines[4]->items.push_back(names[0]);

		lines[5]->items.push_back(names[2]);
		lines[6]->items.push_back(names[0]);
		
		lines[7]->items.push_back(names[1]);
		lines[8]->items.push_back(names[1]);
		// Get specific values in lines
		names = m_drums[1]->GetVisible();
		lines[3]->items.push_back(names[2]);
		lines[4]->items.push_back(names[0]);

		lines[5]->items.push_back(names[1]);
		lines[6]->items.push_back(names[1]);

		lines[7]->items.push_back(names[0]);
		lines[8]->items.push_back(names[2]);
		// Get specific values in lines
		names = m_drums[2]->GetVisible();
		lines[3]->items.push_back(names[1]);
		lines[4]->items.push_back(names[1]);

		lines[5]->items.push_back(names[0]);
		lines[6]->items.push_back(names[2]);

		lines[7]->items.push_back(names[0]);
		lines[8]->items.push_back(names[2]);
		// Get specific values in lines
		names = m_drums[3]->GetVisible();
		lines[3]->items.push_back(names[0]);
		lines[4]->items.push_back(names[2]);

		lines[5]->items.push_back(names[1]);
		lines[6]->items.push_back(names[1]);

		lines[7]->items.push_back(names[0]);
		lines[8]->items.push_back(names[2]);
		// Get specific values in lines
		names = m_drums[4]->GetVisible();
		lines[3]->items.push_back(names[0]);
		lines[4]->items.push_back(names[2]);

		lines[5]->items.push_back(names[2]);
		lines[6]->items.push_back(names[0]);

		lines[7]->items.push_back(names[1]);
		lines[8]->items.push_back(names[1]);

		// Check wins points
		winsPoints = 0;
		for (int i = 0; i < countLines; i++) {
			winsPoints += lines[i]->CheckWin(bet);
		}

	}

}

// Render Scene
void Game::Render()
{
	// Draw all drums
	for (int i = 0; i < 5/*COUNT DRUMS*/; i++) {
		m_drums[i]->Draw(*Renderer);
	}
	
	// Draw backgrounds
	Renderer->DrawSprite(ResourceManager::GetTexture("Book_Of_Ra"),
		glm::vec2(0, 0), glm::vec2(Width, Height), 0.0f, glm::vec3(1.0f, 1.0f, 1.0f));
	Renderer->DrawSprite(ResourceManager::GetTexture("face"),
		glm::vec2(0, 0), glm::vec2(Width, Height), 0.0f, glm::vec3(1.0f, 1.0f, 1.0f));

	// Draw buttons
	m_startButton->Draw(*Renderer);
	m_selectLines->Draw(*Renderer);

	// Set colors
	glm::vec3 red(1.0f, 0.0f, 0.0f);
	glm::vec3 green(0.0f, 1.0f, 0.0f);
	glm::vec3 yel(1.0f, 1.0f, 0.0f); 
	glm::vec3 blue(0.0f, 0.0f, 1.0f);

	// Print count line
	std::string str;
	str = std::to_string((int)countLines);
	fpsTEXT->RenderText(str, Width / 21.15f * 17.85f, Height / 15.85f * 12.00f, 1.0f, blue);
	// Print bet
	str = std::to_string((int)bet);
	fpsTEXT->RenderText(str, Width / 21.15f * 17.85f, Height / 15.85f * 11.50f, 1.0f, yel);
	// Print lines/bet
	str = std::to_string((int)(bet*countLines));
	fpsTEXT->RenderText(str, Width / 21.15f * 17.85f, Height / 15.85f * 13.0f, 1.0f, yel);

	// Calculate FPS and print it
	CalculateFrameRate();
	str = "FPS: " + std::to_string((int)FPS);
	if (FPS < 15)
		fpsTEXT->RenderText(str, 5.0f, Height - 25, 1.0f, red);
	else if (FPS < 30) 
		fpsTEXT->RenderText(str, 5.0f, Height - 25, 1.0f, yel);
	else fpsTEXT->RenderText(str, 5.0f, Height - 25, 1.0f, green);

	// If game state = LINE SHOW
	if (State == GAME_SHOW_LINES) {
		// Draw Lines
		for (int i = 0; i < countLines; i++) {
			lines[i]->Draw(*Renderer);
		}
	}

	// if after rotation mode
	if (State == GAME_STOPPING) {
		// Draw winers lines
		for (int i = 0; i < countLines; i++) {
			if (lines[i]->visible)
				lines[i]->Draw(*Renderer);
		}

		// Print wins points
		if (winsPoints != 0) {
			str = "You WIN " + std::to_string((int)(bet*winsPoints));
			fpsTEXT->RenderText(str, Width / 21.15f * 5.50f, Height / 15.85f * 11.8f, 1.0f, yel);
		}
	}
}

void Game::ProcessInput(GLfloat dt)
{
	// If Game state GAME_EXPECTATION
	if (this->State == GAME_EXPECTATION)
	{
		if (this->Keys[GLFW_MOUSE_BUTTON_1]) {
			//std::cout << "Key Mouse Button 1" << std::endl;
		}
		if (this->Keys[GLFW_MOUSE_BUTTON_2]) {
			//std::cout << "Key Mouse Button 2" << std::endl;
		}
		// if press button "START"
		if (m_startButton->ProcessInput(dt, MousePos, this->Keys[GLFW_MOUSE_BUTTON_1]))
		{
			// change state on GAME_ACTIVE
			this->State = GAME_ACTIVE;
			// Calculate time rotations all drums
			timeRotation = 3.0 + 0.5 * 4 + 0.5f;
			// Start rotation all drums
			for (int i = 0; i < 5/*COUNT DRUMS*/; i++) {
				m_drums[i]->StartRotation(3.0 + 0.5 * i);
			}
		}
		// if press button "Select Lines"
		if (m_selectLines->ProcessInput(dt, MousePos, this->Keys[GLFW_MOUSE_BUTTON_1]))
		{
			// change state on GAME_SHOW_LINES
			this->State = GAME_SHOW_LINES;
			// change count lines
			countLines += 2;
			if (countLines > 9) {
				countLines = 1;
			}
		}
	}

	// IF Game state other
	if ((this->State == GAME_SHOW_LINES) || (this->State == GAME_STOPPING))
	{
		// change game stat on GAME_EXPECTATION
		if ((this->Keys[GLFW_MOUSE_BUTTON_1]) || (this->Keys[GLFW_MOUSE_BUTTON_2])) {
			this->State = GAME_EXPECTATION;
			winsPoints = 0;
			for (int i = 0; i < countLines; i++) {
				lines[i]->visible = false;
			}
		}
	}
}
