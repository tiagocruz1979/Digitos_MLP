#include <SFML/Graphics.hpp>
#include <iostream>

int main()
{
    // Definir o tamanho da janela
    sf::Vector2f windowSize(832.f,512.f);

    //criar a janela
    sf::RenderWindow window(sf::VideoMode(windowSize.x, windowSize.y), "Matriz de Desenho");

    // Configurar a cor do desenho
    sf::Color corFundo = sf::Color(10,10,50);
    sf::Color corDesenho = sf::Color(200,200,0);

    //botoes
    sf::Vector2f botaoTam1(160.f,50.f);

    sf::RectangleShape botaoApagar(botaoTam1);
    botaoApagar.setPosition(sf::Vector2f(600.f,100.f));
    botaoApagar.setFillColor(sf::Color::Blue);

    sf::RectangleShape botaoReconhecer(botaoTam1);
    botaoReconhecer.setPosition(sf::Vector2f(600.f,200.f));
    botaoReconhecer.setFillColor(sf::Color::Blue);


    //Fonte Padrao
    sf::Font font;
    font.loadFromFile("consola.ttf");

    //Texto para botoes
    sf::Text txtBotaoApagar("Apagar", font, 20);
    txtBotaoApagar.setPosition(botaoApagar.getPosition());
    txtBotaoApagar.move(sf::Vector2f(10.f,10.f));
    sf::Text txtBotaoReconhecer("Reconhecer", font, 20);
    txtBotaoReconhecer.setPosition(botaoReconhecer.getPosition());
    txtBotaoReconhecer.move(sf::Vector2f(10.f,10.f));

    //Texto para Saída
    sf::RectangleShape caixaSaida(sf::Vector2f(160.f,50.f));
    caixaSaida.setPosition(sf::Vector2f(600.f,300.f));
    caixaSaida.setFillColor(sf::Color::White);
    sf::Text txtSaida("-", font, 30);
    txtSaida.setFillColor(sf::Color::Red);
    txtSaida.setPosition(caixaSaida.getPosition());

    // Criar o retangulo para pincel
    sf::RectangleShape pincel(sf::Vector2f(24.f,24.f));
    pincel.setPosition(0.0f,0.0f);
    pincel.setFillColor(sf::Color::Green);

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
                if (botaoApagar.getGlobalBounds().contains(mousePos))
                {
                    // Botão clicado
                    std::cout << "Botao Apagar clicado!" << std::endl;
                    for(int i = 0 ; i < matrixHeight ; i++)
                    {
                        for(int j = 0 ; j < matrixWidth;j++)
                        {
                            matrix[i][j].setFillColor(corFundo);
                        }
                    }
                }

                // Verificar se o mouse está sobre o botão
                int vetSaida[64];
                if (botaoReconhecer.getGlobalBounds().contains(mousePos))
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

                    //mostrando resutlado do vetor de saída
                    for(int i = 0 ; i < 64;i++)
                    {
                        std::cout << vetSaida[i] << ",";
                    }
                    std::cout << '\n';
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
                    pincel.setPosition(sf::Vector2f(-50.f,-50.f));
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
        window.draw(botaoApagar);
        window.draw(txtBotaoApagar);
        window.draw(botaoReconhecer);
        window.draw(txtBotaoReconhecer);
        window.draw(caixaSaida);
        window.draw(txtSaida);

        //Imprime os objetos na tela
        window.display();
        }
    }

    return 0;
}
