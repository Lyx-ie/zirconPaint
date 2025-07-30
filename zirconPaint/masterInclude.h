//this file just exists to prevent duplicate includes/declarations
//include this file in all other header files


#pragma once
#include <iostream>
#include <cmath>
#include <SFML/Graphics.hpp>
#include <SFML/Main.hpp>
#include <SFML/Config.hpp>
#include <SFML/Window.hpp>


//different types of tools used in several places in the code
enum toolType { _NULL, _line, _freehand, _ellipse, _rectangle, _triangle, _circle, _octagon };

//using the predefined ellipse tool in the documentation/
class ellipseShape : public sf::Shape
{
public:
    explicit ellipseShape(sf::Vector2f radius = { 0, 0 }) : m_radius(radius)
    {
        update();
    }

    void setRadius(sf::Vector2f radius)
    {
        m_radius = radius;
        update();
    }

    sf::Vector2f getRadius() const
    {
        return m_radius;
    }

    std::size_t getPointCount() const override
    {
        return 30;
    }

    sf::Vector2f getPoint(std::size_t index) const override
    {
        static constexpr float pi = 3.141592654f;

        float angle = index * 2 * pi / getPointCount() - pi / 2;
        float x = std::cos(angle) * m_radius.x;
        float y = std::sin(angle) * m_radius.y;

        return m_radius + sf::Vector2f(x, y);
    }

private:
    sf::Vector2f m_radius;
};
#pragma once
