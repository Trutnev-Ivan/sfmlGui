#include <map>
#include "figure.h"

Figure::~Figure()
{
	delete this->fillColor;
	delete this->outlineColor;
    delete this->coords;
}

void Figure::setWidth(int width)
{
	this->width = width;
}

void Figure::setHeight(int height)
{
	this->height = height;
}

void Figure::setOutlineWidth(int width)
{
	this->outlineWidth = width;
}

int Figure::getWidth()
{
	return this->width;
}

int Figure::getHeight()
{
	return this->height;
}

int Figure::getOutlineWidth()
{
	return this->outlineWidth;
}

void Figure::setFillColor(sf::Color color)
{
	this->fillColor = new sf::Color(color.r, color.g, color.b, color.a);
}

void Figure::setFillColor(sf::Color* color)
{
    this->fillColor = color;
}

sf::Color* Figure::getFillColor()
{
	return this->fillColor;
}

void Figure::setOutlineColor(sf::Color* color)
{
	this->outlineColor = color;
}

void Figure::setOutlineColor(sf::Color color)
{
    this->outlineColor = new sf::Color(color.r, color.g, color.b, color.a);
}

sf::Color* Figure::getOutlineColor()
{
	return this->outlineColor;
}

void Figure::setX(float x)
{
    this->coords->x = x;
}

void Figure::setY(float y)
{
    this->coords->y = y;
}

void Figure::setCoords(float x, float y)
{
    this->setX(x);
    this->setY(y);
}

void Figure::setCoords(sf::Vector2f coords)
{
    this->setX(coords.x);
    this->setY(coords.y);
}

void Figure::setCoords(float* coords)
{
    this->setX(coords[0]);
    this->setY(coords[1]);
}

float Figure::getX()
{
    return this->coords->x;
}

float Figure::getY()
{
    return this->coords->y;
}

sf::Vector2f* Figure::getCoords()
{
    return this->coords;
}

void Figure::draw(sf::RenderWindow& window)
{
    float precision = 0.02f;

	std::map<std::string, float>  m{ 
        { "PRECISION",precision },
		{"a", this->width},
		{"b", this->height},
		{"n", 20} 
    }; // TODO: в параметр

	std::vector<float*> coords = SuperEllipse::execute(m);
    sf::VertexArray superEllipse(sf::PrimitiveType::Lines);

    float x0 = 0;
    float x0minus = 0;
    float x1 = 0;
    float x1minus = 0;
    float y0 = 0;
    float y0minus = 0;
    float y1 = 0;
    float y1minus = 0;

    for (int i = 0; i < coords.size() - 1; ++i)
    {
        x0 = coords[i][0];
        x1 = coords[i + 1][0];
        y0 = coords[i][1];
        y1 = coords[i + 1][1];

        x0minus = -x0 / float(window.getSize().x) * this->width + this->coords->x;
        x1minus = -x1 / float(window.getSize().x) * this->width + this->coords->x;
        x0 = x0 / float(window.getSize().x) * this->width + this->coords->x;
        x1 = x1 / float(window.getSize().x) * this->width + this->coords->x;
        
        y0minus = -y0 / float(window.getSize().y) * this->height + this->coords->y;
        y1minus = -y1 / float(window.getSize().y) * this->height + this->coords->y;
        y0 = y0 / float(window.getSize().y) * this->height + this->coords->y;
        y1 = y1 / float(window.getSize().y) * this->height + this->coords->y;

        /* ¬нутренн€€ область */
        for (float y = y0minus; y < y1; y += precision)
        {
            superEllipse.append(
                sf::Vertex(
                    sf::Vector2f(x0minus, y),
                    *(this->fillColor)
                )
            );
            superEllipse.append(
                sf::Vertex(
                    sf::Vector2f(x1, y),
                    *(this->fillColor)
                )
            );

            superEllipse.append(
                sf::Vertex(
                    sf::Vector2f(x0, y),
                    *(this->fillColor)
                )
            );
            superEllipse.append(
                sf::Vertex(
                    sf::Vector2f(x1minus, y),
                    *(this->fillColor)
                )
            );
        }

        /* √раницы / Borders */
        for (float width = 0; width < this->outlineWidth; width += precision)
        {
            superEllipse.append(
                sf::Vertex(
                    sf::Vector2f(x0 + width, y0 + width),
                    *(this->outlineColor)
                )
            );
            superEllipse.append(
                sf::Vertex(
                    sf::Vector2f(x1 + width, y1 + width),
                    *(this->outlineColor)
                )
            );

            superEllipse.append(
                sf::Vertex(
                    sf::Vector2f(x0 + width, y0minus - width),
                    *(this->outlineColor)
                )
            );
            superEllipse.append(
                sf::Vertex(
                    sf::Vector2f(x1 + width, y1minus - width),
                    *(this->outlineColor)
                )
            );

            superEllipse.append(
                sf::Vertex(
                    sf::Vector2f(x0minus - width, y0 + width),
                    *(this->outlineColor)
                )
            );
            superEllipse.append(
                sf::Vertex(
                    sf::Vector2f(x1minus - width, y1 + width),
                    *(this->outlineColor)
                )
            );

            superEllipse.append(
                sf::Vertex(
                    sf::Vector2f(x0minus - width, y0minus - width),
                    *(this->outlineColor)
                )
            );
            superEllipse.append(
                sf::Vertex(
                    sf::Vector2f(x1minus - width, y1minus - width),
                    *(this->outlineColor)
                )
            );
        }
    }

    float botX0 = coords[coords.size() - 1][0] / float(window.getSize().x) * this->width + this->coords->x;
    float botX1 = -coords[coords.size() - 1][0] / float(window.getSize().x) * this->width + this->coords->x;
    float botY0 = coords[coords.size() - 1][1] / float(window.getSize().y) * this->height + this->coords->y;
    float botY1 = coords[coords.size() - 1][1] / float(window.getSize().y) * this->height + this->coords->y;

    float topX0 = coords[coords.size() - 1][0] / float(window.getSize().x) * this->width + this->coords->x;
    float topX1 = -coords[coords.size() - 1][0] / float(window.getSize().x) * this->width + this->coords->x;
    float topY0 = -coords[coords.size() - 1][1] / float(window.getSize().y) * this->height + this->coords->y;
    float topY1 = -coords[coords.size() - 1][1] / float(window.getSize().y) * this->height + this->coords->y;

    float rightX0 = coords[0][0] / float(window.getSize().x) * this->width + this->coords->x;
    float rightX1 = coords[1][0] / float(window.getSize().x) * this->width + this->coords->x;
    float rightY0 = coords[0][1] / float(window.getSize().y) * this->height + this->coords->y;
    float rightY11 = coords[1][1] / float(window.getSize().y) * this->height + this->coords->y;
    float rightY12 = -coords[1][1] / float(window.getSize().y) * this->height + this->coords->y;

    float leftX0 = -coords[0][0] / float(window.getSize().x) * this->width + this->coords->x;
    float leftX1 = -coords[1][0] / float(window.getSize().x) * this->width + this->coords->x;
    float leftY0 = coords[0][1] / float(window.getSize().y) * this->height + this->coords->y;
    float leftY11 = coords[1][1] / float(window.getSize().y) * this->height + this->coords->y;
    float leftY12 = -coords[1][1] / float(window.getSize().y) * this->height + this->coords->y;

    /* √раницы / Borders 
    * ќстаютс€ дырки сверху-снизу-слева-справа
    */

    for (float width = 0; width < this->outlineWidth; width += precision)
    {
        /*Bot*/
        superEllipse.append(
            sf::Vertex(
                sf::Vector2f(botX0 + width, botY0 + width),
                *(this->outlineColor)
            )
        );
        superEllipse.append(
            sf::Vertex(
                sf::Vector2f(botX1 - width, botY1 + width),
                *(this->outlineColor)
            )
        );

        /*Top*/
        superEllipse.append(
            sf::Vertex(
                sf::Vector2f(topX0 + width, topY0 - width),
                *(this->outlineColor)
            )
        );
        superEllipse.append(
            sf::Vertex(
                sf::Vector2f(topX1 - width, topY1 - width),
                *(this->outlineColor)
            )
        );

        /*Right*/

        superEllipse.append(
            sf::Vertex(
                sf::Vector2f(rightX0 + width, rightY0 - width),
                *(this->outlineColor)
            )
        );
        superEllipse.append(
            sf::Vertex(
                sf::Vector2f(rightX1 + width, rightY11 + width),
                *(this->outlineColor)
            )
        );

        superEllipse.append(
            sf::Vertex(
                sf::Vector2f(rightX0 + width, rightY0 + width),
                *(this->outlineColor)
            )
        );
        superEllipse.append(
            sf::Vertex(
                sf::Vector2f(rightX1 + width, rightY12),
                *(this->outlineColor)
            )
        );

        /*Left*/

        superEllipse.append(
            sf::Vertex(
                sf::Vector2f(leftX0 - width, leftY0 - width),
                *(this->outlineColor)
            )
        );
        superEllipse.append(
            sf::Vertex(
                sf::Vector2f(leftX1 - width, leftY11 + width),
                *(this->outlineColor)
            )
        );

        superEllipse.append(
            sf::Vertex(
                sf::Vector2f(leftX0 - width, leftY0 + width),
                *(this->outlineColor)
            )
        );
        superEllipse.append(
            sf::Vertex(
                sf::Vector2f(leftX1 - width, leftY12),
                *(this->outlineColor)
            )
        );
    }

    window.draw(superEllipse);
}