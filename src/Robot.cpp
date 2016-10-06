// RobotBuilder Version: 2.0
//
// This file was generated by RobotBuilder. It contains sections of
// code that are automatically generated and assigned by robotbuilder.
// These sections will be updated in the future when you export to
// C++ from RobotBuilder. Do not put any code or make any change in
// the blocks indicating autogenerated code or it will be lost on an
// update. Deleting the comments indicating the section will prevent
// it from being updated in the future.


#include "Robot.h"

// BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=INITIALIZATION
std::shared_ptr<DriveTrain> Robot::driveTrain;
std::shared_ptr<FlipperSub> Robot::flipperSub;
std::shared_ptr<Launcher> Robot::launcher;
std::shared_ptr<BoulderIntake> Robot::boulderIntake;
std::unique_ptr<OI> Robot::oi;

    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=INITIALIZATION

void Robot::RobotInit() {

	RobotMap::init();
	// BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=CONSTRUCTORS
    driveTrain.reset(new DriveTrain());
    flipperSub.reset(new FlipperSub());
    launcher.reset(new Launcher());
    boulderIntake.reset(new BoulderIntake());

    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=CONSTRUCTORS
	// This MUST be here. If the OI creates Commands (which it very likely
	// will), constructing it during the construction of CommandBase (from
	// which commands extend), subsystems are not guaranteed to be
	// yet. Thus, their requires() statements may grab null pointers. Bad
	// news. Don't move it.
	oi.reset(new OI());

	// instantiate the command used for the autonomous period
	// BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=AUTONOMOUS

    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=AUTONOMOUS


	datcam = CameraServer::GetInstance();
	datcam->SetQuality(50);
	datcam->StartAutomaticCapture("cam2");//starts capture, video is displayed on custom usb camera plugin on smartdashboard

	choose = new SendableChooser();

	choose->AddDefault("Drive Forward", new AutoDriveOverDefense());//default is to just drive forward
	choose->AddObject("Low Bar", new LowBar());//drive under lowbar, turn, and shoot

	SmartDashboard::PutData("Choose the Autonomous Mode", choose);
	SmartDashboard::PutNumber("Set Launcher Rate", 0.0);//number to maanually set launcher rate instead of using distance calculations.
	SmartDashboard::PutString("Please remember to disable firewall!", "ok");//reminder as we had issues with firewalls
	SmartDashboard::PutString("!", "Please allow 3 seconds for flywheel to stabilize!");//another note for the driver
	SmartDashboard::PutString("Launcher Values:", "470 for goal, 400 for person height");//more notes for programming and drivers
	//SmartDashboard::PutString("Please enter name of driver: (first name lower case)", "default"); //used to have different mappings for each driver, since removed.
}

/**
 * This function is called when the disabled button is hit.
 * You can use it to reset subsystems before shutting down.
 */
void Robot::DisabledInit(){

	SmartDashboard::PutData("Choose the Autonomous Mode", choose);//makes sure the autonomous mode is populated on startup
}

void Robot::DisabledPeriodic() {
	//visionTable = NetworkTable::GetTable("GRIP/report");//constantly gets vision data for debug purposes
	Scheduler::GetInstance()->Run();
}

void Robot::AutonomousInit() {
	//autonomousCommand.release();
	autonomousCommand.reset( (Command *) choose->GetSelected() ); //takes chosen command and sets it to autonomousCommand

	if (autonomousCommand.get() != nullptr)
		autonomousCommand->Start();
}

void Robot::AutonomousPeriodic() {
	Scheduler::GetInstance()->Run();
}

void Robot::TeleopInit() {
	//10.40.65, This makes sure that the autonomous stops running when
	// teleop starts running. If you want the autonomous to
	// continue until interrupted by another command, remove
	// these lines or comment it out.
	//neeed to see whats crashing when oi.reset is called, figure out what happens when using oi.release
	//oi.release();
	//oi.reset(new OI());
	if (autonomousCommand.get() != nullptr)
		autonomousCommand->Cancel();
}

void Robot::TeleopPeriodic() {
	//std::vector<double> centerY = visionTable.get()->GetNumberArray("centerY", 1);//vision was not needed so all vision code was commeneted out
	//std::vector<double> height = visionTable.get()->GetNumberArray("height", 1);
	//std::vector<double> width = visionTable.get()->GetNumberArray("width", 1);

	/*double y = -((2 * (centerY[1] / height[1])) - 1);//had trouble calculating correct distances, tried 2 different equations

	double distanceFromGoal = (RobotMap::TOP_TARGET_HEIGHT_INCHES - RobotMap::CAMERA_HEIGHT_INCHES) / tan(((y*RobotMap::VERTICAL_FOV_DEG/2.0 + RobotMap::CAMERA_PITCH_DEG)*3.14159265359/180.0));
	SmartDashboard::PutNumber("Distance from target", distanceFromGoal);*/

	//SmartDashboard::PutNumber("width0", width[0]);
	//double newDistance = (1.67 * 240) / (2 * width[0]);
	//SmartDashboard::PutNumber("Distance from target", newDistance);

	//SmartDashboard::PutNumber("distance of drive,", Robot::driveTrain.get()->leftEncoder->GetDistance());
	SmartDashboard::PutNumber("Ultrasanic", Robot::launcher.get()->ultrasanicCalculation());//values for debug purposes
	SmartDashboard::PutNumber("limit", Robot::flipperSub.get()->limitFipper.get()->Get());

	if(Robot::launcher.get()->distanceCheck){
		SmartDashboard::PutString("Current Distance Set:", "short distance");
	}else{
		SmartDashboard::PutString("Current Distance Set:", "long distance");
	}

	Scheduler::GetInstance()->Run();
}

void Robot::TestPeriodic() {
	lw->Run();
}

START_ROBOT_CLASS(Robot);

