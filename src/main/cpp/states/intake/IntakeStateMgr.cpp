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

// C++ Includes
#include <map>
#include <memory>
#include <vector>

// FRC includes
#include <networktables/NetworkTableInstance.h>
#include <networktables/NetworkTable.h>
#include <networktables/NetworkTableEntry.h>

// Team 302 includes
#include <states/IState.h>
#include <states/intake/IntakeStateMgr.h>
#include <xmlmechdata/StateDataDefn.h>
#include <controllers/MechanismTargetData.h>
#include <utils/Logger.h>
#include <gamepad/TeleopControl.h>
#include <states/intake/IntakeState.h>
#include <subsys/MechanismFactory.h>
#include <subsys/MechanismTypes.h>


// Third Party Includes

using namespace std;


IntakeStateMgr* IntakeStateMgr::m_instance = nullptr;
IntakeStateMgr* IntakeStateMgr::GetInstance()
{
	if ( IntakeStateMgr::m_instance == nullptr )
	{
		IntakeStateMgr::m_instance = new IntakeStateMgr();
	}
	return IntakeStateMgr::m_instance;
}


/// @brief    initialize the state manager, parse the configuration file and create the states.
IntakeStateMgr::IntakeStateMgr() : m_currentState(),
                                               m_stateVector(),
                                               m_currentStateEnum(BALL_TRANSFER_STATE::OFF)
{
    // Parse the configuration file 
    auto stateXML = make_unique<StateDataDefn>();
    vector<MechanismTargetData*> targetData = stateXML.get()->ParseXML( MechanismTypes::MECHANISM_TYPE::BALL_TRANSFER );

    // initialize the xml string to state map
    map<string, BALL_TRANSFER_STATE> stateMap;
    stateMap["INTAKEOFF"] = BALL_TRANSFER_STATE::OFF;
    stateMap["INTAKEINTAKE"]  = BALL_TRANSFER_STATE::INTAKE;
    stateMap["INTAKEEXPEL"]  = BALL_TRANSFER_STATE::EXPEL;
    m_stateVector.resize(3);
    // create the states passing the configuration data
    for ( auto td: targetData )
    {
        auto stateString = td->GetStateString();
        auto stateStringToEnumItr = stateMap.find( stateString );
        if ( stateStringToEnumItr != stateMap.end() )
        {
            auto stateEnum = stateStringToEnumItr->second;
            if ( m_stateVector[stateEnum] == nullptr )
            {
                auto controlData = td->GetController();
                auto target = td->GetTarget();
                switch ( stateEnum )
                {
                    case BALL_TRANSFER_STATE::OFF:
                    {   
                        auto thisState = new IntakeState( controlData, target );
                        m_stateVector[stateEnum] = thisState;
                        m_currentState = thisState;
                        m_currentStateEnum = stateEnum;
                        m_currentState->Init();
                    }
                    break;

                    case BALL_TRANSFER_STATE::INTAKE:
                    {   
                        auto thisState = new IntakeState( controlData, target );
                        m_stateVector[stateEnum] = thisState;
                    }
                    break;
                   
                    case BALL_TRANSFER_STATE::EXPEL:
                    {   
                        auto thisState = new IntakeState( controlData, target );
                        m_stateVector[stateEnum] = thisState;
                    }
                    break;
                   
                    default:
                    {
                        Logger::GetLogger()->LogError( string("IntakeStateMgr::IntakeStateMgr"), string("unknown state"));
                    }
                    break;
                }
            }
            else
            {
                Logger::GetLogger()->LogError( string("IntakeStateMgr::IntakeStateMgr"), string("multiple mechanism state info for state"));
            }
        }
        else
        {
            Logger::GetLogger()->LogError( string("IntakeStateMgr::IntakeStateMgr"), string("state not found"));
        }
    }
}

/// @brief  run the current state
/// @return void
void IntakeStateMgr::RunCurrentState()
{
    auto nt = nt::NetworkTableInstance::GetDefault().GetTable(string("Ball Transfer State Manager"));

    if ( MechanismFactory::GetMechanismFactory()->GetIntake() != nullptr )
    {
        // process teleop/manual interrupts
        
        auto controller = TeleopControl::GetInstance();
        if ( controller != nullptr )
        {
            auto intakePressed = controller->IsButtonPressed(TeleopControl::FUNCTION_IDENTIFIER::INTAKE);
            auto expelPressed = controller->IsButtonPressed(TeleopControl::FUNCTION_IDENTIFIER::EXPEL);
            if (intakePressed  &&  m_currentStateEnum != BALL_TRANSFER_STATE::INTAKE )
            {
                SetCurrentState( BALL_TRANSFER_STATE::INTAKE, false );
            }
            else if (expelPressed && m_currentStateEnum != BALL_TRANSFER_STATE::EXPEL )
            {
                SetCurrentState( BALL_TRANSFER_STATE::EXPEL, false );
            }           
            else if ((!intakePressed && !expelPressed) && m_currentStateEnum != BALL_TRANSFER_STATE::OFF )
            {
                SetCurrentState( BALL_TRANSFER_STATE::OFF, false );
            }
            else
            {
                // continue running the current state
            }           
        }

        // run the current state
        if ( m_currentState != nullptr )
        {
            m_currentState->Run();
        }
    }

}

/// @brief  set the current state, initialize it and run it
/// @return void
void IntakeStateMgr::SetCurrentState
(
    BALL_TRANSFER_STATE     stateEnum,
    bool                    run
)
{
    if ( MechanismFactory::GetMechanismFactory()->GetIntake() != nullptr )
    {
        auto state = m_stateVector[stateEnum];
        if ( state != nullptr && state != m_currentState)
        {    
            m_currentState = state;
            m_currentStateEnum = stateEnum;       
            m_currentState->Init();
            
            if ( run )
            {
                m_currentState->Run();
            }
            
        }
    }
}




