///////////////// Libs /////////////////

#include <Arduino.h>
#include <Wire.h>
#include <BluetoothSerial.h>

// função que inicializa o bluetooth do ESP32
#if !defined (CONFIG_BT_ENABLED) || !defined (CONFIG_BLUEDROID_ENABLED)
#error Bluetooth is not enabled! Please run `make menuconfig` to and enable it
#endif
// variáveis globais
BluetoothSerial Bluetooth;

////////////////  Functions Declare //////////////////
void allStop();                 // para o veículo
void analyzeCommand(char c);    // analisa o comando recebido pelo bluetooth

// Motor M1 && M3, Lefts Sides (Front Wheels) && (Back wheels)
const uint8_t pwm_M1 = 26;   // ENA1 - Enable and PWM
const uint8_t fwd_M1 = 25;   // IN1 - Forward Drive (Front Wheels) && (Back wheels)
const uint8_t rwd_M1 = 33;   // IN2 - Reverse Drive (Front Wheels) && (Back wheels)

// Motor M2 && M4, Right Side (Front Wheels) && (Back wheels)
const uint8_t pwm_M2 = 21;   // ENB - Enable and PWM -> (Front Wheels) && (Back wheels) 
const uint8_t fwd_M2 = 19;   // IN3 - Forward Drive (Front Wheels) && (Back wheels)
const uint8_t rwd_M2 = 18;   // IN4 - Reverse Drive (Front Wheels) && (Back wheels)

void setup(){
  // configura BluetoothSerial
  Bluetooth.begin("ESP32");
  // Seta os pinos dos modulos (L298) como outputs
  pinMode(pwm_M1, OUTPUT);
  pinMode(fwd_M1, OUTPUT);
  pinMode(rwd_M1, OUTPUT);

  pinMode(pwm_M2, OUTPUT);
  pinMode(fwd_M2, OUTPUT);
  pinMode(rwd_M2, OUTPUT);
}

void loop(){
  if (Bluetooth.available()) {
    char c;
    c = Bluetooth.read();
    analyzeCommand(c);
  }
}

//////////////// Start Functions //////////////////
void  analyzeCommand(char c){
  String s = "";
  s += c;

 
  //Representa as rodas acionadas 'x' e 'O' as não acionadas  
  if (s.startsWith("S")) {        //Stop
    // xO
    // xO
    allStop();
  
  } else if (s.startsWith("F")) {// Front

    // Frente M1 && M3
    // Ox
    // Ox
    digitalWrite(pwm_M1, HIGH);
    digitalWrite(fwd_M1, HIGH);
    digitalWrite(rwd_M1, LOW);
    
    // Right M2 && M4
    // xO
    // xO
    digitalWrite(pwm_M2, HIGH);    
    digitalWrite(fwd_M2, HIGH);
    digitalWrite(rwd_M2, LOW);
         
  } else if (s.startsWith("G")) { // Front Left
    
    // Left M1 && M3
    // 0x
    // 0x
    digitalWrite(pwm_M1, HIGH);
    digitalWrite(fwd_M1, HIGH);
    digitalWrite(rwd_M1, LOW);

    // Right M2 && M4
    // xO
    // xO
    digitalWrite(pwm_M2, HIGH);
    digitalWrite(fwd_M2, HIGH);
    digitalWrite(rwd_M2, LOW);
    
  } else if (s.startsWith("I")) { //Front Right

    // Left M2 && M4
    // xO
    // xO
    digitalWrite(pwm_M2, HIGH);
    digitalWrite(fwd_M2, HIGH);
    digitalWrite(rwd_M2, LOW);

    // Right M1 && M3
    // 0x
    // 0x
    digitalWrite(pwm_M1, HIGH);
    digitalWrite(fwd_M1, HIGH);
    digitalWrite(rwd_M1, LOW);  
    
  } else if (s.startsWith("R")) { //Right

    // Left M2 && M4
    // xO
    // xO
    digitalWrite(pwm_M1, HIGH);
    digitalWrite(fwd_M1, LOW);
    digitalWrite(rwd_M1, HIGH);

    // Frente M1 && M3 
    // 0x
    // 0x
    digitalWrite(pwm_M2, HIGH);
    digitalWrite(fwd_M2, HIGH);
    digitalWrite(rwd_M2, LOW);

  } else if (s.startsWith("L")) { //Left
    // Left M2 && M4
    // xO
    // xO
    digitalWrite(pwm_M1, HIGH);
    digitalWrite(fwd_M1, HIGH);
    digitalWrite(rwd_M1, LOW);

    // Right M1 && M3
    // 0x
    // 0x
    digitalWrite(pwm_M2, HIGH);
    digitalWrite(fwd_M2, LOW);
    digitalWrite(rwd_M2, HIGH);
    

  }  else if (s.startsWith("B")) { //Back

    // Left M2 && M4 
    // xO
    // xO
    digitalWrite(pwm_M2, HIGH);
    digitalWrite(fwd_M2, LOW);
    digitalWrite(rwd_M2, HIGH);

    // Right M1 && M3
    // 0x
    // 0x
    digitalWrite(pwm_M1, HIGH);
    digitalWrite(fwd_M1, LOW);
    digitalWrite(rwd_M1, HIGH);

  } else if (s.startsWith("H")) { //Back Left

    // Left M2 && M4
    // xO
    // xO
    digitalWrite(pwm_M2, HIGH);
    digitalWrite(fwd_M2, LOW);
    digitalWrite(rwd_M2, HIGH);

    // Right M1 && M3
    // 0x
    // 0x
    digitalWrite(pwm_M1, HIGH);
    digitalWrite(fwd_M1, LOW);
    digitalWrite(rwd_M1, HIGH);
    
  } else if (s.startsWith("J")) { //3

    // Left M2 && M4
    // xO
    // xO
    digitalWrite(pwm_M2, HIGH);
    digitalWrite(fwd_M2, LOW);
    digitalWrite(rwd_M2, HIGH);

    // Right M1 && M3
    // 0x
    // 0x
    digitalWrite(pwm_M1, HIGH);
    digitalWrite(fwd_M1, LOW);
    digitalWrite(rwd_M1, HIGH);
  }
}

void allStop() { // para o veículo 
  digitalWrite(fwd_M1, LOW);
  digitalWrite(rwd_M1, LOW);
  digitalWrite(fwd_M2, LOW);
  digitalWrite(rwd_M2, LOW);
  digitalWrite(pwm_M1, LOW);
  digitalWrite(pwm_M2, LOW);
}