# Trabalho Pr�tico de Sistema Operativos 2 2018 / 2019 - ISEC

## Nome do trabalho: Clone Arknoid/Breakout
* Desenvolvido em Visual Studio 2017 / 2019 Community Edition;
* Coment�rios e c�digo em PT-PT;

## Breve descri��o:
- Implementa��o de um jogo estilo Arknoid / Breakout
- Jogo divido por servidor e cliente com uma DLL(bridge) com todas as implementa��es da comuni��o entre o servidor e cliente;
- No servidor temos toda a mec�nica de jogo;
- Cliente tem apenas a configura��o de teclas, envio de nome do jogador e tem de detetar se est� em modo local(memoria partilhada) 
ou em modo remoto(named pipes)


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
- [ ] Cria��o inicial da solu��o em Visual Studio 2017 Community Edition;
- [ ] Cria��o do project servidor(GUI)
- [ ] Cria��o do project cliente(GUI)
- [ ] Cria��o do project bridge(DLL)
- [ ] Cria��o inicial do projecto para o GitHub;
- [ ] Adicionei colaborador;
- [ ] Definir tarefas iniciais;
- [ ] Colocar as op��es Debug / Release, x86 / x64 a funcionar;
- [ ] Corre��es nos projectos;

## Vers�o final
- [ ] Corre��o dos projectos para C e devidas corre��es;
- [ ] Diagramas de arquitectura;

## Extras
TODO

# Outros
- [ ] Suporte x86 / x64;
- [ ] modo debug em ambas as arquiteturas;

## Modulo "Bridge""
- [ ] C�digo inicial da bridge(DDL) :
	- [ ] Livraria DLL;
- [ ] Dados de jogo;
- [ ] Fun��es para zonas de memoria partilhada;
- [ ] Mensagens;
- [ ] Fun��es para zona de dados do jogo;
- [ ] Fun��es para zona de mensagens;

## Modulo "Servidor"
- [ ] C�digo inicial da servidor(consola);
- [ ] Interliga��o DLL impl�cita;
- [ ] Estrutura de dados; (Em progresso!!)

## Modulo "Cliente"
- [ ] C�digo inicial da cliente(consola);
- [ ] Suporte a named pipes;
- [ ] Suporte a threads;
- [ ] Recolhe as teclas do jogador e envia - as ao jogo;

# Como jogar ?
TODO
