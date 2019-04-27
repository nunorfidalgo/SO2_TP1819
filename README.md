# Trabalho Pr�tico de Sistema Operativos 2 2018 / 2019 - ISEC

## Nome do trabalho: Clone Arknoid/Breakout
* Desenvolvido em Visual Studio 2017 / 2019 Community Edition;
* Coment�rios e c�digo em PT-PT;

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
* Threads;
* Mutex, Events, Sem�foros;
* Named Pipes;
* Win32 API
* Windows GUI;

# Entregas
- [ ] Entrega meta1, com c�digo retirado do github(desta forma o projecto fica o mais limpo poss�vel e sem o "lixo" dos projetos compilados);
- [ ] Entrega final em modo release x86 e x64 com c�digo retirado do github(fazer release no github com os bin�rios);

# Para Fazer

## Meta 1
- [x] Cria��o inicial da solu��o em Visual Studio 2017 Community Edition;
- [x] Cria��o do project servidor(GUI)
- [x] Cria��o do project cliente(GUI)
- [x] Cria��o do project bridge(DLL)
- [x] Cria��o inicial do projecto para o GitHub;
- [x] Adicionei colaborador;
- [x] Definir tarefas iniciais;
- [ ] Colocar as op��es Debug / Release, x86 / x64 a funcionar;

## Vers�o final
- [ ] Corre��o dos projectos para C e devidas corre��es;
- [ ] Diagramas de arquitectura;

## Extras
- [ ] Adicionar comunica��o por TCP/IP ou UDP

# Outros
- [ ] Suporte x86 / x64;
- [ ] modo debug em ambas as arquiteturas;

## Modulo "Bridge""
- [x] C�digo inicial da bridge(DDL) :
	- [x] Livraria DLL;
- [ ] Dados de jogo;
- [ ] Fun��es para zonas de memoria partilhada;

## Modulo "Servidor"
- [x] C�digo inicial da servidor(consola);
- [x] Interliga��o DLL impl�cita;
- [ ] Estrutura de dados; (Em progresso!!);
- [ ] Suporte a memoria partilhada;

## Modulo "Cliente"
- [x] C�digo inicial da cliente(consola);
- [ ] Suporte a memoria partilhada;
- [ ] Suporte a threads;
- [ ] Suporte a named pipes;
- [ ] Recolhe as teclas do jogador;

# Como jogar?
TODO
