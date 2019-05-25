# Trabalho Pr�tico de Sistema Operativos 2 2018 / 2019 - ISEC

## Nome do trabalho: Clone Arknoid/Breakout
* Desenvolvido em Visual Studio 2017 / 2019 Community Edition;
* Coment�rios e c�digo em PT-PT (o mais po�vel);

## Alunos
* Nuno Fidalgo [21140369]
* Cl�udio Melo [21170023]

## Breve descri��o:
- Implementa��o de um jogo estilo Arknoid / Breakout
- Jogo divido por servidor e cliente com uma DLL(bridge) que implementa as comuni��es entre o servidor e cliente;
- No servidor vamos ter toda a mec�nica de jogo;
- Cliente tem apenas a configura��o de teclas, envio de nome do jogador e tem de detetar se est� em modo local(memoria partilhada) 
ou em modo remoto(named pipes) (um belo extra seria colcoar a comunicar por TCP/IP ou UDP).

## Tecnologias
* Win32 API
* Threads, Mutex, Events, Sem�foros, Named Pipes;
* Windows GUI (WDA);
* Arquitetura: cliente/servidor;

# Meta 1

## Modulo (DDL) "Bridge" 
- [x] C�digo inicial da bridge(DDL);
- [x] Estrutura de dados; (Em progresso!!);
- [x] Fun��es para zonas de memoria partilhada;
	- [x] Zona de Mensagens;
	- [x] Zona do Jogo;
- [x] Fun��es a implementar;
	- [x] Login;
	- [x] RecebeJogo(ReceiveBroadcast);
	- [x] EnviaMensagem (SendMessage);
	- [x] RecebeMensagem (ReceiveMessage);

## Modulo "Servidor"
- [x] C�digo inicial da servidor(consola);
- [x] Interliga��o DLL impl�cita;
- [x] Suporte a memoria partilhada;
- [x] Protegido de forma a executarmos o servidor em varias instancias;
- [x] Login... d� in�cio ao jogo;
- [x] Suporte a threads;
	- [x] Recebe mensagens;
	- [x] Envio jogo;
	- [x] Movimento da bola;
- [x] Guardar/Ler pontua��es no Registo do Windows;

## Modulo "Cliente"
- [x] C�digo inicial da cliente(consola);
- [x] Interliga��o DLL impl�cita;
- [x] Suporte a memoria partilhada;
- [x] Suporte a threads;
	- [x] Envio mensagens;
	- [x] Recebe jogo;
- [x] Recolhe as teclas do jogador;

## Entrega: Meta 1
- [x] Cria��o inicial da solu��o em Visual Studio 2017 Community Edition;
- [x] Cria��o do project servidor(GUI)
- [x] Cria��o do project cliente(GUI)
- [x] Cria��o do project bridge(DLL)
- [x] Cria��o inicial do projecto para o GitHub;
- [x] Adicionei o colega como colaborador;
- [x] Definir tarefas iniciais;
- [x] Colocar as op��es Debug / Release, x86 / x64 a funcionar;
- [x] Corre��o dos projectos para C e devidas corre��es;
- [x] Diagramas de arquitectura;
- [x] Problema do unicode resolvido, aparentemente quando se coloca no GitHub muda a codifica��o dos ficheiro, solu��o...
- [x] Entrega meta1 em modo release x86 e x64 com c�digo retirado do github (fazer release no github com os bin�rios);
- [x] O README.md foi apenas actualizado/organizador depois da entrega desta meta;

# NOTAS da Meta 1
* fazer com que varios cientes n�o acedam ao servidor...
* mudar as fun��es de comunica��o para a DLL...
* n�o esquecer de ver o waitable...

# Meta 2 (Final)

## NOTAS da Meta 1:
- [ ] fazer com que varios cientes n�o acedam ao servidor...
- [x] mudar as fun��es de comunica��o para a DLL...
- [ ] n�o esquecer de ver o waitable...

## Modulo (DDL) "Bridge" 
- [x] Estrutura de dados; (Em progresso!!);
- [ ] Fun��es para zonas de memoria partilhada;
	- [x] Zona de Mensagens;
	- [x] Zona do Jogo;
- [ ] Fun��es a implementar;
	- [ ] Login;
	- [x] RecebeJogo(ReceiveBroadcast);
	- [x] EnviaMensagem (SendMessage);
	- [x] RecebeMensagem (ReceiveMessage);
- [ ] Corre��es das notas da meta 1 (em progresso);

## Modulo "Servidor"
- [x] Suporte a threads;
	- [x] Recebe mensagens;
	- [x] Envio jogo;
	- [x] Movimento da bola;
	- [ ] Gerir o movimento dos brindes;
	- [x] Gerir o movimento ds(s) bola(s);
	- [ ] Pelo uma para gerir os jogadores;
- [x] Guardar/Ler pontua��es no Registo do Windows;
- [ ] Corre��es das notas da meta 1 (em progresso);
- [ ] Ler ficheiro de configura��o;
- [ ] Adiconar brindes;

## Modulo "Cliente"
- [x] Novo projecto feito para o cliente em WDA;
- [x] Colocar as op��es Debug / Release, x86 / x64 a funcionar;
- [x] Interliga��o DLL impl�cita;
- [ ] Corre��es das notas da meta 1 (em progresso);
- [ ] Suporte a memoria partilhada;
- [ ] Suporte a named pipes;
- [x] Suporte a threads;
	- [x] Envio mensagens;
	- [x] Recebe jogo;
	- [ ] mostrar a informa��o do jogo?;
	- [x] Recolhe as teclas do jogador?;
- [x] Suporte ao WDA;
	- [x] Menu adicionado com dialogs de Login, Configura��es e Sobre;
	- [x] No cliente foram usado no menu os atalhos do teclado (com o uso de Acelaradores);
	- [ ] Melhorar as fun��es de eventos, colocar apenas uma fun��o para tratar os dialogs do menu e outro sendo o trataEventos;
	- [ ] Colocar o Dialog de Login a funcionar;
	- [ ] Colocar o Dialog de configura��es a funcionar;
	- [ ] Dialog Sobre feito;
		- [ ] Apenas falta abrir o link do github com o Syslink Control;
- [ ] Colocar a bola a funcionar;
- [ ] Login a funcionar (n�o � necess�rio password);
- [ ] Icons WDA;

## Modulos:

### Caracteristicas:
* Bola;
* Barreira;
* Tijolo;
	* Normal;
	* Reistente;
	* M�gico;
* Brinde;
	* Speed-up;
	* Slow-down;
	* Vida-extra;
	* Triple;
	* Outros;

### Ciclo de vida (ver bem no enunciado):
* Cria��o do Jogo;
* Associa��o ao jogo;
* In�cio do jogo;
* Decorrer do jogo;
* Final do jogo;

## Entrega: Meta 2 (Final)

- [x] Colocar as op��es Debug / Release, x86 / x64 a funcionar;
- [ ] Problema do unicode resolvido, aparentemente quando se coloca no GitHub muda a codifica��o dos ficheiro, solu��o...
- [ ] Melhorar os diagramas;
- [ ] A resolus�o para o problema do encoding dos ficheiros;
- [ ] Entrega final em modo release x86 e x64 com c�digo retirado do github(fazer release no github com os bin�rios);

# Outros
- [x] Suporte x86 / x64;
- [x] modo debug em ambas as arquiteturas;
- [ ] Mudar ficheiros para .c; -> n�o � possivel de momento devido ao uso da DLL ter fun��es com elementos de cpp;

## Extras
- [x] No cliente foram usado no menu os atalhos do teclado (com o uso de Acelaradores); 
- [ ] Adicionar comunica��o por TCP/IP ou UDP