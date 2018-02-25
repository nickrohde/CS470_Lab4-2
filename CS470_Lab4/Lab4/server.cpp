#include "server.h"
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <sstream>
#include "baseToDecimal.h"

using namespace std;

Server::Server(const string& IP, const int port, const int iterations)
{
	if (port < 1 || iterations < 1)
	{
		cout << "You supplied invalid arguments in the .ini file." << endl;
		cout << "Port and number of iterations (n) must be positive integers." << endl;
		cout << "You supplied port: " << port << " and iterations: " << iterations << "." << endl;
		cout << "Exiting." << endl;
		exit(EXIT_FAILURE);
	} // end if

	s_IP = IP;
	i_port = port;
	i_iterations = iterations;

	memset(primes, true, sizeof(bool)*SIZE);
	sievePrimes();
	
	if((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0)
	{
		cout << "[Server]: Socket creation failed, exiting." << endl;
		exit(EXIT_FAILURE);
	} // end if
	
	if(setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt)))
	{
		cout << "[Server]: Socket could not be attached to port " << i_port << ", exiting." << endl;
		exit(EXIT_FAILURE);
	} // end if
	
	address.sin_family = AF_INET;
	address.sin_addr.s_addr = INADDR_ANY;
	address.sin_port = htons(i_port);
	
	if(bind(server_fd, (struct sockaddr *)&address, sizeof(address)) < 0)
	{
		cout << "[Server]: Socket could not be attached to port " << i_port << ", exiting, exiting." << endl;
		exit(EXIT_FAILURE);
	} // end if
	
	if(listen(server_fd, 3) < 0)
	{
		cout << "[Server]: Could not listen to socket, exiting." << endl;
		exit(EXIT_FAILURE);
	} // end if
	
	/*
	listenfd = socket(AF_INET, SOCK_STREAM, 0);
	memset(&serv_addr, '0', sizeof(serv_addr));
	memset(sendBuff, '0', sizeof(sendBuff)); 

	serv_addr.sin_family = AF_INET;
	serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
	serv_addr.sin_port = htons(i_port);

    bind(listenfd, (struct sockaddr*)&serv_addr, sizeof(serv_addr));
	
	listen(listenfd, 10);
	*/
} // end Constructor

void Server::generateNumberInBase(const int i_base)
{
	int i_length = 0; // length of number
	
	switch(i_base)
	{
		case 2:
			i_length = 16;
			break;
		case 3:
			i_length = 10;
			break;
		case 4:
			i_length = 8;
			break;
		case 5:
			i_length = 7;
			break;
		case 6:
			i_length = 6;
			break;
		case 7:
		case 8:
		case 9:
		case 10:
			i_length = 5;
			break;
	} // end switch
	
	while(true)
	{
		stringstream number;
		
		// pick a number between 1 and base as leading digit
		number << ((rand()%(i_base-1)) + 1);
		
		for(int i = 1; i < i_length; i++)
		{
			int temp = rand() % i_base;
			number << temp;
		} // end for
		
		string num = number.str();
		
		cout << "[Server]: picked number " << num << " (" << i_base << ")" << endl;
		i_current_number = convertToDecimal(num, i_base);
		cout << "[Server]: picked number " << i_current_number << " (10)" << endl;
		
		if(i_current_number < 100000)
		{
			number << " (";
			number << i_base;
			number << ")";
			s_current_number = number.str();
			break;
		} // end if
		else
		{
			cout << "[Server]: number too large, picking new number ..." << endl;
		} // end else
	} // end while
} // end method generateNumberInBase

int Server::getBase(void)
{
	// lower bound: (9k % 9) + 2 = 0 + 2 = 2
	// upper bound: ((9k + 8) % 9) + 2 = 8 + 2 = 10
	return (rand() % 9) + 2;
}

Server::~Server(void)
{

}

int Server::run(void)
{
	for(int i = 0; i < i_iterations; i++)
	{
		generateNumberInBase(getBase());
		
		if((new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t *)&addrlen)) < 0)
		{
			cout << "[Server]: Could not accept connection, exiting." << endl;
			exit(EXIT_FAILURE);
		} // end if
		
		memset(&recvBuffer, 0, i_BUFFERSIZE);
		
		cout << "[Server]: Waiting to receive message from client." << endl;
		
		valread = read(new_socket, recvBuffer, i_BUFFERSIZE);
		cout << "[Server]: Received the message: " << recvBuffer << endl;
		
		memset(&sendBuffer, 0, i_BUFFERSIZE);
		
		int factor = 2;
		
		cout << "[Server]: Preparing message for sending." << endl;
		
		std::copy(static_cast<const char*>(static_cast<const void*>(&i_current_number)),
				  static_cast<const char*>(static_cast<const void*>(&i_current_number)) + sizeof(i_current_number),
				  sendBuffer);
		std::copy(static_cast<const char*>(static_cast<const void*>(&factor)),
				  static_cast<const char*>(static_cast<const void*>(&factor)) + sizeof(factor),
				  sendBuffer+4);
		
		cout << "[Server]: Ready to send message to client." << endl;
		
		send(new_socket, sendBuffer, i_BUFFERSIZE, 0);
		
		cout << "[Server]: Done sending message to client." << endl;
		/*
		connfd = accept(listenfd, (struct sockaddr*)NULL, NULL); 
		
		int factor = 2;
		
		snprintf(sendBuff, sizeof(sendBuff), "%d", i_current_number);
		write(connfd, sendBuff, strlen(sendBuff));
		snprintf(sendBuff, sizeof(sendBuff), "%d", factor);
		write(connfd, sendBuff, strlen(sendBuff));
		close(connfd);
		sleep(1);
		 * 
		 */ 
	} // end for
	
	return 0;
} // end method run


void Server::sievePrimes(void)
{
	primes[0] = false;
	primes[1] = false;
	primes[2] = true;

	// set all evens to false
	for (int i = 4; i < MAX; i += 2)
	{
		primes[i] = false;
	} // end for

	// set remaining non-primes to false
	for (int i = 3; i < MAX; i+=2)
	{
		if (primes[i])
		{
			for (int j = i * i; j < SIZE; j += i)
			{
				primes[j] = false;
			} // end for
		} // end if
	} // end for
} // end method sievePrimes

void Server::receiveResult(void)
{
	
}