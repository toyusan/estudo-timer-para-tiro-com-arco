# Timer Para Tiro Com Arco

---

Tabela de conteúdos
=================
<!--ts-->
   * [Sobre o projeto]
   * [Funcionalidades]
   * [Requisitos de hardware]
   * [Requisitos de software]
   * [Autor]
   * [Licença]
<!--te-->

---

## Sobre o projeto

Desenvolvimento de um timer para ser utilizado em competições não oficiais de tiro com arco indoor.

O timer consiste de um display de 130 x 100 milimetros, montado com LEDs RGB no formato 00:00, em que cada algarismo é composto por sete segmentos. 

O timer possui dois modos de operação, um com contagem regressiva de dois minutos e outro com contagem regressiva de quatro minutos.

Seu controle é realizado através uma botoeira simples com botões, um verde e um vermelho.

---

## Funcionalidades

>- O Arbitro pode selecionar qual o tempo de linha quente, sendo dois ou quatro minutos;

>- Uma vez selecionado o tempo, o dispositivo aciona o buzzer gerando dois sinais sonoros, e inicia uma contagem regressiva de quinze segundos, com o display em vermelho, indicando que os arqueiros devem se posicionar na linha de tiro;

>- Decorrido os quinze segundos, o buzzer é acionado novamente, indicando o inicio do tempo selecionado, liberando a linha para o inicio da bateria de tiros. Nesse momento o display inicia a contagem regressiva selecionada, com o display verde;

>- Faltando quinze segundos para o termino da contagem, o display passa a apresentar os algarismos na cor vermelha;

>- Ao termino da contagem, o buzzer é novamente acionado gerando um sinal sonoro, indicando o termino da bateria de tiros e apagando o display.
---

## Requisitos de hardware

* Lauchpad MSP430 com MCU MSP430G2553
* Shift Register 74HCT595 para controle do display;
* LEDs RGB;
* Transistor de potência BD139;

## Requisitos de software

* O projeto foi desenvolvido no IAR Embedded Workbench para MSP430, versão evaluation;

---

### Autor 

- Airton Y. C. Toyofuku
- airton.toyofuku@gmail.com

---
### Licença
Este projeto esta sob a licença [MIT](./LICENSE).