/// Copyright Martin Ruehlicke, 2019
/// Use, modification and distribution are subject to the
/// MIT Software License, Version 1.0.
/// See accompanying file LICENSE.txt

#pragma once
#define _USE_MATH_DEFINES

#include "..\utils\color_type.h"
#include "rgb_color_space_definition.h"

#include <vector>
#include <exception>
#include <math.h>

namespace color_space
{
	//! Base class for all color spaces.
		/*!
		* This class holds the component vector, max and min vales and overrides operators (==, !=, +).
		*/
	class color_base
	{
	public:
		//! Default constructor.
		/*!
		* Sets number of color components as well as the components max and min values.
		* \param color_space The rgb color space definition used for conversion to or from xyz and lab.
		* \param component_count The number of components the color will have.
		* \param component_max The maximum number each component can have (inclusive).
		* \param component_min The minimum number each component can have (inclusive).
		*/
		color_base(float alpha, rgb_color_space_definition* color_space, size_t component_count, float component_max = 1.f, float component_min = 0.f)
		{
			m_alpha = alpha;
			m_rgb_color_space = color_space;
			m_max = component_max;
			m_min = component_min;

			for (size_t i = 0; i < component_count; ++i)
			{
				m_component_vector.push_back(-1);
			}
		}

		//! Default destructor.
		/*!
		* Default destructor.
		*/
		virtual ~color_base()
		{
			m_component_vector.clear();
		}

		//! Returns the color space the color is located in.
		/*!
		* Returns the color space the color is located in.
		*/
		virtual color_type get_color_type() const { return m_type; }

		//! Returns the colors component values.
		/*!
		* Returns the colors component values as float vector.
		*/
		virtual std::vector<float> get_component_vector() const { return m_component_vector; }

		//! Returns one color component by index.
		/*!
		* Returns one color component by index.
		* /param index is the index of the component to return.
		*/
		virtual float get_component(int index) const
		{
			if (index < 0 || index >= m_component_vector.size()) throw new std::out_of_range("Index out of range by accessing color component.");
			return m_component_vector[index];
		}

		//! Setter for a component. 
		/*!
		* Clamps the given value with the local values of this class and adds it to the component vector.
		* \param new_value The value to add to the component vector.
		* \param index The index in the component vector to where the value should be added.
		*/
		void set_component(float new_value, int index) 
		{
			if (index < 0 || index >= m_component_vector.size()) throw new std::out_of_range("Index out of range by setting color component.");
			m_component_vector[index] = clamp(new_value, m_max, m_min); 
		}

		//! Setter for a component. 
		/*!
		* Clamps the given value with the given max and min values and adds it to the component vector.
		* \param new_value The value to add to the component vector.
		* \param index The index in the component vector to where the value should be added.
		* \param max The maximum number for the clamping operation.
		* \param min The minimum number for the clamping operation.
		*/
		void set_component(float new_value, int index, float max, float min) 
		{
			if (index < 0 || index >= m_component_vector.size()) throw new std::out_of_range("Index out of range by setting color component.");
			m_component_vector[index] = clamp(new_value, max, min); 
		}

		//! Returns the maximum value each component can have.
		/*!
		* Returns the maximum value each component can have.
		*/
		virtual float get_component_max() const { return m_max; }

		//! Returns the minimum value each component can have.
		/*!
		* Returns the minimum value each component can have.
		*/
		virtual float get_component_min() const { return m_min; }

		//! Sets a new color space definition.
		/*! Sets a new color space definition used for conversion to or from xyz and lab.
		*/
		virtual void set_rgb_color_space(rgb_color_space_definition* new_color_space) { m_rgb_color_space = new_color_space; }

		//! Returns the currently used color space definition.
		/*! Returns the currently used color space definition that will be used for conversions from or to xyz and lab color space.
		*/
		virtual rgb_color_space_definition* get_rgb_color_space() const { return m_rgb_color_space; }

		//! Returns the currently set alpha.
		/*! Returns the currently set alpha.
		*/
		virtual float alpha() const { return m_alpha; }

		//! Sets a new alpha value (0-1).
		/*! Sets a new alpha value (0-1).
		*/
		virtual void alpha(float new_alpha) { m_alpha = clamp(new_alpha, m_a_max, m_a_min); }

		//! Equality operator overload.
		/*!
		* First both colors types and component vectors sizes are compared. Afterwards the components get compared.
		*/
		friend bool operator==(const color_base& lhs, const color_base& rhs)
		{
			bool precondition = (lhs.get_color_type() == rhs.get_color_type()) && (lhs.m_component_vector.size() == rhs.m_component_vector.size());

			if (!precondition)
			{
				return false;
			}

			for (std::vector<float>::size_type i = 0; i < lhs.m_component_vector.size(); ++i)
			{
				if (lhs.m_component_vector[i] != rhs.m_component_vector[i])
				{
					return false;
				}
			}

			return true;
		}

		//! Not equal operator overload.
		/*!
		* First both colors types and component vectors sizes are compared. Afterwards the components get compared.
		*/
		friend bool operator!=(const color_base& lhs, const color_base& rhs)
		{
			return !(lhs == rhs);
		}

		//! Plus operator overload.
		/*!
		* Simply performs an add operation for each component and clamps them to max/min values.
		*/
		color_base operator+(const color_base& rhs)
		{
			color_base result(this->alpha(), this->get_rgb_color_space(), this->m_component_vector.size(), this->get_component_max(), this->get_component_min());
			if (this->get_color_type() == rhs.get_color_type() && this->m_component_vector.size() == rhs.m_component_vector.size())
			{
				result.m_type = this->m_type;
				for (size_t i = 0; i < this->m_component_vector.size(); ++i)
				{
					result.m_component_vector[i] = clamp(this->m_component_vector[i] + rhs.m_component_vector[i], m_max, m_min);
				}
			}
			else
			{
				throw new std::invalid_argument("Color Base: Error while adding two colors: The colors to add have different types.");
			}
			return result;
		}

		//! Multiplies each component with alpha.
		/*!
		* Multiplies each component with alpha.
		*/
		void alpha_multiply()
		{
			for (size_t i = 0; i < m_component_vector.size(); ++i)
			{
				m_component_vector[i] *= m_alpha;
			}
		}

		//! Divides each component by alpha.
		/*!
		* Divides each component by alpha.
		*/
		void alpha_divide()
		{
			if (m_alpha == 0.f) return;

			for (size_t i = 0; i < m_component_vector.size(); ++i)
			{
				m_component_vector[i] /= m_alpha;
			}
		}

		//! Does the gamma correction for each component of this color.
		/*!
		* linear color to "normal" color.
		*/
		void do_gamma_correction()
		{
			for (size_t i = 0; i < m_component_vector.size(); ++i)
			{
				m_component_vector[i] = clamp(m_rgb_color_space->get_gamma_curve()->gamma_correction(m_component_vector[i]), m_max, m_min);
			}
		}

		//! Does the inverse gamma correction for each component of this color.
		/*!
		* "Normal" color to linear color.
		*/
		void do_inverse_gamma_correction()
		{
			for (size_t i = 0; i < m_component_vector.size(); ++i)
			{
				m_component_vector[i] = clamp(m_rgb_color_space->get_gamma_curve()->inverse_gamma_correction(m_component_vector[i]), m_max, m_min);
			}
		}

	protected:
		//! Clamps a given value between a given max and min value (inclusive).
		/*!
		* Clamps a given value between a given max and min value (inclusive).
		* \param in_value The value to clamp.
		* \param max The maximum value.
		* \param min The minimum value.
		* \return The clamped value.
		*/
		float clamp(float in_value, float max, float min) { return fmaxf(fminf(in_value, max), min); }


		//! Vector that stores the components of the color.
		/*!
		* Vector that stores the components of the color.
		*/
		std::vector<float> m_component_vector;

		//! The rgb color space definition used for conversion to or from xyz and lab.
		/*!
		* The rgb color space definition used for conversion to or from xyz and lab.
		*/
		rgb_color_space_definition* m_rgb_color_space;

		//! Alpha value of the color.
		/*!
		* Alpha value of the color.
		*/
		float m_alpha;

		//! Maximum value (inclusive) alpha can have.
		/*!
		* Maximum value (inclusive) alpha can have.
		*/
		float m_a_max = 1.f;

		//! Minimum value (inclusive) alpha can have.
		/*!
		* Minimum value (inclusive) alpha can have.
		*/
		float m_a_min = 0.f;

		//! Maximum value (inclusive) each component can have.
		/*!
		* Maximum value (inclusive) each component can have.
		*/
		float m_max = 1.f;

		//! Minimum value (inclusive) each component can have.
		/*!
		* Minimum value (inclusive) each component can have.
		*/
		float m_min = 0.f;

		//! The colors color space.
		/*!
		* The colors color space.
		*/
		color_type m_type = color_type::UNDEFINED;
	};
}