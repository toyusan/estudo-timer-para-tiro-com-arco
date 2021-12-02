/**************************************************************************/
/*                                                                        */
/* Header File de definições do display							                  */
/* Chip: 	MSP430G2553                                                   */
/* Autor:	Airton Y. C. Toyofuku                                         */
/* Versão:	1.1	                                                          */
/* Data:	Abril de 2014												  */
/**************************************************************************/

#ifndef board_h
#define board_h

/***********************************************/

// definindo as saídas

#define Verm1		BIT0	// P1.0
#define data 		BIT2    // P1.2
#define clock 		BIT4    // P1.4
#define Verde1  	BIT5    // P1.5
#define Verm4		BIT6    // P1.6
#define PtoVerde 	BIT7	// P1.7

#define Verm2   	BIT0    // P2.0
#define Verde2  	BIT1    // P2.1
#define Sirene	 	BIT2	// P2.2
#define Verde3  	BIT3    // P2.3
#define Verm3   	BIT4    // P2.4
#define Verde4  	BIT5    // P2.5
                                
/***********************************************/

// Definindo as entradas
#define Botao1 	BIT1    // P1.1
#define Botao2 	BIT3	// P1.3				

/***********************************************/

// Definindo as constantes de tempo
#define delay_ms 1000

#define delay_timerA  62500 // Interrupcao a cada 0,5 sgundos
#define tempoUmSec    2     // Controle para atingir 1 segundo
 
//#define delay_timerA  511 // Xtal 32Khz

/***********************************************/

/***********************************************/
// funcao para configuracao das GPIOs
/***********************************************/
void configura_GPIO(void);

/***********************************************/
// funcao para configuracao do TimerA
// Configurado para gerar uma interrupção 
// a cada segundo
/***********************************************/
void configura_TimerA (void);

/***********************************************/
// funcao para configuracao da SPI
/***********************************************/
void configura_spi(void);
#endif