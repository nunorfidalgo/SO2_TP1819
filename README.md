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
* Threads, Mutex, Events, Semáforos, Named Pipes;
* Win32 API
* Windows GUI;

# Entregas
- [X] Entrega meta1, com código retirado do github(desta forma o projecto fica o mais limpo possível e sem o "lixo" dos projetos compilados);
- [X] Entrega final em modo release x86 e x64 com código retirado do github(fazer release no github com os binários);

# Para Fazer

## Meta 1
- [x] Criação inicial da solução em Visual Studio 2017 Community Edition;
- [x] Criação do project servidor(GUI)
- [x] Criação do project cliente(GUI)
- [x] Criação do project bridge(DLL)
- [x] Criação inicial do projecto para o GitHub;
- [x] Adicionei colaborador;
- [x] Definir tarefas iniciais;
- [X] Colocar as opções Debug / Release, x86 / x64 a funcionar;

## Meta 2
- [ ] O servidor tem que ler ficheiro de configuração;

## Versão final
- [ ] Correção dos projectos para C e devidas correções;
- [ ] Diagramas de arquitectura;

## Extras
- [ ] Adicionar comunicação por TCP/IP ou UDP
- [ ] Problema do unicode resolvido, aparentemente quando se colocano GitHub muda a codificação dos ficheiro, solução...

# Outros
- [X] Suporte x86 / x64;
- [X] modo debug em ambas as arquiteturas;

## Modulo "Bridge""
- [x] Código inicial da bridge(DDL);
- [X] Dados de jogo;
- [ ] Funções para zonas de memoria partilhada;

## Modulo "Servidor"
- [x] Código inicial da servidor(consola);
- [x] Interligação DLL implícita;
- [X] Estrutura de dados; (Em progresso!!);
- [X] Suporte a threads;
- [X] Suporte a memoria partilhada;
- [X] Protegido de forma a executarmos o servidor em varias instancias;

## Modulo "Cliente"
- [x] Código inicial da cliente(consola);
- [x] Interligação DLL implícita;
- [X] Suporte a memoria partilhada;
- [X] Suporte a threads;
- [X] Recolhe as teclas do jogador;
- [ ] Suporte a named pipes;

# NOTAS da Meta 1
* fazer com que varios cientes não acedam ao servidor...
* mudar as funções de comunicação para a DLL...
* não esquecer de ver o waitable...
