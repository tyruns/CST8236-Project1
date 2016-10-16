#pragma once
#ifndef _WINDMILL_H
#define _WINDMILL_H
#define _USE_MATH_DEFINES 
#include <SFML/Graphics.hpp>
#include "TransformNode.h"
#define WINDMILLS 3
#define BLADES 4


class Windmill {
public:
	//Windmill Constructor
	Windmill(std::string windmill, std::string blade); 
	//Getters
	sf::Vector2f getPosition() const;
	double getRotation() const;
	sf::Vector2f getOrigin() const;
	//Setters
	void setPosition(float x, float y);
	void setRotation(float angle);
	void setOrigin(sf::Vector2f origin);
	//Rotations
	void Spin(float x, float y);
	void RotateBase(float x, float y, sf::Vector2f startingPoint);
	void RotateBlades(float angle);
	//Draw
	void Draw(sf::RenderTarget *target);

protected:
	sf::Texture windmillText;
	sf::Texture bladeText;

	sf::RectangleShape baseRect;
	sf::RectangleShape bladeRects[BLADES];
	TransformNode base;
	TransformNode* blades[BLADES];

	sf::Vector2<float> wSize;
	sf::Vector2<float> bSize;
	sf::Vector2<float> origin;
};
#endif