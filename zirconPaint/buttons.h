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
	toolType tool;
	Button(std::string defaultInput, std::string pressedInput, sf::Vector2f locationInput, toolType thisButton);
	~Button();
	sf::Sprite buttonRender();
	bool buttonQuery(sf::Vector2i mouseInput);
	void buttonPressedAction();
	void resetButtonPressed();
	toolType returnToolType();
};