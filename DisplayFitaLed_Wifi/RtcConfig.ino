void displayNumero(int numero, int positionStart, uint32_t color);
void SetClock();
uint32_t defineColor();
void setHora(char num);
void setMin(char num);

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

void SetClock() {
  DateTime ClockNow = Clock.now();
  unsigned char Sec = ClockNow.second();

  Min = ClockNow.minute();
  Hour = ClockNow. hour();
  Day = ClockNow.day();
  Month = ClockNow. month();
  Year = ClockNow.year();


  setHora(Hour);
  setMin(Hour);
 
  FitaLed.show();
}

uint32_t defineColor() {
  DateTime ClockNow = Clock.now();
  Hour = ClockNow. hour();

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

void setHora(char num) {
  int HourDec = ((Hour / 10) % 10);
  int MinUni = ((Hour) % 10);

  Serial.print(HourDec);
  displayNumero(HourDec, PosHourDec, defineColor());
  Serial.print(MinUni);
  displayNumero(MinUni, PosHourUni, defineColor());
}

void setMin(char num) {
  Serial.print(":");
  int MinDec = ((Min / 10) % 10);
  int MinUni = ((Min) % 10);

  Serial.print(MinDec);
  displayNumero(MinDec, PosMinDec, defineColor());
  Serial.println(MinUni);
  displayNumero(MinUni, PosMinUni, defineColor());
}
