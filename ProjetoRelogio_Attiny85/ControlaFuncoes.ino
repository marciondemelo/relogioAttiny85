int btn01Status = 0;
int btn02Status = 0;

int Btn01IsPress() {
  return !digitalRead(Btn01);
}

int Btn02IsPress() {
  return !digitalRead(Btn02);
}

void ValidaBotoes() {
  if (Btn01IsPress() == 0) {
    btn01Status = 1;
  }
  if (Btn02IsPress() == 0) {
    btn02Status = 1;
  }
}

void FuncoesBotao() {
  ValidaBotoes();

  /*Entra no if após o botao 1 ser solto*/
  if (Btn01IsPress() && btn01Status) {
    btn01Status = 0;
    AlterarCor();
  }

  /*Entra no if após o botao 1 ser solto*/
  if (Btn02IsPress() && btn02Status) {
    btn02Status = 2;
    AlteraHora();
  }
}
