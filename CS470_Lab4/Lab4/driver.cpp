#include <stdlib.h>
#include <iostream>
#include "runMode.h"
#include "server.h"
#include "client.h"
#include "IniParser.h"


using namespace std;

const char*  SERVER = "-s";
const char*  CLIENT = "-c";

void printArgError(void);

int main(int argc, char* argv[])
{
	RunMode* mode = NULL;

	bool b_server = false;

	try 
	{
		if (argc < 2)
		{
			cout << "[Driver]: Too few command line arguements supplied." << endl;
			printArgError();
			exit(EXIT_FAILURE);
		} // end if
		if (argc == 2)
		{
			string runMode(argv[1]);

			if (runMode == SERVER)
			{
				cout << "[Driver]: Running in server mode with default settings." << endl;
				b_server = true;
				mode = new Server();
			} // end if
			else if (runMode == CLIENT)
			{
				cout << "[Driver]: Running in client mode with default settings." << endl;
				mode = new Client();
			} // end elif
			else
			{
				cout << "[Driver]: Incorrect mode argument supplied." << endl;
				printArgError();
				exit(EXIT_FAILURE);
			} // end else
		} // end if
		else if (argc == 3)
		{
			IniParser* data = new IniParser(argv[2]);
			
			string s_ip, s_port, s_time, s_n;
			string s_runMode(argv[1]);


			if (!data->isFileGood())
			{
				cout << "[Driver]: File parsing failed, exiting." << endl;
				delete data;
				exit(EXIT_FAILURE);
			} // end if			

			delete data;

			if (s_runMode == SERVER || s_runMode == CLIENT)
			{
				s_ip = (*data)("Connection", "IP");
				s_port = (*data)("Connection", "Port");
				s_time = (*data)("Connection", "Timeout");
				s_n = (*data)("Other", "n");
				cout << "[Driver]: Successfully parsed supplied .ini file. Settings found:" << endl;
				cout << "[Driver]: IP: " << s_ip << endl;
				cout << "[Driver]: Port: " << s_port << endl;
			} // end if
			else
			{
				cout << "[Driver]: Incorrect mode argument supplied." << endl;
				printArgError();
				exit(EXIT_FAILURE);
			} // end else

			if (s_runMode == SERVER)
			{
				cout << "[Driver]: Iterations: " << s_n << endl << endl;
				cout << "[Driver]: Running in server mode with custom settings." << endl;
				b_server = true;
				mode = new Server(s_ip, atoi(s_port.c_str()), atoi(s_n.c_str()));
			} // end if
			else
			{
				cout << "[Driver]: Timeout: " << s_time << endl << endl;
				cout << "[Driver]: Running in client mode with custom settings." << endl;
				mode = new Client(s_ip, atoi(s_port.c_str()), static_cast<time_t>(atoi(s_time.c_str())));
			} // end else
		} // end elif
		else
		{
			cout << "[Driver]: Too many command line arguments supplied." << endl;
			printArgError();
			exit(EXIT_FAILURE);
		} // end else

		int i_exitCode = mode->run();

		switch (i_exitCode)
		{
		case 0:
			cout << "[Driver]: Execution was successfull." << endl;
			break;
		case 1:
			cout << "[Driver]: Client was not able to receive work in the alotted time frame." << endl;
			break;
		case 2:
			cout << "[Driver]: Client was not able to factor the number it received." << endl;
			break;
		case 3:
			cout << "[Driver]: Client was not able to send the result back to the server." << endl;
			break;
		} // end switch
	} // end try
	catch (exception e)
	{
		cout << "[Driver]: An error occurred during execution: " << e.what() << endl;
		printArgError();
		delete mode;
		exit(EXIT_FAILURE);
	} // end catch all

	delete mode;

	return 0;
} // end Main                                                                                               

void printArgError(void)
{
	cout << "[Driver]: You must supply the mode to run in, either a client (-c) or a server (-s)." << endl << endl;
	cout << "[Driver]: To use default settings:" << endl;
	cout << "[Driver]: Example call for Client: ./driver -c" << endl;
	cout << "[Driver]: Example call for Server: ./driver -s" << endl << endl;
	cout << "[Driver]: To use custom settings:" << endl;
	cout << "[Driver]: Example call for Client: ./driver -c Config.ini" << endl;
	cout << "[Driver]: Example call for Server: ./driver -s Config.ini" << endl;
} // end method printArgError
