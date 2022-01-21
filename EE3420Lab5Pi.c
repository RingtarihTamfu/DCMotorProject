/* Author: Ringtarih Tamfu
 * 
 * Microprocessor Laboratory 3: Raspberry Pi 4 Code
 * 
 * Spring 2021 - EE 3420 - 001
 * 
 * Instructor: William Stapleton
 * 
 * Description: 
 */

//All Libraries used in this program
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <pigpio.h>
#include "ee3420_pi.h"
#include "keypad4x4.h"
#include "character_lcd.h"

//Varisables being used
time_t current_time;
time_t start_time;
time_t desired_duration;
char test_string[]="ONE:TWO:Three:Four:five:sIx:?\n";
char command_string[100];
char command_parameters[max_parameter_limit][max_parameter_length];
int delay = 25000;
int increasedDelay = 26000;
int decreasedDelay = 24000;

void PressedA();
void PressedB();
void PressedC();
void PressedD();
void Pressed0();

int main()
{
	//The ee3420_startup() function from ee3420_pi.h should be the first function called
	if(ee3420_startup() <0)
	{ return(ee3420_shutdown()); }	//if unable to intialize completely, end the program
	
	//demonstrating how a command string is parsed using a sample string
	printf("\nParsing test string into parameters ...\n");
	printf("%s",test_string);
	
	command_parameter_counter=parse_command_string(test_string,command_parameters, parameter_separators);
	
	for(int i=0; i<command_parameter_counter; i++)
	{
		if(command_parameters[i][0]=='\0') {break;}
		printf("%s\n",&command_parameters[i][0]);
	}
	printf("\n");
	
	printf("Standardizing parameters to uppercase\n");
	
	make_command_parameters_uppercase(command_parameters);
		
	for(int i=0; i<command_parameter_counter; i++)
	{
		if(command_parameters[i][0]=='\0') {break;}
		printf("%s\n",&command_parameters[i][0]);
	}
	
	///////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//MAIN CODE
	///////////////////////////////////////////////////////////////////////////////////////////////////////////////
	
	int run = 1;       //variable to keep the loop running
	
	while (run == 1)
	{
		sprintf(command_string, "KEYPAD:?\n");
		printf("Sending request ... %s",command_string);
		serial_send_request(serial_handle, command_string, serial_receive_buffer);
		printf("Response ...\n");
		printf("%s\n",serial_receive_buffer);
	
		//if(process_serial_response(serial_receive_buffer) < 0)
		//{
			//display_serial_device_error(serial_device.last_error_code);
		//}
		
		//This takes the char that was being returned by the command above and you can save it 
		//into a variable of your choice
		parse_command_string(serial_receive_buffer, serial_command_parameters, parameter_separators);
		make_command_parameters_uppercase(serial_command_parameters);
		
		char key = serial_command_parameters[1][0];
		printf("Key is %c\n", key);
		
		gpioDelay(250000);
		
		if (key == 'A')
		{
			PressedA();
		}
		else if (key == 'B')
		{
			PressedB();
		}
		else if (key == 'C')
		{
			PressedC();
		}
		else if (key == 'D')
		{
			PressedD();
		}
		else if (key == '0')
		{
			Pressed0();
		}
	}
	
	return(ee3420_shutdown());
	return 0;
}

void PressedA()
{
	sprintf(command_string, "DCMOTOR:1\n");
	printf("Sending request ... %s",command_string);
	serial_send_request(serial_handle, command_string, serial_receive_buffer);
	printf("Response ...\n");
	printf("%s\n",serial_receive_buffer);
	
	if(process_serial_response(serial_receive_buffer) < 0)
	{
		display_serial_device_error(serial_device.last_error_code);
	}
}

void PressedB()
{
	sprintf(command_string, "DCMOTOR:-1\n");
	printf("Sending request ... %s",command_string);
	serial_send_request(serial_handle, command_string, serial_receive_buffer);
	printf("Response ...\n");
	printf("%s\n",serial_receive_buffer);
	
	if(process_serial_response(serial_receive_buffer) < 0)
	{
		display_serial_device_error(serial_device.last_error_code);
	}
}

void PressedC()
{
	sprintf(command_string, "DCMOTOR:10\n");
	printf("Sending request ... %s",command_string);
	serial_send_request(serial_handle, command_string, serial_receive_buffer);
	printf("Response ...\n");
	printf("%s\n",serial_receive_buffer);
	
	if(process_serial_response(serial_receive_buffer) < 0)
	{
		display_serial_device_error(serial_device.last_error_code);
	}
}

void PressedD()
{
	sprintf(command_string, "DCMOTOR:-10\n");
	printf("Sending request ... %s",command_string);
	serial_send_request(serial_handle, command_string, serial_receive_buffer);
	printf("Response ...\n");
	printf("%s\n",serial_receive_buffer);
	
	if(process_serial_response(serial_receive_buffer) < 0)
	{
		display_serial_device_error(serial_device.last_error_code);
	}
}

void Pressed0()
{
	sprintf(command_string, "DCMOTOR:0\n");
	printf("Sending request ... %s",command_string);
	serial_send_request(serial_handle, command_string, serial_receive_buffer);
	printf("Response ...\n");
	printf("%s\n",serial_receive_buffer);
	
	if(process_serial_response(serial_receive_buffer) < 0)
	{
		display_serial_device_error(serial_device.last_error_code);
	}
}

