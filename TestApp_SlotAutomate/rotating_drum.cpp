#include "rotating_drum.h"
#include <time.h>
#include <stdlib.h>
#include <iostream>
#include "ofxTweener.h"

drums_item::drums_item()
	: Position(0, 0), Size(1, 1), Velocity(0, 0), texture() 
{
	//std::Randomize();
}

drums_item::drums_item(glm::vec2 pos, glm::vec2 size, glm::vec2 velocity, Texture2D	txture) 
	: Position(pos), Size(size), Velocity(velocity), texture(txture)
{
}

void drums_item::Init() {

}

void drums_item::Update(GLfloat dt){
	Position.y += Velocity.y * dt;
}

void drums_item::Draw(SpriteRenderer &renderer) {
	renderer.DrawSprite(this->texture, this->Position, this->Size);
}

void drums_item::SetPosition(glm::vec2 pos) {
	Position.x = pos.x;
	Position.y = pos.y;
}

void drums_item::CorrectPosition() {
	int corPos = (int)Position.y / Size.y;
	Tweener.addTween(Position.y, corPos * Size.y, 0.5f);
}

glm::vec2 drums_item::GetPosition() {
	return Position;
}

glm::vec2 drums_item::GetSize() {
	return Size;
}
//--------------------------------------------------
rotating_drum::rotating_drum()
	: Position(0, 0), Size(1, 1), Velocity(0, 0), curentTime(0.0f), timeRotation(-1.0f)
{
}

rotating_drum::rotating_drum(glm::vec2 pos, glm::vec2 size, glm::vec2 velocity) 
	: Position(pos), Size(size), Velocity(velocity), curentTime(0.0f), timeRotation(-1.0f)
{
}

void rotating_drum::addItem(Texture2D item, std::string name)
{
	glm::vec2 posItem(Position.x, Position.y/* + Size.y * items.size()*/);

	items.push_back(new drums_item(posItem, Size, Velocity, item));
	names.push_back(name);
}

void rotating_drum::Init() {
	//srand((unsigned)time(NULL));
	for (int i = 0; i < items.size(); i++) {
		int r = rand() % items.size();
		drums_item* temp;		std::string tstr;
		temp = items[i];		tstr = names[i];
		items[i] = items[r];	names[i] = names[r];
		items[r] = temp;		names[r] = tstr;
	}

	for (int i = 0; i < items.size(); i++) {
		glm::vec2 posItem(Position.x, Position.y + Size.y * i);
		items[i]->SetPosition(posItem);
	}
}

void rotating_drum::Update(GLfloat dt) {
	Tweener.update();

	if (curentTime < timeRotation) {
		curentTime += dt;

		// Rotate drum's items
		for (int i = 0; i < items.size(); i++) {
			items[i]->Update(dt);
		}

		float min = items[0]->GetPosition().y;
		n_min = 0;
		for (int i = 1; i < items.size(); i++) {
			if (min > items[i]->GetPosition().y) {
				min = items[i]->GetPosition().y;
				n_min = i;
			}
		}
		if (items[n_min]->GetPosition().y >= 0) {
			if (n_min != 0) {
				glm::vec2 posOtr(items[n_min]->GetPosition());
				posOtr.y -= items[n_min]->GetSize().y;
				items[n_min - 1]->SetPosition(posOtr);
				n_min = n_min - 1;
			}
			else {
				glm::vec2 posOtr(items[n_min]->GetPosition());
				posOtr.y -= items[n_min]->GetSize().y;
				items[items.size() - 1]->SetPosition(posOtr);
				n_min = items.size() - 1;
			}
		}
	}
	else {
		if (timeRotation != (-1.0f)) {
			// Correct position
			for (int i = 0; i < items.size(); i++) {
				items[i]->CorrectPosition();
			}
			
			std::vector<std::string> n = GetVisible();
			for (int i = 0; i < n.size(); i++) {
				std::cout << n[i] << std::endl;
			}

			std::cout << "Drum stoped" << std::endl;

			timeRotation = -1.0f;
			curentTime = 0.0f;
		}
	}
}

void rotating_drum::Draw(SpriteRenderer &renderer) {
	for (int i = 0; i < items.size(); i++) {
		items[i]->Draw(renderer);
	}
}

void rotating_drum::StartRotation(double time) {
	timeRotation = time;
	curentTime = 0.0f;
}

std::vector<std::string> rotating_drum::GetVisible() {
	std::vector<std::string> namesVisible;
	namesVisible.push_back(names[(n_min + 2) % names.size()]);
	namesVisible.push_back(names[(n_min + 3) % names.size()]);
	namesVisible.push_back(names[(n_min + 4) % names.size()]);

	return namesVisible;
}