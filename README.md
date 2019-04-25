# Trabalho Prático de Sistema Operativos 2 2018 / 2019 - ISEC

## Nome do trabalho: Clone Arknoid/Breakout
* Desenvolvido em Visual Studio 2017 / 2019 Community Edition;
* Comentários e código em PT-PT;

## Breve descrição:
- Implementação de um jogo estilo Arknoid / Breakout
- Jogo divido por servidor e cliente com uma DLL(bridge) com todas as implementações da comunição entre o servidor e cliente;
- No servidor temos toda a mecânica de jogo;
- Cliente tem apenas a configuração de teclas, envio de nome do jogador e tem de detetar se está em modo local(memoria partilhada) 
ou em modo remoto(named pipes)


## Tecnologias
* Threads;
* Mutex, Events, Semáforos;
* Named Pipes;
* Win32 API
* Windows GUI;

# Entregas
- [ ] Entrega meta1, com código retirado do github(desta forma o projecto fica o mais limpo possível e sem o "lixo" dos projetos compilados);
- [ ] Entrega final em modo release x86 e x64 com código retirado do github(fazer release no github com os binários);

# Para Fazer

## Meta 1
- [ ] Criação inicial da solução em Visual Studio 2017 Community Edition;
- [ ] Criação do project servidor(GUI)
- [ ] Criação do project cliente(GUI)
- [ ] Criação do project bridge(DLL)
- [ ] Criação inicial do projecto para o GitHub;
- [ ] Adicionei colaborador;
- [ ] Definir tarefas iniciais;
- [ ] Colocar as opções Debug / Release, x86 / x64 a funcionar;
- [ ] Correções nos projectos;

## Versão final
- [ ] Correção dos projectos para C e devidas correções;
- [ ] Diagramas de arquitectura;

## Extras
TODO

# Outros
- [ ] Suporte x86 / x64;
- [ ] modo debug em ambas as arquiteturas;

## Modulo "Bridge""
- [ ] Código inicial da bridge(DDL) :
	- [ ] Livraria DLL;
- [ ] Dados de jogo;
- [ ] Funções para zonas de memoria partilhada;
- [ ] Mensagens;
- [ ] Funções para zona de dados do jogo;
- [ ] Funções para zona de mensagens;

## Modulo "Servidor"
- [ ] Código inicial da servidor(consola);
- [ ] Interligação DLL implícita;
- [ ] Estrutura de dados; (Em progresso!!)

## Modulo "Cliente"
- [ ] Código inicial da cliente(consola);
- [ ] Suporte a named pipes;
- [ ] Suporte a threads;
- [ ] Recolhe as teclas do jogador e envia - as ao jogo;

# Como jogar ?
TODO
