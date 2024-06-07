#include <iostream>
#include <fstream>
#include <cassert>
#include <cmath>
#include <vector>
#include <algorithm>
#include <chrono>
using namespace std;

#define MAXIMO_MONEDAS 300

struct Moneda {
    int valor, peso, posArrayOriginal;
    double ratio;
};

bool sumaDeArrays(int a[], int b[], int N, int V, vector<Moneda> monedas) {
    bool result = false;
    int sumaA = 0;
    int sumaB = 0;
    for(int i = 0; i < N; i++) {
        sumaA += a[i] * monedas[i].valor;
        sumaB += b[i] * monedas[i].valor;
    }
    if(sumaA == V && sumaB == V) {
        result = true;
    }
    return result;
}

bool CriterioMenorRatio(Moneda a, Moneda b) {
    return a.ratio < b.ratio;
}

bool ComparacionOriginal(Moneda a, Moneda b) {
    return a.posArrayOriginal < b.posArrayOriginal;
}

void monedas(int N, int V, int v[], int p[]) {
    assert(N <= MAXIMO_MONEDAS);

    int *monedasEntregadas = new int[N];
    int *monedasRecibidas = new int[N];

    vector<Moneda> monedas;

    for(int i = 0; i < N; i++) {
        monedasEntregadas[i] = 0;
        monedasRecibidas[i] = 0;
        Moneda dato;
        dato.valor = v[i];
        dato.peso = p[i];
        dato.posArrayOriginal = i;
        dato.ratio = static_cast<double>(v[i]) / p[i];
        monedas.push_back(dato);
    }

    sort(monedas.begin(), monedas.end(), CriterioMenorRatio);

    int valorAct = 0;
    int pesoEnt = 0;
    int monedasAIntroducir = 0;
    for(Moneda moneda : monedas) {
        if (moneda.valor < V) {
            monedasAIntroducir = floor((V - valorAct) / moneda.valor);
            monedasEntregadas[moneda.posArrayOriginal] = monedasAIntroducir;
            valorAct += monedasAIntroducir * moneda.valor;
            pesoEnt += monedasAIntroducir * moneda.peso;
        }
    }

    valorAct = 0;
    int pesoRec = 0;
    monedasAIntroducir = 0;
    for(int i = N - 1; i >= 0; i--) {
        if (monedas[i].valor < V) {
            monedasAIntroducir = floor((V - valorAct) / monedas[i].valor);
            monedasRecibidas[monedas[i].posArrayOriginal] = monedasAIntroducir;
            valorAct += monedasAIntroducir * monedas[i].valor;
            pesoRec += monedasAIntroducir * monedas[i].peso;
        }
    }

    sort(monedas.begin(), monedas.end(), ComparacionOriginal);

    if(!sumaDeArrays(monedasEntregadas, monedasRecibidas, N, V, monedas)) {
        cout << "NO HAY SOLUCION" << endl;
    }
    else {
        int pesoAhorrado = pesoEnt - pesoRec;
        cout << pesoAhorrado << endl;
        for (int i = 0; i < N; i++) {
            if (i != N - 1) {
                cout << monedasEntregadas[i] << " ";
            } else {
                cout << monedasEntregadas[i];
                cout << endl;
            }
        }
        for (int i = 0; i < N; i++) {
            if (i != N - 1) {
                cout << monedasRecibidas[i] << " ";
            } else {
                cout << monedasRecibidas[i] << endl;
            }
        }
    }

    delete[] monedasEntregadas;
    delete[] monedasRecibidas;
}

int main() {
    ifstream inputFile("entrada.txt"); // Nombre de tu archivo de entrada
    int numeroCasos;
    inputFile >> numeroCasos;

    int N, V;
    auto start_time = chrono::high_resolution_clock::now();
    while (numeroCasos > 0) {
        inputFile >> N >> V;
        int *v = new int[N];
        int *p = new int[N];

        int dato;
        for (int i = 0; i < N; i++) {
            inputFile >> dato;
            v[i] = dato;
        }
        for (int i = 0; i < N; i++) {
            inputFile >> dato;
            p[i] = dato;
        }

        monedas(N, V, v, p);

        delete[] v;
        delete[] p;
        numeroCasos--;
    }
    auto end_time = chrono::high_resolution_clock::now();

    auto duration_ms = chrono::duration_cast<chrono::milliseconds>(end_time - start_time).count();

    cout << "Tiempo: " << duration_ms << " milisegundos." << endl;

    return 0;
}
