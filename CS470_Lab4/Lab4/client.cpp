#include "client.h"
#include <math.h>
#include <iostream>
#include <fcntl.h>

using namespace std;

Client::Client(const string& server, const int port, const time_t _timeout)
{
	if (port < 1 || _timeout < 1)
	{
		cout << "[Client]: You supplied invalid arguments in the .ini file." << endl;
		cout << "[Client]: Port and timeout must be positive integers." << endl;
		cout << "[Client]: You supplied port: " << port << " and timeout: " << _timeout << " ms." << endl;
		cout << "[Client]: Exiting." << endl;
		exit(EXIT_FAILURE);
	} // end if
	
	s_IP = server;
	i_port = port;
	t_timeout = _timeout;
	current_task.l_factor = 1;
	
	i_socket = -1;
	
	
	
	for(int i = 0; i < i_TRIES && i_socket == -1; i++)
	{
		i_socket = establishConnection();
		if(i_socket == -1)
		{
			if(i < i_TRIES - 2)
			{
				cout << "[Client]: Connection to server failed. Trying again in " << t_timeout << " ms." << endl;
				sleep(t_timeout);
			} // end if
			else
			{
				cout << "[Client]: Could not connect to server, exiting." << endl;
			} // end else
		} // end if
		else
		{
			break;
		} // end else
	} // end for
	
	/*
	memset(recvBuff, '0',sizeof(recvBuff));
	
	if((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
	{
		cout << "\n Error : Could not create socket \n";
		exit(EXIT_FAILURE);
	} // end if
	
	memset(&serv_addr, '0', sizeof(serv_addr)); 
	
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_port = htons(i_port);
	
	if(inet_pton(AF_INET, s_IP.c_str(), &serv_addr.sin_addr)<=0)
	{
		cout << "\n inet_pton error occured\n";
		exit(EXIT_FAILURE);
	} // end if
	
	for(int i = 0; i < i_TRIES; i++)
	{
		if(i == i_TRIES - 1)
		{
			cout << "[Client]: Unable to connect to server, exiting." << endl;
			exit(EXIT_FAILURE);
		} // end if
		if( connect(sockfd, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0)
		{
			cout << "[Client]: Coult not connect with server, trying again in " << t_timeout << "ms." << endl;
			sleep(t_timeout);
		} // end if
		else
		{
			cout << "[Client]: Connection to server successful" << endl;
			break;
		} // end else
	} // end for
	 * 
	 */
} // end Constructor


Client::~Client(void)
{

}

int Client::establishConnection(void)
{
	int i_socket;
	struct sockaddr_in server_address;
	
	
	if((i_socket = socket(AF_INET, SOCK_STREAM | SOCK_NONBLOCK, 0)) < 0)
	{
		cout << "[Client]: Socket creation failed." << endl;
		exit(EXIT_FAILURE);
	} // end if
	
	memset(&server_address, '0', sizeof(server_address));
	
	server_address.sin_family = AF_INET;
	server_address.sin_port = htons(i_port);
	
	if(inet_pton(AF_INET, s_IP.c_str(), &server_address.sin_addr) <= 0)
	{
		cout << "[Client]: Invalid IP address." << endl;
		return -1;
	} // end if

	if(connect(i_socket, (struct sockaddr *)&server_address, sizeof(server_address)) < 0)
	{
		return -1;
	} // end if
	else
	{
		cout << "[Client]: Successfully connected to server." << endl;
		this->i_socket = i_socket;
		this->server_address = server_address;
		return i_socket;
	} // end else
} // end method 


int Client::run(void)
{
	for(;;)
	{
		try
		{
			getWork();
			
			if(current_task.l_factor == 0)
			{
				cout << "[Client]: Finished, exiting." << endl;
				return 0;
			} // end if
			else
			{
				cout << "[Client]: Received the number " << current_task.l_num
					 << " and the factor "<< current_task.l_factor << endl;
			} // end else
		} // end try
		catch(exception)
		{
			return 1;
		} // end catch
		
		try
		{
			factorNumber();
			
			if (current_result.i_exponent > 0)
			{
				cout << "[Client]: Completed factoring, " << current_task.l_factor << "^" <<  current_result.i_exponent << " is a factor of " << current_task.l_num << endl;
			} // end if
			else
			{
				cout << "[Client]: Completed factoring, " << current_task.l_factor << " is not a factor of " << current_task.l_num  << endl;
			} // end if
		} // end try
		catch(exception)
		{
			return 2;
		} // end catch
		
		try
		{
			sendBackResult();
		} // end try
		catch (exception)
		{
			return 3;
		} // end catch
	} // end for
} // end method run                                        


void Client::getWork(void)
{
	int i_size;
	memset(&recvBuffer, 0, i_BUFFERSIZE);
	
	i_size = read(i_socket, recvBuffer, i_BUFFERSIZE);
	
	cout << "[Client]: Received: " << (unsigned char *)&recvBuffer << endl;
	
	current_task.l_num	  = int((unsigned char)(recvBuffer[0]) << 24 |
								(unsigned char)(recvBuffer[1]) << 16 |
								(unsigned char)(recvBuffer[2]) << 8 |
								(unsigned char)(recvBuffer[3]));
	current_task.l_factor = int((unsigned char)(recvBuffer[4]) << 24 |
								(unsigned char)(recvBuffer[5]) << 16 |
								(unsigned char)(recvBuffer[6]) << 8 |
								(unsigned char)(recvBuffer[7]));
	cout << "[Client]: Received: number " << current_task.l_num << endl
		 << "[Client]: Received: factor " << current_task.l_factor << endl;
	
	/*
	// attempt to connect with server to receive work
	for(int i = 0; i < i_TRIES; i++)
	{
		cout << "[Client]: Ready to start receiving data" << endl;
		while ( (n = read(sockfd, recvBuff, sizeof(recvBuff)-1)) > 0)
		{
			recvBuff[n] = 0;
			cout << "[Client]: Received data: ";
			
			for(int i =0 ; i < 4 || i < n; i++)
			{
				cout << recvBuff[i];
			} // end for
			
			cout << endl;
			cout << "[Client]: Received factor: ";
			
			for(int i = 4; i < n; i++)
			{
				cout << recvBuff[i];
			} // end for
			
			cout << endl;
			cout << "[Client]: Done receiving" << endl;
			
			return;
		} // end while
		
		cout << "[Client]: Sleeping for " << t_timeout << " ms" << endl;
		sleep(t_timeout);
	} // end for
	 */
} // end method getWork

void Client::factorNumber(void)
{
	if (current_task.l_num % current_task.l_factor == 0)
	{
		int i_counter = 0;
		int l_number = current_task.l_num;
		
		while (l_number % current_task.l_factor == 0)
		{
			i_counter++;
			l_number = l_number / current_task.l_factor;
		} // end while
		
		current_result.i_exponent = i_counter;
		current_result.l_factor = current_task.l_factor;
	} // end if
	else
	{
		current_result.i_exponent = 0;
		current_result.l_factor = current_task.l_factor;
	} // end else
} // end method factorNumber

void Client::sendBackResult(void)
{
	memset(&sendBuffer, 0, i_BUFFERSIZE);
	
	std::copy(static_cast<const char*>(static_cast<const void*>(&current_result.l_factor)),
			  static_cast<const char*>(static_cast<const void*>(&current_result.l_factor)) + sizeof(current_result.l_factor),
			  sendBuffer);
	std::copy(static_cast<const char*>(static_cast<const void*>(&current_result.i_exponent)),
			  static_cast<const char*>(static_cast<const void*>(&current_result.i_exponent)) + sizeof(current_result.i_exponent),
			  sendBuffer+4);
	
	send(i_socket, sendBuffer, i_BUFFERSIZE, 0);
	// TODO send result back to server
}

void Client::clientConnect(void)
{
	send(i_socket, "new", sizeof(char)*3, 0);
} // end method clientConnect