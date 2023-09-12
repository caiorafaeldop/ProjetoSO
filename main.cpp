#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>

using namespace std;

int main()
{
  ifstream inputFile("dados.txt"); // Altere o nome do arquivo conforme necessário

  if (!inputFile.is_open())
  {
    cout << "Nao foi possível abrir o arquivo." << endl;
    return 1;
  }

  vector<pair<int, int>> dados;
  int entrada, tempo;

  while (inputFile >> entrada >> tempo)
  {
    dados.emplace_back(entrada, tempo);
  }

  inputFile.close();

  cout << "Dados lidos do arquivo:" << endl;

  for (const auto &par : dados)
  {
    cout << "Entrada: " << par.first << " Tempo: " << par.second << endl;
  }

  return 0;
}
