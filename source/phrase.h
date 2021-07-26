#ifndef PHRASE_H
#define PHRASE_H

#include <iostream>
#include <string>
#include <bits/stdc++.h>

#include "clickable.h"


/*

class Pharase
-> Classe feita para palavras, com todas as suas organizações.


VARIÁVEIS PÚBLICAS:
- sf::Text text -> Tem basicamente tudo sobre o texto, pode ser alterado com tudo.
- sf::Font font -> Serve para mudar a fonte do texto.

FUNÇÕES PÚBLICAS:
- Phrase -> É o construtor da classe Phrase, seta inicialmente tudo o que será necessário, para logo em seguida colocar a fonte.
- bool setFont -> Tem como parâmetro o caminho até o arquivo, onde tenta aplicar essa fonte para o texto.
- int isHovering () -> Essa função é para ver se o mouse está em cima de alguma coisa, para fazer o click no local certo.

*/
class Phrase: public Clickable, public sf::Text{

    private:
        sf::Font* font;
        bool hovering;

    public:
        Phrase(sf::Font* font = NULL, std::string phrase = "", int size = 10, sf::Color color = sf::Color::White, sf::Vector2f position = {0.0f, 0.0f});
        void draw(sf::RenderWindow* window);
        void setLoadedFont(sf::Font* font);
};

#endif /* PHRASE_H */
