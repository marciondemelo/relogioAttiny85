void displayNumero(int numero, int positionStart, uint32_t color);
void SetClock();
uint32_t defineColor();
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

void displayNumero(int numero, int positionStart, uint32_t color) {
  int positionLed = positionStart;
  int indexNumber = 0;

  for ( ; positionLed < positionStart + 7; positionLed++, indexNumber++) {
    if (numbers[numero][indexNumber] == 1) {
      FitaLed.setPixelColor(positionLed, color);
    } else {
      FitaLed.setPixelColor(positionLed, FitaLed.Color(0, 0, 0));
    }
  }

  FitaLed.show();
}


uint32_t defineColor() {
  int Hour = hour();

  uint32_t color;
  if (Hour >= 18 && Hour <= 23) {
    color = colorNoite;
  } else if (Hour >= 0 && Hour <= 5) {
    color = colorMadrugada;
  } else if (Hour >= 6 && Hour <= 11) {
    color = colorManha;
  } else {
    color = colorTarde;
  }

  return color;
}
