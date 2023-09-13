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

void fcfs(const std::vector<Processo> &processos)
{
  int time = 0;
  bool doing = false;
  std::vector<bool> entered(processos.size(), false);
  std::vector<int> tempodeResposta(processos.size());
  std::vector<int> tempodeRetorno(processos.size());
  int i;
  int lookingfor = 0;
  int abrir = std::numeric_limits<int>::max();
  while (time < 60)
  {
    i = 0;

    bool entreiAqui = false;
    if (!doing)
    {
      std::cout << "\nna passada do time: " << time << " nao estou fazendo nada, vou checar os processos agora\n"
                << std::endl;
      for (const Processo &processo : processos)
      {

        if ((processo.entrar <= lookingfor) && !entered[i] && !entreiAqui)
        {
          std::cout << "\nachei o que fazer: " << i << " sera processado a partir de agora\n"
                    << std::endl;

          entreiAqui = true;
          doing = true;
          entered[i] = true;
          tempodeResposta[i] = time - processo.entrar;
          tempodeRetorno[i] = time - processo.entrar + processo.demora;
          abrir = processo.demora - 1;
        }
        i++;
      }
      if (!entreiAqui)
      {
        lookingfor++;
      }
    }
    else
    {
      abrir--;
      std::cout << "\noi, estou no time: " << time << " e estou processando, falta agora: " << abrir
                << std::endl;
      if (abrir == 0)
      {
        doing = false;
      }
    }
    time++;
  }
  float mediaResp = calcularMedia(tempodeResposta);
  float mediaEsp = mediaResp;
  float mediaRet = calcularMedia(tempodeRetorno);

  std::cout << "\nFCFS " << std::fixed << std::setprecision(1) << mediaResp << " " << mediaEsp << " " << mediaRet << "\n"
            << std::endl;
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
}

// std::cout << "\nna passada do time: " << time << " a menor demora ta no: " << ii << std::endl;
/*
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
*/

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

int main()
{
  std::vector<Processo> processos = {{1, 25}, {2, 3}, {1, 6}, {2, 5}, {1, 2}, {2, 4}};
  fcfs(processos);
  return 0;
}