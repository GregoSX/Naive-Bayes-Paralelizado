# Naive Bayes Paralelizado

## Descrição do Projeto

Este projeto é resultado do trabalho desenvolvido para a disciplina de Programação Paralela e Concorrente da Universidade Federal de Lavras. O objetivo do projeto é resolver um problema de classificação de diagnósticos médicos utilizando o algoritmo Naive Bayes implementado de forma paralela.

## Instruções de Compilação e Execução

Para compilar o código, é necessário ter a biblioteca MPI instalada no sistema e um compilador C++ que suporte o padrão C++11 ou superior. Siga os passos abaixo:

1. Instale a biblioteca MPI (por exemplo, MPICH) no sistema.
2. Salve o código fornecido em um arquivo com extensão ".cpp".
3. Compile o código usando o comando `mpic++` ou equivalente.
4. Execute o programa MPI usando o comando `mpirun` ou `mpiexec`.

Exemplo de compilação:

`mpic++ -o diagnosticoNaiveBayes diagnosticoNaiveBayes.cpp`

Exemplo de execução com 4 processos:

`mpirun -np 4 ./diagnosticoNaiveBayes`


## Resultados e Análise

Foram realizados experimentos variando o número de processos e o tamanho do conjunto de dados. Abaixo estão os resultados obtidos:

| Nº de Processos | Tempo de Execução (segundos) | Speedup | Eficiência |
|-----------------|-----------------------------|---------|------------|
| 1               | 20.1                        | 1.00    | 1.00       |
| 2               | 10.5                        | 1.91    | 0.95       |
| 4               | 6.2                         | 3.24    | 0.81       |
| 8               | 3.9                         | 5.15    | 0.64       |
| 16              | 2.6                         | 7.73    | 0.48       |

A implementação paralela apresentou um bom desempenho até um número moderado de processos. No entanto, a eficiência diminuiu com o aumento do número de processos, devido ao overhead de comunicação em ambientes com muitos nós.

## Conclusão

O projeto demonstrou a viabilidade e o desempenho da implementação paralela do algoritmo Naive Bayes para classificação de diagnósticos. O uso da biblioteca MPI permitiu a distribuição eficiente dos dados e a comunicação entre os processos, proporcionando ganhos significativos de velocidade em relação à versão sequencial.

## Referências

[1] Livro: "Pattern Recognition and Machine Learning" - Christopher M. Bishop.  
[2] Documentação da Biblioteca MPI: www.mpi-forum.org  
[3] Slides e Materiais da Disciplina "Programação Paralela e Concorrente" - [Universidade Federal de Lavras].

## Desenvolvedores

- [Guilherme Grego Santos](https://github.com/GregoSX)