//************MARIO CANALELLA 16026677*************
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
#define PORT 4000 //port per  la connessione del client

//funzione per inizializzare gli indirizzi
void addr_inizialize(struct sockaddr_in *indirizzo, int port, long IPaddr);

int main(){
	struct msg{
		char buff[MAX];
	}msg;

	int magic;
	// sd descrittore del socket, error controllo per la connect()
	int sd,error;
	// indirizzo del server
	struct sockaddr_in server_addr;
	//indirizzo del client
	struct sockaddr_in mio_addr;
	// dim indirizzo client
	int mio_addr_len=sizeof(mio_addr);
	//inizializza l'indirizzo del server
	addr_inizialize(&server_addr, PORT, inet_addr("127.0.0.1"));
	//crea l'identificatore del socket
	sd=socket(AF_INET,SOCK_STREAM,0);
	// crea una connessione sul socket creato
	error=connect(sd,(struct sockaddr*)&server_addr,sizeof(server_addr));
	//controllo connect()
	if(error==0){
		printf("ho eseguito la connessione\n");
		strcpy(msg.buff,"nuova partita");
		write(sd,&msg,sizeof(msg));
		while(1){
			read(sd,&msg,sizeof(msg));
			sleep(1);
			if(strcmp(msg.buff,"indovina")==0){
				printf("*********************\n");
				printf("*     BENVENUTO     *\n");
				printf("*CARTA-SASSO-FORBICI*\n");
				printf("*********************\n");		
				printf("Inserire 0 per carta, 1 per sasso e 2 per forbice\n\n"); 
    			printf("Giocatore 1, = [0|1|2]: ");
				scanf("%d",&magic);
				printf("Hai scelto %d\n", magic);
				snprintf(msg.buff,MAX,"%d",magic);
				write(sd,&msg,sizeof(msg));
			}
			else if(strcmp(msg.buff,"Client VINCE!")==0){
				printf("Complimenti, il Client VINCE!\n");
				exit(0);
			}
			else if(strcmp(msg.buff,"Server VINCE!")==0){
				printf("Complimenti, il Server VINCE!\n");
				exit(0);
			}

			else if(strcmp(msg.buff,"Pareggio")==0){
				printf("PARITÀ!\n");
				exit(0);
			}
		}
	}
	else
		printf("Errore di connessione\n\n");
	close(sd);
}

void addr_inizialize(struct sockaddr_in *indirizzo, int port, long IPaddr){
	indirizzo->sin_family=AF_INET; 
	indirizzo->sin_port=htons((u_short)port);
	indirizzo->sin_addr.s_addr=IPaddr;	
}