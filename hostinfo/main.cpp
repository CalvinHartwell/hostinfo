/* 
   Author: Calvin Hartwell 
   Email: mail@calvinhartwell.com 
   Date: Sunday 3rd March 2013 
*/

// Includes 
#include <iostream>
#include <winsock2.h> 

// Need to link with the winsock library 
#pragma comment (lib, "Ws2_32.lib")

// Method for obtaining and displaying network interface information 
void hosts() {
	 
	// Used to store local host name 
	 char localhost[80]; 
	 
	 // Attempt to get local host name
	 if(gethostname(localhost, sizeof(localhost)) == SOCKET_ERROR) {
		 printf("Error getting local host name (error code: %i)", WSAGetLastError);
		 return; 
	 }
	
	 // Attempt to get host from name 
	 struct hostent *host = gethostbyname(localhost); 
	 if(host == 0) {
		printf("Error getting host from name!"); 
		return; 
	 }

	 // Display hostname 
	 printf("Host Name: %s \n", localhost); 

	 // Display ip addresses 
	  for (int ip = 0; host->h_addr_list[ip] != 0; ++ip) {
        struct in_addr addr;
        memcpy(&addr, host->h_addr_list[ip], sizeof(struct in_addr));
		printf("IP Address: %s \n", inet_ntoa(addr)); 
    }
}

// Entry point 
int main()
{
	// Winsock Data 
	WSAData wsaData;

	// Initialise Winsock
	if(WSAStartup(MAKEWORD(1, 1), &wsaData) != 0 ) {
		 printf("Error initialising Winsock!");  
	}

	// Display and Output host information
	hosts(); 

	// Cleanup Winsock... 
	WSACleanup(); 
	
	// Key open until return/enter pressed
	getchar(); 

	return 0; 
}