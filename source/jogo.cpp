#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <bits/stdc++.h>

#include "jogo.h"
#include "phrase.h"
#include "boat.h"
#include "character.h"
#include "gamedata.h"


sf::Color darkBlue (0,72,186); //Colocando uma cor mais harmoniosa no jogo;
sf::Color brown (150, 75, 0); //Setando a cor para utilizala no men;

//--------------------------------------------------------- JOGO --------------------------------------------------------------------------
Jogo::Jogo(): window(sf::VideoMode(1200,600), "Missionarios e Canibais", sf::Style::Default),
              mainView(sf::FloatRect(0, 0, WIDTH, HEIGHT)),
              gameEventsManager(&window),
              gameGraphicsManager(&window){

    window.setFramerateLimit(60); //Diminuindo um pouco o processamento do computador, que para alguns computadores, acaba sendo dificil processar muitos quadros;
    //mainView.setViewport(sf::FloatRect(0,0, window.getSize().x/WIDTH, window.getSize().y/HEIGHT));
    window.setView(mainView);

}

Jogo::~Jogo(){
    for(int i = 0; i < charactersPerType; i++)
        delete characters[i];
}

/*
int Jogo::mainMenu ()
    O motivo principal é o mesmo do nome, serve para fazer o menu de uma forma mais organizada, tendo todos os parâmentros
dentro da classe Jogo.
@param
@return int
*/
int Jogo::mainMenu () {

    sf::Clock clock; //Relógio auxiliador da movimentação da tela no menu inicial;
    sf::Clock secondClock;

    int currentX = 0; //Posição atual da textura, no eixo X;
    bool loading = true;
    bool lightning = true;

    sf::Mouse mouse; //Declarando o mouse, para pegar as suas posições no futuro;

    Phrase miss (gameGraphicsManager.loadFont("../assets/FFF_Tusj.ttf"), "Missionarios", 70, brown, sf::Vector2f(WIDTH * 4 / 17, HEIGHT / 9)); //Colocando a frase título;
    Phrase e (gameGraphicsManager.loadFont("../assets/Vegan.ttf"), "e", 70, sf::Color::Yellow, sf::Vector2f(WIDTH * 4 / 10, (HEIGHT / 9) + 45)); //Colocando um "e", que pertence ao menu;
    Phrase cani (gameGraphicsManager.loadFont("../assets/Nightmare.ttf"), "CANIBAIS", 70, sf::Color::Blue, sf::Vector2f(WIDTH * 4 / 10, (HEIGHT / 9) + 100)); //Colocando a ultima peça faltante, o canibais;

    Phrase jogar (gameGraphicsManager.loadFont("../assets/Pixel.ttf"), "Jogar", 65, sf::Color::Yellow, sf::Vector2f (WIDTH * 4 / 9, HEIGHT / 2)); //Colocando as três opções abaixo, que podem ser escolhidasd no menu;
    Phrase comojogar (gameGraphicsManager.loadFont("../assets/Pixel.ttf"), "Como jogar", 65, sf::Color:: Yellow, sf::Vector2f (WIDTH * 4 / 9.9, HEIGHT * 2 / 3.065));
    Phrase sair (gameGraphicsManager.loadFont("../assets/Pixel.ttf"), "Sair", 65, sf::Color::Yellow, sf::Vector2f (WIDTH * 4 / 8.7, HEIGHT * 2 / 2.5));
    gameEventsManager.addClickable(static_cast<Clickable*>(&jogar));
    gameEventsManager.addClickable(static_cast<Clickable*>(&sair));
    Phrase victornetto (gameGraphicsManager.loadFont("../assets/Amilya.ttf"), "POR: Victor Netto", 25, sf::Color::Yellow, sf::Vector2f(WIDTH * 0.14, HEIGHT * 0.93));
    sf::Sprite fundo(*gameGraphicsManager.loadTexture("../assets/Background.png"));

    sf::Sprite biblia(*gameGraphicsManager.loadTexture("../assets/biblia.png"));
    biblia.setPosition(sf::Vector2f(WIDTH / 6.2, HEIGHT / 9));
    biblia.setScale(sf::Vector2f(0.3, 0.3));

    sf::Sprite faca(*gameGraphicsManager.loadTexture("../assets/faca.png"));
    faca.setPosition(sf::Vector2f(WIDTH * 3 / 5.3, (HEIGHT / 5.3)));
    faca.setScale(sf::Vector2f(0.25, 0.25));

    sf::Sprite peteco(*gameGraphicsManager.loadTexture("../assets/LogoPETECO.png"));
    peteco.setPosition(sf::Vector2f(WIDTH * 0.05, HEIGHT * 0.92));
    peteco.setScale(sf::Vector2f(0.2, 0.2));

    sf::Sprite petecoGrande(*gameGraphicsManager.loadTexture("../assets/LogoPETECO.png"));
    petecoGrande.setPosition(sf::Vector2f(WIDTH * 0.35, HEIGHT * 0.4));
    petecoGrande.setScale(sf::Vector2f(0.8, 0.8));

    sf::SoundBuffer som;

    if (!som.loadFromFile("../assets/bigthu.ogg"))
    {
        std::cout << "\n\n @@@@@@ Error trying to access the sound." << std::endl;

        return 1;
    }

    sf::Sound raio;
    raio.setBuffer(som);
    raio.setVolume(6.0f);


    while (window.isOpen()) {//Começando o loop principal do menu;
        //if (secondClock.getElapsedTime().asSeconds() > 5.4)
        gameEventsManager.pollAll();

        
        //Tratando todas as possibilidades na hora de trocar as cores, caso tenha ou não tenha palavras.
        if (jogar.isHovering()){
            jogar.setFillColor(sf::Color::Blue);

            if(jogar.wasClicked()){
                start(); //Chama a função principal do jogo;

                if(jogar.isHovering()) //Essa verificação é infelizmente necessária para não apresentar um bug na hora de voltar;
                    jogar.setFillColor(sf::Color::Blue);
                else
                    jogar.setFillColor(sf::Color::Yellow);
            }
        }
        else
            jogar.setFillColor(sf::Color::Yellow);

        if (comojogar.isHovering())
            comojogar.setFillColor(sf::Color::Blue);
        else
            comojogar.setFillColor(sf::Color::Yellow);

        if (sair.isHovering()){
            sair.setFillColor(sf::Color::Blue);

            if (sair.wasClicked()) //Essa opção é chamada na saida, caso o botão seja apertado em cima da área de sair;
                gameEventsManager.closeWindow();
        }
        else
            sair.setFillColor(sf::Color::Yellow);

        //case sf::Event::Resized:
            //sf::FloatRect visibleArea(0, 0, event.size.width, event.size.height);
            
            // window.setView(sf::View(visibleArea));
        // break;
            

        if (secondClock.getElapsedTime().asSeconds() < 5) {
            gameGraphicsManager.draw(GET_DRAWABLE_POINTER(fundo));
            window.draw(fundo);

            gameGraphicsManager.draw(GET_DRAWABLE_POINTER(petecoGrande));
        }
        else if (secondClock.getElapsedTime().asSeconds() > 5 && secondClock.getElapsedTime().asSeconds() < 6.05) {
            gameGraphicsManager.draw(GET_DRAWABLE_POINTER(fundo));

            if (secondClock.getElapsedTime().asSeconds() > 5.675) {
                if (lightning == true) {
                    raio.play();

                    lightning = false;
                }
            }
        } 
        else{
            window.clear(sf::Color::Black); //Limpa a tela e coloca uma cor inicial;

            gameGraphicsManager.draw(GET_DRAWABLE_POINTER(fundo)); //Nessa linha e abaixo, printando os sprites;
            gameGraphicsManager.draw(GET_DRAWABLE_POINTER(biblia));
            gameGraphicsManager.draw(GET_DRAWABLE_POINTER(faca));

            gameGraphicsManager.draw(GET_DRAWABLE_POINTER(miss)); //Escreve a palavra depois de ter limpado;
            gameGraphicsManager.draw(GET_DRAWABLE_POINTER(e));
            gameGraphicsManager.draw(GET_DRAWABLE_POINTER(cani));
            gameGraphicsManager.draw(GET_DRAWABLE_POINTER(victornetto));
            gameGraphicsManager.draw(GET_DRAWABLE_POINTER(peteco));

            gameGraphicsManager.draw(GET_DRAWABLE_POINTER(jogar)); //Nessa linha e abaixo, colocando as opções do menu;
            gameGraphicsManager.draw(GET_DRAWABLE_POINTER(sair));
            gameGraphicsManager.draw(GET_DRAWABLE_POINTER(comojogar));
        }

        window.setView(mainView);
        window.display(); //Mostra novamente o que está sendo printado na tela;

        
        if (clock.getElapsedTime().asMicroseconds() > SLOWNESS) { //Fazendo aqui como o fundo irá se mover;

            if (currentX + XSTEXTURE == ENDX) { //Essa parte retorna a textura para seu ponto inicial;
                currentX = 0;
            }

            else 
                currentX += DISTANCE; //Aumenta uma constante DISTÂNCIA, que vai ser basicamente a distância entre os frames;

            clock.restart();

            fundo.setTextureRect(sf::IntRect(currentX, ENDY, XSTEXTURE, YSTEXTURE)); //Coloca a textura em seu devido lugar, atualiza todo o tempo;
        }
        gameEventsManager.isWindowClosed();
    }

    gameEventsManager.removeClickable(static_cast<Clickable*>(&jogar));
    gameEventsManager.removeClickable(static_cast<Clickable*>(&sair));

    return 0; //TODO: Futuramente, caso seja necessário essa função deve retornar algum valor;
}


/*
bool Jogo::startScreen()
    Essa função tem como objetivo montar uma tela inicial, para preparar o jogador do início do jogo.
@param
@return
*/

int Jogo::startScreen(){

    sf::Mouse mouse; //Instanciando o mouse para pegar seus movimentos;

    sf::Image white; //Colocando uma classe sf::Imagem, que serve para fazer uma mascara transparente, e deixar o fundo visualizavel;
    white.create(WIDTH, HEIGHT, sf::Color::White);
    white.createMaskFromColor(sf::Color::White, 100); //Aqui está colocando a mascara, deixando a imagem transparente;

    sf::Sprite startBackground(*gameGraphicsManager.loadTexture("../assets/espaco.png"));


    Phrase start (gameGraphicsManager.loadFont("../assets/afanan.ttf"), "Com quantos personagens deseja jogar?", 70, sf::Color::Yellow, sf::Vector2f(WIDTH * 0.31, WIDTH * 0.17)); //Colocando a frase de pergunta, para o jogador;
    
    Phrase oneSelection (gameGraphicsManager.loadFont("../assets/afanan.ttf"), "1 de cada tipo", 50, sf::Color::White, sf::Vector2f(WIDTH * 0.342, WIDTH * 0.25)); //Ou a opção de voltar ao menu;
    gameEventsManager.addClickable(GET_CLICKABLE_POINTER(oneSelection));
    Phrase twoSelection (gameGraphicsManager.loadFont("../assets/afanan.ttf"), "2 de cada tipo", 50, sf::Color::White, sf::Vector2f(WIDTH * 0.342, WIDTH * 0.34)); //Colocando a opção de iniciar o jogo;
    gameEventsManager.addClickable(GET_CLICKABLE_POINTER(twoSelection));
    Phrase threeSelection (gameGraphicsManager.loadFont("../assets/afanan.ttf"), "3 de cada tipo", 50, sf::Color::White, sf::Vector2f(WIDTH * 0.342, WIDTH * 0.43)); //Ou a opção de voltar ao menu;
    gameEventsManager.addClickable(GET_CLICKABLE_POINTER(threeSelection));
    Phrase fourSelection (gameGraphicsManager.loadFont("../assets/afanan.ttf"), "4 de cada tipo", 50, sf::Color::White, sf::Vector2f(WIDTH * 0.342, WIDTH * 0.52)); //Ou a opção de voltar ao menu;
    gameEventsManager.addClickable(GET_CLICKABLE_POINTER(fourSelection));
    

    while (window.isOpen()){
        gameEventsManager.pollAll();
        
        if (oneSelection.isHovering()){ //No mesmo caso do sim, agora trata-se da opção de voltar ao menu;
            oneSelection.setFillColor(darkBlue);

            if (oneSelection.wasClicked()){
                gameEventsManager.removeClickable(GET_CLICKABLE_POINTER(oneSelection));
                gameEventsManager.removeClickable(GET_CLICKABLE_POINTER(twoSelection));
                gameEventsManager.removeClickable(GET_CLICKABLE_POINTER(threeSelection));
                gameEventsManager.removeClickable(GET_CLICKABLE_POINTER(fourSelection));
                return 1;
            }
        }
        else
            oneSelection.setFillColor(sf::Color::White);

        if (twoSelection.isHovering()){ //Do mesmo jeito feito no menu, caso ele coloque o mouse em cima, irá mudar de cor;
            twoSelection.setFillColor(darkBlue); //Azul para opção;

            if (twoSelection.wasClicked()){ //Caso o jogador clique em cima do sim, retorna true para a função start(), onde o valor será tratado;
                gameEventsManager.removeClickable(GET_CLICKABLE_POINTER(oneSelection));
                gameEventsManager.removeClickable(GET_CLICKABLE_POINTER(twoSelection));
                gameEventsManager.removeClickable(GET_CLICKABLE_POINTER(threeSelection));
                gameEventsManager.removeClickable(GET_CLICKABLE_POINTER(fourSelection));
                return 2;
            };
        }
        else
            twoSelection.setFillColor(sf::Color::White); //Branco para mouse fora;


        if (threeSelection.isHovering()){ //No mesmo caso do sim, agora trata-se da opção de voltar ao menu;
            threeSelection.setFillColor(darkBlue);

            if (threeSelection.wasClicked()){ //Caso contrário o jogador será recolocado no menu;
                gameEventsManager.removeClickable(GET_CLICKABLE_POINTER(oneSelection));
                gameEventsManager.removeClickable(GET_CLICKABLE_POINTER(twoSelection));
                gameEventsManager.removeClickable(GET_CLICKABLE_POINTER(threeSelection));
                gameEventsManager.removeClickable(GET_CLICKABLE_POINTER(fourSelection));
                return 3;
            }
        }
        else
            threeSelection.setFillColor(sf::Color::White);

        if (fourSelection.isHovering()){ //No mesmo caso do sim, agora trata-se da opção de voltar ao menu;
            fourSelection.setFillColor(darkBlue);

            if (fourSelection.wasClicked()){ //Caso contrário o jogador será recolocado no menu;
                gameEventsManager.removeClickable(GET_CLICKABLE_POINTER(oneSelection));
                gameEventsManager.removeClickable(GET_CLICKABLE_POINTER(twoSelection));
                gameEventsManager.removeClickable(GET_CLICKABLE_POINTER(threeSelection));
                gameEventsManager.removeClickable(GET_CLICKABLE_POINTER(fourSelection));
                return 4;
            }
        }
        else
            fourSelection.setFillColor(sf::Color::White);
        
        

        if(gameEventsManager.isWindowClosed()) //Caso fechar a janela;
            return 0; //Retorna "sucesso";   
        

        window.clear(sf::Color::Black);

        //Printando as sprites e textos que foram anunciadas acima;
        gameGraphicsManager.draw(GET_DRAWABLE_POINTER(startBackground)); 
        //gameGraphicsManager.draw(GET_DRAWABLE_POINTER(whiteWindow));
        gameGraphicsManager.draw(GET_DRAWABLE_POINTER(start));
        gameGraphicsManager.draw(GET_DRAWABLE_POINTER(oneSelection));
        gameGraphicsManager.draw(GET_DRAWABLE_POINTER(twoSelection));
        gameGraphicsManager.draw(GET_DRAWABLE_POINTER(threeSelection));
        gameGraphicsManager.draw(GET_DRAWABLE_POINTER(fourSelection));

        window.display(); //Mostrando todas as mudanças que foram feitas;
    }
}

/*
int Jogo::start()
    Essa função é a principal do jogo, pelo menos onde é chamado e organizado todas as verificações do jogo.
@param
@return int
*/
int Jogo::start () {

    charactersPerType = startScreen(); //Atribuindo a variavel escolha qual foi a escolha dele no 2o menu;

    characters = new Character*[charactersPerType*2];

    for(int i = 0; i < charactersPerType; i++){
        characters[i] = new Character(gameGraphicsManager.loadTexture("../assets/padre1.png"), Character::priest, RIGHTSIDE, sf::Vector2f(1200, 180), SCALEPRIEST);
        gameEventsManager.addClickable(GET_CLICKABLE_POINTER(*(characters[i])));
    }
    for(int i = charactersPerType; i < 2*charactersPerType; i++){
        characters[i] = new Character(gameGraphicsManager.loadTexture("../assets/canibal1.png"), Character::cannibal, RIGHTSIDE, sf::Vector2f(1650, 160), SCALECANNIBAL);
        gameEventsManager.addClickable(GET_CLICKABLE_POINTER(*(characters[i])));
    }


    int xinitial, xfinal, side;
    bool isCharAllFalse; //Essa variável é para saber se o mouse não está em cima de nenhum personagem, para auxiliar no barco;
    int winOrLose; //Verificação utilizada para ver se o jogador perdeu, para evitar algumas chamadas extras na função;

    GameData gameData(&gameGraphicsManager, &gameEventsManager, charactersPerType);

    std::stack<sf::Vector2f> leftSpaces;
    std::stack<sf::Vector2f> rightSpaces;
    std::stack<sf::Vector2f> boatSpaces;

    gameData.initializeStacks(leftSpaces, boatSpaces, rightSpaces);
    gameData.submitCurrentGameState();

    sf::Mouse mouse; //Variável para pegar os movimentos do mouse;

    Phrase tempo (gameGraphicsManager.loadFont("../assets/afanan.ttf"), "Tempo (seg): ", 50, darkBlue, sf::Vector2f(WIDTH * 0.7, HEIGHT * 0.01));
    Phrase time (gameGraphicsManager.loadFont("../assets/afanan.ttf"), "0", 50, sf::Color::Yellow, sf::Vector2f(WIDTH * 0.83, HEIGHT * 0.01)); //Instânciando um objeto de tempo, onde será atualizado sempre que mudar os segundos;

    Phrase movimentos(gameGraphicsManager.loadFont("../assets/afanan.ttf"), "Movimentos: ", 50, darkBlue, sf::Vector2f(WIDTH * 0.45, HEIGHT * 0.01));
    Phrase movements (gameGraphicsManager.loadFont("../assets/afanan.ttf"), "0", 50, sf::Color::Yellow, sf::Vector2f(WIDTH * 0.58, HEIGHT * 0.01)); //Esses dois movimentos são a quantidade de movimentos que o jogador realizou;

    Phrase movimentosTotais(gameGraphicsManager.loadFont("../assets/afanan.ttf"), "Total de Mov.: ", 50, darkBlue, sf::Vector2f(WIDTH * 0.45, HEIGHT * 0.08));
    Phrase totalMovements(gameGraphicsManager.loadFont("../assets/afanan.ttf"), "0", 50, sf::Color::Yellow, sf::Vector2f(WIDTH * 0.60, HEIGHT * 0.08));

    Phrase tentativas(gameGraphicsManager.loadFont("../assets/afanan.ttf"), "Tentativas: ", 50, darkBlue, sf::Vector2f(WIDTH * 0.20, HEIGHT * 0.01));
    Phrase attempts(gameGraphicsManager.loadFont("../assets/afanan.ttf"), "0", 50, sf::Color::Yellow, sf::Vector2f(WIDTH * 0.33, HEIGHT * 0.01)); //Aqui são as tentativas, cada vez que o jogador perde soma-se 1 na quantidade;

    sf::Sprite background(*gameGraphicsManager.loadTexture("../assets/backgame.png")); //Iniciando o sprite que carregará o fundo;

    //Character character[NUMBEROFCHARS]; //Inicializando as variáveis de todos os personagens do jogo.
    Boat boat (gameGraphicsManager.loadTexture("../assets/barco.png"), false, 0, SCALEBOAT, sf::Vector2f(BOATXRIGHT, BOATY));
    gameEventsManager.addClickable(GET_CLICKABLE_POINTER(boat));

    for(int i = 0; i < charactersPerType*2; i++){
        characters[i]->setPosition(rightSpaces.top());
        rightSpaces.pop();
        characters[i]->setLocation(RIGHTSIDE);
        characters[i]->setClickBox(characters[i]->getGlobalBounds());
    }

    sf::Image whiteOption; //Colocando uma classe sf::Imagem, que serve para fazer uma mascara transparente, e deixar o fundo visualizavel;
    whiteOption.create(WIDTH, HEIGHT, sf::Color::White);
    whiteOption.createMaskFromColor(sf::Color::White, 100); //Aqui está colocando a mascara, deixando a imagem transparente;

    sf::Sprite whiteWindowOption;// (sf::Vector2f(0.3, 0.15), sf::Vector2f(WIDTH * 0.34, HEIGHT * 0.4)); //Dessa vez instanciando a sprite que será colocada a sf::Image transparente;
    whiteWindowOption.setScale(sf::Vector2f(0.3, 0.15));

    sf::Texture whiteOptionTexture;
    whiteOptionTexture.loadFromImage(whiteOption); //Nessa parte, estamos colocando a textura futura da sprite, e nesse caso colocamos a imagem transparente;
    whiteWindowOption.setTexture(whiteOptionTexture); //Aplicando a textura transparente no sprite;

    gameData.gameTime.restart(); //Restartando o relógio por causa do 2o menu;

    while (window.isOpen()){ //Enquanto a janela está aberta;
    
            gameEventsManager.pollAll();   
            isCharAllFalse = true;

            for (int i = 0; i < charactersPerType*2; i++){ //Esse laço verifica se o mouse está em cima de algum jogador, e logo em seguida muda as variáveis para trabalhar mais abaixo;
                if(characters[i]->isHovering()){
                    characters[i]->setBright(true);
                    isCharAllFalse = false;
                } 
                else{
                    characters[i]->setBright(false);
                }
            }

            if(boat.isHovering() && isCharAllFalse == true) //Aqui verifica se o mouse está em cima do barco ou não, e caso esteja coloca o brilho como true, ou false, caso seja o caso;
                boat.setBright(true);
            else
                boat.setBright(false);
            
                //case sf::Event::KeyPressed: //Essa verificação é sobre o teclado, caso o jogador aperte o ESC, para voltar para o menu;
                    //if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {//ESCAPE == ESC
                    //    return 0;
                    //}

                //break;

            if (boat.wasClicked() && isCharAllFalse == true && !boat.moving){
                if (boat.quantChar != 0){ //Caso o barco tenha apenas mais de 0 jogadores, pois vazio ele não pode andar;
                    gameData.moves += 1; //Soma um no movimento do barco;
                    gameData.totalMoves += 1; //Soma um nos movimentos totais do barco;
                    boat.moveBoat(); //Chama a função de mover o barco, caso ele clique no barco;
                }
            }

            for (int i = 0; i < charactersPerType*2; i++) { //Loop para percorrer todos os personagens;
                if (characters[i]->wasClicked() && !boat.moving){
                    characters[i]->moveTo(leftSpaces, boatSpaces, rightSpaces, boat); //Caso o jogador aperte em cima do personagem, essa função move o personagem para o local correto;
                    characters[i]->setBright(false); //Colocando a luz em volta nele de falso novamente;
                }
            }
                

            if(gameEventsManager.isWindowClosed())
                return 0; 
        

            if (boat.moving == true && boat.getPosition().x != boat.xfinal) { //Fazendo a verificação se o barco está andando, e move ele dentro do if;

                boat.setBright(false); //Colocando essa variável como falso, para deixar o barco na cor normal quando ele estiver se movendo;

                boat.move(boat.speed, 0); //Move a sprite do barco mas em uma velocidade bem pequena;
                //boat.brightsprite.move(boat.speed, 0); //Move a sprite de opção do barco na mesma velocidade;
                boat.setClickBox(boat.getGlobalBounds());
                for (int i = 0; i < charactersPerType*2; i++){ //Esse laço serve para mover caso existam personagens em cima do barco;
                    if (characters[i]->getLocation() == BOATRIGHTSIDE || characters[i]->getLocation() == BOATLEFTSIDE) { //Se ele estiver no barco, em qualquer lado, ele deve ir junto;
                        characters[i]->move(boat.speed, 0);
                        characters[i]->setClickBox(characters[i]->getGlobalBounds());
                        
                    }
                }
            }
            else if(boat.moving){ //TRATAMENTO PÓS MOVIMENTAÇÃO, LOGO APOS O BARCO PARAR;
                for (int i = 0; i < charactersPerType*2; i++){ //Para finalizar o movimento do barco, quando ele estiver se movendo mas já chegou no seu objetivo final, devemos mudar a posição dos perso;
                    if (characters[i]->getLocation() == BOATRIGHTSIDE) {  //Aqui verifica, caso ele veio do barco na direita, colocamos ele no barco do lado esquerdo;
                        characters[i]->setLocation(BOATLEFTSIDE);
                        if (characters[i]->getType() == Character::priest) //ATUALIZANDO OS DADOS DO GAMEDATA;
                            gameData.rightSidePriests -= 1; //Colocando menos um padre do lado direito, nesse caso ele acabou de ir para o lado esquerdo;
                        else
                            gameData.rightSideCannibals -= 1; //Diminunindo um canibal do lado direito, pois ele acabou de atravessar pelo barco;

                        //character[i].brightsprite.setPosition(character[i].sprite.getPosition()); //Arruma a sprite de opção, que não precisa ficar acompanhando todo o tempo;
                    }
                    else if (characters[i]->getLocation() == BOATLEFTSIDE) { //E caso contrário, colocamos ele no lado direito, porque o barco acabou de andar;
                        characters[i]->setLocation(BOATRIGHTSIDE);

                        if (characters[i]->getType() == Character::priest)
                            gameData.rightSidePriests += 1;//Somando mais um padre caso ele venha do lado esquerdo, para o GameData;
                        else
                            gameData.rightSideCannibals += 1; //Colocando mais um canibal caso ele atravesse pelo barco para o lado direito;

                        //character[i].brightsprite.setPosition(character[i].getPosition()); //Arruma a sprite de opção, que não precisa ficar acompanhando todo o tempo;
                    }
                }
                boat.moveBoatFreePos(boatSpaces); //Movendo as posições do barco, para colocar elas no local certo agora que o barco se moveu;
                gameData.submitCurrentGameState();
                boat.moving = false; //Para finalizar, coloca-se o barco como parado, para não mover mais ele;
            }

        gameData.printStatistics(time, movements, attempts, totalMovements);

        window.clear(sf::Color::Black); //Limpando as representações antigas que estavam dispostas na janela;

        gameGraphicsManager.draw(GET_DRAWABLE_POINTER(background)); //Colocando o fundo do jogo;
        
        //Fazendo os prints gerais do texto;
        gameGraphicsManager.draw(GET_DRAWABLE_POINTER(tempo));
        gameGraphicsManager.draw(GET_DRAWABLE_POINTER(time));
        gameGraphicsManager.draw(GET_DRAWABLE_POINTER(movimentos));
        gameGraphicsManager.draw(GET_DRAWABLE_POINTER(movements));
        gameGraphicsManager.draw(GET_DRAWABLE_POINTER(tentativas));
        gameGraphicsManager.draw(GET_DRAWABLE_POINTER(attempts));
        gameGraphicsManager.draw(GET_DRAWABLE_POINTER(movimentosTotais));
        gameGraphicsManager.draw(GET_DRAWABLE_POINTER(totalMovements));

        gameGraphicsManager.draw(GET_DRAWABLE_POINTER(boat));

        //if (boat.bright == false) //Colocando a opção em cima do barco, para o jogador saber que é possível mover o barco;
        //    window.draw(boat.sprite);
        //else
        //    window.draw(boat.brightsprite);
    

        //winOrLose = WIN;
        winOrLose = gameData.verifyWinConditions(characters); //Verificando se o jogador venceu o ganhou, chamando a função verifyWinConditions();

        for (int i = 0; i < charactersPerType*2; i++) { //Esse laço, bem importante, verifica se o mouse está em cima do personagem, e caso esteja desenha o personagem brilhante.
                characters[i]->setBright(characters[i]->isHovering());
                gameGraphicsManager.draw(GET_DRAWABLE_POINTER(*(characters[i])));
        }

        if (winOrLose == WIN || winOrLose == LOSE) { //Agora sim comparando o resultado para ver vitória ou derrota;
            if (winOrLose == LOSE){ //Caso seja uma derrota
                gameGraphicsManager.draw(GET_DRAWABLE_POINTER(whiteWindowOption)); //Desenha a janela transparente;

                gameOverScreen(characters, boat, background); //Faz a opção de jogar novamente;
                //Reseta algumas variáveis;
                gameData.moves = 0; //Reseta os movimentos do jogador, pois só deixa salvo os movimentos totais;
                gameData.currentMoves = 0; //Reseta os movimentos do momento, pelo mesmo motivo acima;
                gameData.numbAttempts += 1; //Numero de tentativas aumenta um, porque o jogador perdeu o jogo;

                //Essa função reseta toda a stack e coloca tudo novamente, para ajeitar o jogo para ajeitar para o jogador novamente;
                gameData.resetStacksAndReplace(leftSpaces, boatSpaces, rightSpaces, characters, boat);
            }
            else{ //É vitória caso o jogador chegue aqui;
                for (int i = 0; i < charactersPerType*2; i++){
                    if (characters[i]->getLocation() == BOATLEFTSIDE){
                        characters[i]->setPosition(leftSpaces.top());
                        characters[i]->setClickBox(characters[i]->getGlobalBounds());
                        leftSpaces.pop();

                        boat.quantChar -= 1;
                    }
                }

                gameData.totalTime = gameData.gameTime.getElapsedTime().asSeconds();
                gameData.currentMoves = 0;
                gameData.currentNumbAttempts = 0;
                gameData.currentTotalMoves = 0;

                for (int i = 0; i < charactersPerType*2; i++) //Printando todos os personagens;
                    gameEventsManager.removeClickable(GET_CLICKABLE_POINTER(*characters[i]));
                gameEventsManager.removeClickable(GET_CLICKABLE_POINTER(boat));

                gameWinScreen(characters, boat, background, whiteWindowOption, &gameData);
                logDisplayScreen(characters, boat, background, &gameData);

                gameData.saveStateLog();

                return 0;
            }
        }

        window.display(); //Mostrando quais foram as alterações no fundo;
    }

    return 0;
}

/*
void Jogo::gameWinScreen()
    Essa função tem o objetivo de mostrar quando o jogador ganhou o jogo, pedir o seu nome e a sua idade
para futuramente tivermos dados suficientes para fazer uma pesquisa.
@param Character character [6] -> Passa todos os personagens como objeto, somente para poder printar eles normalmente.
@param Boat boat -> Para poder printar o barco, ele é passado como objeto.
@param Sprites background -> Evitando um carregamento desnecessário, passa-se também o fundo por objeto.
@param Sprites whiteWindowOption -> A janela de opções instanciada no start() para quando o jogador perde o jogo, é
utilizada novamente porém em um novo formato.
@param GameData gameData -> Para printar os dados do jogo, é passado como objeto o gameData.
@return
*/

void Jogo::gameWinScreen(Character** characters, Boat boat, sf::Sprite background, sf::Sprite whiteWindowOption, GameData* gameData){
    
    bool printEverythingOneTime = true; //Essa variável serve para atualizar somente uma vez os dados do jogo, visando que eles não serão mudados durante a tela de derrota;
    bool moving = true; //Enquanto está tendo a animação dos dados do jogo isso permanece true;
    int movingVerficator = 0; //Verificador para ver se todos os parâmetros já chegaram no final, para evitar atualizações desnecessárias;

    sf::Mouse mouse; //Verificador do mouse, para ver onde está sua posição;

    whiteWindowOption.setScale(sf::Vector2f(0.35, 0.65)); //Aumentando o tamanho da janela e reposicionando ela abaixo para deixar ajeitada para o fim de jogo;
    whiteWindowOption.setPosition(sf::Vector2f((WIDTH / 2) - (whiteWindowOption.getGlobalBounds().width / 2), (HEIGHT / 2) - (whiteWindowOption.getGlobalBounds().height / 2)));

    Phrase tempo(gameGraphicsManager.loadFont("../assets/afanan.ttf"), "Tempo (seg): ", 50, darkBlue, sf::Vector2f(WIDTH * 0.7, HEIGHT * 0.01));
    Phrase time(gameGraphicsManager.loadFont("../assets/afanan.ttf"), "0", 50, sf::Color::Yellow, sf::Vector2f(WIDTH * 0.83, HEIGHT * 0.01)); //Instânciando um objeto de tempo, onde será atualizado sempre que mudar os segundos;

    Phrase movimentos(gameGraphicsManager.loadFont("../assets/afanan.ttf"), "Movimentos: ", 50, darkBlue, sf::Vector2f(WIDTH * 0.45, HEIGHT * 0.01));
    Phrase movements(gameGraphicsManager.loadFont("../assets/afanan.ttf"), "0", 50, sf::Color::Yellow, sf::Vector2f(WIDTH * 0.58, HEIGHT * 0.01)); //Esses dois movimentos são a quantidade de movimentos que o jogador realizou;

    Phrase movimentosTotais(gameGraphicsManager.loadFont("../assets/afanan.ttf"), "Total de Mov.: ", 50, darkBlue, sf::Vector2f(WIDTH * 0.45, HEIGHT * 0.08));
    Phrase totalMovements(gameGraphicsManager.loadFont("../assets/afanan.ttf"), "0", 50, sf::Color::Yellow, sf::Vector2f(WIDTH * 0.60, HEIGHT * 0.08));

    Phrase tentativas(gameGraphicsManager.loadFont("../assets/afanan.ttf"), "Tentativas: ", 50, darkBlue, sf::Vector2f(WIDTH * 0.20, HEIGHT * 0.01));
    Phrase attempts(gameGraphicsManager.loadFont("../assets/afanan.ttf"), "0", 50, sf::Color::Yellow, sf::Vector2f(WIDTH * 0.33, HEIGHT * 0.01)); //Aqui são as tentativas, cada vez que o jogador perde soma-se 1 na quantidade;

    Phrase fimDeJogo(gameGraphicsManager.loadFont("../assets/Pixel.ttf"), "SUCESSO! FIM DE JOGO!", 50, sf::Color::Yellow, sf::Vector2f(WIDTH * 0.347, HEIGHT * 0.19)); //Instanciando o fim de jogo, frase que ficará escrita no pequeno menu;
    Phrase fimDeJogo1(gameGraphicsManager.loadFont("../assets/Pixel.ttf"), "SUCESSO! FIM DE JOGO!", 50, sf::Color::Blue, sf::Vector2f(WIDTH * 0.3451, HEIGHT * 0.19)); //Instanciando uma "sombra" para dar um efeito diferente na escrita;

    Phrase continuar(gameGraphicsManager.loadFont("../assets/Pixel.ttf"), "Continuar", 40, sf::Color::White, sf::Vector2f(WIDTH * 0.45, HEIGHT * 0.70)); //Unica opção disponível nesse menu de finalizar o jogo;
    gameEventsManager.addClickable(GET_CLICKABLE_POINTER(continuar));



    while (window.isOpen()){ //Começando o loop principal do menu;
        
        gameEventsManager.pollAll();

        if (continuar.isHovering()) //Caso o mouse fique em cima do continuar;
            continuar.setFillColor(sf::Color::Blue); //Muda a cor par azul;
        else
            continuar.setFillColor(sf::Color::White); //Caso contrário, muda para branco;


        if (continuar.wasClicked()){ //Se apertar retorna sem valor, dizendo que ele terminou o jogo e está pronto para ir ao menu;
            gameEventsManager.removeClickable(GET_CLICKABLE_POINTER(continuar));
            return;
        }

        

        window.clear(sf::Color::Black); //Limpa a tela e coloca uma cor inicial;

        gameGraphicsManager.draw(GET_DRAWABLE_POINTER(background)); //Printa o fundo do jogo;

        if (printEverythingOneTime) { //Atualizando somente pela primeira vez;
            gameData->printStatistics(time, movements, attempts, totalMovements); //Atualizando os dados do gameData;

            printEverythingOneTime = false;
        }

        gameGraphicsManager.draw(GET_DRAWABLE_POINTER(boat)); //Printando o barco;

        for (int i = 0; i < charactersPerType*2; i++) //Printando todos os personagens;
            gameGraphicsManager.draw(GET_DRAWABLE_POINTER(*(characters[i])));

        gameGraphicsManager.draw(GET_DRAWABLE_POINTER(whiteWindowOption)); //Colocando a janela branca transparente;

        //Printando as frases que serão apresentadas;
        gameGraphicsManager.draw(GET_DRAWABLE_POINTER(fimDeJogo1));
        gameGraphicsManager.draw(GET_DRAWABLE_POINTER(fimDeJogo));
        gameGraphicsManager.draw(GET_DRAWABLE_POINTER(continuar));

        if (moving == true) { //Caso esteja tendo a animação ainda, entra dentro dessas opções;
            if (tentativas.getPosition().x <= XFINALATTEMPTS) { //Enquanto a palavra tentativass não chegou ainda no final da sua animação;
                tentativas.move(sf::Vector2f(3.16, 3.3));
                attempts.move(sf::Vector2f(3.16, 3.3));
            } else
                movingVerficator += 1; //Quando chegar avisa a variável;
            
            if (movimentos.getPosition().x >= XFINALMOVES) { //Enquanto movimentos não chegou ainda também em seu objetivo final;
                movimentos.move(sf::Vector2f(-1.64, 4.25)); 
                movements.move(sf::Vector2f(-1.64, 4.25));
            } else
                movingVerficator += 1;

            if (tempo.getPosition().x >= XFINALTIME) { //Enquanto a palavra tempo não chegou no final da animação;
                tempo.move(sf::Vector2f(-6.42, 4.95));
                time.move(sf::Vector2f(-6.42, 4.95));
            } else
                movingVerficator += 1;

            if (movimentosTotais.getPosition().x >= XFINALTOTALMOVES) { //Enquanto o movimentos totais não chegou no final da animação ainda;
                movimentosTotais.move(sf::Vector2f(-1.62, 5.1));
                totalMovements.move(sf::Vector2f(-1.62, 5.1));
            } else
                movingVerficator += 1;
            

            if (movingVerficator > 4) //Caso ele já tenha passado por todos, limita de entrar nesse laço para evitar repetições;
                moving = false;
        }

        //Fazendo os prints gerais do texto;
        gameGraphicsManager.draw(GET_DRAWABLE_POINTER(tempo));
        gameGraphicsManager.draw(GET_DRAWABLE_POINTER(time));
        gameGraphicsManager.draw(GET_DRAWABLE_POINTER(movimentos));
        gameGraphicsManager.draw(GET_DRAWABLE_POINTER(movements));
        gameGraphicsManager.draw(GET_DRAWABLE_POINTER(tentativas));
        gameGraphicsManager.draw(GET_DRAWABLE_POINTER(attempts));
        gameGraphicsManager.draw(GET_DRAWABLE_POINTER(movimentosTotais));
        gameGraphicsManager.draw(GET_DRAWABLE_POINTER(totalMovements));

        window.display(); //Mostra novamente o que está sendo printado na tela;

        gameEventsManager.isWindowClosed();
    }
    gameEventsManager.removeClickable(GET_CLICKABLE_POINTER(continuar));
}

void Jogo::logDisplayScreen(Character** characters, Boat boat, sf::Sprite background, GameData* gameData){
    Phrase continuar(gameGraphicsManager.loadFont("../assets/Pixel.ttf"), "Continuar", 40, sf::Color::White, sf::Vector2f(WIDTH * 0.45, HEIGHT * 0.70)); //Unica opção disponível nesse menu de finalizar o jogo;
    gameEventsManager.addClickable(GET_CLICKABLE_POINTER(continuar));

    Character upArrow(gameGraphicsManager.loadTexture("../assets/seta_cima.png"), Character::characterType::none, 0, sf::Vector2f(WIDTH * 0.30, HEIGHT * 0.05));
    Character downArrow(gameGraphicsManager.loadTexture("../assets/seta_cima.png"), Character::characterType::none, 0, sf::Vector2f(WIDTH * 0.30, HEIGHT * 0.70), sf::Vector2f(1.0f, -1.0f));

    gameEventsManager.addClickable(GET_CLICKABLE_POINTER(upArrow));
    gameEventsManager.addClickable(GET_CLICKABLE_POINTER(downArrow));

    std::vector<Phrase*>movements;
    int listPosition = 0;

    for(int i = 1; i < gameData->gameStateLog.size(); i++){
        std::string movementText("Moveu ");
        int movedPriests = gameData->gameStateLog[i]->rightPriests - gameData->gameStateLog[i-1]->rightPriests;
        int movedCannibals = gameData->gameStateLog[i]->rightCannibals - gameData->gameStateLog[i-1]->rightCannibals;
        
        if(movedPriests){
            movementText += std::to_string(abs(movedPriests));
            movementText += abs(movedPriests) > 1 ? " padres" : " padre";
        }
        if(movedCannibals){
            if(movedPriests)
                movementText += " e ";
            movementText += std::to_string(abs(movedCannibals));
            movementText += abs(movedCannibals) > 1 ? " canibais" : " canibal";
        }

        movementText += i % 2 ? " para a esquerda." : " para a direita.";

        Phrase* movementPhrase = new Phrase(gameGraphicsManager.loadFont("../assets/Pixel.ttf"), movementText, 40, sf::Color::White, sf::Vector2f(WIDTH * 0.37, HEIGHT * 0.05 + HEIGHT * 0.05 * i));
        movements.push_back(movementPhrase);
    }

    while (window.isOpen()){ //Começando o loop principal do menu;
        //printf("vector size before poll: %d\n", movements.size());
        gameEventsManager.pollAll();
        //printf("vector size after poll: %d\n", movements.size());

        if (continuar.isHovering()) { //Faz o tratamento clássico caso o mouse passe por cima da frase;
            continuar.setFillColor(sf::Color::Blue); //Coloca cor azul caso esteja em cima;
        }
        else{
            continuar.setFillColor(sf::Color::Yellow); //Ou amarelo caso não esteja em cima;
        }
        if (continuar.wasClicked()){ //Se apertar retorna sem valor, dizendo que ele terminou o jogo e está pronto para ir ao menu;
            for(auto i = movements.begin(); i != movements.end(); i++)
                delete *i;

            gameEventsManager.removeClickable(GET_CLICKABLE_POINTER(continuar));
            gameEventsManager.removeClickable(GET_CLICKABLE_POINTER(upArrow));
            gameEventsManager.removeClickable(GET_CLICKABLE_POINTER(downArrow));
            
            return;
        }


        if (upArrow.isHovering() && listPosition > 0) { //Faz o tratamento clássico caso o mouse passe por cima da frase;
            upArrow.setBright(true); //Coloca cor azul caso esteja em cima;
        }
        else{
            upArrow.setBright(false); //Ou amarelo caso não esteja em cima;
        }
        if(upArrow.wasClicked()){ //Se apertar retorna sem valor, dizendo que ele terminou o jogo e está pronto para ir ao menu;
            if(listPosition > 0){
                listPosition--;
                for(auto i = movements.begin(); i != movements.end(); i++)
                    (*i)->move(sf::Vector2f(0.0f, HEIGHT * 0.05));
            }
        }

        if (downArrow.isHovering() && listPosition < movements.size() - 11) { //Faz o tratamento clássico caso o mouse passe por cima da frase;
            downArrow.setBright(true); //Coloca cor azul caso esteja em cima;
        }
        else{
            downArrow.setBright(false); //Ou amarelo caso não esteja em cima;
        }
        if(downArrow.wasClicked()){ //Se apertar retorna sem valor, dizendo que ele terminou o jogo e está pronto para ir ao menu;
            if(listPosition < movements.size() - 11){
                listPosition++;
                for(auto i = movements.begin(); i != movements.end(); i++)
                    (*i)->move(sf::Vector2f(0.0f, -HEIGHT * 0.05));
            }
        }

        window.clear(sf::Color::Black); //Limpa a tela e coloca uma cor inicial;

        gameGraphicsManager.draw(GET_DRAWABLE_POINTER(background));

        gameGraphicsManager.draw(GET_DRAWABLE_POINTER(boat));

        for (int i = 0; i < charactersPerType*2; i++) //Printando todos os personagens;
            gameGraphicsManager.draw(GET_DRAWABLE_POINTER(*(characters[i])));

        for(int i = listPosition; i < listPosition + 11 && i < movements.size(); i++)
            gameGraphicsManager.draw(GET_DRAWABLE_POINTER(*movements[i]));
        

        gameGraphicsManager.draw(GET_DRAWABLE_POINTER(upArrow));
        gameGraphicsManager.draw(GET_DRAWABLE_POINTER(downArrow));

        gameGraphicsManager.draw(GET_DRAWABLE_POINTER(continuar));

        window.display(); //Mostra novamente o que está sendo printado na tela;

        gameEventsManager.isWindowClosed();
    }
    for(auto i = movements.begin(); i != movements.end(); i++)
        delete *i;

    gameEventsManager.removeClickable(GET_CLICKABLE_POINTER(continuar));
    gameEventsManager.removeClickable(GET_CLICKABLE_POINTER(upArrow));
    gameEventsManager.removeClickable(GET_CLICKABLE_POINTER(downArrow));
}

void Jogo::gameOverScreen(Character** characters, Boat boat, sf::Sprite background){
    Phrase voceperdeu (gameGraphicsManager.loadFont("../assets/Pixel.ttf"), "TENTAR NOVAMENTE", 50, sf::Color::Yellow, sf::Vector2f(WIDTH * 0.365, HEIGHT * 0.44)); //Texto de tentar novamente que aparece caso o jogador perca;

    gameEventsManager.addClickable(GET_CLICKABLE_POINTER(voceperdeu));
    //if (!voceperdeu.setFont("Pixel.ttf")) //Colocando o arquivo da fonte dentro da frase e verificando se é possível abrir o arquivo;
    //{
    //    std::cout << "\n\n @@@@@@ Error trying to access the file." << std::endl; //Frase caso não seja possível abrir o arquivo;
    //
    //    return;
    //}
    while (!gameEventsManager.isWindowClosed()){
        
        gameEventsManager.pollAll();

            
        if (voceperdeu.isHovering()) { //Faz o tratamento clássico caso o mouse passe por cima da frase;
            voceperdeu.setFillColor(sf::Color::Blue); //Coloca cor azul caso esteja em cima;
        }
        else{
            voceperdeu.setFillColor(sf::Color::Yellow); //Ou amarelo caso não esteja em cima;
        }

        if(voceperdeu.wasClicked()){//Quando aperta, ele verifica se está em cima e retorna diretamente para a função start() novamente;
            //gameEventsManager.removeClickable(GET_CLICKABLE_POINTER(voceperdeu));
            return;
        }

        window.clear(sf::Color::Black); //Limpando as representações antigas que estavam dispostas na janela;

        gameGraphicsManager.draw(GET_DRAWABLE_POINTER(background)); //Colocando o fundo do jogo;

        gameGraphicsManager.draw(GET_DRAWABLE_POINTER(boat)); //Printando o barco;

        for (int i = 0; i < charactersPerType*2; i++) //Printando todos os personagens;
            gameGraphicsManager.draw(GET_DRAWABLE_POINTER(*(characters[i])));

        gameGraphicsManager.draw(GET_DRAWABLE_POINTER(voceperdeu)); //Printa o texto;

        window.display(); //Mostrando todas as mudanças que foram feitas;
    }
    gameEventsManager.removeClickable(GET_CLICKABLE_POINTER(voceperdeu));
}
