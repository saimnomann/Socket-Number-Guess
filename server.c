#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <winsock2.h>
#include<time.h>

#define PORT 5000 
#define Max_client 5
int points=0;

int main() {
    int diff;
    char buffer[1024]={0};
    char *message="\n==================================================\n       Welcome to the Number Guessing Game      \n==================================================\n\n";
int guess;
    WSADATA wsaData;
    int client=0;
    SOCKET sock_fd,new_sock;
    struct sockaddr_in address;
	int addrlen=sizeof(address);
	char *x;

   WSAStartup(MAKEWORD(2,2),&wsaData);
sock_fd = socket(AF_INET, SOCK_STREAM, 0);
    
address.sin_family = AF_INET;
address.sin_addr.s_addr =inet_addr("192.168.1.122"); //port used for connnection
address.sin_port = htons(PORT); //convert port into bytes


bind(sock_fd,(struct sockaddr *)&address,addrlen);

if(listen(sock_fd,5)==SOCKET_ERROR){
	printf("Server Listening Failed\n");
	closesocket(sock_fd);
	WSACleanup();
	return 1;
}
	
printf("Server Listening on port: %d\n",PORT);
new_sock=accept(sock_fd,(struct sockaddr *)&address,&addrlen);
if(new_sock==SOCKET_ERROR){
	printf("Accept Failed\n");
	closesocket(sock_fd);
	WSACleanup();
}
printf("Client Connected\n");
send(new_sock,message,strlen(message),0);

while(points<5){
memset(buffer,0,sizeof(buffer));
srand(time(0));
int number=rand()%100+1;
printf("The number generated is %d\n",number); 
	while(1){
	char *msg="Enter your Guess ";
	send(new_sock,msg,strlen(msg),0);
	memset(buffer,0,sizeof(buffer));
	int recieve=recv(new_sock,buffer,sizeof(buffer),0); 
     int guess = atoi(buffer);
    printf("The number recieved from client is %d\n",guess);  
    if(guess>number){
    	diff=guess-number;
    	if(diff>0 && diff<10){
    	x="You are too Close,the guess is little high";
		}
		else{
			x="The guess is too High";
//			send(new_sock,x,strlen(x),0);
		}}
			else if(guess<number){
    	diff=number-guess;
    	if(diff>0 && diff<10){
		 x="You are too Close,the guess is little low";
//		 send(new_sock,x,strlen(x),0);
		}                                              
		else{	
		x="The guess is too Low";
//			send(new_sock,x,strlen(x),0);
		}
		                                 
}
		else{
			points++;
			x="Congratulations! You have guessed correctly";
			send(new_sock,x,strlen(x),0);
			break;	
		}
    	send(new_sock,x,strlen(x),0);
}


if(points>=5){
x="Congratulations You have Won!Thanks For Playing.";
send(new_sock,x,strlen(x),0);
printf("%s\n",buffer);


}
}
closesocket(new_sock);
closesocket(sock_fd);
WSACleanup();
printf("Server Has been Closed\n");
}