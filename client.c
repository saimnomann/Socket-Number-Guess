#include<stdio.h>
#include<string.h>
#include<Stdlib.h>
#include<winsock2.h>
#include<windows.h>

#define PORT 5000
int main(){
char buffer[1024]={0};
struct sockaddr_in address;
WSADATA wsaData;
int points=0;
SOCKET sock;
WSAStartup(MAKEWORD(2,2),&wsaData);

sock=socket(AF_INET,SOCK_STREAM,0);
address.sin_family=AF_INET;
address.sin_addr.s_addr=inet_addr("192.168.1.122");
address.sin_port=htons(PORT);

int guess;

if(connect(sock,(struct sockaddr *)&address,sizeof(address))==SOCKET_ERROR){
	printf("Connection Failed.Please check the server address and try again.\n");
	closesocket(sock);
	WSACleanup();
	
}
else{
printf("\nConnected to Server Successfully!\n");
 recv(sock,buffer,sizeof(buffer),0);
 printf("\n%s\n",buffer);
 memset(buffer, 0, sizeof(buffer)); 
 PlaySound(TEXT("number guessing game intro.wav"), NULL, SND_FILENAME | SND_ASYNC);// add path for intro audio

while(points<5){
memset(buffer, 0, sizeof(buffer));
recv(sock,buffer,sizeof(buffer),0); 
printf("%s\n",buffer);
 memset(buffer, 0, sizeof(buffer));
scanf("%d",&guess);
sprintf(buffer,"%d",guess);
send(sock,buffer,strlen(buffer),0);
 memset(buffer, 0, sizeof(buffer)); 
 recv(sock,buffer,sizeof(buffer),0);
 printf("%s\n",buffer);
 if(strstr(buffer,"Congratulations! You have guessed correctly")!=NULL){
  points++; 	
  PlaySound(TEXT("correct guess.wav"), NULL, SND_FILENAME | SND_SYNC);// enter path for correct guess sound

   printf("\nPoints Earned: %d\n", points);
 }  
 else {
  PlaySound(TEXT("try again.wav"), NULL, SND_FILENAME | SND_SYNC); // enter path for try again sound

 }
 
}
 memset(buffer, 0, sizeof(buffer)); 
recv(sock, buffer, sizeof(buffer), 0);
printf("%s\n",buffer);
closesocket(sock);
WSACleanup();
PlaySound(TEXT("won the game.wav"), NULL, SND_FILENAME | SND_SYNC);// enter path for congratulations sound

 printf("\nGame Over. Thank you for playing!\n");
}
}