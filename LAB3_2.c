//*****************************************************************************
// Fichier:      LAB3_2.C
// Auteur:      Pierre-Olivier Riverin
//
// Date:         18-02-2016
// Revision :    A
// Compilateur:  Keil uVision 5
// Description:  
//
//
//
// Modification: 
//
//*****************************************************************************
//
//                              DALLAS   DS89C450
//                      ------------------------------
//                    1 | P1.0 - T2              Vcc | 40 
//                    2 | P1.1 - T2 EX    AD0 - P0.0 | 39 
//                    3 | P1.2            AD1 - P0.1 | 38 
//                    4 | P1.3            AD2 - P0.2 | 37 
//                    5 | P1.4 - INT2     AD3 - P0.3 | 36 
//                    6 | P1.5 - /INT3    AD4 - P0.4 | 35 
//                    7 | P1.6 - INT4     AD5 - P0.5 | 34 
//      5V--*--*--*   8 | P1.7 - /INT5    AD6 - P0.6 | 33 
//          |  |  |   9 | RESET           AD7 - P0.7 | 32 
//        10k 10k 10k10 | P3.0 - RX              /EA | 31 
//          |  |  |  11 | P3.1 - TX              ALE | 30 
// Gnd--Sw2-*--+--+--12 | P3.2 - /INT0         /PSEN | 29 
// Gnd--Sw3----*--+--13 | P3.3 - /INT1    A15 - P2.7 | 28 
// Gnd--Sw4-------*--14 | P3.4 - T0       A14 - P2.6 | 27 
// 5V--Led--R330ohm--15 | P3.5 - T1       A13 - P2.5 | 26 
//                   16 | P3.6 - /WR      A12 - P2.4 | 25 
//                   17 | P3.7 - /RD      A11 - P2.3 | 24 
//                   18 | XTAL2           A10 - P2.2 | 23 
//                   19 | XTAL1            A9 - P2.1 | 22 
//                   20 | GND              A8 - P2.0 | 21 
//                      ------------------------------
//
//*****************************************************************************

#include <stdio.h>                        // Predeclarations des functions I/O
#include "_DeclarationGenerale.h"


// *** D E F I N I T I O N S   S W I T C H   E T   L E D S    KIT DALLAS ******
#define SW2   P3_2       // Switch sur le Port 3 bit 2
#define SW3   P3_3       // Switch sur le Port 3 bit 3
#define SW4   P3_4       // Switch sur le Port 3 bit 4
#define LED   P3_5       // DEL sur le Port 3 bit 5


//****** P R O T O T Y P E   D E S   F O N C T I O N S ************************
void vDelaiMs(UI uiDelai);     // Delai de X millisecondes.
void vInitPortSerie(void);     // Init port serie à 57600 n,8,1.
void vInitTimer0(void);         // Init Timers interne Dallas 
void vDelaiMsTimer0(UI uiDelai); // Timer Dallas

//****** P R O G R A M M E   P R I N C I P A L ********************************
void main(void) 
{ 

  vInitPortSerie();  // Initialise le port série a 57600 bds, N, 8, 1
  vInitTimer0();     // Initialise le Timer 0
  
  printf("\nProg xxxxxxx"); // verification a l'ecran que programme debute

  while(TRUE)
  {
    vDelaiMsTimer0(100);    // delais effectuer avec timer dallas
	  LED = !LED ;            // Toggle LED sur dallas ON-OFF
	
  }                    
} 
//****** F I N   D U   P R O G R A M M E   P R I N C I P A L ******************



//****** L E S   F O N C T I O N S ********************************************



//*****************************************************************************
// Nom de la fct:   vDelaiMs                   Fait par: Pierre-Olivier Riverin
// Date:            17/02/2016
// Revision :       A
// Modification : 
// Prototype:       void vDelaiMs(UI uiDelai);
//
// Description:     Fait un delai de logitiel uiDelai millisecondes.
//   
// Parametre d'entre: UI uiDelai     - Nombre de milliseconde du delai.
//
// Parametre de sortie: Aucun.
//               
// Exemple d'appel: vDelaiMs(50);     // Delai 50 ms.
//*****************************************************************************
void vDelaiMs(UI uiDelai)
{
  unsigned int uiDelaiIn = 0; 
  unsigned int uiDelaiOut = 0; 

  for(uiDelaiOut = 0; uiDelaiOut < uiDelai; uiDelaiOut++ )
  {
    for( uiDelaiIn = 0; uiDelaiIn < 1164; uiDelaiIn++ )
      {
      }	  
  }	 
}                           // Fin vDelaiMs(). 


//*****************************************************************************
// Nom de la fct:   vInitPortSerie                   Fait par: Pierre Chouinard
// Date:            17 Decembre 2008
// Revision :       A
// Modification : 
// Prototype:       void vInitPortSerie(void)
// Description:     Initialise le port serie0  à 57600,n,8,1
//   
// Parametre d'entre: Aucun.
//
// Parametre de sortie: Aucun.
//                
// Exemple d'appel: vInitPortSerie();
//*****************************************************************************
void vInitPortSerie(void)
{
  T2CON = T2CON & 0xCF; // RXClk et TXClk viennent du Timer 1
  SCON0 = 0x50;         // Port Serie 0: mode 1, 8-bit UART avec reception.     
  TMOD  = TMOD | 0x20;  // TMOD: Timer 1, mode 2, 8-bit auto reload.     
  TH1   = 0xFF;         // TH1:  reload value for 57600 baud @ 11.059MHz.
                        //       0xFA = 9600, 0xFD = 19200, 0xFE = 28800.    
  PCON  = PCON | 0x80;  // SMOD_0 = 1 (doubleur de baud).
  TR1   = 1;            // TR1:  Part le Timer 1.                       
  TI_0  = 1;            // TI a 1 pour permettre transmission 1er charactere. 
}                       // Fin   vInitPortSerie()

//*****************************************************************************
// Nom de la fct:   vInitTimer0                  Fait par: Pierre-Olivier Riverin
// Date:            18/02/2016
// Revision :       A
// Modification : 
// Prototype:       void vInitTimer0(void);   
//
// Description:     Initialise le Timer Dallas
//   
// Parametre d'entre:    Aucun 
//
// Parametre de sortie: Aucun.
//               
// Exemple d'appel: vInitTimer0();    
//*****************************************************************************
void vInitTimer0(void)
{
  TMOD = TMOD & 0XF0;   // indique le mode de timer utiliser 
  TMOD = TMOD | 0x01;   // deuxieme partit pour le choix du mode timer 
  TL0 = 0x66;           // LO de 1ms 922 conts - 64614 en HEX  
  TH0 = 0xFC;           // HI de 1ms meme calculs 
  TF0 = 0;              // Mise a zero du debordement
  TR0 = 0;              // Arrete le timer 
}
//*****************************************************************************
// Nom de la fct:   vDelaiMsTimer0            Fait par: Pierre-Olivier Riverin
// Date:            17/02/2016
// Revision :       A
// Modification : 
// Prototype:       void vDelaiMsTimer0(UI uiDelai);
//
// Description: Fait un delai avec Timers carte dallas de uiDelai millisecondes
//   
// Parametre d'entre: UI uiDelai     - Nombre de milliseconde du delai.
//
// Parametre de sortie: Aucun.
//               
// Exemple d'appel: vDelaiMsTimer0(50);     // Delai 50 ms.
//*****************************************************************************
void vDelaiMsTimer0(UI uiDelai)
{
  UI i;                         // intialise i
  
  TR0 = 1;                      // Demmare le timer 
  for(i = 0; i < uiDelai; i++)  // boucle d'incrementation
  {
    while(TF0 == 0)             // Verification d'overflow 
    {
    }
    TL0 = 0x66;                 //   Reinitialise 
    TH0 = 0xFC;                 //   les parametre
    TF0 = 0;                    //    du timers 
  }
  TR0 = 0;
}  

// ****************************************************************************
//                  INFORMATION SUPLEMENTAIRE 
// ****************************************************************************
// Adresse des Registers a fonctions speciales (SFR)
//
// P0    = 0x80;    P1    = 0x90;    P2    = 0xA0;    P3    = 0xB0;
// PCON  = 0x87;    SCON0 = 0x98;    TL1   = 0x8B;    TH1   = 0x8D;
// TCON  = 0x88;    TMOD  = 0x89;
// 
// BITS  de certain Registers a fonctions speciales (SFR)  Reset
//             7    6    5    4    3    2    1    0
//  TCON      TF1  TR1  TF0  TR0  IE1  IT1  IE0  IT0       00000000
//  TMOD      GATE C/T  M1   M0   GATE C/T  M1   M0        00000000
//  SCON0     SM0  SM1  SM2  REN  TB8  RB8  TI_0 RI_0      00000000
//  P1        INT5 INT4 INT3 INT2 TXD1 RXD1 T2EX T2        11111111
//  P3        RD   WR   T1   T0   INT1 INT0 TXD0 RXD0      11111111
