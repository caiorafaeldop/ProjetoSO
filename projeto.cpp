#include <iostream>
#include <vector>
#include <limits>
#include <iomanip>

struct Processo
{
  int entrar;
  int demora;
};

float calcularMedia(const std::vector<int> &vetor)
{
  int soma = 0;
  for (int valor : vetor)
  {
    soma += valor;
  }

  if (vetor.size() > 0)
  {
    float media = static_cast<float>(soma) / vetor.size();
    return media;
  }
  else
  {
    return 0.0;
  }
}

void sjf(const std::vector<Processo> &processos)
{
  int time = 0;
  bool doing = false;
  // int trespera[processos.size()];
  std::vector<bool> entered(processos.size(), false);
  std::vector<int> tempodeResposta(processos.size());
  std::vector<int> tempodeRetorno(processos.size());
  int i = 0;
  int ii = 0;
  int jumpEnterProcess = 0;
  int menorDemora = std::numeric_limits<int>::max();
  while (time < 46)
  {
    i = 0;
    bool existeProcesso = false;
    int tempodeEntrada, tempofazendo;
    for (const Processo &processo : processos)
    {
      // std::cout << "demora: " << processo.demora << ", entrar: " << processo.entrar << std::endl;
      if ((processo.entrar <= time) && !entered[i])
      {
        existeProcesso = true;
        if (processo.demora < menorDemora)
        {
          menorDemora = processo.demora;
          ii = i;
          tempodeEntrada = processo.entrar;
          tempofazendo = processo.demora;
        }
      }
      i++;
    }
    // std::cout << "\nna passada do time: " << time << " a menor demora ta no: " << ii << std::endl;

    if (!doing and existeProcesso)
    {
      jumpEnterProcess = menorDemora - 1;
      doing = true;
      entered[ii] = true;
      tempodeResposta[ii] = time - tempodeEntrada;
      tempodeRetorno[ii] = time - tempodeEntrada + tempofazendo;
      menorDemora = std::numeric_limits<int>::max();
    }
    else
    {
      jumpEnterProcess--;
      if (jumpEnterProcess == 0)
      {
        doing = false;
      }
    }

    // std::cout << "\nna passada do time: " << time << " jumpEnterProcess eh: " << jumpEnterProcess << " sou o processo: " << ii << std::endl;

    time++;
  }
  /*
  std::cout << "\ntempodeResposta: ";
  for (int i = 0; i < tempodeResposta.size(); i++)
  {
    std::cout << tempodeResposta[i] << " ";
  }
  std::cout << std::endl;
  std::cout << "\ntempodeEspera: ";
  for (int i = 0; i < tempodeResposta.size(); i++)
  {
    std::cout << tempodeResposta[i] << " ";
  }
  std::cout << std::endl;
  std::cout << "\ntempodeRetorno: ";
  for (int i = 0; i < tempodeRetorno.size(); i++)
  {
    std::cout << tempodeRetorno[i] << " ";
  }
  std::cout << "\n " << std::endl;
  */
  float mediaResp = calcularMedia(tempodeResposta);
  float mediaEsp = mediaResp;
  float mediaRet = calcularMedia(tempodeRetorno);

  std::cout << "\nSJF " << std::fixed << std::setprecision(1) << mediaResp << " " << mediaEsp << " " << mediaRet << "\n"
            << std::endl;
}

int main()
{
  std::vector<Processo> processos = {{1, 25}, {1, 3}, {1, 6}, {1, 5}, {2, 2}, {2, 4}};
  sjf(processos);
  return 0;
}