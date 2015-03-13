// =============================================================================
// File Name: AutoMotionProfile.cpp
// Description: Drives forward
// Author: FRC Team 3512, Spartatroniks
// =============================================================================

#include "../Robot.hpp"

void Robot::AutoMotionProfile() {
    robotDrive->setLeftManual(0.f);
    robotDrive->setRightManual(0.f);
    robotDrive->setLeftSetpoint(0.f);
    robotDrive->setRightSetpoint(0.f);
    robotDrive->resetProfile();

    robotDrive->setControlMode(CANTalon::kPosition);

    BezierCurve curve;
    curve.push_back(std::make_pair(0.0, 0.0));
    curve.push_back(std::make_pair(0.0, 50.0));
    curve.push_back(std::make_pair(0.0, 100.0));
    curve.push_back(std::make_pair(0.0, 150.0));

    robotDrive->resetEncoders();

    autoTimer->Reset();

    // Move robot forward
    robotDrive->setGoal(curve, autoTimer->Get());
    while (IsAutonomous() && IsEnabled() && !robotDrive->atGoal()) {
        DS_PrintOut();

        robotDrive->updateSetpoint(autoTimer->Get());
        robotDrive->setLeftSetpoint(
            robotDrive->BezierTrapezoidProfile::getLeftSetpoint());
        robotDrive->setRightSetpoint(
            robotDrive->BezierTrapezoidProfile::getRightSetpoint());

        Wait(0.01);
    }

    // Stop moving
    robotDrive->setLeftManual(0.f);
    robotDrive->setRightManual(0.f);

    while (IsAutonomous() && IsEnabled()) {
        DS_PrintOut();
        Wait(0.01);
    }
}

