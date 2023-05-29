#ifndef RN_H_INCLUDED
#define RN_H_INCLUDED

//#include <iostream>
#include <vector>
//#include <cmath>


class Neuronio
{
    int qEntrada = 0;
    double pesoEntrada[100];
    Neuronio *neuroEntrada[100];
    double valor=0.0;
    double bias=0.0;
    int indice=0;

    public:

    Neuronio(int qEntrada, double bias);
    setValor(double valor);
    double getValor();
    somaValor(double valor);
    setNeuroEntrada(Neuronio *neuro, double peso);
    double getPeso(int i );
    Neuronio* getNeuroSaida(int indice);
    int getQuantSaida();
    double somaPonderadaPBias();
    double relu(double v);
    double softMax(double somaExp);
};

void SoftMax(std::vector<Neuronio*> &camada);
int classificacao(std::vector<Neuronio*> saida);
void atualizarCamadaRELU(std::vector<Neuronio*> camada);
void atualizarCamadaSoftmax(std::vector<Neuronio*> camada);

#endif // RN_H_INCLUDED
