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


Neuronio e1(1,new double[1]{1.0});
Neuronio e2(1,new double[1]{1.0});
Neuronio e3(1,new double[1]{1.0});
e1.setValor(3);
e2.setValor(2);
e3.setValor(0);
std::vector<Neuronio> camada1{e1,e2,e3};


Neuronio h1(3,new double[3]{0.4,-0.6,0.2});
Neuronio h2(3,new double[3]{0.3,0.5,0.1});
std::vector<Neuronio> camada2{h1,h2};


Neuronio s1(2,new double[2]{0.5,0.7});
Neuronio s2(2,new double[2]{0.3,0.1});
std::vector<Neuronio> camada3{s1,s2};

int x = 2;
int y = 3;

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
        camada2.at(i).setValor(0);
    }
}

x = 2;
y = 2;

for(int i = 0 ; i < x ;i++)
{
    double valor = 0.0;
    for(int j = 0 ; j < y ;j++)
    {
        valor+=camada2.at(j).getValor() * camada3.at(i).getPesoN(j);
    }

    if(valor>0.0)
    {
        camada3.at(i).setValor(1);
    }
    else
    {
        camada3.at(i).setValor(0);
    }
}


std::cout << "\nCamada1 getValor: ";
for(int i = 0 ; i < 3;i++)
{
    std::cout << camada1.at(i).getValor() << " ";
}
std::cout << "\nCamada2 getValor: ";
for(int i = 0 ; i < 2;i++)
{
    std::cout << camada2.at(i).getValor() << " ";
}
std::cout << "\nCamada3 getValor: ";
for(int i = 0 ; i < 2;i++)
{
    std::cout << camada3.at(i).getValor() << " ";
}














return 0;
}
