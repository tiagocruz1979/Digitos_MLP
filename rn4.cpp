#include <iostream>
#include <vector>


class Neuronio
{
    int qSaida = 0;
    Neuronio *neuroSaida[100];
    double pesoSaida[100];
    double valor=0.0;
    double threshold = 0.0;
    int indice=0;

    public:

    Neuronio(int qSaida, double threshold)
    {
        this->qSaida=qSaida;
        this->threshold=threshold;
        this->indice=0;
        this->valor=0.0;
    }

    double getThreshold()
    {
        return this->threshold;
    }
    int getqSaida()
    {
        return this->qSaida;
    }

    setValor(double valor)
    {
        this->valor = valor;
    }
    double getValor()
    {
        return this->valor;
    }

    somaValor(double valor)
    {
        this->valor=this->valor+valor;
    }

    setNeuroSaida(Neuronio *neuro, double peso)
    {
        this->neuroSaida[indice] = neuro;
        this->pesoSaida[indice] = peso;
        indice++;
    }

    double getPeso(int i )
    {
        return pesoSaida[i];
    }

    Neuronio* getNeuroSaida(int indice)
    {
        return neuroSaida[indice];
    }

    int getQuantSaida()
    {
        return this->indice;
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


Neuronio e1(4,3.17614);
Neuronio e2(4,-3.18059);
Neuronio e3(4,-3.03918);
Neuronio e4(4,-3.042027);
e1.setValor(1);
e2.setValor(1);
e3.setValor(1);
e4.setValor(1);


Neuronio h1(4,0.298400);
Neuronio h2(4,0.5506623);
Neuronio h3(4,0.4200062);
Neuronio h4(4,0.3767315);

Neuronio s1(1,1.0);
Neuronio s2(1,1.0);
Neuronio s3(1,1.0);
Neuronio s4(1,1.0);

e1.setNeuroSaida(&h1,-1.543604);
e1.setNeuroSaida(&h2,-2.462571);
e1.setNeuroSaida(&h3,-2.121344);
e1.setNeuroSaida(&h4,-1.934074);

e2.setNeuroSaida(&h1,1.594021);
e2.setNeuroSaida(&h2,2.429903);
e2.setNeuroSaida(&h3,2.088415);
e2.setNeuroSaida(&h4,1.962861);

e3.setNeuroSaida(&h1,-0.887545);
e3.setNeuroSaida(&h2,-0.851645);
e3.setNeuroSaida(&h3,-0.762553);
e3.setNeuroSaida(&h4,-0.788466);

e4.setNeuroSaida(&h1,-0.907751);
e4.setNeuroSaida(&h2,-0.808199);
e4.setNeuroSaida(&h3,-0.736405);
e4.setNeuroSaida(&h4,-0.795331);


h1.setNeuroSaida(&s1,1.059869);
h1.setNeuroSaida(&s2,0.7554732);
h1.setNeuroSaida(&s3,1.669852);
h1.setNeuroSaida(&s4,0.8442662);

h2.setNeuroSaida(&s1,1.3096911);
h2.setNeuroSaida(&s2,0.992474);
h2.setNeuroSaida(&s3,2.261861);
h2.setNeuroSaida(&s4,1.140787);

h3.setNeuroSaida(&s1,1.234604);
h3.setNeuroSaida(&s2,0.8740399);
h3.setNeuroSaida(&s3,2.0445345);
h3.setNeuroSaida(&s4,1.0325925);

h4.setNeuroSaida(&s1,1.146811);
h4.setNeuroSaida(&s2,0.8709550);
h4.setNeuroSaida(&s3,1.953618);
h4.setNeuroSaida(&s4,0.9827710);


std::vector<Neuronio*> camada1{&e1,&e2,&e3,&e4};
std::vector<Neuronio*> camada2{&h1,&h2,&h3,&h4};
std::vector<Neuronio*> camada3{&s1,&s2,&s3,&s4};


int tam = camada1.size();
for(int i = 0 ; i < tam;i++)
{
    Neuronio *nEnt = camada1.at(i);
    int q = nEnt->getQuantSaida();
    for(int j = 0 ; j < q ;j++)
    {
        Neuronio* nSaida = nEnt->getNeuroSaida(j);
        double valor = nEnt->getValor() * nEnt->getPeso(j);
        nSaida->somaValor(valor);
    }
}

tam = camada2.size();
for(int i = 0 ; i < tam;i++)
{
    Neuronio *nEnt = camada2.at(i);
    int q = nEnt->getQuantSaida();

    for(int j = 0 ; j < q ;j++)
    {
        Neuronio* nSaida = nEnt->getNeuroSaida(j);
        double valor = nEnt->getValor() * nEnt->getPeso(j);
        nSaida->somaValor(valor);
    }
}




std::cout << "Saída da camada de entrada getValor()\n";
for(int i = 0 ; i < 4;i++)
{
    std::cout << camada1.at(i)->getValor() << " ";
}
std::cout << '\n';

std::cout << "Saída da camada2 getValor()\n";
for(int i = 0 ; i < 4;i++)
{
    std::cout << camada2.at(i)->getValor() << " ";
}
std::cout << '\n';

std::cout << "Saída da ultima camada getValor()\n";
for(int i = 0 ; i < 4;i++)
{
    std::cout << camada3.at(i)->getValor() << " ";
}
std::cout << '\n';



return 0;
}
