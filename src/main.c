/****************************************************************************/
/*                                                                        	*/
/* Projeto: Timer para linha de Tiro - Arco e Flecha - Rodnei Ramos       	*/
/* Chip: 	MSP430G2553                                                   	*/
/* Autor:	Airton Y. C. Toyofuku                                         	*/
/* Versão:	1.2	                                                          	*/
/* Data:	23 de maio de 2014											  	*/
/* Alterações																*/
/* - Dois apitos para indicar linha quente.									*/
/* - Um apito para indicar inicio dos disparos								*/
/****************************************************************************/



/****************************************************************************/
/* Includes																	*/
/****************************************************************************/

#include "util.h"


/****************************************************************************/
/* Variaveis																*/
/****************************************************************************/

// variavel para controle da interrupçao de tempo
char interruptUmSegundo = 0;

// Variavel para determinar a selecao do tempo a ser cronometrador
char selecaoTempo = None;

// Variavel para determinar o modo de operaçao
char modo = Stop;

// Para teste de tempo e display
//char modo = Teste;

// Estado do display
char estado = Alerta;

// Variaveis para controle do display
char minutos = 0;
char decSegundos = 0;
char uniSegundos = 0;

// Mapa de algarismos para mostrar no display
char numero[10] = {	!BIT0 +  BIT1 +	 BIT2 +  BIT3  +  BIT4  +  BIT5  +  BIT6  + !BIT7,  	// Zero
  					!BIT0 + !BIT1 +	 BIT2 +  BIT3  + !BIT4  + !BIT5  + !BIT6  + !BIT7,		// Um
					!BIT0 +  BIT1 +	 BIT2 + !BIT3  +  BIT4  +  BIT5  + !BIT6  +  BIT7,		// Dois
					!BIT0 +  BIT1 +	 BIT2 +  BIT3  +  BIT4  + !BIT5  + !BIT6  +  BIT7,      // Tres
  					!BIT0 + !BIT1 +	 BIT2 +  BIT3  + !BIT4  + !BIT5  +  BIT6  +  BIT7,		// Quatro
					!BIT0 +  BIT1 +	!BIT2 +  BIT3  +  BIT4  + !BIT5  +  BIT6  +  BIT7,		// Cinco								
					!BIT0 +  BIT1 +	!BIT2 +  BIT3  +  BIT4  +  BIT5  +  BIT6  +  BIT7,      // Seis
					!BIT0 +  BIT1 +	 BIT2 +  BIT3  + !BIT4  + !BIT5  + !BIT6  + !BIT7,		// Sete
					!BIT0 +  BIT1 +	 BIT2 +  BIT3  +  BIT4  +  BIT5  +  BIT6  +  BIT7,		// Oito
					!BIT0 +  BIT1 +	 BIT2 +  BIT3  +  BIT4  + !BIT5  +  BIT6  +  BIT7,      // Nove
				};		

/****************************************************************************/
/* Funcoes																	*/
/****************************************************************************/
                                                    
// Rotina principal
void main (void)
{
    // Desligando o watchdog
    WDTCTL = WDTPW + WDTHOLD;               
    
	DCOCTL  = CALDCO_1MHZ;   //Ajusta o oscilador interno a 1MHz e ...
  	BCSCTL1 = CALBC1_1MHZ;   //... calibra o sistema interno de clock para 1MHz
  
	// Configurando as GPIOs
	configura_GPIO(); 
	
	// Configura a SPI
	configura_spi();
	
	// Esperando um tempo até o hardware se estabilizar
	__delay_cycles(delay_ms);
	
	// Limpando o display
	limpa_display();
	
	// Ligando o sinal ":" em verde
	P1OUT |= PtoVerde;
  	
	// Configura o Timer para gerar um evento por segundo;
	configura_TimerA();
	
	//while(TRUE);
	
	//Habilita o tratamento de interrupções e entra em low power mode
	_BIS_SR(LPM0_bits + GIE);
	__no_operation();	
}


/***********************************************/
// ISR (interrupt service routine) para tratamento 
// de interrupções do PORT1
/***********************************************/
#pragma vector = PORT1_VECTOR
__interrupt void botao_pressionado (void)
{ 
  
  // desabilitando a interrupçao
  P1IE &=  Botao1 + Botao2;
	
  // tempo de debonce
  __delay_cycles(300000);
	
  // Foi pressionado o botao de selecao de tempo
  if(P1IFG & Botao1)
  {	
	// Foi selecionado o modo cancel
   	if(modo == Pause)
   	{
	  	// limpa o display
		limpa_display();
		
		// Ligando o sinal ":" em vermelho
		P1OUT |= PtoVerde;
	
		// colocando o timer em modo stop
		modo = Stop;
		
		// colocando a maqina de estados que controla o timer no inicio
		estado = Alerta;
		
		// Cancelando a seleçao de tempo
		selecaoTempo = None;
   	}
	
	else if(modo == Stop)
	{
		// Inicializa o display com 2 minutos
		if(selecaoTempo == None)
		{
		  
		  	// Limpando os registradores dos shiftregisters
			envia_data_spi(0x00,Todos);
		  
			// Carregando 02:00
			envia_data_spi(numero[0],NumeralVerde1);
			envia_data_spi(numero[2],NumeralVerde2);
			envia_data_spi(numero[0],NumeralVerde3);
			envia_data_spi(numero[0],NumeralVerde4);
			
			selecaoTempo = Min_2;
		}
		
		// Inicializa o display com 4 minutos
		else if( selecaoTempo == Min_2)
		{
		  	// Limpando os registradores dos shiftregisters
			envia_data_spi(0x00,Todos);
			
			// Carregando 04:00
			envia_data_spi(numero[0],NumeralVerde1);
			envia_data_spi(numero[4],NumeralVerde2);
			envia_data_spi(numero[0],NumeralVerde3);
			envia_data_spi(numero[0],NumeralVerde4);
			
			selecaoTempo = Min_4;
		}
		
		// Inicializa o display apagado
		else if (selecaoTempo == Min_4)
		{
		  	limpa_display();
		  	selecaoTempo = None;
		}
	}
  }
  
  // Foi precionado o botao de selecao de modo
  if (P1IFG & Botao2)
  {
	if(selecaoTempo != None)
	{
		// se estiver parado
		if(modo == Stop)
		{
		  	// habilita o contador
		  	modo = Run;
		}
		
		// se estiver rodando
		else if(modo == Run)
		{
		  	// pausa o contador
		  	modo = Pause;
		}
		
		// se estiver pausado
		else if (modo == Pause)
		{
		  	// habilita o contador
		  	modo = Run;
		}
	}
  }
  
  // limpa o flag de interrupção
  P1IFG &= ~(Botao1 + Botao2);
  // Habilitando a interrupção no botão
  P1IE  |=  Botao1 + Botao2;
	
}


/***********************************************/
// ISR (interrupt service routine) para tratamento 
// de interrupções do Timer_A0
/***********************************************/
#pragma vector=TIMER0_A0_VECTOR
__interrupt void Timer_A (void)
{	
  	// variavel para controlar os sinais sonoros
  	int atraso = 0;
	
	// Controle para termos uma interrupção de 1 segundo
	interruptUmSegundo++;
	if(interruptUmSegundo == tempoUmSec)
	{
	   interruptUmSegundo = 0;
	}
	else 
	{
	  //CCR0 += delay_timerA;  //Recarrega o contador do timer
	  return;
	}
	
	// para teste do display e tempo -> Precisa inicar o modo = Teste!
	if(modo == Teste)
	{
	  uniSegundos++;
	  if(uniSegundos > 9)
		uniSegundos = 0;
	  envia_data_spi(numero[uniSegundos],NumeralVerde3);
	}
		   	
	// Foi selecionado o modo de contagem
	if (modo == Run)
	{
		switch (estado)
		{
		  	// Dois apitos para indicar posicionamento
		  	case (Alerta):
			  
			  for(atraso = 0; atraso < 2; atraso++)
			  {
			  	P2OUT |= Sirene;
                 	__delay_cycles(500000);
			  	P2OUT &= ~Sirene;
				__delay_cycles(500000);
			  }
			  
			  // Muda o estado da maquina
			  estado = Posicao;
			  
		  	break;
			
			// Aciona o display com o tempo para posicionamento dos atletas
		  	case (Posicao):
			  			  
			  // Limpa o display
			  limpa_display();
			  
			  // apaga o sinal ":" verde
			  P1OUT &= ~PtoVerde;
			  
			  // Atualizando as variaveis de controle do display
			  decSegundos = 1;
			  uniSegundos = 5;
			  
			  // Carrega 15 segundos em vermelho
			  envia_data_spi(numero[0],NumeralVerm1);
			  envia_data_spi(numero[0],NumeralVerm2);
			  envia_data_spi(numero[decSegundos],NumeralVerm3);
			  envia_data_spi(numero[uniSegundos],NumeralVerm4);
			  
			  // Muda o estado da maquina
			  estado = CronometroPosicao;
			  
		  	break;

			// Inicia a contagem do tempo de posicionamento
			case (CronometroPosicao):
			 
			  // Decrementa os segundos
			  uniSegundos--;
			  
			  // Se os segundos zeraram, decrementa as dezenas
			  if(uniSegundos == 255 && decSegundos == 1)
			  {
					decSegundos--;
					uniSegundos = 9;
			  }
			  
			  // Acabou o tempo
			  else if (uniSegundos == 0 && decSegundos == 0)
			  {
				 // Muda o estado da maquina
				 estado =  AlertaInicio;
			  }
			  
			  envia_data_spi(numero[0],NumeralVerm1);
			  envia_data_spi(numero[0],NumeralVerm2);
			  envia_data_spi(numero[decSegundos],NumeralVerm3);
			  envia_data_spi(numero[uniSegundos],NumeralVerm4); 
			  
		  	break;
			
			// Um apito para indicar "linha quente"
			case (AlertaInicio):
			  
			  	P2OUT |= Sirene;
                 __delay_cycles(1000000);
			  	P2OUT &= ~Sirene;
			  
			  // Muda o estado da maquina
			  estado = Inicio;
		  	break;
			
			// Carregando o tempo de 2 ou 4 minutos
		  	case(Inicio):

			  // Limpa o display
			  limpa_display();
			  
			  // Acende o sinal ":" verde
			  P1OUT |= PtoVerde;
			  
			  // selecionando o algarismo dos minutos
			  if(selecaoTempo == Min_2)
			  {
					minutos = 2;
			  }
			  else
			  {
					minutos = 4;
			  }
				
			  decSegundos = 0;
			  uniSegundos = 0;
			  
			  // Carregando no display
			  envia_data_spi(numero[0],NumeralVerde1);
			  envia_data_spi(numero[minutos],NumeralVerde2);
			  envia_data_spi(numero[decSegundos],NumeralVerde3);
			  envia_data_spi(numero[uniSegundos],NumeralVerde4);
			  
			  // Muda o estado da maquina
			  estado = CronometroInicio;
			break;

			// Inicia a contagem do cronometro
			case(CronometroInicio):
			  
			  // Decrementa os segundos
			  uniSegundos--;
			  
			  // Se as unidades de segundos zeraram, decrementa as dezenas
			  if(uniSegundos == 255)
			  {
					decSegundos--;
					uniSegundos = 9;
			  }
			  
			  // Se as dezenas de segundos zeraram, decrementa os minutos
			  if(decSegundos == 255)
			  {
					minutos --;
					decSegundos = 5;
					uniSegundos = 9;
			  }
			  
			  // Acabou o tempo em verde (00:31)
			  if (minutos == 0 && decSegundos == 3  && uniSegundos == 1)
			  {
				 // Muda o estado da maquina
				 estado =  AlertaFim;
			  }
			  
			  envia_data_spi(numero[0],NumeralVerde1);
			  envia_data_spi(numero[minutos],NumeralVerde2);
			  envia_data_spi(numero[decSegundos],NumeralVerde3);
			  envia_data_spi(numero[uniSegundos],NumeralVerde4); 
			  
			break;
			
			// mostra 00:30 em vermelho no display
			case(AlertaFim):
			  
			  // Limpa o display
			  limpa_display();
			  
			  // Apaga o sinal ":" verde
			  P1OUT &= ~PtoVerde;
			  
			  // atualzando a unidade dos segundos
			  uniSegundos = 0;
			  
			  // Enviando 00:30 em vermelho
			  envia_data_spi(numero[0],NumeralVerm1);
			  envia_data_spi(numero[minutos],NumeralVerm2);
			  envia_data_spi(numero[decSegundos],NumeralVerm3);
			  envia_data_spi(numero[uniSegundos],NumeralVerm4); 

			  // Muda o estado da maquina
			  estado =  CronometroFim;
			break;
			
			// Inicia a contagem do cronometro
			case(CronometroFim):
			  
			  // Decrementa os segundos
			  uniSegundos--;
			  
			  // Se os segundos zeraram, decrementa as dezenas
			  if(uniSegundos == 255)
			  {
					decSegundos--;
					uniSegundos = 9;
			  }
			  
			  // Acabou o tempo
			  else if (uniSegundos == 0 && decSegundos == 0)
			  {
				 // Muda o estado da maquina
				 estado =  Fim;
			  }
			  
			  envia_data_spi(numero[0],NumeralVerm1);
			  envia_data_spi(numero[0],NumeralVerm2);
			  envia_data_spi(numero[decSegundos],NumeralVerm3);
			  envia_data_spi(numero[uniSegundos],NumeralVerm4);
			  
			break;
			
			case(Fim):
			    
			  	P2OUT |= Sirene;
                __delay_cycles(500000);
			  	P2OUT &= ~Sirene;
				
				// Limpa o display
			   limpa_display();
			  
			   // apaga o sinal ":" verde
			   P1OUT |= PtoVerde;
			   
			   // Voltando as variaveis de controle ao inicio
			   selecaoTempo = None;
			   modo = Stop;
			   estado = Alerta;
			   minutos = 0;
			   decSegundos = 0;
			   uniSegundos = 0;
				
			break;
		}

	}
   // CCR0 += delay_timerA;  //Recarrega o contador do timer
}   