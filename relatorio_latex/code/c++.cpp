// Cout
#include <iostream>

// Open
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

// Write e Sleep
#include <unistd.h>



// Perror
#include <stdio.h>
#include <cerrno>


// Memset
#include <string.h>


// Strtol
#include <stdlib.h>



/*

? --> Menu
3 --> Start
4 --> End

*/


using namespace std;

void leDados(int USB);
void mostraMenu(int USB);
void PiscaLeds(int USB);

int main()
{


  int USB;


  const char *portname = "/dev/ttyACM0";

  USB = open (portname, O_RDWR | O_NOCTTY);


  if (USB < 0)
  {
    cout << "Erro " << errno << " - Abrir Porta Serie: " << portname << endl;   
  }
  else
  {
  
  cout << "leDados(USB) - Proximidade,Frequencia:" << endl; 
  leDados(USB);
  
  
  //cout << "\n\nmostraMenu(USB):" << endl;
  //mostraMenu(USB);
  
  //cout << "PiscaLeds(USB):" << endl; 
  //PiscaLeds(USB);
  
  }



  write(USB,"4",1);
  close(USB);
 
  return(0);
  
}


void mostraMenu(int USB)
{

  int n;
  char buf[21];
  
  memset(buf,0,sizeof(buf));
  
  write(USB,"?",1);

  for(int i = 0; i < 12; i++)
  {
    n = read(USB,buf , sizeof(buf));
    
    buf[n] = '\0';
    printf("\n%s",buf);
  }
  
}

void leDados(int USB)
{

  int n;
  char buf[16];
  char proximidade[4];
  char frequencia[4];
  
  int prox_int;
  int freq_int;
  
  memset(buf,0,sizeof(buf));
  
  
  
  
  write(USB,"3",1);
  read(USB,buf,sizeof(buf));  // a primeira stream e "stream start"

  for(int i = 0; i < 10; i++)
  {
  
    n = read(USB,buf , sizeof(buf));
    buf[n] = '\0';
    
    proximidade[0] = buf[2];
    proximidade[1] = buf[3];
    proximidade[2] = buf[4];
    proximidade[3] = buf[5];
    proximidade[4] = '\0';
    
    frequencia[0] = buf[9];
    frequencia[1] = buf[10];
    frequencia[2] = buf[11];
    frequencia[3] = buf[12];
    frequencia[4] = '\0';
    
    prox_int = (int) strtol(proximidade, NULL, 16);  // Converte hexadecimal para inteiro
    freq_int = (int) strtol(frequencia, NULL, 16);
    
    printf("\nProximidade: %d Frequencia: %d",prox_int,freq_int);
 
    printf("\nValores: %s",buf);
  
  }


}


void PiscaLeds(int USB)
{

  int n;
  char buf[16];
  
  memset(buf,0,sizeof(buf));
  
 for(int i = 0; i < 8; i++)
 {
  write(USB,"7",1);
  sleep(1);
 }


}

