#include "stdafx.h"
#include "cmyk.h"

color_space::cmyk::cmyk(float cyan, float magenta, float yellow, float black, float alpha, rgb_color_space_definition* color_space) : color_base(alpha, color_space, 4)
{
	this->m_type = color_type::CMYK;
	this->cyan(cyan);
	this->magenta(magenta);
	this->yellow(yellow);
	this->black(black);
}

color_space::cmyk::cmyk(const color_space::cmyk & other) : color_base(other.alpha(), other.get_rgb_color_space(), 4, other.get_component_max(), other.get_component_min())
{
	this->m_type = other.get_color_type();
	this->m_component_vector = other.get_component_vector();
	this->alpha(other.alpha());
}

color_space::cmyk::cmyk(const color_base & other) : color_base(other.alpha(), other.get_rgb_color_space(), 4, other.get_component_max(), other.get_component_min())
{
	if (other.get_color_type() == color_type::CMYK && other.get_component_vector().size() == 4)
	{
		this->m_type = color_type::CMYK;
		this->m_component_vector = other.get_component_vector();
	}
	else
	{
		throw new std::invalid_argument("CMYK: Error while creating cmyk class from base object. Base object and this derived class have different types.");
	}
}

color_space::cmyk & color_space::cmyk::operator=(const cmyk & other)
{
	if (this != &other)
	{
		this->m_type = other.get_color_type();
		this->m_component_vector = other.get_component_vector();
		this->m_max = other.get_component_max();
		this->m_min = other.get_component_min();
	}
	return *this;
}

float color_space::cmyk::cyan() const
{
	return m_component_vector[0];
}

void color_space::cmyk::cyan(float new_cyan)
{
	set_component(new_cyan, 0);
}

float color_space::cmyk::magenta() const
{
	return m_component_vector[1];
}

void color_space::cmyk::magenta(float new_magenta)
{
	set_component(new_magenta, 1);
}

float color_space::cmyk::yellow() const
{
	return m_component_vector[2];
}

void color_space::cmyk::yellow(float new_yellow)
{
	set_component(new_yellow, 2);
}

float color_space::cmyk::black() const
{
	return m_component_vector[3];
}

void color_space::cmyk::black(float new_black)
{
	set_component(new_black, 3);
}
