#pragma once

#include <units/acceleration.h>
#include <units/angular_acceleration.h>
#include <units/angular_velocity.h>
#include <units/length.h>
#include <units/velocity.h>


#include <memory>

#include <subsys/interfaces/IChassis.h>
#include <hw/interfaces/IDragonMotorController.h>
#include <hw/usages/IDragonMotorControllerMap.h>

class ChassisFactory
{

		public:
			enum CHASSIS_TYPE
			{
				UNKNOWN_CHASSIS = -1,
				TANK_CHASSIS,
				MECANUM_CHASSIS,
				SWERVE_CHASSIS,
				MAX_CHASSIS_TYPES
			};
			static ChassisFactory* GetChassisFactory();

			IChassis* GetIChassis();

			//=======================================================================================
			// Method:  		CreateChassis
			// Description:		Create a chassis from the inputs
			// Returns:         Void
			//=======================================================================================
			IChassis* CreateChassis
			(
				CHASSIS_TYPE     			        						type,				// <I> - Chassis Type
				units::length::inch_t										wheelDiameter,		// <I> - Diameter of the wheel
			    units::length::inch_t		        						wheelBase,			// <I> - Front-Back distance between wheel centers
				units::length::inch_t		        						track,				// <I> - Left-Right distance between wheels (same axle)
				units::velocity::meters_per_second_t 						maxVelocity,
				units::radians_per_second_t 								maxAngularSpeed,
				units::acceleration::meters_per_second_squared_t 			maxAcceleration,
				units::angular_acceleration::radians_per_second_squared_t 	maxAngularAcceleration,
				const IDragonMotorControllerMap&    						motors 		        // <I> - Motor Controllers
			);

		private:
			std::shared_ptr<IDragonMotorController> GetMotorController
			(
				const IDragonMotorControllerMap&				motorControllers,
				MotorControllerUsage::MOTOR_CONTROLLER_USAGE	usage
			);
			ChassisFactory() = default;
			~ChassisFactory() = default;
			IChassis*        m_chassis;

			static ChassisFactory*	m_chassisFactory;

};
