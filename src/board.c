/****************************************************************************/
/*                                                                        	*/
/* Projeto: Timer para linha de Tiro - Arco e Flecha - Rodnei Ramos       	*/
/* Chip: 	MSP430G2553                                                   	*/
/* Autor:	Airton Y. C. Toyofuku                                         	*/
/* Versão:	1.1	                                                          	*/
/* Data:	Abril de 2014												  	*/
/*																			*/
/****************************************************************************/



/****************************************************************************/
/* Includes																	*/
/****************************************************************************/

#include "util.h"


/****************************************************************************/
/* Funcoes																	*/
/****************************************************************************/

/***********************************************/
// funcao para configuracao das GPIOs
/***********************************************/
void configura_GPIO(void)
{
    // Configurando as saidas do Port1
    P1DIR |= Verm1 + Verde1 + Verm4 + PtoVerde;
	
    // Estado inicial do sistema com saidas em desabilitadas
    P1OUT = 0x00;
	
    // Habilita o resistor pullup/pulldown
    P1REN = Botao1 + Botao2;  
    
	// Seleciona o resistor de pullup
    P1OUT |= Botao1 + Botao2;
    
	// Habilitando a interrupção no botão
    P1IE  |=  Botao1 + Botao2;
    
	// Interrupção com borda de descida
    P1IES |=  Botao1 + Botao2;
    
	// Limpando o Flag de interrupção do botão
    P1IFG &= ~(Botao1 + Botao2);	
	
	// Configurando as saidas do Port2
    P2DIR |= Verm2 + Verde2 + Sirene + Verde3 + Verm3 + Verde4;
	
    // Estado inicial do sistema com saidas em desabilitadas
    P2OUT = 0x00;
}

/***********************************************/
// funcao para configuracao do TimerA
// Configurado para gerar uma interrupção 
// a cada segundo
/***********************************************/
void configura_TimerA (void)
{
  	CCR0  = delay_timerA;           // ... a cada 31.250 ciclos ...
  	TACTL = TASSEL_2 +       // ... do SMCLK ( 1MHz ) ...
          ID_3 +           // ... dividido por 8 ( 125kHz ) ...
          MC_2;            // ... usando contagem crescente contínua.
	CCTL0 = CCIE;            // Habilita interrupção do Timer A...
  
  /*
  	// ACLK/8
  	BCSCTL1 |= DIVA_3;
	
	//12.5pF cap- setting
	BCSCTL3 |= XCAP_3;				
	
	// CCR0 interrupt enabled
	CCTL0 = CCIE;
	// 512 -> 1 sec, 30720 -> 1 min
	
	CCR0 = delay_timerA;
	
	// ACLK, /8, upmode
	TACTL = TASSEL_1 + ID_3 + MC_1;
  */
}

/***********************************************/
// funcao para configuracao da SPI
/***********************************************/
void configura_spi(void)
{
  	// Selecionando as saidas
  	P1SEL =  data + clock;
  	P1SEL2 = data + clock;
  	
	// parando a maquina
	UCA0CTL1 = UCSWRST;
	
	// 3-pin, 8-bit SPI master
	UCA0CTL0 |= UCCKPH + UCMSB + UCMST + UCSYNC;
	
	// 2 SMCLK
  	UCA0CTL1 |= UCSSEL_2;
	
	// dividindo por 2
  	UCA0BR0 |= 0x02;                          
  	UCA0BR1 = 0; 
	
	// No modulation
  	UCA0MCTL = 0; 
	
	// **Initialize USCI state machine**
  	UCA0CTL1 &= ~UCSWRST;                     
}
