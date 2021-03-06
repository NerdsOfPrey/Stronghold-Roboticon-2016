// RobotBuilder Version: 2.0
//
// This file was generated by RobotBuilder. It contains sections of
// code that are automatically generated and assigned by robotbuilder.
// These sections will be updated in the future when you export to
// C++ from RobotBuilder. Do not put any code or make any change in
// the blocks indicating autogenerated code or it will be lost on an
// update. Deleting the comments indicating the section will prevent
// it from being updated in the future.




#include "FlipperSub.h"
#include "../RobotMap.h"
// BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=INCLUDES
// END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=INCLUDES

// BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=CONSTANTS

    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=CONSTANTS

FlipperSub::FlipperSub() : Subsystem("FlipperSub") {//the flipper is the part inside the robot that pushes the ball into the launcher
    // BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=DECLARATIONS
    flipperMotor = RobotMap::flipperSubflipperMotor;
    limitFipper = RobotMap::flipperSublimitFipper;

    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=DECLARATIONS
    
    x = 0;

}

void FlipperSub::InitDefaultCommand() {
    // Set the default command for a subsystem here.
    // SetDefaultCommand(new MySpecialCommand());
    // BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=DEFAULT_COMMAND


    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=DEFAULT_COMMAND
}

void FlipperSub::stop(){

	flipperMotor->Set(0.0);
}

void FlipperSub::fipDown(){

	while(limitFipper.get()->Get() == 1){//uses limit switch to stop flipper as it is going down
		flipperMotor->Set(0.2);
	}
	//SmartDashboard::PutNumber("limit", limitFipper.get()->Get());//debug purposes
	flipperMotor->Set(0.0);

}

void FlipperSub::fipUp(){//spelt wrong because

	flipperMotor->Set(-0.2);//-.2

}

void FlipperSub::fipLock(){//used in the lock ball to hold flipper in place against ball so it doesn't fall out

	flipperMotor->Set(-0.6);

}

void FlipperSub::resetTimer(){//used in the autoflipper command to run flipper for a certain time in conjuction with the timeout of the command so the flipper will turn on after the launcher spins up in autonomous, and not as the launcher spins up.

	x = 0;

}
