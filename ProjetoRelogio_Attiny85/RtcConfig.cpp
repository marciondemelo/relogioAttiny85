

#include "RtcConfig.h"

const unsigned int PosHourDec = 0, PosHourUni = 7, PosMinDec = 15, PosMinUni = 22;
unsigned long tempoAtualiza;
static int colorManha;
static int colorTarde;
static int colorNoite;
static int colorMadrugada;
int dot;


int numbers[10][7] = {
  //0,1, 2, 3, 4, 5, 6
  { 0, 1, 1, 1, 1, 1, 1 },  //0
  { 0, 1, 0, 0, 0, 0, 1 },  //1
  { 1, 0, 1, 1, 0, 1, 1 },  //2
  { 1, 1, 1, 0, 0, 1, 1 },  //3
  { 1, 1, 0, 0, 1, 0, 1 },  //4
  { 1, 1, 1, 0, 1, 1, 0 },  //5
  { 1, 1, 1, 1, 1, 1, 0 },  //6
  { 0, 1, 0, 0, 0, 1, 1 },  //7
  { 1, 1, 1, 1, 1, 1, 1 },  //8
  { 1, 1, 1, 0, 1, 1, 1 }   //9
};
const int qtdCores = 21;
int cores[][3] = {
  { 0, 0, 0 },        // 0 - Sem Cor
  { 255, 0, 0 },      // 1 - Vermelho
  { 0, 255, 0 },      // 2 - Verde
  { 0, 0, 255 },      // 3 - Azul
  { 255, 255, 0 },    // 4 - Amarelo
  { 255, 0, 255 },    // 5 - Rosa
  { 0, 255, 255 },    // 6 - Ciano
  { 255, 165, 0 },    // 7 - Laranja
  { 128, 0, 128 },    // 8 - Roxo
  { 165, 42, 42 },    // 9 - Marrom
  { 64, 224, 208 },   // 10 - Turquesa
  { 173, 216, 230 },  // 11 - Azul claro
  { 50, 205, 50 },    // 12 - Verde limão
  { 211, 211, 211 },  // 13 - Cinza claro
  { 0, 0, 139 },      // 14 - Azul escuro
  { 0, 100, 0 },      // 15 - Verde escuro
  { 139, 0, 0 },      // 16 - Vermelho escuro
  { 169, 169, 169 },  // 17 - Cinza escuro
  { 245, 245, 220 },  // 18 - Bege
  { 255, 0, 255 },    // 19 - Magenta
  { 0, 255, 255 }     // 20 - Aqua
};

#define PinFitaLed 1
#define TotalLed 29

Adafruit_NeoPixel FitaLed(TotalLed, PinFitaLed, NEO_GRB + NEO_KHZ800);
DS3232RTC Clock;

void param_init_rtc() {

  tmElements_t tm;
  time_t t;

  Clock.begin();
  FitaLed.begin();

  setSyncProvider(Clock.get);  // the function to get the time from the RTC
  tm.Hour = hour();
  tm.Minute = minute();
  t = makeTime(tm);
  // setTime(22, 51, 0, 22, 3, 2023);            // Initial time & date setup of RTC
  Clock.set(t);  // Update the RTC with current time
  setTime(t);

  colorNoite = 6;      //NOITE - ciano
  colorMadrugada = 9;  //MADRUGADA - azul
  colorManha = 4;      //MANHA - amarelo
  colorTarde = 19;     //TARDE - magenta

  tempoAtualiza = 0;
  dot = 0;
}

void ConfigHora(int hora) {
  if (hora >= 0 && hora <= 24) {
    tmElements_t tm;
    time_t t;

    setSyncProvider(Clock.get);  // the function to get the time from the RTC
    tm.Hour = hora;
    tm.Minute = minute();
    t = makeTime(tm);
    Clock.set(t);  // Update the RTC with current time
    setTime(t);
    setHoraDisplay(hora);
  } else {

    setHoraDisplay(88);
    setMinDisplay(88);
    UpdateFita();
    delay(1000);
    ShowClock();
  }
}


void ConfigMinuto(int minuto) {
  if (minuto >= 0 && minuto <= 59) {
    tmElements_t tm;
    time_t t;

    setSyncProvider(Clock.get);  // the function to get the time from the RTC
    tm.Hour = hour();
    tm.Minute = minuto;
    t = makeTime(tm);
    Clock.set(t);  // Update the RTC with current time
    setTime(t);
    setMinDisplay(minuto);
  } else {

    setHoraDisplay(88);
    setMinDisplay(88);
    UpdateFita();
    delay(1000);
    ShowClock();
  }
}

void ShowClock() {

  if (millis() > tempoAtualiza) {
    tempoAtualiza = millis() + 2000;
    Clock.get();
    int Hour = hour();
    int Min = minute();

    setHoraDisplay(Hour);
    setMinDisplay(Min);

    UpdateFita();
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

  for (; positionLed < positionStart + 7; positionLed++, indexNumber++) {
    if (numbers[numero][indexNumber] == 1) {
      mudaCor(positionLed, color);
    } else {
      mudaCor(positionLed, 0);
    }
  }

  UpdateFita();
}



void ShowDot(bool show) {
  if (show) {
    FitaLed.setPixelColor(14, FitaLed.Color(255, 255, 255));
    UpdateFita();
  } else {
    FitaLed.setPixelColor(14, FitaLed.Color(0, 0, 0));
    UpdateFita();
  }
}

void UpdateFita() {
  FitaLed.show();
}

void ApagaFita() {
  FitaLed.clear();
  UpdateFita();
}

static unsigned long tempo;
bool tempoDeAjuste(bool reset = false) {
  if (reset || tempo == 0) {
    tempo = millis() + 30000;
  } else {
    if (millis() > tempo) {
      return false;
    } else {
      return true;
    }
  }
}

unsigned long tempoPisca;
bool ascende = true;
bool tempoDePiscar() {

  if (millis() > tempoPisca) {
    tempoPisca = millis() + 200;
    return !ascende;
  }
}

/*
=============================================================================================================
          -- HORAS AJUSTE DE 
=============================================================================================================
*/

void alteraHora() {
  int posicaoRelogio = 0;

  int Hora = hour();
  int Minuto = minute();

  int horadecimal = 0;
  int minutodecimal = 0;


  while (tempoDeAjuste()) {

    if (comandoIRremote() == "*") {
      tempoDeAjuste(true);
      posicaoRelogio++;
      if (posicaoRelogio == 3) {
        posicaoRelogio = 0;
      }
    }


    int pessNumber = numeroIRremote();

    //if para manter o display piscando
    if (tempoDePiscar()) {
      if (pessNumber != 99) {

        //HORAS decimal___________________________________________

        if (posicaoRelogio == 0) {
          if (pessNumber >= 0 && pessNumber <= 2) {
            horadecimal = pessNumber;
            displayNumero(horadecimal, PosHourDec, defineColor());
          }

        }  //hora unidade_________________________________________

        else if (posicaoRelogio == 1) {

          if (horadecimal == 0 || horadecimal == 1) {
            Hora = horadecimal == 0 ? pessNumber : 10 + pessNumber;
            ConfigHora(Hora);
          } else if (horadecimal == 2) {

            if (pessNumber == 0) {
              Hora = 20;
              ConfigHora(Hora);
            } else if (pessNumber >= 1 && pessNumber <= 3) {
              Hora = 20 + pessNumber;
              ConfigHora(Hora);
            }
          }

        }

        //MINUTOS decimal_________________________________________
        else if (posicaoRelogio == 2) {

          if (pessNumber >= 0 && pessNumber <= 5) {
            minutodecimal = pessNumber;
            displayNumero(pessNumber, PosMinDec, defineColor());
          }

        }  //minuto unidade___________________________________________

        else if (posicaoRelogio == 3) {

          Minuto = minutodecimal == 0 ? pessNumber : minutodecimal * 10 + pessNumber;
          ConfigMinuto(Minuto);
        }

        UpdateFita();  //liga os leds referente ao numero
      }

    } else {
      /*apaga todos os leds*/
      ApagaFita();
    }

    if (comandoIRremote() == "ok") {
      UpdateFita();
      return;
    }

    //fim do while
  }
}


/*
=============================================================================================================
          -- CORES DEFINICAO DAS 
=============================================================================================================
*/


// Passe a posição do array
void mudaCor(int positionLed, int indiceCor) {

  // Verifique se a posição está dentro dos limites do array
  if (indiceCor >= 0 && indiceCor < sizeof(cores) / sizeof(cores[0])) {

    // Se a posição estiver dentro dos limites, atribua a cor correspondente ao LED
    FitaLed.setPixelColor(positionLed, FitaLed.Color(cores[indiceCor][0], cores[indiceCor][1], cores[indiceCor][2]));
  }
}

int defineColor() {
  int Hour = hour();

  int color;
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

void alteraCor() {
  int indicePeriodo = 0;
  int indiceCores = 0;

  bool manha = false;
  bool tarde = false;
  bool noite = false;
  bool madrugada = false;


  /*fica no while até o 10 sec sem apertar nenhum botao
    caso um botao seja precionado o tempo é reiniciado*/
  while (tempoDeAjuste()) {

    /*se o botao 1 for precionado novamente sera
      anternado entre as opcoes de ajuste de cores de 0 a 3*/
    if (comandoIRremote() == "up") {
      tempoDeAjuste(true);
      if (indiceCores == (qtdCores - 1)) {
        indiceCores = 0;
      } else {
        indiceCores++;
      }
    }
    if (comandoIRremote() == "dw") {
      tempoDeAjuste(true);
      if (indiceCores == 0) {
        indiceCores = (qtdCores - 1);
      } else {
        indiceCores--;
      }
    }

    if (comandoIRremote() == "#") {
      tempoDeAjuste(true);
      indicePeriodo++;
      if (indicePeriodo == 3) {
        indicePeriodo = 0;
      }
    }

    /* base de calculo para o display ficar piscando durante o modo de ajuste*/



    //if para manter o display piscando
    if (tempoDePiscar()) {
      if (indicePeriodo == 0) {  //manha
        if (!manha) {
          manha = true;
          tarde = false;
          noite = false;
          madrugada = false;
          indiceCores = colorManha;
        }
        colorManha = indiceCores;
        //usa 6 horas para representar o periodo da manha
        setHoraDisplay(6);
        setMinDisplay(00);
      }

      if (indicePeriodo == 1) {  //tarde
        if (!tarde) {
          manha = false;
          tarde = true;
          noite = false;
          madrugada = false;
          indiceCores = colorTarde;
        }
        colorTarde = indiceCores;
        //usa 12 horas para representar o periodo da tarde
        setHoraDisplay(12);
        setMinDisplay(00);
      }

      if (indicePeriodo == 2) {  //noite
        if (!noite) {
          manha = false;
          tarde = false;
          noite = true;
          madrugada = false;
          indiceCores = colorNoite;
        }
        colorNoite = indiceCores;
        //usa 18 horas para representar o periodo da noite
        setHoraDisplay(18);
        setMinDisplay(00);
      }

      if (indicePeriodo == 3) {  //madrugada
        if (!madrugada) {
          manha = false;
          tarde = false;
          noite = false;
          madrugada = true;
          indiceCores = colorMadrugada;
        }
        colorMadrugada = indiceCores;
        //usa 00 horas para representar o periodo da madrugada
        setHoraDisplay(00);
        setMinDisplay(00);
      }

      UpdateFita();  //liga os leds referente ao numero
    } else {
      /*apaga todos os leds*/
      ApagaFita();
    }
    if (comandoIRremote() == "ok") {
      UpdateFita();
      return;
    }

    // fim do while
  }
}
