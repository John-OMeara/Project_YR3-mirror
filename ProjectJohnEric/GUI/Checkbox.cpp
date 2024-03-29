#include "Checkbox.h"

/// <summary>
/// Checkbox constructor
/// </summary>
/// <param name="parent"></param>
Checkbox::Checkbox( sf::Font & font, Widget * parent = nullptr) :
	Button(font, parent)
{
	//std::cout << "Checkbox created" << std::endl;
	//m_selectedColor = sf::Color::Blue; //Sets highlight colour of checkbox box
	//m_unselectedColor = sf::Color::Black; //Sets default colour of checkbox box
	m_label = new Label( font, this); //Initialise label with pointer to widget(Checkbox)
	m_label->setSize(30); //Sets character size of label text
	m_on = false;
	m_translucent = sf::Color(0, 0, 0, 0);	//Off color for the checkbox
	m_tickRect.setFillColor(m_translucent);	//Sets the tick to be off in color
	m_boxRect.setOutlineColor(m_outlineColor);
	m_type = typeid(Checkbox).name();
}

/// <summary>
/// Deconstructor
/// </summary>
Checkbox::~Checkbox()
{
	std::cout << "Checkbox destroyed" << std::endl;
}

/// <summary>
/// Update variables here
/// </summary>
void Checkbox::update()
{
	if (m_hasFocus)
	{
		m_boxRect.setOutlineThickness(5);
		m_boxRect.setOutlineColor(m_selectedColor);
		m_label->setColour(m_selectedColor);
	}
	else
	{
		m_boxRect.setOutlineColor(m_unselectedColor);
		m_label->setColour(m_unselectedColor);
	}
}

/// <summary>
/// Updates sf::Shapes in checkbox
/// objects
/// </summary>
void Checkbox::updateShape()
{
	sf::FloatRect labelSize = m_label->getSize();
	//int width = 0, height = 0;
	//if (labelSize.width > m_boxRect.getLocalBounds().width)
	//{
	//	width = labelSize.width + 2;
	//}
	//if (labelSize.height > m_boxRect.getLocalBounds().height)
	//{
	//	height = labelSize.height + 2;
	//}
	//if (width != 0 && height != 0)
	//{
	//	setSize(width, height);
	//}
	//else if (width != 0)
	//{
	//	setSize(width, m_boxRect.getLocalBounds().height);
	//}
	//else if (height != 0)
	//{
	//	setSize(m_boxRect.getLocalBounds().width, height);
	//}
	setSize(labelSize.height, labelSize.height);
}

/// <summary>
/// Process Xbox controller input for checkbox objects
/// </summary>
/// <param name="controller"></param>
void Checkbox::processInput(Xbox360Controller & controller)
{
	Widget::processInput(controller);
	if ((controller.m_currentState.buttonCross && !controller.m_previousState.buttonCross) ||
		KeyboardHandler::GetInstance()->KeyPressed(sf::Keyboard::Return))
	{
		m_on = !m_on;
		if (m_on) {
			m_tickRect.setFillColor(m_fillColor);
			if (m_soundsActive)
				m_clickSound.play();
		}
		else {
			m_tickRect.setFillColor(m_translucent);
			if (m_soundsActive)
				m_clickSound.play();
		}
	}
}
void Checkbox::setColors(sf::Color selectedColor, sf::Color unselectedColor, sf::Color fillColor, sf::Color outlineColor)
{
	m_selectedColor = selectedColor;
	m_unselectedColor = unselectedColor;
	m_fillColor = fillColor;
	m_outlineColor = outlineColor;

	//m_boxRect.setFillColor(fillColor);
	m_boxRect.setOutlineColor(outlineColor);
	m_tickRect.setFillColor(m_translucent);
	//m_tickRect.setOutlineColor(outlineColor);
	m_label->setColors(selectedColor, unselectedColor, fillColor, outlineColor);
}
/// <summary>
/// Draws checkbox objects here
/// </summary>
/// <param name="target"></param>
/// <param name="states"></param>
void Checkbox::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	target.draw(m_boxRect, states); //Draws outer checkbox rectangle
	target.draw(m_tickRect, states);	//Draws the tick if it is selected
	m_label->draw(target, states); //Calls label draw function
}

/// <summary>
/// Sets size of checkbox rectangles
/// </summary>
/// <param name="width"></param>
/// <param name="height"></param>
void Checkbox::setSize(int width, int height)
{
	m_boxRect.setSize(sf::Vector2f(width, height));
	m_tickRect.setSize(sf::Vector2f(width - m_boxRect.getOutlineThickness(), height - m_boxRect.getOutlineThickness()));
}

/// <summary>
/// Sets position of checkbox rectangles
/// </summary>
/// <param name="pos"></param>
void Checkbox::setPosition(sf::Vector2f pos)
{
	m_boxRect.setPosition(pos);
	m_tickRect.setPosition(pos + sf::Vector2f(m_boxRect.getOutlineThickness(), m_boxRect.getOutlineThickness()));
	m_label->setPosition(sf::Vector2f(pos.x + m_boxRect.getLocalBounds().width + 1, pos.y));
}

/// <summary>
/// Sets colour of checkbox rectangles
/// </summary>
/// <param name="c"></param>
void Checkbox::setColour(sf::Color c)
{
	m_tickRect.setFillColor(c);
}

/// <summary>
/// Sets text of checkbox label
/// </summary>
/// <param name="s"></param>
void Checkbox::setLabel(sf::String s)
{
	m_label->setString(s);
}