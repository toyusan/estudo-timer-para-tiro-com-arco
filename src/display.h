/**************************************************************************/
/*                                                                        */
/* Header File de definições do display							                  */
/* Chip: 	MSP430G2553                                                   */
/* Autor:	Airton Y. C. Toyofuku                                         */
/* Versão:	1.1	                                                          */
/* Data:	Abril de 2014												  */
/**************************************************************************/

#ifndef display_h
#define display_h

/***********************************************/

// definindo as cores dos leds
#define Verde 		0
#define Vermelho 	1

// Definindo as constantes para identificar os Numerais
#define NumeralVerm1		11
#define NumeralVerm2		12
#define NumeralVerm3		13
#define NumeralVerm4		14
#define TodosVerm 			15

#define NumeralVerde1		21
#define NumeralVerde2		22
#define NumeralVerde3		23
#define NumeralVerde4		24
#define TodosVerde			25

#define Todos				30
#define Nenhum				 0

/***********************************************/


/***********************************************/
// funcao para Limpar o display
/***********************************************/
void limpa_display (void);

/***********************************************/
// funcao para trocar as cores do led
/***********************************************/
void troca_cor_led (int corLed);

/***********************************************/
// funcao para acionar os shiftregisters
/***********************************************/
void toogle_latch (char selecaoNumeral);

/***********************************************/
// funcao para enviar informacoes pela spi
/***********************************************/
void envia_data_spi(char info, char destino);

#endif