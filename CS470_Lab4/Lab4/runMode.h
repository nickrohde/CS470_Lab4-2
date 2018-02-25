#include <string>
#include <fstream>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <netdb.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <arpa/inet.h> 
#include <time.h>

using namespace std;

#ifndef TASK_H_
#define TASK_H_

typedef struct 
{
	int l_num;
	int l_factor;
} Task; // end Class Task

#endif

#ifndef RESULT_H_
#define RESULT_H_

typedef struct
{
	int l_factor  ;
	int i_exponent;
} Result; // end Class Result

#endif


#ifndef RUNMODE_H_
#define RUNMODE_H_

class RunMode
{
public:
	virtual ~RunMode(void)
	{

	}
	virtual int run(void) = 0;

protected:
	static const int i_BUFFERSIZE = 8;

	char recvBuffer[i_BUFFERSIZE];
	char sendBuffer[i_BUFFERSIZE];

	int i_port;
	string s_IP;

}; // end Class RunMode

#endif /* RUNMODE_H_ */

