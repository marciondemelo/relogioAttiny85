//#include <TinyWireM.h>
#include <Wire.h>
#include "RtcConfig.h"



//===================================================================

//===================================================================
void param_init_IR();
void param_init_rtc();
void SetClock();
void alteraCor();
void alteraHora();

void setup() {

  Wire.begin();

  param_init_IR();

  param_init_rtc();
}

//===================================================================
//===================================================================
void loop() {
  ShowClock();
  FuncoesBotao();
}

void FuncoesBotao() {
  if (comandoIRremote() == "#") {
    alteraCor();
  }

  if (comandoIRremote() == "*") {
    alteraHora();
  }
}
