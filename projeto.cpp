#include <iostream>
#include <vector>
#include <limits>
#include <iomanip>

struct Processo
{
  int entrar;
  int demora;
};

void rr(const std::vector<Processo> &processos)

{
  int time = 0;
  int quantum = 2;
  bool doing = false;
  std::vector<bool> entered(processos.size(), false);
  std::vector<bool> firstEntryBool(processos.size(), true);

  std::vector<int> tempodeResposta(processos.size());
  std::vector<int> tempodeRetorno(processos.size());
  std::vector<int> tempodeEspera(processos.size());

  int i;
  int lookingfor = 0;
  int abrir = std::numeric_limits<int>::max();
  bool umjaentrou = false;
  std::vector<int> fila;
  std::vector<int> demoras(processos.size());
  std::vector<int> demorasStatic(processos.size());
  std::vector<int> entrada(processos.size());

  while (time < 10 || !fila.empty())
  {
    std::cout << "\nOi, estou dentro do while no tempo " << time << "\n"
              << std::endl;
    int i = 0;

    for (const Processo &processo : processos)
    {
      if (processo.entrar <= time && !entered[i])
      {
        fila.push_back(i); // Adicione o valor 'i' no final da fila.
        demoras[i] = processo.demora;
        demorasStatic[i] = processo.demora;
        entrada[i] = processo.entrar;
        entered[i] = true;
        std::cout << "\nColocando na fila " << i << " e a demora dele: " << demoras[i] << " primeiro da fila: "
                  << fila[0]
                  << std::endl;
      }

      i++;
    }

    if (!fila.empty())
    {
      int vez = fila[0];
      if (firstEntryBool[vez])
      {
        firstEntryBool[vez] = false;
        tempodeResposta[vez] = time - entrada[vez];
      }
      quantum--;
      demoras[vez] -= 1;
      if (demoras[vez] == 0)
      {
        tempodeRetorno[vez] = time - entrada[vez] + 1;
        tempodeEspera[vez] = tempodeRetorno[vez] - demorasStatic[vez];

        fila.erase(fila.begin()); // Remova o primeiro elemento da fila.
        quantum = 2;
      }
      if (quantum == 0)
      {
        if (demoras[vez] > 0)
        {
          fila.push_back(vez); // Adicione de volta ao final da fila.
        }

        fila.erase(fila.begin()); // Remova o primeiro elemento da fila.
        quantum = 2;
      }
    }
    // coloque aqui para ele printar a fila
    std::cout << "Conteudo da fila: ";
    for (int processo : fila)
    {
      std::cout << processo << " ";
    }
    std::cout << std::endl;
    std::cout << "time: " << time
              << "\n"
              << std::endl;
    time++;
  }
  std::cout << "\ntempodeRetorno: ";
  for (int i = 0; i < tempodeRetorno.size(); i++)
  {
    std::cout << tempodeRetorno[i] << " ";
  }
  std::cout << "\n " << std::endl;
  std::cout << "\ntempodeEspera: ";
  for (int i = 0; i < tempodeEspera.size(); i++)
  {
    std::cout << tempodeEspera[i] << " ";
  }
  std::cout << "\ntempodeResposta: ";
  for (int i = 0; i < tempodeResposta.size(); i++)
  {
    std::cout << tempodeResposta[i] << " ";
  }
  std::cout << std::endl;
}
/*
    i = 0;
    bool incrementarTime = true;
    bool entreiAqui = false;
    if (!doing)
    {
      bool encerrar = true;
      for (bool value : entered)
      {
        if (!value)
        {
          encerrar = false;
        }
      }
      if (encerrar)
      {
        break;
      }

      for (const Processo &processo : processos)
      {

        if ((processo.entrar <= lookingfor) && !entered[i] && !entreiAqui)
        {
          umjaentrou = true;
          entreiAqui = true;
          doing = true;
          entered[i] = true;
          tempodeResposta[i] = time - processo.entrar;
          tempodeRetorno[i] = time - processo.entrar + processo.demora;
          abrir = processo.demora - 1;
        }
        i++;
      }
      bool temfalse = true;
      for (bool value : entered)
      {
        if (!value)
        {
          temfalse = false;
        }
      }
      if (!temfalse and !entreiAqui)
      {
        lookingfor++;
        if (time != 0 and umjaentrou)
        {
          incrementarTime = false;
        }
      }
    }
    else
    {
      abrir--;
      if (abrir == 0)
      {
        doing = false;
      }
    }
    if (incrementarTime)
    {
      time++;
    }
  }
  float mediaResp = calcularMedia(tempodeResposta);
  float mediaEsp = mediaResp;
  float mediaRet = calcularMedia(tempodeRetorno);

  std::cout << "\nFCFS " << std::fixed << std::setprecision(1) << mediaRet << " " << mediaResp << " " << mediaEsp << "\n"
            << std::endl;
            */

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

  std::vector<bool> entered(processos.size(), false);
  std::vector<int> tempodeResposta(processos.size());
  std::vector<int> tempodeRetorno(processos.size());
  int i = 0;
  int ii = 0;
  int jumpEnterProcess = 0;
  int menorDemora = std::numeric_limits<int>::max();
  while (1)
  {
    i = 0;
    bool existeProcesso = false;
    int tempodeEntrada, tempofazendo;
    if (!doing)
    {
      bool encerrar = true;
      for (bool value : entered)
      {
        if (!value)
        {
          encerrar = false;
        }
      }
      if (encerrar)
      {
        break;
      }
    }

    for (const Processo &processo : processos)
    {

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

  std::cout << "\nSJF " << std::fixed << std::setprecision(1) << mediaRet << " " << mediaResp << " " << mediaEsp << "\n"
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
  bool umjaentrou = false;
  while (1)
  {
    i = 0;
    bool incrementarTime = true;
    bool entreiAqui = false;
    if (!doing)
    {
      bool encerrar = true;
      for (bool value : entered)
      {
        if (!value)
        {
          encerrar = false;
        }
      }
      if (encerrar)
      {
        break;
      }

      for (const Processo &processo : processos)
      {

        if ((processo.entrar <= lookingfor) && !entered[i] && !entreiAqui)
        {
          umjaentrou = true;
          entreiAqui = true;
          doing = true;
          entered[i] = true;
          tempodeResposta[i] = time - processo.entrar;
          tempodeRetorno[i] = time - processo.entrar + processo.demora;
          abrir = processo.demora - 1;
        }
        i++;
      }
      bool temfalse = true;
      for (bool value : entered)
      {
        if (!value)
        {
          temfalse = false;
        }
      }
      if (!temfalse and !entreiAqui)
      {
        lookingfor++;
        if (time != 0 and umjaentrou)
        {
          incrementarTime = false;
        }
      }
    }
    else
    {
      abrir--;
      if (abrir == 0)
      {
        doing = false;
      }
    }
    if (incrementarTime)
    {
      time++;
    }
  }
  float mediaResp = calcularMedia(tempodeResposta);
  float mediaEsp = mediaResp;
  float mediaRet = calcularMedia(tempodeRetorno);

  std::cout << "\nFCFS " << std::fixed << std::setprecision(1) << mediaRet << " " << mediaResp << " " << mediaEsp << "\n"
            << std::endl;
}

int main()
{
  std::vector<Processo> processos = {{3, 4}, {1, 3}, {0, 6}, {6, 5}, {0, 2}, {0, 4}};
  // sjf(processos);
  // fcfs(processos);
  rr(processos);
  return 0;
}