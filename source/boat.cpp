#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <bits/stdc++.h>

#include "boat.h"
#include "sprites.h"

#define BOATXRIGHT 1032
#define BOATXLEFT 500
#define BOATVELOCITY 4
#define BOATY 900
#define BOATLEFT 1 //O barco no lado esqurdo vale 1;
#define BOATRIGHT 2 //O barco no lado direito vale 2;
#define NUMBCHARS 6 //Era 6;

#define XAXISBOATDISTANCE 532

class Character;


//-------------------------------------------------------- BOAT ---------------------------------------------------------------------------

/*

Boat::Boat(bool isOnTheLeft, int quantChar, sf::Vector2f scale, sf::Vector2f position)

    Esse construtor serve para iniciar todas as variáveis e poupar código no jogo.cpp.

@param bool isOnTheLeft -> Onde está localizado o barco, se é no lado true (esquerdo) ou no lado false (direito).
@param int quantChar -> Quantos persongens estão em cima do barco atualmente.
@param sf::Vector2f scale -> Qual a escala do barco.
@param sf::Vector2f position -> Onde é a posição inicial do barco.
@return

*/
Boat::Boat(sf::Texture* texture, bool isOnTheLeft, int quantChar, sf::Vector2f scale, sf::Vector2f position): sf::Sprite(), Clickable()
{
    if(!texture)
        printf("WARNING: no texture set!\n");
    setTexture(*texture);

    this->isOnTheLeft = isOnTheLeft;
    this->quantChar = quantChar;
    moving = false;

    setScale(scale);
    setPosition(position);

    //brightsprite.setScale(scale);
    //brightsprite.setPosition(position);

    //bright = false;

    setClickBox(getGlobalBounds());

    xfinal = 0;
    xinitial = 0;
    speed = 0;
}

/*

void Boat::moveBoat ()

    A função moveBoat () tem o objetivo único de mover o barco para o outro lado.

@param
@return

*/
void Boat::moveBoat()
{
    if (isOnTheLeft == false) {
        xinitial = BOATXRIGHT; //Setando as configurações para o movimento do barco;
        xfinal = BOATXLEFT;

        speed = -BOATVELOCITY; //Velocidade que o barco andará.
        isOnTheLeft = true; //Informando que o lado foi trocado;
        moving = true;

        setPosition(xinitial, BOATY); //Para fazer o espelhamento do barco, é necessário essas duas ultimas linhas no código;
        setScale(0.5, 0.5); //Essa espelha o barco, e a de cima corrige a sua posição;
        setClickBox(getGlobalBounds());

        //brightsprite.setPosition(xinitial, BOATY);
        //brightsprite.setScale(0.5, 0.5);
    }
    else{
        xinitial = BOATXLEFT; //Colocando outras configurações caso ele esteja do lado direito;
        xfinal = BOATXRIGHT + getGlobalBounds().width;

        speed = BOATVELOCITY;  
        isOnTheLeft = false;  //Informando que o lado foi trocado;
        moving = true;
                            
        setPosition(xinitial + getGlobalBounds().width, BOATY); //Do mesmo jeito que na ida para o lado esquerdo, precisa dessas duas linhas;
        setScale(-0.5, 0.5); //A primeira corrige a posição do x, e a segunda espelha o barco para ir em sentido da volta;
        setClickBox(getGlobalBounds());
        //brightsprite.setPosition(xinitial + sprite.getGlobalBounds().width, BOATY);
        //brightsprite.setScale(-0.5, 0.5);
    }   
}

/*

void Boat::moveBoatFreePos (std::stack<sf::Vector2f> &boatSpaces)

    Essa função move as posições do barco, faz com que no final de cada movimento do barco elas sejam atualizadas com a nova posição;

@param std::stack<sf::Vector2f> &boatSpaces -> Aqui ficam as posições livres do barco;
@return

*/
void Boat::moveBoatFreePos (std::stack<sf::Vector2f> &boatSpaces){
    int distance = -XAXISBOATDISTANCE; //Deixando pronto caso ele esteja na direita;

    std::stack<sf::Vector2f> correctedStack; //Essa é a stack que estará corrigida;
    sf::Vector2<float> vectorForChange; //Esse é o vetor corretor, onde vamos colocar o valor corrigido antes de colocar na stack corrigida;

    if (isOnTheLeft) //Aqui ta corrigindo para diferenciar as distâncias, pois para a direita ele move positivamente;
        distance = -distance;

    while(!boatSpaces.empty()){ //Enquanto o barco não está vazio;
        vectorForChange = boatSpaces.top(); //Coloca no vetor de mudança, para colocar a distância nova na posição, que é feito na linha abaixo;
        vectorForChange.x -= distance;

        correctedStack.push(vectorForChange); //Aqui coloca tudo na stack corrigida;

        boatSpaces.pop(); //E tira esse posição do barco, pois agora ela está atualizada;
    }

    while (!correctedStack.empty()) { //Esse loop serve basicamente para tirar os elementos da corrigida e levar para a boatSpaces, onde estará atualizada;
        boatSpaces.push(correctedStack.top()); 

        correctedStack.pop();
    }
}

void Boat::setLoadedTexture (sf::Texture* loadedTexture){
    if(loadedTexture)
        setTexture(*loadedTexture);
}

void Boat::setBright(bool bright){
    if(bright)
        setColor(sf::Color::Blue);
    else
        setColor(sf::Color::White);
}

bool Boat::isOnLeft(){
    return isOnTheLeft;
}

//-----------------------------------------------------------------------------------------------------------------------------------------