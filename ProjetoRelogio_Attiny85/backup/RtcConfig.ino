void displayNumero(int numero, int positionStart, int color);
void SetClock();
void setHoraDisplay(int num);
void setMinDisplay(int num);


unsigned long tempoAtualiza;
void SetClock() {

  if (millis() > tempoAtualiza) {
    tempoAtualiza = millis() + 2000;
    Clock.get();
    int Hour = hour();
    int Min = minute();

    setHoraDisplay(Hour);
    setMinDisplay(Min);

    FitaLed.show();
  }
}

void setHoraDisplay(int num) {
  int HourDec = ((num / 10) % 10);
  int HourUni = ((num) % 10);


  displayNumero(HourDec, PosHourDec, defineColor());
  displayNumero(HourUni, PosHourUni, defineColor());
}

void setMinDisplay(int num) {
  int MinDec = ((num / 10) % 10);
  int MinUni = ((num) % 10);

  displayNumero(MinDec, PosMinDec, defineColor());
  displayNumero(MinUni, PosMinUni, defineColor());
}

void displayNumero(int numero, int positionStart, int color) {
  int positionLed = positionStart;
  int indexNumber = 0;

  for ( ; positionLed < positionStart + 7; positionLed++, indexNumber++) {
    if (numbers[numero][indexNumber] == 1) {
      mudaCor(positionLed, color);
    } else {
      mudaCor(positionLed, 0);
    }
  }

  FitaLed.show();
}

