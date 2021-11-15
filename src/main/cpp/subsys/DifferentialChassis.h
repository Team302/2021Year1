#pragma once

#include <subsys/interfaces/IChassis.h>
#include <hw/interfaces/IDragonMotorController.h>
#include <frc/kinematics/DifferentialDriveKinematics.h>
#include <frc/kinematics/DifferentialDriveOdometry.h>
#include <frc/drive/DifferentialDrive.h>

class DifferentialChassis : public IChassis {

    public:
        DifferentialChassis() = delete;
        virtual ~DifferentialChassis() = default;

        DifferentialChassis(IDragonMotorController& leftMotor, 
                        IDragonMotorController& rightMotor,
                        units::meter_t trackWidth,
                        units::velocity::meters_per_second_t maxSpeed,
                        units::angular_velocity::degrees_per_second_t maxAngSpeed,
                        units::length::inch_t wheelDiameter);

        void Drive(frc::ChassisSpeeds chassisSpeeds) override;

        frc::Pose2d GetPose() const override;
        void ResetPose(const frc::Pose2d& pose) override;
        void UpdatePose() override;

        units::length::inch_t GetWheelDiameter() const override ;

        bool IsMoving() const override;

    private:
        IDragonMotorController& m_leftMotor;
        IDragonMotorController& m_rightMotor;
        
        units::velocity::meters_per_second_t m_maxSpeed;
        units::angular_velocity::degrees_per_second_t m_maxAngSpeed;
        units::length::inch_t   m_wheelDiameter;

        frc::DifferentialDriveKinematics*  m_kinematics;
        frc::DifferentialDrive*             m_differentialDrive;
        frc::DifferentialDriveOdometry*     m_differentialOdometry;

};