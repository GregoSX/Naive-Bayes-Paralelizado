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

using namespace std;

// Estrutura de dados para armazenar os dados de diagnóstico
struct DiagnosisData {
    string temperature;
    string cough;
    bool hasDisease;
};

// Função para treinar o modelo Naive Bayes
void trainNaiveBayes(vector<DiagnosisData>& localData, double& probHasDisease, double& probNoDisease) {
    int numHasDisease = 0;
    int numNoDisease = 0;

    //Aqui, você deve calcular as probabilidades P(doença) e P(não_doença)
    for (const auto& data : localData) {
        if (data.hasDisease) {
            numHasDisease++;
        } else {
            numNoDisease++;
        }
    }

    probHasDisease = static_cast<double>(numHasDisease) / localData.size();
    probNoDisease = static_cast<double>(numNoDisease) / localData.size();
}

// Função para classificar os diagnósticos
void classifyDiagnosis(vector<DiagnosisData>& localData, double probHasDisease, double probNoDisease) {
    for (const auto& data : localData) {
        double probHasDiseaseGivenData = probHasDisease;
        double probNoDiseaseGivenData = probNoDisease;

        // Aqui, você deve calcular as probabilidades condicionais P(doença|dados) e P(não_doença|dados)
        // Usando a suposição "naive" de independência entre os atributos
        // Por exemplo, P(doença|dados) = P(temperatura|doença) * P(tosse|doença) * P(doença) e assim por diante

        // Aqui você pode imprimir a classificação para cada diagnóstico
        // Ou armazená-la em uma estrutura de dados para posterior análise
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
    startTime = = MPI_Wtime();  

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &numProcesses);

    // Cada nó possui uma parte do conjunto de dados
    // Aqui, apenas para fins de exemplo, estou criando um conjunto de dados manualmente
    // Você deve carregar os dados corretamente do seu conjunto de dados real
    DiagnosisData data1 = { "normal", "no", false };
    DiagnosisData data2 = { "high", "yes", true };
    DiagnosisData data3 = { "high", "no", true };
    DiagnosisData data4 = { "normal", "yes", false };

    allData.push_back(data1);
    allData.push_back(data2);
    allData.push_back(data3);
    allData.push_back(data4);

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
    cout << "\nProcess's processing time: " << (endTime - startTime) << "s" << endl;
    return 0;
}
