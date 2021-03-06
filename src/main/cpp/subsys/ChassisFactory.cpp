
#include <memory>

#include <units/acceleration.h>
#include <units/angular_acceleration.h>
#include <units/angular_velocity.h>
#include <units/length.h>
#include <units/velocity.h>

#include <subsys/interfaces/IChassis.h>
#include <subsys/DifferentialChassis.h>
#include <subsys/ChassisFactory.h>
#include <hw/interfaces/IDragonMotorController.h>
#include <hw/usages/IDragonMotorControllerMap.h>

#include <utils/Logger.h>

using namespace std;

ChassisFactory* ChassisFactory::m_chassisFactory = nullptr;
ChassisFactory* ChassisFactory::GetChassisFactory()
{
    if ( ChassisFactory::m_chassisFactory == nullptr )
    {
        ChassisFactory::m_chassisFactory = new ChassisFactory();
    }
    return ChassisFactory::m_chassisFactory;
}

IChassis* ChassisFactory::GetIChassis()
{
    return m_chassis;
}

//=======================================================================================
// Method:  		CreateChassis
// Description:		Create a chassis from the inputs
// Returns:         Void
//=======================================================================================
IChassis* ChassisFactory::CreateChassis
(
    ChassisFactory::CHASSIS_TYPE   	                            type,				// <I> - Chassis Type
    units::length::inch_t										wheelDiameter,		// <I> - Diameter of the wheel
    units::length::inch_t		        						wheelBase,			// <I> - Front-Back distance between wheel centers
    units::length::inch_t		        						track,				// <I> - Left-Right distance between wheels (same axle)
    units::velocity::meters_per_second_t 						maxVelocity,
    units::radians_per_second_t 								maxAngularSpeed,
    units::acceleration::meters_per_second_squared_t 			maxAcceleration,
    units::angular_acceleration::radians_per_second_squared_t 	maxAngularAcceleration,
 	const IDragonMotorControllerMap&                            motors 		        // <I> - Motor Controllers
)
{
    switch ( type )
    {
        case ChassisFactory::CHASSIS_TYPE::TANK_CHASSIS:
        {
            auto leftMotor = GetMotorController(motors, MotorControllerUsage::MOTOR_CONTROLLER_USAGE::DIFFERENTIAL_LEFT_MAIN);
            auto rightMotor = GetMotorController(motors, MotorControllerUsage::MOTOR_CONTROLLER_USAGE::DIFFERENTIAL_RIGHT_MAIN);
            m_chassis = new DifferentialChassis(leftMotor,
                                                rightMotor,
                                                track,
                                                maxVelocity,
                                                maxAngularSpeed,
                                                wheelDiameter);

        }
        break;

        case ChassisFactory::CHASSIS_TYPE::MECANUM_CHASSIS:
        {
            // todo plug in mecanum drive
        }
        break;

        case ChassisFactory::CHASSIS_TYPE::SWERVE_CHASSIS:
        {
            // todo plug in swerve drive
        }
        break;

        default:
        break;

    }

    return m_chassis;
}
shared_ptr<IDragonMotorController> ChassisFactory::GetMotorController
(
	const IDragonMotorControllerMap&				motorControllers,
	MotorControllerUsage::MOTOR_CONTROLLER_USAGE	usage
)
{
	shared_ptr<IDragonMotorController> motor;
	auto it = motorControllers.find( usage );
	if ( it != motorControllers.end() )  // found it
	{
		motor = it->second;
	}
	else
	{
		string msg = "motor not found; usage = ";
		msg += to_string( usage );
		Logger::GetLogger()->LogError( string( "ChassisFactory::GetMotorController" ), msg );
	}
	
	if ( motor.get() == nullptr )
	{
		string msg = "motor is nullptr; usage = ";
		msg += to_string( usage );
		Logger::GetLogger()->LogError( string( "ChassisFactory::GetMotorController" ), msg );
	}
	return motor;
}


