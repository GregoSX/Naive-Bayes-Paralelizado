#ifndef DATASETS_H
#define DATASETS_H

#include <string>
#include <vector>

using namespace std;

// Estrutura de dados para armazenar os dados de diagnóstico
struct DiagnosisData {
    string temperature;
    string cough;
    bool hasDisease;
};

// Dataset fictício de COVID-19 
vector<DiagnosisData> covid19SymptomsDataset = {
    { "normal", "no", false },
    { "high", "yes", true },
    { "high", "no", true },
    { "normal", "yes", false },
    { "normal", "no", false },
    { "high", "no", true },
    { "normal", "yes", true },
    { "high", "yes", true },
    { "high", "yes", false },
    { "normal", "no", true },
    { "high", "no", true },
    { "normal", "yes", false },
    { "normal", "yes", false },
    { "high", "no", true },
    { "normal", "yes", true },
    { "high", "yes", true },
    { "normal", "no", true },
    { "high", "yes", false },
    { "normal", "yes", false },
    { "normal", "no", true },
    { "high", "no", true },
    { "normal", "yes", false },
    { "normal", "no", false },
    { "high", "yes", true },
    { "high", "yes", true },
    { "normal", "yes", false },
    { "normal", "no", false },
    { "high", "yes", false },
    { "normal", "yes", true },
    { "high", "yes", true },
    { "high", "yes", false },
    { "normal", "no", true },
    { "high", "no", true },
    { "normal", "yes", false },
    { "normal", "yes", false },
    { "high", "no", true },
    { "normal", "yes", true },
    { "high", "yes", true },
    { "normal", "no", true },
    { "high", "yes", false },
    { "normal", "yes", false },
    { "normal", "no", true },
    { "high", "no", true },
    { "normal", "yes", false },
    { "high", "yes", true },
    { "normal", "yes", false },
    { "normal", "no", false },
    { "high", "yes", true },
    { "high", "no", true },
    { "normal", "yes", true },
    { "normal", "no", true },
    { "high", "yes", true },
    { "high", "yes", false },
    { "normal", "no", true },
    { "normal", "yes", false },
    { "normal", "yes", false },
    { "high", "no", true },
    { "normal", "yes", true },
    { "high", "yes", true },
    { "normal", "no", true },
    { "high", "yes", false },
    { "normal", "no", false },
    { "high", "no", true },
    { "normal", "yes", true },
    { "normal", "yes", false },
    { "high", "yes", false }  
};

#endif // DATASETS_H