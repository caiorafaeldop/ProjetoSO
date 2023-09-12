#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <algorithm>
#include <iomanip>

using namespace std;

struct Processo
{
  int entrada;
  int tempo;
};

bool compararTempo(const Processo &p1, const Processo &p2)
{
  return p1.tempo < p2.tempo;
}

void escalonadorSJF(const vector<Processo> &processos)
{
  vector<Processo> processosOrdenados = processos;
  sort(processosOrdenados.begin(), processosOrdenados.end(), compararTempo);

  double tempoRetornoTotal = 0;
  double tempoRespostaTotal = 0;
  double tempoEsperaTotal = 0;

  int tempoAtual = 0;

  cout << "SJF ";

  for (const Processo &processo : processosOrdenados)
  {
    tempoRetornoTotal += tempoAtual + processo.tempo - processo.entrada;
    tempoRespostaTotal += tempoAtual - processo.entrada;
    tempoEsperaTotal += tempoAtual - processo.entrada;

    cout << processo.tempo << ",";

    tempoAtual += processo.tempo;
  }

  double tempoRetornoMedio = tempoRetornoTotal / processosOrdenados.size();
  double tempoRespostaMedio = tempoRespostaTotal / processosOrdenados.size();
  double tempoEsperaMedio = tempoEsperaTotal / processosOrdenados.size();

  cout << " " << fixed << setprecision(1) << tempoRetornoMedio
       << " " << fixed << setprecision(1) << tempoRespostaMedio
       << " " << fixed << setprecision(1) << tempoEsperaMedio << endl;
}

int main()
{
  // Lê os processos do arquivo dados.txt
  ifstream inputFile("dados.txt");

  if (!inputFile.is_open())
  {
    cout << "Não foi possível abrir o arquivo." << endl;
    return 1;
  }

  vector<Processo> processos;
  int entrada, tempo;

  while (inputFile >> entrada >> tempo)
  {
    processos.push_back({entrada, tempo});
  }

  inputFile.close();

  // escalonadorSJF(processos);
  cout << "Conteudo dos processos:" << endl;
  for (const Processo &processo : processos)
  {
    cout << "Entrada: " << processo.entrada << " Tempo: " << processo.tempo << endl;
  }
  return 0;
}
