#include "mindsensors-motormux.h"
#include "PC_FileIO.c"

/*
Side and corresponding motors
WHITE_SIDE = motorA;
YELLOW_SIDE = mmotor_S3_1;
GREEN_SIDE = motorD;
RED_SIDE = mmotor_S4_1;
BLUE_SIDE = motorB;
ORANGE_SIDE = motorC;
*/

// Declaring Constants
const int MOTPOWER = 45;
const int MUXPOWER = 40;
const int MUXANGLE = 80;
const int WAITTIME = 1200;

//Jacob to initialize motor mux
void configure_sensors()
{
	SensorType[S3] = sensorI2CCustom;
	SensorType[S4] = sensorI2CCustom;
	MSMMUXinit();
	wait1Msec(200);
}

//Makis
void muxmove(tMUXmotor move_instruction)
{
	MSMMotorEncoderReset(move_instruction);
	MSMMotor(move_instruction, -1*MUXPOWER);
	while (abs(MSMMotorEncoder(move_instruction)) < MUXANGLE)
	{}
	MSMotorStop(move_instruction);
	wait1Msec(WAITTIME);
}

//Makis
void move(tMotor move_instruction)
{
	nMotorEncoder[move_instruction] = 0;
	motor[move_instruction] = -1*MOTPOWER;
	while (abs(nMotorEncoder[move_instruction]) < 90)
	{}
	motor[move_instruction] = 0;
	wait1Msec(WAITTIME);
}

//Makis
void prime_move(tMotor move_instruction)
{
	nMotorEncoder[move_instruction] = 0;
	motor[move_instruction] = MOTPOWER;
	while (abs(nMotorEncoder[move_instruction]) < 90)
	{}
	motor[move_instruction] = 0;
	wait1Msec(WAITTIME);
}

//Makis
void muxprime_move(tMUXmotor move_instruction)
{
	MSMMotorEncoderReset(move_instruction);
	MSMMotor(move_instruction, MUXPOWER);
	while (abs(MSMMotorEncoder(move_instruction)) < MUXANGLE)
	{}
	MSMotorStop(move_instruction);
	wait1Msec(WAITTIME);
}

//Makis
void display_solution(string solution)
{
	displayString(2, "     I am Better Than U");
	displayString(3, "       The solution is");
	displayString(4, "   %s", solution);
}

// Ivan
void button_press(int time)
{
	// If the button is pressend and released within a certain time then it will automatically start the solve
	time1[T2] = 0;
	while((!getButtonPress(buttonEnter)) && (time1[T2] < time))
	{}
	while((getButtonPress(buttonEnter)) && (time1[T2] < time))
	{}
}

task main()
{
	configure_sensors();

	//open file
	TFileHandle fin;
	bool fileOkay = openReadPC(fin,"moves.txt");
	if (fileOkay == 0)
	{
		displayString (3, "The file did not open");
		wait1Msec(5000);
		stopAllTasks();
	}

	// declaring instructions
	char move_instruction = ' ';
	int Move_Counter = 0;
	char solution[200];

	// initialize the char array, assume length of solution is less than 500 moves
	for (int index = 0; index < 200; index ++)
	{
		solution[index] = '*';
	}

	// reading in from the file
	while (readCharPC(fin, move_instruction) && move_instruction != '*')
	{
      solution[Move_Counter] = move_instruction;
      Move_Counter ++;
  }

	// make solution into a string
	string strsolution = " ";
	for (int index = 0; index < Move_Counter; index ++)
	{
		strsolution += solution[index];
	}

	// Display the moves to solve the cube
	display_solution(strsolution);

	// The solving is started by the push of a the enter button.
	button_press(10000);

	// Start timer
	time1[T1] = 0;

	// loop over the solution string taking the index of the string to find the move instruction
	for (int count = 0; (count < Move_Counter) && (SensorValue(S1) == 0); count++)
	{
		if (solution[count] == 'F')
		{
			move(motorD);
		}
		else if (solution[count] == 'A')
		{
			prime_move(motorD);
		}
		else if (solution[count] == 'U')
		{
			muxmove(mmotor_S3_1);
		}
		else if (solution[count] == 'C')
		{
			muxprime_move(mmotor_S3_1);
		}
		else if (solution[count] == 'D')
		{
			move(motorA);
		}
		else if (solution[count] == 'E')
		{
			prime_move(motorA);
		}
		else if (solution[count] == 'R')
		{
			move(motorC);
		}
		else if (solution[count] == 'G')
		{
			prime_move(motorC);
		}
		else if (solution[count] == 'L')
		{
			muxmove(mmotor_S4_1);
		}
		else if (solution[count] == 'H')
		{
			muxprime_move(mmotor_S4_1);
		}
		else if (solution[count] == 'B')
		{
			move(motorB);
		}
		else if (solution[count] == 'I')
		{
			prime_move(motorB);
		}
	}

	// set variable for time
	int time = time1[T1];

	//display time to solve, shutdown procedure
	displayString(6, "The cube has been solved in ");
	displayString(7, "%d ms", time);
	displayString(8, "The cube was solved %d moves ", Move_Counter);
	button_press(30000);

	//close file
	closeFilePC(fin);

	stopAllTasks();
}
