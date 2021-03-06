/// Copyright Martin Ruehlicke, 2019
/// Use, modification and distribution are subject to the
/// MIT Software License, Version 1.0.
/// See accompanying file LICENSE.txt

#pragma once

#include "color_base.h"
#include <string>
#include <vector>

namespace color_space
{
	//! Color space to represents grey true colors.
		/*!
		* This class holds getters and setters for grey value, alpha and various constructors.
		*/
	class grey_truecolor : public color_base
	{
	public:
		//! Default constructor.
		/*!
		* Sets grey and alpha value.
		* \param value The value that will be set for grey value.
		* \param alpha The value that will be set for alpha.
		* \param color_space The rgb color space definition used for conversion to or from xyz and lab.
		*/
		grey_truecolor(float value, float alpha, rgb_color_space_definition* color_space);

		//! Default copy constructor.
		/*!
		* Constructs a grey color from a given one.
		* \param other The grey object to construct this color from.
		*/
		grey_truecolor(const grey_truecolor& other);

		//! Default copy constructor.
		/*!
		* Constructs a grey color from a color_base object.
		* \param other The color_base object to construct this color from.
		*/
		grey_truecolor(const color_base& other);

		//! Assignment operator overload.
		/*!
		* Assigns the components from the right hand object to the corresponding components of the left hand object.
		* \param other The grey_truecolor object to get the component values from.
		*/
		grey_truecolor& operator=(const grey_truecolor& other);

		//! Getter for grey component.
		//! \return The grey component of this color.
		float grey();

		//! Setter for grey component.
		//! \param new_grey The grey value to set.
		void grey(float new_grey);

		//! Returns the currently set alpha.
		/*! Returns the currently set alpha.
		*/
		float alpha() const override;

		//! Sets a new alpha value (0-1).
		/*! Sets a new alpha value (0-1).
		*/
		void alpha(float new_alpha) override;

	private:

	};
}