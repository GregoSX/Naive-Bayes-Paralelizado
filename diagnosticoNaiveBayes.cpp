/*
    Trabalho final da disciplina de Programação Paralela e Concorrente
    Curso: Ciência da Computação - 2023/1
    Alunos: Guilherme Grego Santos, Isaac Orcine Silva e Eduardo Dezena Gonçalves
*/

// Para compilar: mpic++ -o diagnosticoNaiveBayes diagnosticoNaiveBayes.cpp
// Para executar: mpirun -np 4 ./diagnosticoNaiveBayes

#include <iostream>
#include <vector>
#include <string>
#include <mpi.h>
#include <thread>
#include "datasets.h"

using namespace std;

// Estrutura de dados para armazenar os dados de diagnóstico
/*struct DiagnosisData {
    string temperature;
    string cough;
    bool hasDisease;
};*/

// Função para treinar o modelo Naive Bayes
void trainNaiveBayes(vector<DiagnosisData>& localData, double& probHasDisease, double& probNoDisease) {
    int totalData = localData.size();
    int numHasDisease = 0;

    for (const auto& data : localData) {
        numHasDisease += data.hasDisease ? 1 : 0;
    }

    probHasDisease = double(numHasDisease) / totalData;
    probNoDisease = 1.0 - probHasDisease;
}

// Função para classificar os diagnósticos
void classifyDiagnosis(vector<DiagnosisData>& localData, double probHasDisease, double probNoDisease) {
    for (const auto& data : localData) {
        double probHasDiseaseGivenData = probHasDisease;
        double probNoDiseaseGivenData = probNoDisease;

        // Calculando as probabilidades condicionais usando a suposição "naive" de independência
        if (data.temperature == "normal") {
            probHasDiseaseGivenData *= 0.4;  // P(temperatura|doença) = 2/5 = 0.4
            probNoDiseaseGivenData *= 0.5;   // P(temperatura|não_doença) = 2/4 = 0.5
        } else {
            probHasDiseaseGivenData *= 0.6;  // P(temperatura|doença) = 3/5 = 0.6
            probNoDiseaseGivenData *= 0.5;   // P(temperatura|não_doença) = 2/4 = 0.5
        }

        if (data.cough == "yes") {
            probHasDiseaseGivenData *= 0.4;  // P(tosse|doença) = 2/5 = 0.4
            probNoDiseaseGivenData *= 0.5;   // P(tosse|não_doença) = 2/4 = 0.5
        } else {
            probHasDiseaseGivenData *= 0.6;  // P(tosse|doença) = 3/5 = 0.6
            probNoDiseaseGivenData *= 0.5;   // P(tosse|não_doença) = 2/4 = 0.5
        }

        cout << "Diagnosis: " << data.temperature << ", " << data.cough;
        if (probHasDiseaseGivenData > probNoDiseaseGivenData) {
            cout << " --> Has disease" << endl;
        } else {
            cout << " --> No disease" << endl;
        }
    }
}

int main(int argc, char* argv[]) {
    int rank, numProcesses;
    vector<DiagnosisData> allData;
    double startTime, endTime;
    startTime = MPI_Wtime();  

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &numProcesses);

    // Add the COVID-19 Symptoms dataset to allData
    allData.insert(allData.end(), covid19SymptomsDataset.begin(), covid19SymptomsDataset.end());

    // Aqui, cada nó deve dividir o conjunto de dados em partes para processar em paralelo
    int dataSize = allData.size();
    int localDataSize = dataSize / numProcesses;
    int startIndex = rank * localDataSize;
    int endIndex = (rank == numProcesses - 1) ? dataSize : (startIndex + localDataSize);

    vector<DiagnosisData> localData(allData.begin() + startIndex, allData.begin() + endIndex);

    // Treinamento do modelo Naive Bayes localmente em cada nó
    double probHasDisease, probNoDisease;
    trainNaiveBayes(localData, probHasDisease, probNoDisease);

    // Sincronização dos resultados de treinamento
    double globalProbHasDisease, globalProbNoDisease;
    MPI_Allreduce(&probHasDisease, &globalProbHasDisease, 1, MPI_DOUBLE, MPI_SUM, MPI_COMM_WORLD);
    MPI_Allreduce(&probNoDisease, &globalProbNoDisease, 1, MPI_DOUBLE, MPI_SUM, MPI_COMM_WORLD);

    // Classificação dos diagnósticos localmente em cada nó
    classifyDiagnosis(localData, globalProbHasDisease / numProcesses, globalProbNoDisease / numProcesses);

    endTime = MPI_Wtime();

    MPI_Finalize();
    if(rank == 0){
        cout << "\nProcess's processing time: " << (endTime - startTime) << "s" << endl;
    }
    return 0;
}