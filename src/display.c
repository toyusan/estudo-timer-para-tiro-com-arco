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
// funcao para Limpar o display
/***********************************************/
void limpa_display (void)
{
  	// mandando 0x00 pela spi
	 envia_data_spi(0x00, Todos);
}


/***********************************************/
// funcao para trocar as cores do led
/***********************************************/
void troca_cor_led (int corLed)
{
  if(corLed == Verde)
	corLed = Vermelho;
  else
	corLed = Verde;
}

/***********************************************/
// funcao para enviar informacoes pela spi
/***********************************************/
void envia_data_spi(char info, char destino)
{
  	UCA0TXBUF = info;
	while (!(IFG2 & UCA0TXIFG));
	toogle_latch(destino);
}

/***********************************************/
// funcao para acionar os shiftregisters
/***********************************************/
void toogle_latch (char selecaoNumeral)
{
  	switch (selecaoNumeral)
	{
		case Todos:
	  		// forçando os latches
			P1OUT |= Verm1 + Verde1 + Verm4 ;
			P2OUT |= Verm2 + Verde2 + Verde3 + Verm3 + Verde4;
			__delay_cycles(delay_ms);		
			// baixando os latches
			P1OUT &= ~(Verm1 + Verde1 + Verm4);
			P2OUT &= ~(Verm2 + Verde2 + Verde3 + Verm3 + Verde4);
		  break;
	  
		case TodosVerm:
		  	// forçando os latches
		 	P1OUT |= Verm1 + Verm4;
			P2OUT |= Verm2 + Verm3;
		    __delay_cycles(delay_ms);
			// baixando os latches
			P1OUT &= ~(Verm1 + Verm4);
			P2OUT &= ~(Verm2 + Verm3);
		break;
		
		case TodosVerde:
	  		// forçando os latches
			P1OUT |=  Verde1;
			P2OUT |=  Verde2 + Verde3 + Verde4;
			__delay_cycles(delay_ms);		
			// baixando os latches
			P1OUT &= ~(Verde1);
			P2OUT &= ~(Verde2 + Verde3 + Verde4);	  
	  	break;
		 
		case NumeralVerm1:
		  P1OUT |=  Verm1;
		  __delay_cycles(delay_ms);
		  P1OUT &= ~Verm1;
		break ;
		
		case NumeralVerm2:
		  P2OUT |= Verm2;
		  __delay_cycles(delay_ms);
		  P2OUT &= ~Verm2;
	  	break;
		
	  	case NumeralVerm3:
		  P2OUT |= Verm3;
		  __delay_cycles(delay_ms);
		  P2OUT &= ~Verm3;
		break;
		
		case NumeralVerm4:
		  P1OUT |=  Verm4;
		  __delay_cycles(delay_ms);
		  P1OUT &= ~Verm4;
		break;
		
		case NumeralVerde1:
			P1OUT |= Verde1;
			__delay_cycles(delay_ms);		
			P1OUT &= ~(Verde1);
		break;
		
		case NumeralVerde2:
		  	P2OUT |= Verde2;
			__delay_cycles(delay_ms);		
			P2OUT &= ~(Verde2);
	  	break;
		
	  	case NumeralVerde3:
		  	P2OUT |= Verde3;
			__delay_cycles(delay_ms);		
			P2OUT &= ~(Verde3);		  
		break;
		
		case NumeralVerde4:
		  	P2OUT |= Verde4;
			__delay_cycles(delay_ms);		
			P2OUT &= ~(Verde4);
		break;
		  
	default:
	  	break;
	}
}