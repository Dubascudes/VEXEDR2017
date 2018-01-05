#pragma config(Motor,  port1,           leftBack,      tmotorVex393_HBridge, openLoop)
#pragma config(Motor,  port2,           leftTop,       tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port3,           rightBack,     tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port4,           mobileLift,    tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port5,           leftScissor,   tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port6,           rightScissor,  tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port7,           arm,           tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port8,           claw,          tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port10,          rightTop,      tmotorVex393_HBridge, openLoop)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

#define FULLPWR 127
#define HALFPWR 63
#define QTRPWR 32


void sideDrive(int drivespd_direction, int time)
{
	//this function drives to the left or the right at a chosen speed
	motor[rightTop] = drivespd_direction;
	motor[leftBack] = -drivespd_direction;
	wait1Msec(time); //1000 miliseconds is 1 second
	stopAllMotors();
}

void sideDriveGoal(int drivespd_direction, int time)
{
	//this function drives to the left or the right at a chosen speed
	motor[rightTop] = drivespd_direction - 48;
	motor[leftBack] = -drivespd_direction;
	wait1Msec(time); //1000 miliseconds is 1 second
	stopAllMotors();
}

void frontDrive(int drivespd_direction, int time)
{
	//this function drives forward of backward at a chosen speed
	motor[rightBack] = drivespd_direction;
	motor[leftTop] = -drivespd_direction;
	wait1Msec(time);
}

void turnNinetyNinety(int drivespd_direction, int time)
{
	motor[rightBack] = drivespd_direction - 10;
	motor[leftBack] = drivespd_direction;
	motor[rightTop] = drivespd_direction - 10;
	motor[leftTop] = drivespd_direction - 10;
	wait1Msec(time);
}

void scissorLift (int spd)
{
	motor[leftScissor] = spd;
	motor[rightScissor] = spd;
	wait1Msec(1000); //still have to find out how long it takes to lift the scissor lift
}

void mobileLiftDrive (int spd, int time)
{
	motor[rightBack] = spd;
	motor[leftTop] = -spd;
	wait1Msec(time);
	int count = 0;
	while (count <1 && motor[leftTop] == -spd && motor[rightBack] == spd)
	{
		motor[mobileLift] = FULLPWR;
		wait1Msec(time);
		count++;
	}
}

task mobileHook ()
{
		//I took the while loops out to test it out without it first. It should work, if not uncomment the while loop
	//while (1)
	//{
		motor[mobileLift] = FULLPWR;
		//wait1Msec(9999); //If it claw doesnt lift and robot doesnt go forward re-instate this line of code for both tasks
	//}
}

task frontDriveOne()
{
	//I took the while loops out to test it out without it first. It should work, if not uncomment the while loop
	//while(1)
	//{
		//frontDrive(HALFPWR, 2990);
	//}

//this function drives forward of backward at a chosen speed
	motor[rightBack] = HALFPWR;
	motor[leftTop] = -HALFPWR;
	//wait1Msec(2990);
}

task main()
{

	//I
	motor [mobileLift] = -FULLPWR;
	wait1Msec(550);

	//Move Robot forward and lift hook at same time.
	startTask(frontDriveOne);
	startTask( mobileHook );
	wait1Msec(1000);

	//Next step in program
	frontDrive(-FULLPWR, 2000);
	sideDriveGoal(FULLPWR, 700);
	startTask( mobileHook );
  turnNinetyNinety(HALFPWR, 500); //TEST TIME
  //sideDrive(FULLPWR, 1000);
  //turnNinetyNinety(-FULLPWR, 250); //should be the same direction turn as one above


	//II
//	frontDrive(-HALFPWR, 4000);
	// move diagonally for abt 2-3 sec
//	sideDrive(HALFPWR, 4000);

}
