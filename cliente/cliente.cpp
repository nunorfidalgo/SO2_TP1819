# Trabalho Prático de Sistema Operativos 2 2018 / 2019 - ISEC

## Nome do trabalho: Clone Arknoid/Breakout
* Desenvolvido em Visual Studio 2017 / 2019 Community Edition;
*Comentários e código em PT - PT;

## Breve descrição:
-Implementação de um jogo estilo Arknoid / Breakout
- Jogo divido por servidor e cliente com uma DLL(bridge) com todas as implementações da comunição entre o servidor e cliente;
-No servidor temos toda a mecânica de jogo;
-Cliente tem apenas a cofiguração de teclas, envio de nome do jogador e tem de detetar se está em modo local(memoria partilhada) ou em modo remoto(named pipes)


## Tecnologias
* Threads;
*Mutex, Events, Semáforos;
*Named Pipes;
*Win32 API
* Windows GUI;

# Entregas
- [x] Entrega meta1, com código retirado do github(desta forma o projecto fica o mais limpo possível e sem o "lixo" dos projetos compilados);
-[] Entrega final em modo release x86 e x64 com código retirado do github(fazer realesa no github com os binários);

# Para Fazer

## Meta 1
- [x] Criação inicial da solução em Visual Studio 2017 Community Edition;
-[x] Criação do project servidor(GUI)
- [x] Criação do project cliente(GUI)
- [x] Criação do projecto gateway(DMD)
- [x] Criação do project bridge(DLL)
- [x] Criação inicial do projecto para o GitHub;
-[x] Adicionei colaborador;
-[x] Definir tarefas iniciais;
-[x] Colocar as opções Debug / Release, x86 / x64 a funcionar;
-[x] Correções nos projectos;

## Versão final
- [x] Correção dos projectos para C e devidas correções;
-[] Diagramas de arquitectura;

## Extras
TODO

# Outros
- [] suporta x86 / x64;
-[] modo debug em ambas as arquiteturas;

## Modulo "Bridge""
- [x] Código inicial da bridge(DDL) :
	-[x] Livraria DLL;
-[] Dados de jogo;
-[] Funções para zonas de memoria partilhada;
-[] Mensagens;
-[] Funções para zona de dados do jogo;
-[] Funções para zona de mensagens;

## Modulo "Servidor"
- [x] Código inicial da servidor(consola);
-[] Interligação DLL implícita;
-[] Estrutura de dados; ->Em progresso!!;

## Modulo "Cliente"
- [x] Código inicial da cliente(consola);
-[] Suporte a named pipes;
-[] Suporte a threads;
-[] Recolhe as teclas do jogador e envia - as ao jogo;

# Como jogar ?
TODO
