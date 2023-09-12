#include <iostream>
#include <vector>
#include <limits>

struct Processo
{
  int entrar;
  int demora;
};

void sjf(const std::vector<Processo> &processos)
{
  int time = 0;
  bool doing = false;
  // int trespera[processos.size()];
  std::vector<bool> entered(processos.size(), false);
  std::vector<int> tempoQueEntrou(processos.size());
  int i = 0;
  int ii = 0;
  int jumpEnterProcess = 0;
  int menorDemora = std::numeric_limits<int>::max();
  while (time < 46)
  {
    i = 0;
    bool existeProcesso = false;
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
      tempoQueEntrou[ii] = time;
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

    std::cout << "\nna passada do time: " << time << " jumpEnterProcess eh: " << jumpEnterProcess << " sou o processo: " << ii << std::endl;

    time++;
  }
  // std::cout << "\nmenor demora: " << menorDemora << " jump enter process: " << jumpEnterProcess << std::endl;
}

int main()
{
  std::vector<Processo> processos = {{1, 25}, {1, 3}, {1, 6}, {1, 5}, {2, 2}, {2, 4}};
  sjf(processos);
  return 0;
}