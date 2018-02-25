#include "runMode.h"
#include <string>

using namespace std;

#ifndef SERVER_H_
#define SERVER_H_

class Server : public RunMode
{
public:
	Server(const string& IP="127.0.0.1", const int port = 1234, const int iterations=10);
	~Server(void);

	int run(void);


private:
	static const int MAX = 316; 
	static const int SIZE = 100000;

	int i_iterations;
	int i_current_number;
	
	string s_current_number;

	bool primes[SIZE];
	
	int listenfd = 0, connfd = 0;
    struct sockaddr_in serv_addr; 

	int server_fd, new_socket, valread;
	struct sockaddr_in address;
	int opt = 1;
	int addrlen = sizeof(address);

	void generateNumberInBase(const int);

	void setupTCPHost(void);
	void sievePrimes(void);
	
	void receiveResult(void);

	int getBase(void);

};



#endif /* SERVER_H_ */
