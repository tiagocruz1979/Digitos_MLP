#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <cmath>
#include <cstdlib>
#include <ctime>
#include "rn.h"
#include "pesosRN.h"

// Inicio de Funções de Desenho

void apagarMatrizDesenho(sf::RectangleShape matriz[32][32], sf::Color *cor, int Height, int Width)
{
    for(int i = 0 ; i < Height ; i++)
    {
         for(int j = 0 ; j < Width;j++)
         {
              matriz[i][j].setFillColor(*cor);
         }
    }
}
void trocarCorMatrizDesenho(sf::RectangleShape matriz[32][32], sf::Color *corAtual, sf::Color *corNova, int Height, int Width)
{
    for(int i = 0 ; i < Height ; i++)
    {
         for(int j = 0 ; j < Width;j++)
         {
              if(matriz[i][j].getFillColor()==*corAtual)
              {
                matriz[i][j].setFillColor(*corNova);
              }
         }
    }
}


class Botao
{
    sf::RectangleShape *corpo;
    sf::RectangleShape *sombra;
    sf::Text *texto;

    public:

    Botao(std::string txt, sf::Color corTexto, sf::Color cor, float largura, float altura, sf::Font &font)
    {
        corpo = new sf::RectangleShape(sf::Vector2f(largura,altura));
        texto = new sf::Text(txt,font, altura*0.5);
        this->corpo->setFillColor(cor);
        this->corpo->setOutlineColor(sf::Color::Black);
        this->corpo->setOutlineThickness(1.f);
        this->texto->setColor(corTexto);
        this->sombra = new sf::RectangleShape(sf::Vector2f(largura+4.f,altura+4.f));
        this->sombra->setFillColor(sf::Color(120,120,120));
    }

    void exibir(sf::RenderWindow &w)
    {
        w.draw(*this->sombra);
        w.draw(*this->corpo);
        w.draw(*this->texto);
                texto->setPosition(corpo->getPosition());
        texto->move(5.f,0.f);
    }

    void setPosition(float x, float y)
    {
        corpo->setPosition(sf::Vector2f(x,y));
        sombra->setPosition(sf::Vector2f(x-2.f,y-2.f));
        texto->setPosition(corpo->getPosition());
        texto->move(5.f,0.f);
    }

    void setTextSize(unsigned int s)
    {
        this->texto->setCharacterSize(s);
    }

    bool dentroDoLimite(sf::Vector2f pos, sf::RenderWindow &w)
    {
        if (this->corpo->getGlobalBounds().contains(pos))
        {
            this->texto->move(2.f,2.f);
            w.draw(*this->texto);
            return true;
        }
        return false;
    }

};





int main(){

std::srand(std::time(0));


//Montagem da Rede Neural ( 4 neurônios de entrada , 3 neuronios na camada oculta e 3 neuronios de saida)

//Camada de entrada - setar valores
std::vector<Neuronio*> camada1;
for(int i = 0 ; i < 64 ; i++)
{
    Neuronio *e = new Neuronio(0,0.0);
    e->setValor(0);
    camada1.push_back(e);
}

//Camada oculta - configurar quantidade de entradas e pesos de cada entrada
std::vector<Neuronio*> camada2;
for(int i = 0 ; i < 16;i++)
{
    Neuronio *h = new Neuronio(64,bias_camada1.at(i));
    for(int j = 0 ; j < 64 ;j++)
    {
        h->setNeuroEntrada(camada1.at(j),pesocamada1.at(j).at(i));
    }
    camada2.push_back(h);
}

//Camada de Saida
std::vector<Neuronio*> camada3;
for(int i = 0 ; i < 10;i++)
{
    Neuronio *s = new Neuronio(16,bias_camada2.at(i));
    for(int j = 0 ; j < 16 ;j++)
    {
        s->setNeuroEntrada(camada2.at(j),pesocamada2.at(j).at(i));
    }
    camada3.push_back(s);
}

    // Definir o tamanho da janela
    sf::Vector2f windowSize(832.f,512.f);

    //criar a janela
    sf::RenderWindow window(sf::VideoMode(windowSize.x, windowSize.y), "Matriz de Desenho");

    // Configurar a cor do desenho
    sf::Color corFundo = sf::Color(10,10,50);
    sf::Color corDesenho = sf::Color(200,200,0);

    // Botao de configuração pincel
    sf::RectangleShape botaoConfigPincel[6];
    sf::Color coresBotaoPincel[6]={{255,255,255},{255,255,255},{0,255,0},{255,0,255},{255,0,125},{200,200,0}};
    for(int i = 0 ; i < 6;i++)
    {
        botaoConfigPincel[i].setSize(sf::Vector2f(50.f,50.f));
        botaoConfigPincel[i].setPosition(sf::Vector2f(512.0+50*i,0));
        botaoConfigPincel[i].setFillColor(coresBotaoPincel[i]);
        botaoConfigPincel[i].setOutlineThickness(2.f);
        botaoConfigPincel[i].setOutlineColor(sf::Color::Blue);

    }


    //Fonte Padrao
    sf::Font font;
    font.loadFromFile("consola.ttf");

    //Botao Apagar novo
    Botao botaoApagar("Apagar",sf::Color::White, sf::Color::Blue,160.f,50.f,font);
    botaoApagar.setPosition(600.f,100.f);

    //Botao Reconhecer novo
    Botao botaoReconhecer("Reconhecer",sf::Color::White, sf::Color::Blue,160.f,50.f,font);
    botaoReconhecer.setPosition(600.f,200.f);

    //Botao Reconhecer Prencher
    Botao botaoPreencher("Preencher",sf::Color::White, sf::Color::Blue,160.f,50.f,font);
    botaoPreencher.setPosition(600.f,300.f);



    // texto configPincel
    sf::Text txtMenos("-", font, 40);
    txtMenos.setPosition(botaoConfigPincel[0].getPosition());
    txtMenos.setFillColor(sf::Color::Black);
    txtMenos.move(sf::Vector2f(7.f,0.f));
    sf::Text txtMais("+", font, 40);
    txtMais.setPosition(botaoConfigPincel[1].getPosition());
    txtMais.setFillColor(sf::Color::Black);
    txtMais.move(sf::Vector2f(7.f,0.f));

    //Texto para Saída
    sf::RectangleShape caixaSaida(sf::Vector2f(160.f,50.f));
    caixaSaida.setPosition(sf::Vector2f(600.f,400.f));
    caixaSaida.setFillColor(sf::Color::White);
    sf::Text txtSaida("?", font, 30);
    txtSaida.setFillColor(sf::Color::Red);
    txtSaida.setPosition(caixaSaida.getPosition());

    // Criar o retangulo para pincel
    sf::RectangleShape pincel(sf::Vector2f(32.f,32.f));
    pincel.setPosition(0.0f,0.0f);
    pincel.setFillColor(sf::Color::Green);
    //pincel.rotate(45);

    // Definir o tamanho da matriz de desenho
    const int matrixWidth = 32;
    const int matrixHeight = 32;

    // Criar a matriz de desenho
    sf::RectangleShape matrix[matrixWidth][matrixHeight];
    for (int i = 0; i < matrixWidth; i++)
    {
        for (int j = 0; j < matrixHeight; j++)
        {
            matrix[i][j].setSize(sf::Vector2f(16.f, 16.f));
            matrix[i][j].setPosition(i * 16.f, j * 16.f);
            matrix[i][j].setFillColor(corFundo);
        }
    }

    bool isDrawing = false; // verifica se o usuario esta desenhando

    while (window.isOpen())
    {
        sf::Event event;
        sf::Vector2f lastMousePos;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();

            // Clique no botao Apagar
            if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left)
            {
                // Verificar se o mouse está sobre o botão
                sf::Vector2f mousePos = sf::Vector2f(event.mouseButton.x, event.mouseButton.y);

                if (botaoApagar.dentroDoLimite(mousePos,window))
                {
                    // Botão clicado
                    std::cout << "Botao Apagar clicado!" << std::endl;
                    apagarMatrizDesenho(matrix,&corFundo,32,32);
                    txtSaida.setString("?");
                }

                // Verificar se o mouse está sobre o botão
                int vetSaida[64];
                if (botaoReconhecer.dentroDoLimite(mousePos,window))
                {
                    // Botão clicado
                    std::cout << "Botao botaoReconhecer clicado!" << std::endl;
                    int idx = 0;
                    for(int i = 0 ; i < matrixHeight ; i+=4)
                    {
                        for(int j = 0 ; j < matrixWidth;j+=4)
                        {
                            int soma = 0;
                            for(int ii = i ; ii<i+4;ii++)
                            {
                                for(int jj=j;jj<j+4;jj++)
                                {
                                    if(matrix[jj][ii].getFillColor()!=corFundo)
                                    {
                                        soma++;
                                    }
                                }
                            }
                            vetSaida[idx++] = soma;
                        }
                    }

                if (botaoConfigPincel[0].getGlobalBounds().contains(mousePos))
                {
                    std::cout << "botao configPincel clicado\n";
                }


                    //mostrando resutlado do vetor de saída
                    for(int i = 0 ; i < 64;i++)
                    {
                        std::cout << vetSaida[i] << ",";
                    }
                    std::cout << '\n';

                    //testar reconhecimento da imagem
                    for(int i = 0 ; i < 64;i++)
                    {
                        camada1.at(i)->setValor(vetSaida[i]);
                    }
                    atualizarCamadaRELU(camada2);
                    atualizarCamadaSoftmax(camada3);
                    int resultado = classificacao(camada3);
                    std::string strRes = std::to_string(resultado);
                    txtSaida.setString(strRes);

                    std::cout << "Resultado = " << resultado << '\n';
                }


                //Botao Config Pincel
                for(int i = 0 ; i < 6 ;i++)
                {
                    if (botaoConfigPincel[i].getGlobalBounds().contains(mousePos))
                    {
                        std::cout << "botao configPincel clicado\n";
                        if(i==0) // botao de -
                        {
                            float tamanho = pincel.getSize().x;
                            if(tamanho > 12)
                            {
                                tamanho -= 4.f;
                                pincel.setSize(sf::Vector2f(tamanho,tamanho));
                            }
                        }
                        else if (i==1) // botao de mais
                        {
                            float tamanho = pincel.getSize().x;
                            if(tamanho < 64)
                            {
                                tamanho += 4.f;
                                pincel.setSize(sf::Vector2f(tamanho,tamanho));
                            }
                        }
                        else // botao de cores
                        {
                            sf::Color corAtual = corDesenho;
                            corDesenho = botaoConfigPincel[i].getFillColor();
                            pincel.setFillColor(corDesenho);
                            trocarCorMatrizDesenho(matrix,&corAtual,&corDesenho,32,32);
                        }
                    }
                }




                // Verificar se o mouse está sobre o botão Preencher
                if (botaoPreencher.dentroDoLimite(mousePos,window))
                {
                    // Botão Preencher clicado
                    std::cout << "Botao botaoPreencher clicado!" << std::endl;





                    std::string leitura;
                    int sorteio = rand()%10;
                    switch(sorteio)
                    {
                    case 0:
                    leitura="0000000000000110000000000000000000000000000011111100000000000000000000000001111111110000000000000000000001111111111100000000000000000001111111111111100000000000000000001111111000111100000000000000000111111000000111000000000000000001111110000001110000000000000000111111000000011100000000000000001111110000000111100000000000000011111100000000011100000000000000111111000000000111000000000000001111100000000000111000000000000011111000000000001110000000000000011111000000000001110000000000000111110000000000011100000000000001111100000000000111000000000000111110000000000001110000000000001111100000000000011100000000000000111100000000000011100000000000001111000000000001111000000000000011110000000000011110000000000000111100000000001111100000000000000111100000000001111100000000000001111100000000111110000000000000011111000000011111100000000000000111110000001111110000000000000001111110001111111100000000000000000111111111111110000000000000000001111111111111000000000000000000001111111111000000000000000000000000111110000000000000";
                    break;
                    case 1:
                    leitura="0000000000000000000000110000000000000000000000000000111110000000000000000000000000011111110000000000000000000000000111111000000000000000000000000011111110000000000000000000000000111111110000000000000000000000011111111000000000000000000000011111111110000000000000000000001111111111100000000000000000011111111111110000000000000000001111111111111100000000000000000111111111111111000000000000000011111111111111110000000000000001111111111111111000000000000000111111111011111110000000000000001111111000111111100000000000000011111100001111111000000000000000011111000011111110000000000000000001100000011111100000000000000000000000000111111100000000000000000000000011111110000000000000000000000000111111100000000000000000000000001111111100000000000000000000000001111111000000000000000000000000011111110000000000000000000000000011111100000000000000000000000000011111100000000000000000000000001111110000000000000000000000000011111100000000000000000000000000011111000000000000000000000000000111110000000000000000000000000000111000000000";
                    break;
                    case 2:
                    leitura="0000000001111111000000000000000000000000011111111100000000000000000000001111111111100000000000000000000111111111111000000000000000000001111111111111000000000000000000111111111111110000000000000000001111100001111100000000000000000011100000001111000000000000000000111000000011110000000000000000001110000000111100000000000000000000000000001111000000000000000000000000000011110000000000000000000000000001111000000000000000000000000000111110000000000000000000000000011111000000000000000000000000011111100000000000000000000000000111111000000000000000000000000001111100000000000000000000000000111110000000000000000000000000011111000000000000000000000000001111100000000000000000000000000011110000000000000000000000000000111100000000000000000000000000001111000000000000000000000000000011100000000000000000000000000001111000000000000000000000000000011110000001111111110000000000000111111111111111111110000000000001111111111111111111100000000000001111111111111111111000000000000001111111111111111110000000000000001111111110000001000000";
                    break;
                    case 3:
                    leitura="0000000000000011111000000000000000000000000011111111000000000000000000000011111111110000000000000000000011111111111100000000000000000000111111111111000000000000000000001111111111111000000000000000000111111000111110000000000000000000111100001111100000000000000000000100000011111000000000000000000000000000111110000000000000000000000000011111000000000000000000000000001111110000000000000000000000001111111000000000000000000000000111111111000000000000000000000001111111111000000000000000000000111111111111100000000000000000001111111111111100000000000000000011111111111111100000000000000000000000111111111000000000000000000000000011111110000000000000000000000000001111100000000000000000000000000011111000000000000000000000000000111110000000000000000000000000001111100000000000000000000000000011111000000000000000000000000011111110000000000000000001110111111111000000000000000000111111111111100000000000000000001111111111100000000000000000000011111111110000000000000000000000111111100000000000000000000000000111100000000000000000";
                    break;
                    case 4:
                    leitura="0000000000000001110000000000000000000000000000111110000000000000000000000000011111000000000000000000000000000111110000000000000000000000000011111000000000000000000000000000111110000000000000000000000000111111000000000000000000000000001111110000000000000000000000000011111100000000000100000000000001111100000000000111100000000000011111000000000011111100000000001111100000000001111110000000000111111000000000011111100000000011111100000000011111100000000000111111000000000111111000000000011111100000000011111100000000000011111000000001111111000000000000111111000011111111110000000000011111100011111111111000000000000111111111111111111100000000000001111111111111111110000000000000001111111111111111100000000000000011111111101111110000000000000000011111000011111100000000000000000000000001111110000000000000000000000000011111100000000000000000000000000111110000000000000000000000000011111000000000000000000000000000111110000000000000000000000000011111000000000000000000000000000111110000000000000000000000000011110000000000000000";
                    break;
                    case 5:
                    leitura="0000000000000110011110000000000000000000000111111111111111000000000000000111111111111111111100000000000001111111111111111111000000000000011111111101000001100000000000000111111100000000000000000000000011110000000000000000000000000001111100000000000000000000000000011111000111100000000000000000000111110001111100000000000000000001111111111111111000000000000000011111111111111110000000000000000111111111111111111000000000000001111111111111111100000000000000011111111000111111100000000000000111111000000111111000000000000001111100000000111110000000000000011110000000001111100000000000000000000000000000111100000000000000000000000000001111000000000000000000000000000111100000000000000000000000000001111000000000000000000000000000111110000000000000000000000000011111000000000000000000111000000111110000000000000000001110000011111100000000000000000011111011111110000000000000000001111111111110000000000000000000011111111111000000000000000000000111111111100000000000000000000000111111100000000000000000000000000010000000000000000000";
                    break;
                    case 6:
                    leitura="0000000000000001100000000000000000000000000000111000000000000000000000000000000111000000000000000000000000000011110000000000000000000000000001111110000000000000000000000000011111000000000000000000000000000111110000000000000000000000000011111100000000000000000000000001111111000000000000000000000000011111100000000000000000000000000111111000000000000000000000000011111100000000000000000000000000011111000000000000000000000000001111110000000000000000000000000011111000000000000000000000000000111111000000000000000000000000001111000000000000000000000000000011110011110000000000000000000000111111111111110000000000000000001111111111111111000000000000000111111111111111110000000000000001111111111111111111000000000000011111111111111111110000000000000111111100000000111110000000000001111111000000001111100000000000001111110000000111111000000000000001111111000111111111000000000000001111111111111111110000000000000001111111111111111000000000000000000111111111111100000000000000000000111111111111000000000000000000000011111111100000";
                    break;
                    case 7:
                    leitura="0000000000000111111000000000000000000000000011111111111111111000000000000001111111111111111111000000000000111111111111111111100000000000001111110011111111111000000000000011111000000001111110000000000001111100000000111111000000000000001110000000001111100000000000000011110000000111110000000000000001110000000011110000000000000000011000000001111100000000000000000000000000011110000000000000000000000000001111000000000000000000000000000011110000000000000000000000000001111100000000000000000001111111111111110000000000000000011111111111111111000000000000000111111111111111110000000000000011111111111111111000000000000000011111111111111100000000000000000000000111100000000000000000000000000111110000000000000000000000000001111100000000000000000000000000011111000000000000000000000000001111100000000000000000000000000011111000000000000000000000000000111110000000000000000000000000111111000000000000000000000000001111110000000000000000000000000001111100000000000000000000000000111110000000000000000000000000001111000000000000000000";
                    break;
                    case 8:
                    leitura="0000000000001111111100000000000000000000001111111111111000000000000000000011111111111111000000000000000111111111111111110000000000000001111111111111111110000000000000011111111111111111100000000000001111110011111111111000000000000011111000000011111110000000000000111100000000011111100000000000001111100000000111111000000000000001111110000011111100000000000000011111100001111110000000000000000011111111111111100000000000000000011111111111110000000000000000000011111111111000000000000000000000111111111110000000000000000000001111111111100000000000000000000011111111111100000000000000000001111111111111000000000000000000111111100111111000000000000000001111110001111111000000000000000011111000001111111000000000000000111100000001111110000000000000011111000000001111110000000000000011111000000001111100000000000000111110000000011111000000000000000111111000000111110000000000000001111111111111111100000000000000001111111111111111000000000000000011111111111111110000000000000000011111111111110000000000000000000001111111111000000000";
                    break;
                    default:
                    leitura="0000000000000011110000000000000000000000000111111111000000000000000000000111111111111000000000000000000011111111111110000000000000000001111111111111111000000000000000011111100001111111110000000000000111110000001111111100000000000011111000000000111111000000000000111110000000001111110000000000001111110000000011111100000000000001111111000000111110000000000000011111111111111111100000000000000001111111111111111000000000000000001111111111111110000000000000000000011111111111100000000000000000000011111111111000000000000000000000000000111110000000000000000000000000001111100000000000000000000000000001111000000000000000000000000000011110000000000000000000000000000111100000000000000000000000000001111000000000000000000000000000011110000000000000000000000000000011100000000000000000000000000001111100000000000000000000000000001111000000000000001111110000000011110000000000000011111111100001111100000000000000111111111111111111000000000000000111111111111111110000000000000001111111111111110000000000000000000011111111111100000000";
                    break;
                    }

                    int idx = 0;
                    for(int i = 0 ; i < matrixHeight ; i+=1)
                    {
                        for(int j = 0 ; j < matrixWidth;j+=1)
                        {
                            matrix[j][i].setFillColor(corFundo);
                            if(leitura.at(idx++)=='1')
                            {
                                matrix[j][i].setFillColor(corDesenho);
                            }
                        }
                    }
                    txtSaida.setString("?");
                 }



                }


            //pincel acompanha o movimento do mouse
            if (event.type == sf::Event::MouseMoved)
            {
                sf::Vector2f mousePos = window.mapPixelToCoords(sf::Vector2i(event.mouseMove.x-pincel.getSize().x/2, event.mouseMove.y-pincel.getSize().y/2)); // Converter as coordenadas do mouse para as coordenadas da janela
                // se estiver dentro da janela de desenho o pincel aparece
                if(mousePos.y>0 && mousePos.y < 512 && mousePos.x>0 && mousePos.x<512)
                {
                    pincel.setPosition(mousePos);
                }
                else
                {
                    pincel.setPosition(sf::Vector2f(-64.f,-64.f));
                }
            }

            // Verificar se o botão foi clicado
            if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left)
            {
                isDrawing = true;
            }

            if (event.type == sf::Event::MouseButtonReleased)
            {
                // Parar de desenhar
                isDrawing = false;
            }

            else if (event.type == sf::Event::MouseMoved && isDrawing)
            {
                // se o botao do mouse não for liberado e houver colisão com da matriz com o pincel , a matriz será desenhada sob o pincel
                for (int i = 0; i < matrixWidth; i++)
                {
                    for (int j = 0; j < matrixHeight; j++)
                    {
                        if(matrix[i][j].getGlobalBounds().intersects(pincel.getGlobalBounds()))
                        {
                            matrix[i][j].setFillColor(corDesenho);
                        }
                    }
                }

            }


        window.clear();

        // Desenhar a matriz na janela
        for (int i = 0; i < matrixWidth; i++)
        {
            for (int j = 0; j < matrixHeight; j++)
            {
                window.draw(matrix[i][j]);
            }
        }

        //Desenhar objetos
        window.draw(pincel);
        window.draw(caixaSaida);
        window.draw(txtSaida);
        botaoApagar.exibir(window);
        botaoPreencher.exibir(window);
        botaoReconhecer.exibir(window);


        for(int i = 0 ; i < 6;i++)
        {
            window.draw(botaoConfigPincel[i]);
        }
        window.draw(txtMenos);
        window.draw(txtMais);

        //Imprime os objetos na tela
        window.display();
        }
    }

    return 0;
}
