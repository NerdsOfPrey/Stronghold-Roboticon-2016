	// RobotBuilder Version: 2.0
//
// This file was generated by RobotBuilder. It contains sections of
// code that are automatically generated and assigned by robotbuilder.
// These sections will be updated in the future when you export to
// C++ from RobotBuilder. Do not put any code or make any change in
// the blocks indicating autogenerated code or it will be lost on an
// update. Deleting the comments indicating the section will prevent
// it from being updated in the future.




#include "DriveTrain.h"
#include "../RobotMap.h"
// BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=INCLUDES
#include "../Commands/TankDrive.h"
// END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=INCLUDES

// BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=CONSTANTS

    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=CONSTANTS

DriveTrain::DriveTrain() : Subsystem("DriveTrain") {
    // BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=DECLARATIONS
    frontLeft = RobotMap::driveTrainfrontLeft;
    frontRight = RobotMap::driveTrainfrontRight;
    rearLeft = RobotMap::driveTrainrearLeft;
    rearRight = RobotMap::driveTrainrearRight;
    robotDrive41 = RobotMap::driveTrainRobotDrive41;
    spoopyGyro = RobotMap::driveTrainspoopyGyro;
    rightEncoder = RobotMap::driveTrainRightEncoder;

    left = 0;
    right = 0;
  //  leftEncoder = RobotMap::driveTrainLeftEncoder; //left encoder broke, so its not being used right now

    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=DECLARATIONS
}

void DriveTrain::InitDefaultCommand() {
    // Set the default command for a subsystem here.
    // SetDefaultCommand(new MySpecialCommand());
    // BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=DEFAULT_COMMAND

        SetDefaultCommand(new TankDrive()); //makes sure tankdrive command is always running to allow driving of the robot

    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=DEFAULT_COMMAND
}

void DriveTrain::JoyDrive(std::shared_ptr<Joystick> ps3Controller){
		//ps3 drive:
		left = ps3Controller->GetRawAxis(1);
		right = ps3Controller->GetRawAxis(5);
		if(fabs(left) >= 0.1 || fabs(right) >= 0.1){ //takes absolute value to make calculations easier.
					left = -1 * ps3Controller->GetRawAxis(1);
					right = ps3Controller->GetRawAxis(5);

						frontLeft->Set(left);//sets motors to values of joysticks
						rearLeft->Set(left);
						frontRight->Set(right);
						rearRight->Set(right);

					}

}

void DriveTrain::AutoDrive(){//uses encoders for distance drive, easier to use time however
	double rightDis = rightEncoder->GetDistance();
	double leftDis = leftEncoder->GetDistance();
	SmartDashboard::PutNumber("Right Encoder Distance", rightDis); //for debugging purposes
	SmartDashboard::PutNumber("Left Encoder Distance", leftDis);
	if(rightDis < 100){//need to see how many counts is one foot
		double angle = spoopyGyro->GetAngle();
		robotDrive41->Drive(-0.9, -angle * 0.03);
		Wait (0.004); //drive using gyro. kp is a set variable that needs to be 0.03. might need further testing to change this value to make sure robot drive straight.
	}else{//may need to use encoders to drive instead of gyro due to sway of robot.
		robotDrive41->Drive(0.0, 0.0);//might not be able to use encoders due to defenses.
	}
}

void DriveTrain::Stop(){

	frontLeft->Set(0.0);
	rearLeft->Set(0.0);
	frontRight->Set(0.0);
	rearRight->Set(0.0);
}

void DriveTrain::ForwardDrive(){
		frontLeft->Set(1.0);
		rearLeft->Set(1.0);
		frontRight->Set(-1.0);
		rearRight->Set(-1.0);
}

void DriveTrain::Turn(){

		frontLeft->Set(0.3);
		rearLeft->Set(0.3);
		frontRight->Set(0.3);
		rearRight->Set(0.3);
}
