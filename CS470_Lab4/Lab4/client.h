#include "runMode.h"
#include <stdlib.h>
#include <string.h>

using namespace std;

#ifndef CLIENT_H_
#define CLIENT_H_

class Client : public RunMode
{
public:
	Client(const string& server = "127.0.0.1", const int port = 1234, const time_t _timeout = 3000);
	~Client(void);

	int run(void);

private:
	time_t t_timeout;
	Task current_task;
	Result current_result;
	const int i_TRIES = 5;
	
	int i_socket,
		i_valRead;
	
	struct sockaddr_in inSocket,
					   server_address;
	
	
	int sockfd = 0, n = 0;

    struct sockaddr_in serv_addr;

	void clientConnect(void);
	void getWork(void);
	void factorNumber(void);
	void sendBackResult(void);
	int establishConnection(void);
};



#endif /* CLIENT_H_ */
