
#include "drawingFunctions.h"
int main()
{
    //initialising parametersS
    sf::RenderWindow window(sf::VideoMode({ 1080,720 }), "SFML window");
    window.setFramerateLimit(60);

    //current tool is none
    toolType currentTool = _NULL;

    //initialise default font and current font parameters which can be changed later
    const sf::Font defaultFont("assets/fonts/arial.ttf");
    const sf::Color defaultColour = sf::Color::White;
    const float defaultSize = 5;
    sf::Font currentFont = defaultFont;
    sf::Color currentColour = defaultColour;
    float currentSize = defaultSize;

    //initialise functional variables
    sf::Vector2i mouseLocationVectorInt;
    sf::Vector2f mouseDownLocation(mouseLocationVectorInt);
    sf::Vector2f moveOffset;
    sf::Vector2f previewLocation;
    bool mouseBusy = false;
    bool keyboardActionThisFrame = false;

    //create vector view hierarchy cache (unlimited) If have time, create limited action hierarchy cache
    std::vector <Tools*> hierarchy; // <-- *

    //initialise pointers for various tool types in use by the program
    ellipseTool* currentEllipse = NULL;
    rectangleTool* currentRectangle = NULL;
    freehandTool* currentFreehand = NULL;
    lineTool* currentLine = NULL;

    sf::CircleShape previewCircle;

    //main loop begins
    while (window.isOpen()) {
        window.clear();

        //get and store the current mouse location as a vector and a float for later use
        mouseLocationVectorInt = sf::Mouse::getPosition(window);
        sf::Vector2f mouseLocationVectorFloat(mouseLocationVectorInt);

        while (const std::optional event = window.pollEvent())
        {
            if (currentTool == _ellipse) {
                if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))
                {
                    if (mouseBusy == false) { //if this is the first frame that the mouse has been pressed down
                        //create a new ellipse
                        currentEllipse = new ellipseTool();
                        mouseDownLocation = createEllipse(mouseLocationVectorFloat, currentEllipse, currentColour);
                        mouseBusy = true;
                    }
                    else if (mouseBusy == true) { //if the mouse is already busy this frame
                        //update the size values of the shape this frame
                        currentEllipse->setEllipseSize(mouseLocationVectorFloat - mouseDownLocation);
                    }
                }
                else if (mouseBusy == true) { //if the mouse is released this frame
                    //push tool data to the stack
                    hierarchy.push_back(currentEllipse);
                    mouseBusy = false;
                }
            }
            else if (currentTool == _rectangle) {//see above
                if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))
                {
                    if (mouseBusy == false) {
                        currentRectangle = new rectangleTool();
                        mouseDownLocation = createRectangle(mouseLocationVectorFloat, currentRectangle, currentColour);
                        mouseBusy = true;
                    }
                    else if (mouseBusy == true) {
                        currentRectangle->setRectangleSize(mouseLocationVectorFloat - mouseDownLocation);
                    }
                }
                else if (mouseBusy == true) {
                    hierarchy.push_back(currentRectangle);
                    mouseBusy = false;
                }
            }
            else if (currentTool == _freehand) {
                if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)) { // if clicked
                    if (mouseBusy == false) { //initialise new freehand tool
                        currentFreehand = new freehandTool;
                        mouseBusy = true;
                        createFreehand(mouseDownLocation, currentFreehand, currentColour);
                        previewLocation = mouseLocationVectorFloat;
                    }
                    while (mouseBusy == true) {
                        if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)) { //while lmb is pressed
                            //this loop stores a freehand stroke in one hierarchy data entry in the stack, optimisation so cool
                            window.setFramerateLimit(255);
                            mouseLocationVectorInt = sf::Mouse::getPosition(window);
                            sf::Vector2f mouseLocationVectorFloat(mouseLocationVectorInt);
                            currentFreehand->freehandDraw(mouseLocationVectorFloat);
                            for (Tools* currentTool : hierarchy) {
                                window.draw(currentTool->render());
                            }
                            window.draw(currentFreehand->render());
                            window.display();
                        }
                        else {//if mouse is released this frame
                            //push data to stack
                            hierarchy.push_back(currentFreehand);
                            mouseBusy = false;
                            window.setFramerateLimit(60);
                        }
                    }
                }
            }
            else if (currentTool == _line) {
                if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))
                {
                    if (mouseBusy == false) {
                        //create a new line
                        currentLine = new lineTool();
                        mouseDownLocation = createLine(mouseLocationVectorFloat, currentLine, currentColour);
                        mouseBusy = true;
                    }
                    else if (mouseBusy == true) {
                        //draw the line
                        currentLine->setLineLocation(mouseLocationVectorFloat - mouseDownLocation);
                    }
                }
                else if (mouseBusy == true) {
                    //push the line to the stack
                    hierarchy.push_back(currentLine);
                    mouseBusy = false;
                }
            }
            if (event->is<sf::Event::Closed>()) { window.close(); }//close the window if the cross is pressed
            //tool change function (there are set colours here because I don't have a colour swatch yet, but colour change infrastructure is implemented).
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Num1)) {
                currentTool = _ellipse;
                currentColour = sf::Color::Blue;
            }
            else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Num2)) {
                currentTool = _rectangle;
                currentColour = sf::Color::Magenta;
            }
            else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Num3)) {
                currentTool = _freehand;
                currentColour = sf::Color::White;
            }
            else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Num4)) {
                currentTool = _line;
                currentColour = sf::Color::Red;
            }
            //undo function
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::LControl)) {
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Z)) {
                    if (keyboardActionThisFrame == false && hierarchy.size() > 0) {
                        hierarchy.erase(hierarchy.end() - 1);
                        keyboardActionThisFrame = true;
                    }
                }
                else {
                    keyboardActionThisFrame = false;
                }
            }
            else {
                keyboardActionThisFrame = false;
            }
        }
        //render hierarchy
        for (Tools* currentTool : hierarchy) {
            window.draw(currentTool->render());
        }
        //priority render the shape being made if mouse is down
        if (mouseBusy) {
            if (currentEllipse && currentTool == _ellipse) {
                window.draw(currentEllipse->renderEllipse());
            }
            else if (currentRectangle && currentTool == _rectangle) {
                window.draw(currentRectangle->renderRectangle());
            }
            else if (currentLine && currentTool == _line) {
                window.draw(currentLine->renderLine());
            }
        }
        //render prievews if required
        if (currentTool == _freehand) {
            moveOffset = previewLocation - mouseLocationVectorFloat;
            if (moveOffset != sf::Vector2f(0, 0)) { //don't update the location if the mouse hasn't moved this frame.
                previewLocation = mouseLocationVectorFloat;
            }
            else {}
            //draw the circle preview
            previewCircle.setFillColor(currentColour);
            previewCircle.setRadius(currentSize);
            previewCircle.setPosition(previewLocation - sf::Vector2f(currentSize, currentSize));
            window.draw(previewCircle);
        }
        else if (currentTool == _line) {
            moveOffset = previewLocation - mouseLocationVectorFloat;
            if (moveOffset != sf::Vector2f(0, 0)) {
                previewLocation = mouseLocationVectorFloat;
            }
            else {}
            previewCircle.setFillColor(currentColour);
            previewCircle.setRadius(currentSize);
            previewCircle.setPosition(previewLocation - sf::Vector2f(currentSize, currentSize));
            window.draw(previewCircle);
        }
        //the big one
        window.display();
    }
}
