#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <time.h>
int main()
{
    int socket_in=0;
    unsigned long long TIEMPO_1970=2208988800;//0 años = 2.208.988.800 segundos, 01-01-1900 00:00 a 01: 01-1970 00:00

  typedef struct  ///Estructura de datos para el
  {
    unsigned char LI_VN_Mode; 

    unsigned char Stratum; 
    unsigned char Poll; 
    unsigned char Precision;  
    unsigned int Root_Delay;      
    unsigned int Root_Dispersion;
    unsigned int Reference_Identifier; 
    unsigned int Reference_ts_sec; 
    unsigned int Reference_ts_f;  
    unsigned int Originate_s;       
    unsigned int Originate_f;       
    unsigned int recibidos_s;        
    unsigned int recibidos_f;       
    unsigned int Transmitir_time_s;         
    unsigned int Transmitir_time_f;  

  } PROTOCOLO_NTP;      

  PROTOCOLO_NTP ntp = {27,27,27,27,27,27,27,27,27,27,27,27,27,27,27};
  
  struct sockaddr_in servidor; 

  socket_in = socket( AF_INET, SOCK_DGRAM, 0); 

  servidor.sin_family = AF_INET;
  servidor.sin_addr.s_addr = inet_addr("200.89.75.197");
  servidor.sin_port = htons(123);

  connect( socket_in, ( struct sockaddr * ) &servidor, sizeof( servidor) );

  send( socket_in, ( char* ) &ntp, sizeof( PROTOCOLO_NTP ),0);

  recv( socket_in, ( char* ) &ntp, sizeof( PROTOCOLO_NTP ),0);

  time_t tiempo_segundos = (ntohl( ntp.Transmitir_time_s) - TIEMPO_1970) ;

  printf( "Sincronizacion de tiempo: %s", ctime( ( const struct time_t* ) &tiempo_segundos ) );

  return 0;
}
 