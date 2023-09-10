#include <unistd.h>
#include <stdio.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <string.h>
#include <arpa/inet.h>

#define PORT 5984
#define BUFF_SIZE 4096

int main(int argc, const char *argv[])
{
	int sock = 0;
	struct sockaddr_in serv_addr;
	char *hello = "Hello from client";
	char buffer[BUFF_SIZE] = {0};

	/* [C1]
	 * Explaint the following here.
	 
	Variable sock will be set to the return value of socket(AF_INET, SOCK_STREAM, 0).
	The function socket() will return -1 if error occure so then main() will print error message
	and return -1 as well. However, if no error occure then socket() will return a file descriptor
	and code will continue.

	This part main just check if a connection is established or not.

	 */
	if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
		printf("\n Socket creation error \n");
		return -1;
	}

	/* [C2]
	 * Explaint the following here.

	Fill the amount of bytes needed for serv_addr with '0'. Then the struct serv_addr will have its
	space for use. 

	This is to avoid errors.

	Then the serv_addr's variables will be set to AF_INET(ipv4 protocal)
	and use htons() to get network byte order of port number.

	 */
	memset(&serv_addr, '0', sizeof(serv_addr));
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_port = htons(PORT);

	/* [C3]
	 * Explaint the following here.

	Convert the ipv4 in serv_addr to binary form and check if succeeded.
	It convert 127.0.0.1 to binary form and put it in the address of serv_addr.sin_addr
	for future referencing.

	 */
	if(inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr) <= 0) {
		printf("\nInvalid address/ Address not supported \n");
		return -1;
	}

	/* [C4]
	 * Explaint the following here.

	Start a connection with input as information stored in serv_addr struct.
	Here sock which is the file descriptor is being used to determine the format of serv_addr.
	If succeed then return 0 and code continue else -1 and print out error message and return.

	 */
	if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) {
		printf("\nConnection Failed \n");
		return -1;
	}


	/* [C5]
	 * Explaint the following here.

	Ask the user to press a key and use getchar() to remove the user input.
	Basically wait for the user to be ready and then do preceding steps.

	 */
	printf("Press any key to continue...\n");
	getchar();

	/* [C6]
	 * Explaint the following here.

	Send the string hello ("Hello from client") to the socket whick the file descriptor sock reference to.
	Then print the messsage was sent.

	 */
	send(sock , hello , strlen(hello) , 0 );
	printf("Hello message sent\n");

	/* [C7]
	 * Explaint the following here.

	read the response after sending the message.
	If error occur then read() will return -1 and stop running and print out error message
	else read() will return the amount returned and continue. Then print out the message.
	 */
	if (read( sock , buffer, 1024) < 0) {
		printf("\nRead Failed \n");
		return -1;
    }
	printf("Message from a server: %s\n",buffer );
	return 0;
}
