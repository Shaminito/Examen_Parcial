#include <iostream>
#include <fstream>

using namespace std;

void cogerDatos(ifstream &fin);
void observarDatos();
void municipiosTotales();
void promedioAltura();
void alturaMaxima();
void alturaMinima();
void menosPoblado();
void masPoblado();

void menosDensidad();

void masDensidad();

void compararAvilaMadrid();

int municipios = 0;

struct provincia{
    int cp;
    string municipio;
    int poblacion;
    int altura;
    int superficie;
    provincia * sgt;
    provincia * ant;
};

provincia * peek;
provincia * lista;

int main() {
    ifstream fin("../AVILA.tsv");

    cogerDatos(fin);
    //observarDatos();
    municipiosTotales();
    promedioAltura();
    alturaMaxima();
    alturaMinima();
    menosPoblado();
    masPoblado();
    menosDensidad();
    masDensidad();
    compararAvilaMadrid();
}

void compararAvilaMadrid() {
    provincia * aux = lista;
    int poblacionAvila = 0;
    int poblacionMadrid = 6507184;
    while (aux != NULL){
        poblacionAvila += aux -> poblacion;
        aux = aux -> sgt;
    }
    int diferencia = poblacionMadrid / poblacionAvila;
    cout<<"La población de Madrid es "<<diferencia<<" veces más poblado que Ávila"<<endl;
}

void masDensidad() {
    provincia * aux = lista;
    provincia * provMayorDensidad = new provincia;
    int mayorDensidad = 0;
    while (aux != NULL){

        if(mayorDensidad < (aux -> poblacion / aux -> superficie)){
            provMayorDensidad = aux;
        }
        aux = aux -> sgt;
    }
    cout<<"El municipio es "<<provMayorDensidad->municipio<<" es menos denso."<<endl;
}

void menosDensidad() {
    provincia * aux = lista;
    provincia * provMenosDensidad = new provincia;
    int menorDensidad = 10000;
    while (aux != NULL){

        if(menorDensidad > (aux -> poblacion / aux -> superficie)){
            provMenosDensidad = aux;
        }
        aux = aux -> sgt;
    }
    cout<<"El municipio es "<<provMenosDensidad->municipio<<" es menos denso."<<endl;
}

void masPoblado() {
    provincia * aux = lista;
    provincia *provMasPob = new provincia;
    provMasPob -> poblacion = 0;
    while (aux != NULL){
        if(provMasPob ->poblacion < aux -> poblacion){
            provMasPob = aux;
        }
        aux = aux -> sgt;
    }
    cout<<"El municipio es "<<provMasPob->municipio<<" es menos poblado con "<<provMasPob->poblacion<<" habitantes."<<endl;
}

void menosPoblado() {
    provincia * aux = lista;
    provincia *provMinPob = new provincia;
    provMinPob -> poblacion = 10000;
    while (aux != NULL){
        if(provMinPob ->poblacion > aux -> poblacion){
            provMinPob = aux;
        }
        aux = aux -> sgt;
    }
    cout<<"El municipio es "<<provMinPob->municipio<<" es más poblado con "<<provMinPob->poblacion<<" habitantes."<<endl;
}

void alturaMinima() {
    provincia * aux = lista;
    provincia *provMin = new provincia;
    provMin -> altura = 10000;
    while (aux != NULL){
        if(provMin ->altura > aux -> altura){
            provMin = aux;
        }
        aux = aux -> sgt;
    }
    cout<<"El municipio es "<<provMin->municipio<<" con una altura mínima de: "<<provMin->altura<<endl;
}

void alturaMaxima() {
    provincia * aux = lista;
    provincia *provMax = new provincia;
    provMax -> altura = 0;
    while (aux != NULL){
        if(provMax ->altura < aux -> altura){
            provMax = aux;
        }
        aux = aux -> sgt;
    }
    cout<<"El municipio es "<<provMax->municipio<<" con una altura máxima de: "<<provMax->altura<<endl;
}

void promedioAltura() {
    provincia * aux = lista;
    int alturaTotal = 0;
    while (aux != NULL){
        alturaTotal += aux -> altura;
        aux = aux -> sgt;
    }
    cout<<"promedio: "<<alturaTotal / municipios<<endl;
}

void municipiosTotales() {
    cout << "Número de municipios totales en la provincia de Avila: " << municipios << endl;
}

void observarDatos() {
    provincia *aux = lista;
    while (aux != NULL){
        cout<<aux->municipio<<endl;
        aux = aux -> sgt;
    }
}

void cogerDatos(ifstream &fin) {
    try{
        while(!fin.eof()){
            if(!lista){
                provincia * prov = new provincia;
                fin >> prov->cp >> prov->municipio >> prov->poblacion >> prov->altura >> prov->superficie;
                prov -> sgt = NULL;
                prov -> ant = NULL;
                lista = prov;
                peek = prov;

            }
            else{
                provincia * prov = new provincia;
                fin >> prov->cp >> prov->municipio >> prov->poblacion >> prov->altura >> prov->superficie;
                peek -> sgt = prov;
                prov -> sgt = NULL;
                prov -> ant = peek;
                peek = prov;
            }
            //cout<<" "<<prov->cp<<" "<<prov->municipio<<" "<<prov->poblacion<<" "<<prov->altura<<" "<<prov->superficie<<endl;
            municipios++;
        }
    }
    catch(...){
        fin.close();
    }
}
