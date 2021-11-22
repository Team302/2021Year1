
/*========================================================================================================
 * LinearProfile.h
 *========================================================================================================
 *
 * File Description:  This applies a linear profile to the input values.
 *
 *========================================================================================================*/

//====================================================================================================================================================
// Copyright 2021 Lake Orion Robotics FIRST Team 302 
//
// Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"),
// to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense,
// and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
// MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM,
// DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE
// OR OTHER DEALINGS IN THE SOFTWARE.
//====================================================================================================================================================

#pragma once

// C++ Includes

// FRC includes

// Team 302 includes
#include <gamepad/axis/IProfile.h>


// Third Party Includes



//==================================================================================
/// <summary>
/// Class:          LinearProfile
/// Description:    This provides profile to be applied to input values.
/// </summary>
//==================================================================================
class LinearProfile : public IProfile
{
    public:

    
        //==================================================================================
        /// <summary>
        /// Method:         GetInstance
        /// Description:    Static singleton method to create the object
        /// Returns:        LinearProfile*  Singleton linear profile object
        /// </summary>
        //==================================================================================
        static LinearProfile* GetInstance();


        //==================================================================================
        /// <summary>
        /// Method:         ApplyProfile
        /// Description:    Apply the profile
        /// </summary>
        //==================================================================================
        double ApplyProfile
        (
            double      inputVal            // <I> - value to apply profile to
        ) const override;

    private:
        LinearProfile() = default;
        ~LinearProfile() = default;

        static LinearProfile*       m_instance;

};

