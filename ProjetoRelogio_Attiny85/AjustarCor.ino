


void AlterarCor() {
  FitaLed.setPixelColor(14, FitaLed.Color(255, 255, 255));
  FitaLed.show();
  int indicePeriodo = 0;
  int indiceCores = 0;
  bool ascende = true;

  unsigned long tempo = millis() + 10000;
  unsigned long tempoPisca = millis() + 100;

  /*fica no while até o 10 sec sem apertar nenhum botao
    caso um botao seja precionado o tempo é reiniciado*/
  while (millis() < tempo) {

    /*se o botao 1 for precionado novamente sera
      anternado entre as opcoes de ajuste de cores de 0 a 3*/
    if (Btn01IsPress() == 0) {
      tempo = millis() + 10000;
      delay(200);
      while (Btn01IsPress() == 0);
      if (indicePeriodo == 3) {
        FitaLed.setPixelColor(14, FitaLed.Color(0, 255, 255));
        FitaLed.show();
        indicePeriodo = 0;
        delay(500);
      } else {
        FitaLed.setPixelColor(14, FitaLed.Color(0, 0, 255));
        FitaLed.show();
        indicePeriodo++;
        delay(500);
      }
    }
    
    FitaLed.setPixelColor(14, FitaLed.Color(255, 255, 255));
    FitaLed.show();
    
    //    if (Btn02IsPress() == 0) {
    //      while (Btn02IsPress() == 0);
    //
    //      //funcao para alterar a cor
    //
    //    }

    /* base de calculo para o display ficar piscando durante o modo de ajuste*/
    if (millis() > tempoPisca ) {
      ascende = !ascende;
      tempoPisca = millis() + 200;
    }


    //if para manter o display piscando
    if (ascende) {
      if (indicePeriodo == 0) { //manha
        //usa 6 horas para representar o periodo da manha
        setHoraDisplay(6);
        setMinDisplay(00);
      }

      if (indicePeriodo == 1) { //tarde
        //usa 12 horas para representar o periodo da tarde
        setHoraDisplay(12);
        setMinDisplay(00);
      }

      if (indicePeriodo == 2) { //noite
        //usa 18 horas para representar o periodo da noite
        setHoraDisplay(18);
        setMinDisplay(00);
      }

      if (indicePeriodo == 3) { //madrugada
        //usa 00 horas para representar o periodo da madrugada
        setHoraDisplay(00);
        setMinDisplay(00);
      }

      FitaLed.show();     //liga os leds referente ao numero
    }
    else {
      /*apaga todos os leds*/
      FitaLed.clear();
      FitaLed.show();
    }
    //
    //    if (Btn01IsPress() == 0) {
    //      tempo = millis() + 10000;         //reseta o tempo  caso um botao seja apertado
    //    }
    //
    //    if (Btn02IsPress() == 0) {
    //      tempo = millis() + 10000;         //reseta o tempo  caso um botao seja apertado
    //    }

    // fim do while
  }
  FitaLed.setPixelColor(14, FitaLed.Color(0, 0, 0));
  FitaLed.show();
}
