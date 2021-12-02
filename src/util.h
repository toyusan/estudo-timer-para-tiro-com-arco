/**************************************************************************/
/*                                                                        */
/* Header File de definições							                  */
/* Chip: 	MSP430G2553                                                   */
/* Autor:	Airton Y. C. Toyofuku                                         */
/* Versão:	1.1	                                                          */
/* Data:	Abril de 2014												  */
/**************************************************************************/

#ifndef util_h
#define util_h

// Definindo o chip usado
#include <msp430g2553.h>

#include "stdlib.h"
#include "intrinsics.h"
#include "display.h"
#include "board.h"

/***********************************************/

// definindo constantes de booleanas
#define TRUE 		1
#define FALSE 		0

// definindo os modos de inicialização
#define None		0
#define Min_2		2
#define Min_4       4

// definindo os modos de operação
#define Stop		0
#define	Run			1
#define Pause		2
#define Teste       3

// definindo os estados de operação
#define Alerta				0	// Um apito
#define Posicao				1   // 15 segundos em vermelho
#define CronometroPosicao	2   // Decremente os 15 segundos
#define AlertaInicio      	3   // Dois apitos
#define Inicio				4   // 4 ou 2 minutos
#define CronometroInicio	5   // Decrementa o tempo
#define AlertaFim			6   // 30 segundos em vermelho
#define CronometroFim		7   // Decrementa os 30 segundos
#define	Fim                 8	// um apito

#endif