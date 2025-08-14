#include "buttons.h"




Button::Button(std::string defaultInput, std::string pressedInput, sf::Vector2f locationInput, toolType thisButton, sf::Color inputColour)
{
	bool resizeSuccessful;
	tool = thisButton;
	buttonPosition = locationInput;
	buttonBoundsLR.x = buttonPosition.x;
	buttonBoundsLR.y = buttonPosition.x + 64;
	buttonBoundsUD.x = buttonPosition.y;
	buttonBoundsUD.y = buttonPosition.y + 64;
	buttonTexture.loadFromFile(defaultInput);
	buttonPressed.loadFromFile(pressedInput);
	buttonCurrentTexture.loadFromFile(defaultInput);
	buttonColour = inputColour;
}

Button::~Button()
{
}

sf::Sprite Button::buttonRender()
{
	sf::Sprite sprite(buttonCurrentTexture);
	sprite.setPosition(buttonPosition);

	return sprite;
}

bool Button::buttonQuery(sf::Vector2i mouseInput)
{
	
	if ((mouseInput.x > buttonBoundsLR.x) && (mouseInput.x < buttonBoundsLR.y) && (mouseInput.y > buttonBoundsUD.x) && (mouseInput.y < buttonBoundsUD.y)) {
		return 1;
	}
	return 0;
}

void Button::buttonPressedAction()
{
	buttonCurrentTexture = buttonPressed;
}

void Button::resetButtonPressed()
{
	buttonCurrentTexture = buttonTexture;
}

sf::Color Button::returnButtonColour()
{
	return sf::Color(buttonColour);
}

toolType Button::returnToolType()
{
	return toolType(tool);
}
