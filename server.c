#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <stdlib.h>
#include <pthread.h>
#include <arpa/inet.h>
#include <unistd.h>

#define MAX 5000
#define PORT 4000
#define MAXCONN 3

void addr_inizialize(struct sockaddr_in *indirizzo, int port, long IPaddr);

int main(){
	int sd, new_sd;
	int pid;
	int conn=0;
	int carta = 0, sasso = 1, forbice = 2;
	
	struct msg{
		char buff[MAX];
	}msg;
	
	struct sockaddr_in server_addr;
	struct sockaddr_in client_addr;
	int client_len=sizeof(client_addr);
	addr_inizialize(&server_addr, PORT,htonl(INADDR_ANY));
	sd=socket(AF_INET,SOCK_STREAM,0);
	bind(sd,(struct sockaddr*)&server_addr,sizeof(server_addr));
	listen(sd,MAXCONN);
	
	printf("Mi pongo in attesa di richieste di connessione\n");
	printf("Sulla porta: %d\n", ntohs(server_addr.sin_port));
	
	while(1){
		new_sd=accept(sd,(struct sockaddr*)&client_addr,&client_len);
		printf("Ho accettato una connessione dal client con porta: %d\n", ntohs(client_addr.sin_port));
		printf("conn=%d\n",conn);
		conn++;
		
		if((pid=fork())<0){
			printf("Errore fork\n");
			exit(0);
		}
		else if(pid==0){
			close(sd);
			read(new_sd,&msg,sizeof(msg));
			printf("Ricevuto %s\n",msg.buff);
			sleep(2);
			if(strcmp(msg.buff,"nuova partita")==0){
				int magic=rand()%3;
				printf("Il server ha scelto %d\n",magic);
				strcpy(msg.buff,"indovina");
				write(new_sd,&msg,sizeof(msg));
				while(1){
					read(new_sd,&msg,sizeof(msg));
					if(atoi(msg.buff)==carta){
						if(magic==carta){
						strcpy(msg.buff,"Pareggio");
						write(new_sd,&msg,sizeof(msg));
						exit(0);
					}
						else if(magic==sasso){
						strcpy(msg.buff,"Client VINCE!");
						write(new_sd,&msg,sizeof(msg));
						exit(0);	

						}

						else if(magic==forbice) {
						strcpy(msg.buff,"Server VINCE!");
						write(new_sd,&msg,sizeof(msg));
						exit(0);
						}
					}
					else if(atoi(msg.buff)==sasso){
						if (magic==sasso){
							strcpy(msg.buff,"Pareggio");
							write(new_sd,&msg,sizeof(msg));
							exit(0);
						}
						else if (magic==carta){
							strcpy(msg.buff,"Server VINCE!");
							write(new_sd,&msg,sizeof(msg));
							exit(0);
						}

						else if (magic==forbice){
						strcpy(msg.buff,"Client VINCE!");
						write(new_sd,&msg,sizeof(msg));
						exit(0);
					}
				}
					else if(atoi(msg.buff)==forbice){
						if(magic==carta){
							strcpy(msg.buff,"Client VINCE!");
							write(new_sd,&msg,sizeof(msg));
							exit(0);
						}

						else if (magic==sasso){
							strcpy(msg.buff,"Server VINCE!");
							write(new_sd,&msg,sizeof(msg));
							exit(0);
						}
						else if(magic==forbice){
						strcpy(msg.buff,"Pareggio");
						write(new_sd,&msg,sizeof(msg));
						exit(0);
					}
				
				}
			close(new_sd);
				}
			}
		}
	}
}
		
void addr_inizialize(struct sockaddr_in *indirizzo, int port, long IPaddr){

	indirizzo->sin_family=AF_INET; 
	indirizzo->sin_port = htons((u_short)port);
	indirizzo->sin_addr.s_addr=IPaddr;
}