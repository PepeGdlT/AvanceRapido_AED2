#include <iostream>
#include <fstream>
#include <cstdlib>
#include <ctime>

using namespace std;

void generarCasosPrueba(int numeroCasos, int valorMaximoN, int valorMaximoV, int valorMaximoMoneda) {
    ofstream outputFile("casos_prueba.txt");

    // Semilla para la generación de números aleatorios
    srand(time(NULL));

    outputFile << numeroCasos << endl;

    for (int i = 0; i < numeroCasos; ++i) {
        int N = rand() % valorMaximoN + 1; // Genera un valor aleatorio para N entre 1 y valorMaximoN
        int V = rand() % valorMaximoV + 1; // Genera un valor aleatorio para V entre 1 y valorMaximoV

        outputFile << N << " " << V << endl;

        for (int j = 0; j < N; ++j) {
            int valorMoneda = rand() % valorMaximoMoneda + 1; // Genera un valor aleatorio para la moneda entre 1 y valorMaximoMoneda
            outputFile << valorMoneda;
            if (j != N - 1) {
                outputFile << " ";
            }
        }
        outputFile << endl;

        for (int j = 0; j < N; ++j) {
            int pesoMoneda = rand() % valorMaximoMoneda + 1; // Genera un peso aleatorio para la moneda entre 1 y valorMaximoMoneda
            outputFile << pesoMoneda;
            if (j != N - 1) {
                outputFile << " ";
            }
        }
        outputFile << endl;
    }

    outputFile.close();
}

int main() {
    int numeroCasos = 1; // Número de casos de prueba a generar
    int valorMaximoN = 1000; // Máximo valor para N
    int valorMaximoV = 2000; // Máximo valor para V
    int valorMaximoMoneda = 150; // Máximo valor para las monedas

    generarCasosPrueba(numeroCasos, valorMaximoN, valorMaximoV, valorMaximoMoneda);

    cout << "Casos de prueba generados correctamente." << endl;

    return 0;
}
