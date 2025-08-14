#pragma once
#include "masterInclude.h"
#include "tools.h"
#include "buttons.h"

int main()
{
    //initialising parametersS
    sf::RenderWindow window(sf::VideoMode({ 1080,720 }), "SFML window");
    window.setFramerateLimit(60);

    //current tool is none
    toolType currentTool = _NULL;
    toolType previousTool = _NULL;

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
    bool allowDrawing = false;
    bool stampToolInstancePrompt = true;
    bool imageSuccess = false;
    std::string stampFilePath;

    //create vector view hierarchy cache (unlimited) If have time, create limited action hierarchy cache
    std::vector <Tools*> hierarchy; // <-- *

    //initialise pointers for various tool types in use by the program
    ellipseTool* currentEllipse = NULL;
    rectangleTool* currentRectangle = NULL;
    freehandTool* currentFreehand = NULL;
    lineTool* currentLine = NULL;
    stampTool* currentStamp = NULL;
    customShapeTool* currentCustom = NULL;
    
    sf::CircleShape previewCircle;

    //initialise UI elements
    sf::RectangleShape verticalBar(sf::Vector2f(100, 720));
    verticalBar.setFillColor(sf::Color(225, 225, 225, 255));
    sf::RectangleShape horizontalBar(sf::Vector2f(980, 100));
    horizontalBar.setPosition(sf::Vector2f(100, 0));
    horizontalBar.setFillColor(sf::Color(225, 225, 225, 255));
    
    sf::RectangleShape otherVerticalBar(sf::Vector2f(80, 700));
    otherVerticalBar.setFillColor(sf::Color(225, 225, 225, 255));
    otherVerticalBar.setPosition(sf::Vector2f(1000, 100));
    sf::RectangleShape otherHorizontalBar(sf::Vector2f(900, 20));
    otherHorizontalBar.setPosition(sf::Vector2f(100, 700));
    otherHorizontalBar.setFillColor(sf::Color(225, 225, 225, 255));

    sf::RectangleShape background(sf::Vector2f(1080, 720));

    std::vector <Button> buttons;

    Button testButton("assets/icons/default.png", "assets/icons/default.png", sf::Vector2f(20, 20), _NULL);
    buttons.push_back(testButton);
    Button rectangleButton("assets/icons/rectDefault.png", "assets/icons/rectPressed.png", sf::Vector2f(180, 20), _rectangle);
    buttons.push_back(rectangleButton);
    Button ellipseButton("assets/icons/ellipseDefault.png", "assets/icons/ellipsePressed.png", sf::Vector2f(260, 20), _ellipse);
    buttons.push_back(ellipseButton);
    Button lineButton("assets/icons/lineDefault.png", "assets/icons/linePressed.png", sf::Vector2f(340, 20), _line);
    buttons.push_back(lineButton);
    Button freehandButton("assets/icons/freehandDefault.png", "assets/icons/freehandPressed.png", sf::Vector2f(100, 20), _freehand);
    buttons.push_back(freehandButton);
    Button customButton("assets/icons/customDefault.png", "assets/icons/customDefault.png", sf::Vector2f(564, 20), _custom);
    buttons.push_back(customButton);
    Button stampButton("assets/icons/stampDefault.png", "assets/icons/stampPressed.png", sf::Vector2f(420, 20), _stamp);
    buttons.push_back(stampButton);
    Button dropDown("assets/icons/dropdown.png", "assets/icons/dropdown.png", sf::Vector2f(484, 20), _stampSelect);
    buttons.push_back(dropDown);
    Button whiteButton("assets/icons/White.png", "assets/icons/White.png", sf::Vector2f(20, 100), _NULL, sf::Color::White);
    buttons.push_back(whiteButton);
    Button redButton("assets/icons/Red.png", "assets/icons/Red.png", sf::Vector2f(20, 164), _NULL, sf::Color::Red);
    buttons.push_back(redButton);
    Button blueButton("assets/icons/Blue.png", "assets/icons/Blue.png", sf::Vector2f(20, 228), _NULL, sf::Color::Blue);
    buttons.push_back(blueButton);
    Button tealButton("assets/icons/Teal.png", "assets/icons/Teal.png", sf::Vector2f(20, 292), _NULL, sf::Color(115, 251, 253, 255));
    buttons.push_back(tealButton);
    Button blackButton("assets/icons/Black.png", "assets/icons/Black.png", sf::Vector2f(20, 356), _NULL, sf::Color::Black);
    buttons.push_back(blackButton);
    Button magentaButton("assets/icons/Magenta.png", "assets/icons/Magenta.png", sf::Vector2f(20, 420), _NULL, sf::Color::Magenta);
    buttons.push_back(magentaButton);
    Button limeGreenButton("assets/icons/limeGreen.png", "assets/icons/limeGreen.png", sf::Vector2f(20, 484), _NULL, sf::Color::Green);
    buttons.push_back(limeGreenButton);
    Button darkGreenButton("assets/icons/darkGreen.png", "assets/icons/darkGreen.png", sf::Vector2f(20, 548), _NULL, sf::Color(55, 126, 71, 255));
    buttons.push_back(darkGreenButton);
    Button yellowButton("assets/icons/Yellow.png", "assets/icons/Yellow.png", sf::Vector2f(20, 612), _NULL, sf::Color::Yellow);
    buttons.push_back(yellowButton);

    
    //main loop begins
    while (window.isOpen()) {
        window.clear();



        //get and store the current mouse location as a vector and a float for later use
        mouseLocationVectorInt = sf::Mouse::getPosition(window);
        sf::Vector2f mouseLocationVectorFloat(mouseLocationVectorInt);

        //allow drawing function checks
        if (window.hasFocus() != true) { allowDrawing = false; }
        else if (mouseLocationVectorFloat.x < 100 || mouseLocationVectorFloat.y < 100) { allowDrawing = false; }
        else if (mouseLocationVectorFloat.x > 1000 || mouseLocationVectorFloat.y > 700) { allowDrawing = false; }
        else { allowDrawing = true; }

        while (const std::optional event = window.pollEvent())
        {
            if (allowDrawing == false) {

                if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)) {
                    for (Button& thisButton : buttons) {
                        if (thisButton.buttonQuery(mouseLocationVectorInt)) {
                            currentTool = thisButton.returnToolType();
                            if (currentTool == _NULL) {
                                currentColour = thisButton.returnButtonColour();
                                currentTool = previousTool;
                            }
                            else {
                                previousTool = currentTool;

                            }
                        }
                    }
                }
            }

            //main drawing loop
            if (allowDrawing == true || currentTool == _stampSelect || currentTool == _stamp) {

                
                if (currentTool == _ellipse) {
                    if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))
                    {
                        if (mouseBusy == false) { //if this is the first frame that the mouse has been pressed down
                            //create a new ellipse
                            currentEllipse = new ellipseTool();
                            mouseDownLocation = mouseLocationVectorFloat;
                            currentEllipse->setEllipseColour(currentColour);
                            currentEllipse->setEllipseLocation(mouseLocationVectorFloat);
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
                            mouseDownLocation = mouseLocationVectorFloat;
                            currentRectangle->setRectangleColour(currentColour);
                            currentRectangle->setRectangleLocation(mouseLocationVectorFloat);
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
                            currentFreehand->setFreehandColour(currentColour);
                            currentFreehand->setFreehandSize(currentSize);
                            previewLocation = mouseLocationVectorFloat;
                        }
                        while (mouseBusy == true) {
                            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Escape)) {
                                if (hierarchy.size() > 0) {
                                    hierarchy.erase(hierarchy.end() - 1);
                                }
                                break;
                            }
                            if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)) { //while lmb is pressed
                                //this loop stores a freehand stroke in one hierarchy data entry in the stack, optimisation so cool
                                window.setFramerateLimit(255);
                                window.clear();
                                mouseLocationVectorInt = sf::Mouse::getPosition(window);
                                sf::Vector2f mouseLocationVectorFloat(mouseLocationVectorInt);
                                currentFreehand->freehandDraw(mouseLocationVectorFloat);
                                window.draw(background);
                                for (Tools* currentTool : hierarchy) {
                                    window.draw(currentTool->render());
                                }

                                window.draw(currentFreehand->render());
                                window.draw(verticalBar);
                                window.draw(horizontalBar);
                                window.draw(otherVerticalBar);
                                window.draw(otherHorizontalBar);
                                for (Button& thisButton : buttons) {
                                    window.draw(thisButton.buttonRender());
                                }
                                window.display();
                            }
                            else {//if mouse is released this frame
                                //push data to stack
                                window.clear();
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
                            mouseDownLocation = mouseLocationVectorFloat;
                            currentLine->setLineColour(currentColour);
                            currentLine->setLineOrigin(mouseLocationVectorFloat);
                            currentLine->setLineThickness(currentSize * 2);
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
                else if (currentTool == _stamp || currentTool == _stampSelect) {
                    if (currentStamp == NULL) {
                        currentStamp = new stampTool();
                        currentTool = _stampSelect;
                    }
                    if (currentTool == _stampSelect) {
                        openFile();
                        stampFilePath = returnFilePath();
                        imageSuccess = currentStamp->setImage(stampFilePath);
                        if (imageSuccess == false) {
                            incorrectFileTypeDialogueBox();
                            allowDrawing = false;
                            currentTool = _NULL;
                        }
                        else { currentTool = _stamp; }
                    }
                    if (currentTool == _stamp && allowDrawing) {
                        bool successfulDrawing = currentStamp->stampLocation(mouseLocationVectorFloat);
                        if (successfulDrawing == false) { currentTool = _NULL; }
                        else if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)) {
                            if (mouseBusy == false) {
                                currentStamp = new stampTool();
                                currentStamp->setImage(stampFilePath);
                                currentStamp->stampLocation(mouseLocationVectorFloat);
                                currentStamp->stampRender();
                                hierarchy.push_back(currentStamp);
                                mouseBusy = true;
                            }
                        }
                        else { mouseBusy = false; }
                    }
                }
                else if (currentTool == _custom) {
                    bool newLinePlaced = false;
                    bool linePlaced = false;
                    if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)) { // if clicked
                        if (mouseBusy == false) {
                            currentCustom = new customShapeTool;
                            mouseBusy = true;
                            currentCustom->setColour(currentColour);
                            currentCustom->placeLine(mouseLocationVectorFloat);
                        }
                        while (mouseBusy == true) {
                            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Escape)) {
                                if (hierarchy.size() > 0) {
                                    hierarchy.erase(hierarchy.end() - 1);
                                }
                                break;
                            }

                            mouseLocationVectorInt = sf::Mouse::getPosition(window);
                            sf::Vector2f mouseLocationVectorFloat(mouseLocationVectorInt);
                            if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)) {
                                if (linePlaced == false) {
                                    currentCustom->placeLine(mouseLocationVectorFloat);
                                    currentCustom->renderLines(mouseLocationVectorFloat);
                                    newLinePlaced = true;
                                    if (currentCustom->shapeCreated) {
                                        window.clear();
                                        hierarchy.push_back(currentFreehand);
                                        mouseBusy = false;
                                        window.setFramerateLimit(60);
                                        break;
                                    }
                                    linePlaced = true;
                                }
                            }
                            else {
                                linePlaced = false;
                            }
                            window.setFramerateLimit(255);
                            window.clear();
                            window.draw(background);
                            for (Tools* currentTool : hierarchy) {
                                window.draw(currentTool->render());
                            }
                            
                            window.draw(verticalBar);
                            window.draw(horizontalBar);
                            window.draw(otherVerticalBar);
                            window.draw(otherHorizontalBar);
                            for (Button& thisButton : buttons) {
                                window.draw(thisButton.buttonRender());
                            }
                            if (newLinePlaced) {
                                newLinePlaced = false;
                            }
                            else {
                                window.draw(currentCustom->renderLines(mouseLocationVectorFloat));
                            }
                            window.display();

                        }
                    }
                }
            }

            if (event->is<sf::Event::Closed>()) { window.close(); }//close the window if the cross is pressed
            //tool change function (there are set colours here because I don't have a colour swatch yet, but colour change infrastructure is implemented).
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Num1)) {
                currentColour = sf::Color::Blue;
            }
            else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Num2)) {
                currentColour = sf::Color::Magenta;
            }
            else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Num3)) {
                currentColour = sf::Color::Black;
            }
            else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Num4)) {
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

        window.draw(background);
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
        else if (currentStamp && currentTool == _stamp) {
            window.draw(currentStamp->stampRender());
        }
        //re-get mouse position so the preview doesn't bug

        mouseLocationVectorInt = sf::Mouse::getPosition(window);
        mouseLocationVectorFloat.x = mouseLocationVectorInt.x;
        mouseLocationVectorFloat.y = mouseLocationVectorInt.y;

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

        //draw UI on top
        window.draw(verticalBar);
        window.draw(horizontalBar);
        window.draw(otherVerticalBar);
        window.draw(otherHorizontalBar);

        

        //draw buttons
        for (Button& thisButton : buttons) {
            window.draw(thisButton.buttonRender());
        }
        //the big one
        window.display();
    }
}
