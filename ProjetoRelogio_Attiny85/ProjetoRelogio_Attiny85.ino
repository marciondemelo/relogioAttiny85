#include <TinyWireM.h>
//#include <Wire.h>
#include <Adafruit_NeoPixel.h>

#include <DS3232RTC.h>             //http://github.com/JChristensen/DS3232RTC

#define PinFitaLed      1
#define TotalLed        29
#define Btn01           3
#define Btn02           4

Adafruit_NeoPixel FitaLed(TotalLed, PinFitaLed, NEO_GRB + NEO_KHZ800);
DS3232RTC Clock;
//===================================================================

//===================================================================
extern void displayNumero(int numero, int positionStart, uint32_t color);
extern void SetClock();
extern uint32_t defineColor();
extern void setHoraDisplay(int num);
extern void setMinDisplay(int num);
extern unsigned long tempoAtualiza;

const unsigned int PosHourDec = 0, PosHourUni = 7, PosMinDec = 15, PosMinUni = 22;

int numbers[10][7] = {
  //0,1, 2, 3, 4, 5, 6
  {0, 1, 1, 1, 1, 1, 1}, //0
  {0, 1, 0, 0, 0, 0, 1}, //1
  {1, 0, 1, 1, 0, 1, 1}, //2
  {1, 1, 1, 0, 0, 1, 1}, //3
  {1, 1, 0, 0, 1, 0, 1}, //4
  {1, 1, 1, 0, 1, 1, 0}, //5
  {1, 1, 1, 1, 1, 1, 0}, //6
  {0, 1, 0, 0, 0, 1, 1}, //7
  {1, 1, 1, 1, 1, 1, 1}, //8
  {1, 1, 1, 0, 1, 1, 1} //9
};


static byte colorNoite;
static byte colorMadrugada;
static byte colorManha;
static byte colorTarde;

int dot;

void setup()
{
  tmElements_t tm;
  time_t t;

  pinMode(Btn01, INPUT_PULLUP);
  pinMode(Btn02, INPUT_PULLUP);

  //  Wire.begin();
  Clock.begin();
  FitaLed.begin();

  setSyncProvider(Clock.get);                 // the function to get the time from the RTC
  tm.Hour = 22;
  tm.Minute = 11;
  t = makeTime(tm);
  // setTime(22, 51, 0, 22, 3, 2023);            // Initial time & date setup of RTC
  Clock.set(t);                           // Update the RTC with current time
  setTime(t);
  colorNoite = FitaLed.Color(0, 250, 255);    //NOITE - ciano
  colorMadrugada = FitaLed.Color(0, 0, 255);  //MADRUGADA - azul
  colorManha = FitaLed.Color(255, 250, 0);    //MANHA - amarelo
  colorTarde = FitaLed.Color(255, 0, 250);    //TARDE - magenta

  tempoAtualiza = 0;
  dot = 0;
}

//===================================================================
//===================================================================
void loop()
{
  Clock.get();

  SetClock();
  FuncoesBotao();
}
