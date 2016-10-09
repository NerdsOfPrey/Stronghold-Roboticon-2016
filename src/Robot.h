// RobotBuilder Version: 2.0
//
// This file was generated by RobotBuilder. It contains sections of
// code that are automatically generated and assigned by robotbuilder.
// These sections will be updated in the future when you export to
// C++ from RobotBuilder. Do not put any code or make any change in
// the blocks indicating autogenerated code or it will be lost on an
// update. Deleting the comments indicating the section will prevent
// it from being updated in the future.


#ifndef _ROBOT_H
#define _ROBOT_H

#include "WPILib.h"
#include "Commands/Command.h"
#include "RobotMap.h"
#include "LiveWindow/LiveWindow.h"
#include <cmath>
// BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=INCLUDES
#include "Commands/AutonomousCommands/AutoDriveOverDefense.h"
#include "Commands/AutonomousCommands/LowBar.h"
#include "Subsystems/BoulderIntake.h"
#include "Subsystems/DriveTrain.h"
#include "Subsystems/FlipperSub.h"
#include "Subsystems/Launcher.h"


    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=INCLUDES
#include "OI.h"


class Robot : public IterativeRobot {
public:
	std::unique_ptr<Command> autonomousCommand;
	static std::unique_ptr<OI> oi;
	LiveWindow *lw = LiveWindow::GetInstance();
	CameraServer* datcam; //usb camera on roboRio
	SendableChooser* choose; //chooser that is populated to smartdashboard to choose autonomous mode.
	std::shared_ptr<NetworkTable> visionTable; //table that populates from vision software on a co-processor

	// BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=DECLARATIONS
    static std::shared_ptr<DriveTrain> driveTrain;
    static std::shared_ptr<FlipperSub> flipperSub;
    static std::shared_ptr<Launcher> launcher;
    static std::shared_ptr<BoulderIntake> boulderIntake;

    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=DECLARATIONS
	virtual void RobotInit();
	virtual void DisabledInit();
	virtual void DisabledPeriodic();
	virtual void AutonomousInit();
	virtual void AutonomousPeriodic();
	virtual void TeleopInit();
	virtual void TeleopPeriodic();
	virtual void TestPeriodic();
};
#endif
