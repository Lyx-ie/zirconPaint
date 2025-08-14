#pragma once
#include "masterInclude.h"

class Button {
public:
	sf::Vector2i buttonBoundsLR;
	sf::Vector2i buttonBoundsUD;
	sf::Vector2f buttonPosition;
	sf::Texture buttonTexture;
	sf::Texture buttonPressed;
	sf::Texture buttonCurrentTexture;

	sf::Color buttonColour;
	toolType tool;
	Button(std::string defaultInput, std::string pressedInput, sf::Vector2f locationInput, toolType thisButton = _NULL, sf::Color inputColour = sf::Color::Transparent);
	~Button();
	sf::Sprite buttonRender();
	bool buttonQuery(sf::Vector2i mouseInput);
	void buttonPressedAction();
	void resetButtonPressed();
	sf::Color returnButtonColour();
	toolType returnToolType();
};