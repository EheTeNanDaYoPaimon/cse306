#include <unistd.h>
#include <stdio.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <string.h>

#define PORT 5984
#define BUFF_SIZE 4096

int main(int argc, const char *argv[])
{
	int server_fd, new_socket;
	struct sockaddr_in address;
	int opt = 1;
	int addrlen = sizeof(address);
	char buffer[BUFF_SIZE] = {0};
	char *hello = "Hello from server";

	/* [S1]
	 * Explaint the following here.

	 Variable server_fd will be set to the return value of socket(AF_INET, SOCK_STREAM, 0).
	The function socket() will return -1 if error occure so then main() will print error message
	and return -1 as well. However, if no error occure then socket() will return a file descriptor
	and code will continue.

	This part main just check if a connection is established or not.

	 */
	if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
		perror("socket failed");
		exit(EXIT_FAILURE);
	}

	/* [S2]
	 * Explaint the following here.

	setsockopt manipulates options in socket file desceriptor referenced by server_fd.
	Since SOL_SOCKET is set then this function call will try to manipulate
	the options at socket api level. The option name is the third parameter
	and will be set to fourth parameter.

	If there is error then it will exit.
	 */
	if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT,
		       &opt, sizeof(opt))) {
		perror("setsockopt");
		exit(EXIT_FAILURE);
	}

	/* [S3]
	 * Explaint the following here.

	 Sets the value of the variables inside struct address.
	 The sin_port just like the client side, will be use 
	 htons() to get network byte order of port number.
	 */
	address.sin_family = AF_INET;
	address.sin_addr.s_addr = INADDR_ANY;
	address.sin_port = htons( PORT );

	/* [S4]
	 * Explaint the following here.

	After setting up address struct variable it will then be 
	used and bind to the server_fd which is the file descriptor.

	 */
	if (bind(server_fd, (struct sockaddr *)&address, sizeof(address)) < 0) {
		perror("bind failed");
		exit(EXIT_FAILURE);
	}

	/* [S5]
	 * Explaint the following here.

	listen for connection on the socket which server_fd reference to.
	3 is the queue for which the pending connection for server_fd may grow.
	So there can only be 3 connection request be pended.

	 */
	if (listen(server_fd, 3) < 0) {
		perror("listen");
		exit(EXIT_FAILURE);
	}

	/* [S6]
	 * Explaint the following here.

	start to accept the first connection request and new_socket will have the new file 
	descriptor for the accepted socket. 

	if succeed then continue else exit

	 */
	if ((new_socket = accept(server_fd, (struct sockaddr *)&address,
				 (socklen_t*)&addrlen)) < 0) {
		perror("accept");
		exit(EXIT_FAILURE);
	}

	/* [S7]
	 * Explaint the following here.

	Ask the user to press a key and use getchar() to remove the user input.
	Basically wait for the user to be ready and then do preceding steps.


	 */
	printf("Press any key to continue...\n");
	getchar();

	/* [S8]
	 * Explaint the following here.

	read the response from client. (the client side sends a hello message)
	If error occur then read() will return -1 and stop running and print out error message
	else read() will return the amount returned and continue. Then print out the message.
	
	 */
	if (read( new_socket , buffer, 1024) < 0) {
		perror("accept");
		exit(EXIT_FAILURE);
	}
	printf("Message from a client: %s\n",buffer );

	/* [S9]
	 * Explaint the following here.

	(send reponse from the server side)
	Send the string hello ("Hello from client") to the socket whick the file descriptor sock reference to.
	Then print the messsage was sent.

	 */
	send(new_socket , hello , strlen(hello) , 0 );
	printf("Hello message sent\n");
	return 0;
}
