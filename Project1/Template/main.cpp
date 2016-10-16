#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "TransformNode.h"
#include "Windmill.h"

/*Did not have time to complete audio portion.*
* All related code should now be removed*/
int main(int argc, char *argv) {
	sf::RenderWindow window(sf::VideoMode(800, 800), "Tyler Runions Project 1", sf::Style::Titlebar | sf::Style::Close);
	/*Texture related code was found and modified from 'sept25-2015 repo*/

	sf::Texture cloudText;
	cloudText.loadFromFile("res/tiling_clouds.jpg");
	cloudText.setRepeated(true);
	sf::Sprite cloudSprite;
	cloudSprite.setTexture(cloudText);
	cloudSprite.setTextureRect(sf::IntRect(0, 0, window.getSize().x, window.getSize().y));
	sf::IntRect backgroundRect = cloudSprite.getTextureRect();
	float secondTimer = 0.0f; 
	float movementSpeed = 150.0f; 

	//starting position of first windmill. numbers should make sense a little lower in the code
	sf::Vector2<float> millPos(window.getSize().x*0.25f, window.getSize().y*0.5f);

	//create the windmills
	Windmill* windmills[WINDMILLS];
	for (int i = 0; i < WINDMILLS; i++) {
		windmills[i] = new Windmill("res/eyeofsauron.png", "res/CryManWindmillBlade.png");
		windmills[i]->setPosition(millPos.x * (i + 1), millPos.y); //0.25x*2 should place second windmill in center of screen
		if (i != 0)
			//check if windmill is not first, origin can be set relative to first windmill
			windmills[i]->setOrigin(windmills[i - 1]->getPosition());
		else
			//origin of first windmill must be set to some point
			windmills[i]->setOrigin(sf::Vector2f(window.getSize().x / 2.0f, window.getSize().y / 2.0f));
	}

	sf::Event evt;
	sf::Clock appTimer;
	float angle = 90.0f;
	int selected = 1;
	sf::Vector2<int>prev(sf::Mouse::getPosition().x, sf::Mouse::getPosition().y);

	while (window.isOpen()) {
		float deltaTime = appTimer.restart().asSeconds();

		/* code is based on 'Sept30-2016' repo*/
		while (window.pollEvent(evt)) {
			switch (evt.type) {
			case sf::Event::Closed:
				window.close();
			case sf::Event::KeyPressed:
				if (evt.key.code == sf::Keyboard::Num1) {
					selected = 0; break; 
				}
				if (evt.key.code == sf::Keyboard::Num2) {
					selected = 1; break;
				}
				if (evt.key.code == sf::Keyboard::Num3) {
					selected = 2; break;
				}
				if (evt.key.code == sf::Keyboard::Num4 || evt.key.code == sf::Keyboard::A) {
					selected = WINDMILLS; 
					for (int i = 0; i < WINDMILLS; i++) {
						windmills[i]->setPosition(millPos.x * (i + 1), millPos.y); 
						windmills[i]->setRotation(0);
					}
					break;
				}
			case sf::Event::MouseMoved:
				//Handle x movement
				if (evt.mouseMove.x != prev.x)
				{
					float changeX = float(evt.mouseMove.x) - prev.x;
					if (selected != WINDMILLS)
					{
						windmills[selected]->Spin(changeX, window.getSize().x);
					}else {
						for (int i = 0; i < WINDMILLS; i++)
						{
							windmills[i]->Spin(changeX, window.getSize().x);
						}
					}
					prev.x = evt.mouseMove.x; 
				}
				//Handle y movement
				if (evt.mouseMove.y != prev.y) 
				{ 
					float changeY = float(evt.mouseMove.y) - prev.y;
					if (selected != WINDMILLS) 
					{
						windmills[selected]->RotateBase(changeY, window.getSize().y, windmills[selected]->getOrigin());
					}
					else {
						sf::Vector2f origins;
						for (int i = 0; i < WINDMILLS; i++)
						{
							if (i == 1)
							{ 
								origins = windmills[0]->getPosition(); 
							}
							else if (i == 2) 
							{ 
								origins = windmills[1]->getPosition(); 
							}else{
								origins = windmills[i]->getOrigin();
							}
							windmills[i]->RotateBase(changeY, window.getSize().y, origins);
						}
					}
					prev.y = evt.mouseMove.y; 
				}
			default:
				break;
			}
		}

		//Again, sprite related code was found and modified from 'Sept25-2016' repo
		secondTimer += deltaTime;
		sf::IntRect deltaRect = backgroundRect;
		deltaRect.left = backgroundRect.left + int(movementSpeed * secondTimer);
		cloudSprite.setTextureRect(deltaRect);

		if (secondTimer > 1.0f) {
			secondTimer -= 1.0f;
			backgroundRect.left += int(movementSpeed);
			if (backgroundRect.left >= float(cloudText.getSize().x)) {
				backgroundRect.left -= cloudText.getSize().x;
			}
		}

		//draw and display everything
		window.clear();
		window.draw(cloudSprite);
		for (int i = 0; i < WINDMILLS; i++) {
			windmills[i]->RotateBlades(angle * deltaTime);
			windmills[i]->Draw(&window); 
		}
		window.display();
	}

	return 0;
}