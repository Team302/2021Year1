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

#include <string>
#include <vector>
#include <controllers/ControlData.h>

class MechanismTargetData
{
    public:
        enum SOLENOID
        {
            NONE,
            ON,
            OFF
        };
        /// @brief      Create the ControlData object that is used to control mechanisms
        /// @param [in] state - State indentifier
        /// @param [in] controller - controller indentifer
        /// @param [in] target - target value         
        /// @param [in] solenoid value
        /// @param [in] secondTarget - a second target value that can be used for two independent motors

        
        MechanismTargetData
        (
            std::string                                 state,
            std::string                                 controller,
            std::string                                 controller2,
            double                                      target,
            SOLENOID                                    solenoid,
            double                                      secondTarget
        );
        MechanismTargetData() = delete;

        virtual ~MechanismTargetData() = default;

        /// @brief  Retrieve the state indentier string
        /// @return std::string  state identifier
        inline std::string GetStateString() const { return m_state; };

        /// @brief  Retrieve the controller identifier
        /// @return std::string controller indentifier
        inline std::string GetControllerString() const { return m_controller; };

        /// @brief  Retrieve the controller
        /// @return ControlData* controller
        inline ControlData* GetController() const { return m_controlData; };


        /// @brief  Retrieve the controller
        /// @return ControlData* controller
        inline ControlData* GetController2() const { return m_controlData2; };

        /// @brief  Retrieve the target value
        /// @return double - target value
        inline double GetTarget() const { return m_target; };

        /// @brief get the solenoid state
        /// @return SOLENOID state of the solenoid
        SOLENOID GetSolenoidState() const { return m_solenoid; }

        /// @brief  Retrieve the target value
        /// @return double - target value
        inline double GetSecondTarget() const { return m_secondTarget; };

        /// @brief update to include ControlData
        /// @param [in] std::vector<ControlData*> - vector of ControlData Objects
        /// @return void
        void Update( std::vector<ControlData*> data );



 
    private:
        std::string                                 m_state;
        std::string                                 m_controller;
        std::string                                 m_controller2;
        double                                      m_target;
        ControlData*                                m_controlData;
        ControlData*                                m_controlData2;
        SOLENOID                                    m_solenoid;
        double                                      m_secondTarget;
};


