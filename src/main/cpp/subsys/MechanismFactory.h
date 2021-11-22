
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

//========================================================================================================
/// MechanismFactory.h
//========================================================================================================
///
/// File Description:
///     This controls the creation of mechanisms/subsystems
///
//========================================================================================================

#pragma once

// C++ Includes
#include <map>
#include <memory>
#include <vector>

// FRC includes

// Team 302 includes
#include <subsys/MechanismTypes.h>
#include <hw/usages/IDragonMotorControllerMap.h>
#include <hw/usages/DigitalInputMap.h>
#include <hw/usages/ServoMap.h>
#include <hw/usages/DragonSolenoidMap.h>
#include <subsys/interfaces/IMech.h>
#include <subsys/Intake.h>
#include <subsys/BallTransfer.h>
#include <subsys/Arm.h>
#include <subsys/BallRelease.h>

// Third Party Includes

// forward declares
class DragonAnalogInput;
class DragonDigitalInput;
class DragonServo;
class DragonSolenoid;
class IDragonMotorController;
class IMech;

namespace ctre
{
	namespace phoenix
	{
		namespace sensors
		{
			class CANCoder;
		}
	}
}


class MechanismFactory
{
	public:

		static MechanismFactory* GetMechanismFactory();


		//=====================================================================================
		/// Method:         GetIMechanism
		/// Description:    Find or create the requested mechanism
		/// Returns:        IMechanism*     pointer to the mechanism or nullptr if mechanism 
		///                                 doesn't exist and cannot be created.
		//=====================================================================================
		IMech* GetIMechanism
		(
			MechanismTypes::MECHANISM_TYPE			type		// <I> - manipulator type
		);

		//=====================================================================================
		/// Method:         CreateIMechanism
		/// Description:    Find or create the requested mechanism
		/// Returns:        IMechanism*     pointer to the mechanism or nullptr if mechanism 
		///                                 doesn't exist and cannot be created.
		//=====================================================================================
		IMech*  CreateIMechanism
		(
			MechanismTypes::MECHANISM_TYPE							type,
			const IDragonMotorControllerMap&        				motorControllers,   // <I> - Motor Controllers
			const DragonSolenoidMap&                				solenoids,
			const ServoMap&						    				servos,
			const DigitalInputMap&									digitalInputs,
			std::shared_ptr<ctre::phoenix::sensors::CANCoder>		canCoder
		);
		inline std::shared_ptr<Intake> GetIntake() const { return m_intake;};
		inline std::shared_ptr<BallTransfer> GetBallTransfer() const { return m_ballTransfer;};
		inline std::shared_ptr<Arm> GetArm() const { return m_arm;};
		inline std::shared_ptr<BallRelease> GetBallRelease() const { return m_ballRelease;};

	private:
		std::shared_ptr<IDragonMotorController> GetMotorController
		(
			const IDragonMotorControllerMap&				motorControllers,
			MotorControllerUsage::MOTOR_CONTROLLER_USAGE	usage
		);
		std::shared_ptr<DragonSolenoid> GetSolenoid
		(
			const DragonSolenoidMap&						solenoids,
			SolenoidUsage::SOLENOID_USAGE					usage
		);
		std::shared_ptr<DragonServo> GetServo
		(
			const ServoMap&									servos,
			ServoUsage::SERVO_USAGE							usage
		);
		std::shared_ptr<DragonDigitalInput> GetDigitalInput
		(
			const DigitalInputMap&							digitaInputs,
			DigitalInputUsage::DIGITAL_SENSOR_USAGE			usage
		);
		/**
		std::shared_ptr<DragonAnalogInput> GetAnalogInput
		(
			const AnalogInputMap&							analogInputs,
			AnalogInputUsage::ANALOG_SENSOR_USAGE			usage
		);
		**/

		MechanismFactory();
		virtual ~MechanismFactory() = default;

		static MechanismFactory*	m_mechanismFactory;

		std::vector<IMech*> m_mechanisms;
		std::shared_ptr<Intake> 		m_intake;
		std::shared_ptr<BallTransfer> 	m_ballTransfer;
		std::shared_ptr<Arm> 			m_arm;
		std::shared_ptr<BallRelease>	m_ballRelease;
};