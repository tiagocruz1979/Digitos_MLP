#include <iostream>
#include <vector>


class Neuronio
{
    double pesoEntrada[100];
    int qEntrada;
    double valor=0;

    public:

    Neuronio(int qEntrada, double p[100] )
    {
        this->qEntrada=qEntrada;
        for (int i = 0 ; i < qEntrada; i++)
        {
            this->pesoEntrada[i]=p[i];
        }
    }

    double getPesoN(int n)
    {
        if(n<=qEntrada)
        {
            return pesoEntrada[n];
        }
        return 0.0;
    }

    setValor(double v)
    {
        this->valor = v;
    }
    double getValor()
    {
        return this->valor;
    }

    int getTamanho()
    {
        return this->qEntrada;
    }

};

class Camada
{

};



int main(){

//exemplos  de treinamento
//  +1 -1 +1 +1     = +1
//  -1 -1 -1 -1     = -1
//  +1 +1 +1 +1     = +1
//  -1 -1 -1 +1     = -1
//  -1 -1 +1 +1     = +1
//  +1 +1 -1 +1     = +1

Neuronio e1(1,new double[1]{1.0});
Neuronio e2(1,new double[1]{1.0});
Neuronio e3(1,new double[1]{1.0});
Neuronio e4(1,new double[1]{1.0});
e1.setValor(1);
e2.setValor(1);
e3.setValor(-1);
e4.setValor(1);
std::vector<Neuronio> camada1{e1,e2,e3,e4};



Neuronio s1(4,new double[4]{0.9,-0.6,0.2,0.4});
std::vector<Neuronio> camada2{s1};

int x = 1;
int y = 4;

for(int i = 0 ; i < x ;i++)
{
    std::cout << '.';
    double valor = 0.0;
    for(int j = 0 ; j < y ;j++)
    {
        valor+=camada1.at(j).getValor() * camada2.at(i).getPesoN(j);
    }

    if(valor>0.0)
    {
        camada2.at(i).setValor(1);
    }
    else
    {
        camada2.at(i).setValor(-1);
    }
}

x = 2;
y = 2;



std::cout << "\nCamada1 getValor: ";
for(int i = 0 ; i < 4;i++)
{
    std::cout << camada1.at(i).getValor() << " ";
}
std::cout << "\nCamada2 getValor: ";
for(int i = 0 ; i < 1;i++)
{
    std::cout << camada2.at(i).getValor() << " ";
}















return 0;
}
