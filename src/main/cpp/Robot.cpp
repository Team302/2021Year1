// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "Robot.h"

#include <fmt/core.h>

#include <xmlhw/RobotDefn.h>
#include <subsys/ChassisFactory.h>
#include <gamepad/TeleopControl.h>
#include <subsys/interfaces/IChassis.h>

void Robot::RobotInit() 
{
  //read the xml file to build the robot
  auto defn = new RobotDefn();
  defn->ParseXML();

  //Get local copies of the teleop controller and thee chassis
  m_controller = TeleopControl::GetInstance();
  auto factory = ChassisFactory::GetChassisFactory();
  m_chassis = factory->GetIChassis();

 
}

/**
 * This function is called every robot packet, no matter the mode. Use
 * this for items like diagnostics that you want ran during disabled,
 * autonomous, teleoperated and test.
 *
 * <p> This runs after the mode specific periodic functions, but before
 * LiveWindow and SmartDashboard integrated updating.
 */
void Robot::RobotPeriodic() 
{
  if (m_chassis != nullptr)
  {
    m_chassis->UpdatePose();
  }
}

/**
 * This autonomous (along with the chooser code above) shows how to select
 * between different autonomous modes using the dashboard. The sendable chooser
 * code works with the Java SmartDashboard. If you prefer the LabVIEW Dashboard,
 * remove all of the chooser code and uncomment the GetString line to get the
 * auto name from the text box below the Gyro.
 *
 * You can add additional auto modes by adding additional comparisons to the
 * if-else structure below with additional strings. If using the SendableChooser
 * make sure to add them to the chooser code above as well.
 */
void Robot::AutonomousInit() 
{
 
}

void Robot::AutonomousPeriodic() 
{

}

void Robot::TeleopInit() 
{

}

void Robot::TeleopPeriodic() 
{
  if (m_chassis != nullptr && m_controller != nullptr)
  {
    auto throttle = m_controller->GetAxisValue(TeleopControl::FUNCTION_IDENTIFIER::ARCADE_THROTTLE);
    auto steer = m_controller->GetAxisValue(TeleopControl::FUNCTION_IDENTIFIER::ARCADE_STEER);


  }
}

void Robot::DisabledInit() {}

void Robot::DisabledPeriodic() {}

void Robot::TestInit() {}

void Robot::TestPeriodic() {}

#ifndef RUNNING_FRC_TESTS
int main() {
  return frc::StartRobot<Robot>();
}
#endif
