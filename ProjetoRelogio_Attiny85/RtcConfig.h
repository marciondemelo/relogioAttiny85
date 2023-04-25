#include <Adafruit_NeoPixel.h>
#include <DS3232RTC.h>  //http://github.com/JChristensen/DS3232RTC
#include "LerIR.h"

void displayNumero(int numero, int positionStart, int color);
void ShowClock();
void setHoraDisplay(int num);
void setMinDisplay(int num);
void param_init_rtc();
int defineColor();
void mudaCor(int positionLed, int indiceCor);
void ApagaFita();
void UpdateFita();
void ShowDot(bool show);

void alteraHora();