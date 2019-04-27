# Trabalho Prático de Sistema Operativos 2 2018 / 2019 - ISEC

## Nome do trabalho: Clone Arknoid/Breakout
* Desenvolvido em Visual Studio 2017 / 2019 Community Edition;
* Comentários e código em PT-PT;

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
- [x] Criação inicial da solução em Visual Studio 2017 Community Edition;
- [x] Criação do project servidor(GUI)
- [x] Criação do project cliente(GUI)
- [x] Criação do project bridge(DLL)
- [x] Criação inicial do projecto para o GitHub;
- [x] Adicionei colaborador;
- [x] Definir tarefas iniciais;
- [ ] Colocar as opções Debug / Release, x86 / x64 a funcionar;

## Versão final
- [ ] Correção dos projectos para C e devidas correções;
- [ ] Diagramas de arquitectura;

## Extras
- [ ] Adicionar comunicação por TCP/IP ou UDP

# Outros
- [ ] Suporte x86 / x64;
- [ ] modo debug em ambas as arquiteturas;

## Modulo "Bridge""
- [x] Código inicial da bridge(DDL) :
	- [x] Livraria DLL;
- [ ] Dados de jogo;
- [ ] Funções para zonas de memoria partilhada;

## Modulo "Servidor"
- [x] Código inicial da servidor(consola);
- [x] Interligação DLL implícita;
- [ ] Estrutura de dados; (Em progresso!!);
- [ ] Suporte a memoria partilhada;

## Modulo "Cliente"
- [x] Código inicial da cliente(consola);
- [ ] Suporte a memoria partilhada;
- [ ] Suporte a threads;
- [ ] Suporte a named pipes;
- [ ] Recolhe as teclas do jogador;

# Como jogar?
TODO
