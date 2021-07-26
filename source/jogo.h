#ifndef JOGO_H
#define JOGO_H

#include <iostream>
#include "graphicsManager.h"
#include "eventsManager.h"

#include "gamedata.h"

#define SLOWNESS 10000 //Lentidão da tela, a velocidade em que ela muda cada frame;
#define DISTANCE 1.7 //A distância que cada frame percorre (não são dados reais);
#define ENDX 3840 //Em qual lugar é finalizado a textura;
#define ENDY 0 //Em qual lugar é iniciado e finalizado a textura no eixo Y (constante);
#define XSTEXTURE 1920  //Qual o tamanho do eixo X de um frame completo na textura;
#define YSTEXTURE 1080 //O tamanho no eixo Y de um frame inteiro;

#define SCALEPRIEST sf::Vector2f(0.32, 0.32) //Tamanho da sprite do padre;
#define SCALECANNIBAL sf::Vector2f(0.385, 0.385) //Tamanho da sprite do canibal;
#define SCALEBOAT sf::Vector2f(0.5, 0.5) //Tamanho da sprite do barco; 
#define LEFTSIDE 0 //O lado esquerdo vale como 0;
#define BOATLEFTSIDE 1 //O barco no lado esqurdo vale 1;
#define BOATRIGHTSIDE 2 //O barco no lado direito vale 2;
#define RIGHTSIDE 3 //Quando está no lado direito, vale 3;
#define BOATXRIGHT 1032 //A posição X inicial do barco é essa, no lado direito;
#define BOATY 900 //Essa é a posição fixa do Y, não varia em nenhum momento;

#define CONTINUE 0
#define LOSE 1
#define WIN 2

#define TIMEFORANIMATION 1.5
#define XFINALATTEMPTS 700
#define XFINALMOVES 705
#define XFINALTIME 704.5
#define XFINALTOTALMOVES 704

/*

class Jogo
-> Classe principal do jogo, com TODAS as informações principais.

VARIÁVEIS PÚBLICAS:
- sf::RenderWindow window -> Instancia a janela, coloca todas as suas configurações para ser usado por todo o jogo.
- sf::Event event -> Serve para o tratamento de eventos, ele foi colocado dentro da struct para poder ser utilizado com mais facilidade.


FUNÇÕES PÚBLICAS:
- int mainMenu () -> O motivo principal é o mesmo do nome, serve para fazer o menu de uma forma mais organizada, tendo todos os parâmentros
dentro da classe Jogo.
- int jogar () -> Essa função é a principal do jogo, pelo menos onde é chamado e organizado todas as verificações do jogo.
- bool startScreen () -> Essa função tem como objetivo montar uma tela inicial, para preparar o jogador do início do jogo.
- void gameWinScreen (...) -> Função com objetivo de mostrar a vitória ao jogador, com todos os seus dados necessários.

*/

class Jogo {
    public:
        sf::RenderWindow window;

        sf::View mainView;
        GraphicsManager gameGraphicsManager;
        EventsManager gameEventsManager;
        float displayWidth, displayHeight;

        Character** characters;
        int charactersPerType;

        Jogo();
        ~Jogo();
        int mainMenu();
        int start();
        int startScreen ();
        void gameWinScreen (Character** characters, Boat boat, sf::Sprite background, sf::Sprite whiteWindowOption, GameData* gameData);
        void logDisplayScreen(Character** characters, Boat boat, sf::Sprite background, GameData* gameData);
        void gameOverScreen (Character** characters, Boat boat, sf::Sprite background);
        void instructions();
};

#endif /* JOGO_H */
