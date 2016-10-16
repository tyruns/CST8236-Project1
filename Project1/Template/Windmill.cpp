#include "Windmill.h"

//Constructor
Windmill::Windmill(std::string windmill, std::string blade) {
	//First load textures
	windmillText.loadFromFile(windmill);
	bladeText.loadFromFile(blade);
	//Create vectors for blades and mill
	sf::Vector2<float> millSize((float)windmillText.getSize().x, (float)windmillText.getSize().y);
	sf::Vector2<float> bladeSize((float)bladeText.getSize().x * 0.25, (float)bladeText.getSize().y * 0.25);

	//create rectangles with the vectors
	baseRect = sf::RectangleShape(millSize);
	baseRect.setTexture(&windmillText);
	//The rest of this function was modelled after online examples. Seems to work perfectly fine after a few tweakings.
	baseRect.setOrigin(baseRect.getLocalBounds().left + baseRect.getLocalBounds().width / 2.0f, baseRect.getLocalBounds().top + baseRect.getLocalBounds().height / 2.0f);  
	baseRect.setScale(0.5, 0.5);
	base.m_CurrentShape = &baseRect;

	//Need to create 4 blades
	for (int i = 0; i < BLADES; i++) {
		//each iteration makes a new rectangle 
		sf::RectangleShape bladeRect(bladeSize);
		bladeRect.setTexture(&bladeText);
		bladeRect.setOrigin(0, bladeRect.getLocalBounds().height / 2.0f);
		//the iteration is saved and setup in an array the scope of the loop
		bladeRects[i] = bladeRect;
		bladeRects[i].setRotation(90.0f*i); 
		bladeRects[i].setPosition(0, (-baseRect.getLocalBounds().height / 4.0f));
		//once setup, copy it over 
		blades[i] = new TransformNode(&bladeRects[i]);
		//re-add all children
		base.AddChild(blades[i]);
	}
}

//Getters

sf::Vector2f Windmill::getPosition() const {
	return baseRect.getPosition();
}

double Windmill::getRotation() const {
	return baseRect.getRotation();
}

sf::Vector2f Windmill::getOrigin() const {
	return this->origin;
}

//Setters

void Windmill::setPosition(float x, float y) {
	baseRect.setPosition(x, y);
}

void Windmill::setRotation(float angle) {
	baseRect.setRotation(angle);
}

void Windmill::setOrigin(sf::Vector2f origin) {
	this->origin = origin;
}

//Rotational Functions

void Windmill::Spin(float x, float y) {
	baseRect.rotate(360.0f*(x/ y));
}


//NOTE - this function was completely modelled after an example i found online
void Windmill::RotateBase(float x, float y, sf::Vector2f start) {
	float angleToRotate = (x / y) * M_PI * 2;
	float xChange = cos(angleToRotate) * (baseRect.getPosition().x - start.x) - sinf(angleToRotate) * (baseRect.getPosition().y - start.y) + start.x;
	float yChange = sinf(angleToRotate) * (baseRect.getPosition().x - start.x) + cosf(angleToRotate) * (baseRect.getPosition().y - start.y) + start.y;
	baseRect.setPosition(xChange, yChange);
}


void Windmill::RotateBlades(float angle) {
	for (int i = 0; i < BLADES; i++) {
		bladeRects[i].rotate(angle);
	}
}

//draw :D
void Windmill::Draw(sf::RenderTarget* target) {
	base.Draw(target);
}