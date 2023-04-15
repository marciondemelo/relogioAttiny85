#include <Adafruit_NeoPixel.h>
#include <WiFiManager.h>
#include "RTClib.h"

//http://ai2.appinventor.mit.edu/#5643721247686656

#define SDA   21
#define SCL   22

#define PinFitaLed      23

#define TotalLed        29

WiFiServer server(80);
Adafruit_NeoPixel FitaLed(TotalLed, PinFitaLed, NEO_GRB + NEO_KHZ800);
RTC_DS3231 Clock;

extern void displayNumero(int numero, int positionStart, uint32_t color);
extern void SetClock();
extern uint32_t defineColor();
extern void setHora(char num);
extern void setMin(char num);
extern void WebServerAjusteTime();

const unsigned char PosHourDec = 0, PosHourUni = 7, PosMinDec = 15, PosMinUni = 22;
unsigned char Min, Hour, Day, Month, Year;


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

void defaultColorPeriodo();
int dot;
void setup() {
  // Open serial communications and wait for port to open:
  Serial.begin(115200);
  Clock.begin();
  FitaLed.begin();
  pinMode(PinFitaLed, OUTPUT);

  WiFiManager wm;

  if (Clock.lostPower()) {
    Serial.println("RTC lost power, let's set the time!");
    // When time needs to be set on a new device, or after a power loss, the
    // following line sets the RTC to the date & time this sketch was compiled
    Clock.adjust(DateTime(F(__DATE__), F(__TIME__)));
    // This line sets the RTC with an explicit date & time, for example to set
    // January 21, 2014 at 3am you would call:
    // rtc.adjust(DateTime(2014, 1, 21, 3, 0, 0));
  }

  wm.setSTAStaticIPConfig(IPAddress(192, 168, 68, 145), IPAddress(192, 168, 68, 1), IPAddress(255, 255, 255, 0));

  bool res;
  res = wm.autoConnect("MMSolutions", "pipocadoce");

  if (!res) {
    Serial.println("Failed to connect");
    // ESP.restart();
  }
  else {
    //if you get here you have connected to the WiFi
    Serial.println("connected...yeey :)");
  }


  server.begin();


  colorNoite = FitaLed.Color(0, 250, 255); //NOITE - ciano
  colorMadrugada = FitaLed.Color(0, 0, 255); //MADRUGADA - azul
  colorManha = FitaLed.Color(255, 250, 0); //MANHA - amarelo
  colorTarde = FitaLed.Color(255, 0, 250); //TARDE - magenta

  dot = 0;
}

void loop() {
   delay(1000);
displayNumero(7, PosHourDec, FitaLed.Color(0, 255, 0));
FitaLed.show();
//  if (dot == 0) {
//    FitaLed.setPixelColor(14, FitaLed.Color(255, 255, 255));
//    dot = 1;
//  } else {
//    FitaLed.setPixelColor(14, FitaLed.Color(0, 0, 0));
//    dot = 0;
//  }
//  SetClock();
//  WebServerAjusteTime();

}
