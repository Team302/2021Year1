// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "Robot.h"

#include <fmt/core.h>
#include <frc/smartdashboard/SmartDashboard.h>
#include <frc/Timer.h>
#include <frc/kinematics/ChassisSpeeds.h>

#include <units/velocity.h>
#include <units/angular_velocity.h>

#include <xmlhw/RobotDefn.h>
#include <subsys/ChassisFactory.h>
#include <gamepad/TeleopControl.h>
#include <subsys/interfaces/IChassis.h>
#include <subsys/MechanismFactory.h>

void Robot::RobotInit() 
{
  // Read the XML file to build the robot 
  auto defn = new RobotDefn();
  defn->ParseXML();

  // Get local copies of the teleop controller and the chassis
  m_controller = TeleopControl::GetInstance();
  auto factory = ChassisFactory::GetChassisFactory();
  m_chassis = factory->GetIChassis();

  m_armStateMgr = ArmStateMgr::GetInstance();
  m_ballReleaseStateMgr = BallReleaseStateMgr::GetInstance();
  m_ballTransferStateMgr = BallTransferStateMgr::GetInstance();
  m_intakeStateMgr = IntakeStateMgr::GetInstance();

  auto mechFactory = MechanismFactory::GetMechanismFactory();
  m_arm = mechFactory->GetArm();
  m_ballRelease = mechFactory->GetBallRelease();
  m_ballTransfer = mechFactory->GetBallTransfer();
  m_intake = mechFactory->GetIntake();
  

  m_timer = new frc::Timer();
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
  m_timer->Reset();
}

void Robot::AutonomousPeriodic() 
{
  if (m_chassis != nullptr)
  {
    frc::ChassisSpeeds speeds;
    speeds.vx = 0_mps;
    speeds.vy = 0_mps;
    speeds.omega = 0_rad_per_s;
    if (m_timer->Get() < 3_s)
    {
      speeds.vx = 1_mps;
    }
    m_chassis->Drive(speeds);
  }
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

    frc::ChassisSpeeds speeds;
    speeds.vx = throttle * m_chassis->GetMaxSpeed();
    speeds.vy = 0_mps; //units::velocity::meters_per_second_t(0)
    speeds.omega = steer * m_chassis->GetMaxAngularSpeed();
    m_chassis->Drive(speeds);
  }

  if (m_intake != nullptr && m_intakeStateMgr != nullptr)
  {
    m_intakeStateMgr->RunCurrentState();
  }

  if (m_ballTransfer != nullptr && m_ballTransferStateMgr != nullptr)
  {
    m_ballTransferStateMgr->RunCurrentState();
  }

  if (m_arm != nullptr && m_armStateMgr != nullptr)
  {
    m_armStateMgr->RunCurrentState();
  }

  if (m_ballRelease != nullptr && m_ballReleaseStateMgr != nullptr )
  {
    m_ballReleaseStateMgr->RunCurrentState();
  }
}

void Robot::DisabledInit() {}

void Robot::DisabledPeriodic() {}

void Robot::TestInit() {}

void Robot::TestPeriodic() 
{

}

#ifndef RUNNING_FRC_TESTS
int main() {
  return frc::StartRobot<Robot>();
}
#endif
