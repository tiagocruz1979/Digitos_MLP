//#include <iostream>
//#include <vector>
#include <cmath>
#include "rn.h"


    Neuronio::Neuronio(int qEntrada, double bias)
    {
        this->qEntrada = qEntrada;
        this->bias = bias;

    }

    Neuronio::setValor(double valor)
    {
        this->valor = valor;
    }
    double Neuronio::getValor()
    {
        return this->valor;
    }

    Neuronio::somaValor(double valor)
    {
        this->valor=this->valor+valor;
    }

    Neuronio::setNeuroEntrada(Neuronio *neuro, double peso)
    {
        this->neuroEntrada[indice] = neuro;
        this->pesoEntrada[indice] = peso;
        indice++;
    }

    double Neuronio::getPeso(int i )
    {
        return pesoEntrada[i];
    }

    Neuronio* Neuronio::getNeuroSaida(int indice)
    {
        return neuroEntrada[indice];
    }

    int Neuronio::getQuantSaida()
    {
        return this->indice;
    }

    double Neuronio::somaPonderadaPBias()
    {
        double soma = 0.0;
        for(int i = 0 ; i < qEntrada ;i++)
        {
            soma+=neuroEntrada[i]->getValor()*pesoEntrada[i];
        }
        return soma+this->bias;
    }

    double Neuronio::relu(double v)
    {
        return (v<0)?0:v;
    }

    double Neuronio::softMax(double somaExp)
    {
        return std::exp(this->getValor()) / somaExp;
    }

void SoftMax(std::vector<Neuronio*> &camada)
{
    int tam = camada.size();
    double somaExp = 0.0;
    for (int i = 0 ; i < tam ; i++)
    {
        Neuronio* n = camada.at(i);
        somaExp+= std::exp(n->getValor());
    }
    for (int i = 0 ; i < tam ; i++)
    {
        Neuronio* n = camada.at(i);
        n->setValor(std::exp(n->getValor())/somaExp);
    }

}

int classificacao(std::vector<Neuronio*> saida)
{
    int tam = saida.size();
    int idx = 0;
    double maior = 0.0;
    for(int i = 0 ; i < tam ; i++)
    {
        Neuronio* n = saida.at(i);
        double valor = n->getValor();
        if(valor>maior)
        {
            maior = valor;
            idx = i;
        }
    }
    return idx;
}

void atualizarCamadaRELU(std::vector<Neuronio*> camada)
{
    int tam = camada.size();
    for(int i = 0 ; i < tam;i++)
    {
        Neuronio *n = camada.at(i);
        double soma = n->somaPonderadaPBias();
        n->setValor(n->relu(soma));
    }
}

void atualizarCamadaSoftmax(std::vector<Neuronio*> camada)
{
    int tam = camada.size();
    for(int i = 0 ; i < tam;i++)
    {
        Neuronio *n = camada.at(i);
        double soma = n->somaPonderadaPBias();
        n->setValor(soma);
     }
    // aplicar função softmax na camada
    SoftMax(camada);
}
