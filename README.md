# Trabalho Prático de Sistema Operativos 2 2018 / 2019 - ISEC

## Nome do trabalho: Clone Arknoid/Breakout
* Desenvolvido em Visual Studio 2017 / 2019 Community Edition;
* Comentários e código em PT-PT (o mais poível);

## Alunos
* Nuno Fidalgo [21140369]
* Cláudio Melo [21170023]

## Breve descrição:
- Implementação de um jogo estilo Arknoid / Breakout
- Jogo divido por servidor e cliente com uma DLL(bridge) que implementa as comunições entre o servidor e cliente;
- No servidor vamos ter toda a mecânica de jogo;
- Cliente tem apenas a configuração de teclas, envio de nome do jogador e tem de detetar se está em modo local(memoria partilhada) 
ou em modo remoto(named pipes) (um belo extra seria colcoar a comunicar por TCP/IP ou UDP).

## Tecnologias
* Win32 API
* Threads, Mutex, Events, Semáforos, Named Pipes;
* Windows GUI (WDA);
* Arquitetura: cliente/servidor;

# Meta 1

## Modulo (DDL) "Bridge" 
- [x] Código inicial da bridge(DDL);
- [x] Estrutura de dados; (Em progresso!!);
- [x] Funções para zonas de memoria partilhada;
	- [x] Zona de Mensagens;
	- [x] Zona do Jogo;
- [x] Funções a implementar;
	- [x] Login;
	- [x] RecebeJogo(ReceiveBroadcast);
	- [x] EnviaMensagem (SendMessage);
	- [x] RecebeMensagem (ReceiveMessage);

## Modulo "Servidor"
- [x] Código inicial da servidor(consola);
- [x] Interligação DLL implícita;
- [x] Suporte a memoria partilhada;
- [x] Protegido de forma a executarmos o servidor em varias instancias;
- [x] Login... dá início ao jogo;
- [x] Suporte a threads;
	- [x] Recebe mensagens;
	- [x] Envio jogo;
	- [x] Movimento da bola;
- [x] Guardar/Ler pontuações no Registo do Windows;

## Modulo "Cliente"
- [x] Código inicial da cliente(consola);
- [x] Interligação DLL implícita;
- [x] Suporte a memoria partilhada;
- [x] Suporte a threads;
	- [x] Envio mensagens;
	- [x] Recebe jogo;
- [x] Recolhe as teclas do jogador;

## Entrega: Meta 1
- [x] Criação inicial da solução em Visual Studio 2017 Community Edition;
- [x] Criação do project servidor(GUI)
- [x] Criação do project cliente(GUI)
- [x] Criação do project bridge(DLL)
- [x] Criação inicial do projecto para o GitHub;
- [x] Adicionei o colega como colaborador;
- [x] Definir tarefas iniciais;
- [x] Colocar as opções Debug / Release, x86 / x64 a funcionar;
- [x] Correção dos projectos para C e devidas correções;
- [x] Diagramas de arquitectura;
- [x] Problema do unicode resolvido, aparentemente quando se coloca no GitHub muda a codificação dos ficheiro, solução...
- [x] Entrega meta1 em modo release x86 e x64 com código retirado do github (fazer release no github com os binários);
- [x] O README.md foi apenas actualizado/organizador depois da entrega desta meta;

# NOTAS da Meta 1
* fazer com que varios cientes não acedam ao servidor...
* mudar as funções de comunicação para a DLL...
* não esquecer de ver o waitable...

# Meta 2 (Final)

## NOTAS da Meta 1:
- [ ] fazer com que varios cientes não acedam ao servidor...
- [x] mudar as funções de comunicação para a DLL...
- [ ] não esquecer de ver o waitable...

## Modulo (DDL) "Bridge" 
- [x] Estrutura de dados; (Em progresso!!);
- [ ] Funções para zonas de memoria partilhada;
	- [x] Zona de Mensagens;
	- [x] Zona do Jogo;
- [ ] Funções a implementar;
	- [ ] Login;
	- [x] RecebeJogo(ReceiveBroadcast);
	- [x] EnviaMensagem (SendMessage);
	- [x] RecebeMensagem (ReceiveMessage);
- [ ] Correções das notas da meta 1 (em progresso);

## Modulo "Servidor"
- [x] Suporte a threads;
	- [x] Recebe mensagens;
	- [x] Envio jogo;
	- [x] Movimento da bola;
	- [ ] Gerir o movimento dos brindes;
	- [x] Gerir o movimento ds(s) bola(s);
	- [ ] Pelo uma para gerir os jogadores;
- [x] Guardar/Ler pontuações no Registo do Windows;
- [ ] Correções das notas da meta 1 (em progresso);
- [ ] Ler ficheiro de configuração;
- [ ] Adiconar brindes;

## Modulo "Cliente"
- [x] Novo projecto feito para o cliente em WDA;
- [x] Colocar as opções Debug / Release, x86 / x64 a funcionar;
- [x] Interligação DLL implícita;
- [ ] Correções das notas da meta 1 (em progresso);
- [ ] Suporte a memoria partilhada;
- [ ] Suporte a named pipes;
- [x] Suporte a threads;
	- [x] Envio mensagens;
	- [x] Recebe jogo;
	- [ ] mostrar a informação do jogo?;
	- [x] Recolhe as teclas do jogador?;
- [x] Suporte ao WDA;
	- [x] Menu adicionado com dialogs de Login, Configurações e Sobre;
	- [x] No cliente foram usado no menu os atalhos do teclado (com o uso de Acelaradores);
	- [ ] Melhorar as funções de eventos, colocar apenas uma função para tratar os dialogs do menu e outro sendo o trataEventos;
	- [ ] Colocar o Dialog de Login a funcionar;
	- [ ] Colocar o Dialog de configurações a funcionar;
	- [ ] Dialog Sobre feito;
		- [ ] Apenas falta abrir o link do github com o Syslink Control;
- [ ] Colocar a bola a funcionar;
- [ ] Login a funcionar (não é necessário password);
- [ ] Icons WDA;

## Modulos:

### Caracteristicas:
* Bola;
* Barreira;
* Tijolo;
	* Normal;
	* Reistente;
	* Mágico;
* Brinde;
	* Speed-up;
	* Slow-down;
	* Vida-extra;
	* Triple;
	* Outros;

### Ciclo de vida (ver bem no enunciado):
* Criação do Jogo;
* Associação ao jogo;
* Início do jogo;
* Decorrer do jogo;
* Final do jogo;

## Entrega: Meta 2 (Final)

- [x] Colocar as opções Debug / Release, x86 / x64 a funcionar;
- [ ] Problema do unicode resolvido, aparentemente quando se coloca no GitHub muda a codificação dos ficheiro, solução...
- [ ] Melhorar os diagramas;
- [ ] A resolusão para o problema do encoding dos ficheiros;
- [ ] Entrega final em modo release x86 e x64 com código retirado do github(fazer release no github com os binários);

# Outros
- [x] Suporte x86 / x64;
- [x] modo debug em ambas as arquiteturas;
- [ ] Mudar ficheiros para .c; -> não é possivel de momento devido ao uso da DLL ter funções com elementos de cpp;

## Extras
- [x] No cliente foram usado no menu os atalhos do teclado (com o uso de Acelaradores); 
- [ ] Adicionar comunicação por TCP/IP ou UDP