

void AlteraHora() {
  int sai;
  while(sai == 241){
  PiscaRelogio();
  if(Serial.read()){
    
  }
    
  }

}

bool ascende = false;
void PiscaRelogio() {

  unsigned long tempoPisca = millis() + 100;
  if (millis() > tempoPisca ) {
    ascende = !ascende;
    tempoPisca = millis() + 200;
  }

  if (ascende) {
    FitaLed.show();
    SetClock();
  } else {
    FitaLed.clear();
    FitaLed.show();
  }
}
