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
#include <states/arm/ArmStateMgr.h>
#include <xmlmechdata/StateDataDefn.h>
#include <controllers/MechanismTargetData.h>
#include <utils/Logger.h>
#include <gamepad/TeleopControl.h>
#include <states/intake/IntakeState.h>
#include <states/StateMgr.h>
#include <states/StateStruc.h>
#include <subsys/MechanismFactory.h>
#include <subsys/MechanismTypes.h>


// Third Party Includes

using namespace std;


ArmStateMgr* ArmStateMgr::m_instance = nullptr;
ArmStateMgr* ArmStateMgr::GetInstance()
{ 
	if ( ArmStateMgr::m_instance == nullptr )
	{
		ArmStateMgr::m_instance = new ArmStateMgr();
	}
	return ArmStateMgr::m_instance;
}


/// @brief    initialize the state manager, parse the configuration file and create the states.
ArmStateMgr::ArmStateMgr()
{
     map<string, StateStruc> stateMap;
    StateStruc struc;

    struc.id = ARM_STATE::ARMUP;
    struc.isDefault = true;
    struc.type = StateType::ARM;
    stateMap["ARMUP"] = struc;
    
    struc.id = ARM_STATE::ARMDOWN;
    struc.isDefault = false;
    struc.type = StateType::ARM;
    stateMap["ARMDOWN"] = struc;
    
    struc.id = ARM_STATE::ARMHOLDUP;
    struc.isDefault = false;
    struc.type = StateType::ARM;
    stateMap["ARMHOLDUP"] = struc;

    
    struc.id = ARM_STATE::ARMHOLDDOWN;
    struc.isDefault = false;
    struc.type = StateType::ARM;
    stateMap["ARMHOLDDOWN"] = struc;

    Init(MechanismFactory::GetMechanismFactory()->GetArm(), stateMap);
}   


/// @brief  run the current state
/// @return void
void ArmStateMgr::CheckForDriveTeamInput()
{
    if ( MechanismFactory::GetMechanismFactory()->GetArm() != nullptr )
    {
        // process teleop/manual interrupts
        auto currentState = static_cast<ARM_STATE>(GetCurrentState());
    
        auto controller = TeleopControl::GetInstance();
        if ( controller != nullptr )
         {
        //     auto upPressed = controller->IsButtonPressed(TeleopControl::FUNCTION_IDENTIFIER::DOWN);
        //     auto downPressed = controller->IsButtonPressed(TeleopControl::FUNCTION_IDENTIFIER::UP);
        //     if (intakePressed  &&  currentState != arm_state::INTAKE )
        //     {
        //         SetCurrentState( INTAKE_STATE::INTAKE, false );
        //     }
        //     else if (expelPressed && currentState != INTAKE_STATE::EXPEL )
        //     {
        //         SetCurrentState( INTAKE_STATE::EXPEL, false );
        //     }           
        //     else if ((!intakePressed && !expelPressed) && currentState != INTAKE_STATE::OFF )
        //     {
        //         SetCurrentState( arm_state::OFF, false );
        //     }
        }
    
    }

}





