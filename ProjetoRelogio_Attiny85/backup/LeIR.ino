int numeroIRremote();
String comandoIRremote();

/*
 * 
 * tabela de valores e correspondencia
    1 -> 17843
    2 -> 18098
    3 -> 18353
    4 -> 17588
    5 -> 16568
    6 -> 17333
    7 -> 2033
    8 -> 5603
    9 -> 2543
    0 -> 6623
    * -> 5858
    # -> 3563
    up -> 6368
    dw -> 21158
    lf -> 2288
    rh -> 23198
    ok -> 7388
 * 
 */


int numeroIRremote(){
  switch(getIrKey()){
    
    case 6623:{
      return 0;
    }
    case 17843:{
      return 1;
    }
    case 18098:{
      return 2;
    }
    case 18353:{
      return 3;
    }
    case 17588:{
      return 4;
    }
    case 16568:{
      return 5;
    }
    case 17333:{
      return 6;
    }
    case 2033:{
      return 7;
    }
    case 5603:{
      return 8;
    }
    case 2543:{
      return 9;
    }
    default :{
      return 99;
    }
  }
}

String comandoIRremote(){
  switch(getIrKey()){
    case 5858:{
      return "*";
    }
    case 3563:{
      return "#";
    }
    case 6368:{
      return "up";
    }
    case 21158:{
      return "dw";
    }
    case 2288:{
      return "lf";
    }
    case 23198:{
      return "rh";
    }
    case 7388:{
      return "ok";
    }
    default :{
      return "--";
    }
  }  
}

int getIrKey(){
  int len = pulseIn(pinIr,LOW);
  int key, temp;
  key = 0;
  //Serial.print("len=");
  //Serial.println(len);
  if(len > 5000) {
    for(int i=1;i<=32;i++){
      temp = pulseIn(pinIr,HIGH);
      if(temp > 1000)
        key = key + (1<<(i-17));
    }
  }
  if(key < 0 )
    key = -key;

  delay(250);
  return key;
}
