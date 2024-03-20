#include <Ultrasonic.h>
#include <AFMotor.h>
 int desviar = 0;


AF_DCMotor motor_esquerda_frente(1); // direita frente
AF_DCMotor motor_esquerda_tras(2); // direita tras
AF_DCMotor motor_direita_frente(3); // direita frente
AF_DCMotor motor_direita_tras(4); // direita tras

int Sensor_direito = 24;
int Sensor_meio = 23;
int Sensor_esquerdo = 22;
int Sensor_direito_fora = 25;
int Sensor_esquerdo_fora = 27;

Ultrasonic ultrasonicfrente(26, 28);     //TRIG/ECHO
int sonar_frente;
Ultrasonic ultrasonicesquerdo(30, 29);     //TRIG/ECHO
int sonar_esquerdo;


void setup() {

  pinMode(Sensor_direito, INPUT);
  pinMode(Sensor_meio, INPUT);
  pinMode(Sensor_esquerdo, INPUT);
  pinMode(Sensor_direito_fora, INPUT);
  pinMode(Sensor_esquerdo_fora, INPUT);



  motor_esquerda_frente.run(RELEASE);
  motor_esquerda_tras.run(RELEASE);
  motor_direita_frente.run(RELEASE);
  motor_direita_tras.run(RELEASE);
  Serial.begin(9600);
  Serial.println("Motor test!");

}

void loop() {

 sonar_frente = ultrasonicfrente.read();


segue_linha();
desviar_esquerdo();

}



////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void desviar_esquerdo(){
sonar_frente = ultrasonicfrente.read();
sonar_frente = ultrasonicfrente.read();
  if (sonar_frente  <= 4){

  motor_esquerda_frente.run(RELEASE);   // PARA
  motor_esquerda_tras.run(RELEASE);
  motor_direita_frente.run(RELEASE);
  motor_direita_tras.run(RELEASE);
  delay(1000);

  motor_direita_tras.setSpeed(190);    // GIRA PRA ESQUERDA
  motor_direita_frente.setSpeed(190); 
  motor_esquerda_frente.setSpeed(190);
  motor_esquerda_tras.setSpeed(190);
  motor_esquerda_frente.run(BACKWARD);  
  motor_esquerda_tras.run(BACKWARD);  
  motor_direita_frente.run(FORWARD);  
  motor_direita_tras.run(FORWARD);  
  delay(1200);

  frente();                              // FRENTE
  delay(600);

  motor_esquerda_frente.run(RELEASE);    // PARA
  motor_esquerda_tras.run(RELEASE);   
  motor_direita_frente.run(RELEASE);
  motor_direita_tras.run(RELEASE);
  delay(1000); 
  
  while(1){
  sonar_esquerdo = ultrasonicesquerdo.read();
  if (sonar_esquerdo > 7 ){  
  motor_direita_tras.setSpeed(45);
  motor_direita_frente.setSpeed(45);
  motor_esquerda_frente.setSpeed(220);
  motor_esquerda_tras.setSpeed(220);
  motor_direita_frente.run(FORWARD);  
  motor_direita_tras.run(FORWARD);  
  motor_esquerda_frente.run(FORWARD);  
  motor_esquerda_tras.run(FORWARD);  
  } else if (sonar_esquerdo <= 6 ){
  motor_direita_tras.setSpeed(90);
  motor_direita_frente.setSpeed(90);
  motor_direita_frente.run(FORWARD);  
  motor_direita_tras.run(FORWARD);  
  }
  if (digitalRead(Sensor_direito_fora) == HIGH){                         // sensor direito dentro = preto
  motor_esquerda_frente.run(RELEASE);
  motor_esquerda_tras.run(RELEASE);
  motor_direita_frente.run(RELEASE);
  motor_direita_tras.run(RELEASE);
  delay(2000); 
  direita_segue();
  delay(400);
  frente();
  delay(1200);
  while(digitalRead(Sensor_meio) != HIGH){
  esquerda_segue();
  }
  re();
  delay(400);
  break;
  }
  if (digitalRead(Sensor_direito) == HIGH){                         // sensor direito dentro = preto
  motor_esquerda_frente.run(RELEASE);
  motor_esquerda_tras.run(RELEASE);
  motor_direita_frente.run(RELEASE);
  motor_direita_tras.run(RELEASE);
  delay(2000); 
  direita_segue();
  delay(400);
  frente();
  delay(1400);
  while(digitalRead(Sensor_meio) != HIGH){
  esquerda_segue();
  }
  re();
  delay(400);
  break;
}
}
}
}

void segue_linha(){

  frente();   

  if (digitalRead(Sensor_direito) == HIGH){                             // sensor direito dentro = preto
  direita_segue();
  delay(150);
}

  if (digitalRead(Sensor_esquerdo) == HIGH){                            // sensor esquerdo dentro = preto
  esquerda_segue();
  delay(150);
}

  if (digitalRead(Sensor_direito_fora) == HIGH){                             // sensor direito fora = preto
  direita_segue();
}

  if (digitalRead(Sensor_esquerdo_fora) == HIGH){                             // sensor esquerdo fora  = preto
  esquerda_segue();
}

/////////////////////////////////falso_90 e 90 graus//////////////////////////////////
  if (digitalRead(Sensor_esquerdo_fora) == HIGH && digitalRead(Sensor_esquerdo) == HIGH ) {     // os dois sensores esquerdo = preto

  motor_esquerda_frente.run(RELEASE);
  motor_esquerda_tras.run(RELEASE);                                    // para
  motor_direita_frente.run(RELEASE);
  motor_direita_tras.run(RELEASE);
  delay(500); 

  frente();                                                            //frente
  delay(1000);

  direita_segue();                                                     //direita
  delay(500); 

  motor_esquerda_frente.run(RELEASE);                                  //para
  motor_esquerda_tras.run(RELEASE);
  motor_direita_frente.run(RELEASE);
  motor_direita_tras.run(RELEASE);
  delay(400); 

  while(digitalRead(Sensor_meio) != HIGH) {                            //esquerda 
  esquerda_segue();
}

  re();                                                                 //re
  delay(400);

}

  if (digitalRead(Sensor_direito_fora) == HIGH && digitalRead(Sensor_direito) == HIGH ) {      // os dois sensores direito = preto

  motor_esquerda_frente.run(RELEASE);                                           //para
  motor_esquerda_tras.run(RELEASE);
  motor_direita_frente.run(RELEASE);
  motor_direita_tras.run(RELEASE);
  delay(500); 

  frente();                                                                     //frente
  delay(1000);

  esquerda_segue();                                                             //esquerda
  delay(500);
 
  motor_esquerda_frente.run(RELEASE);                                           //para
  motor_esquerda_tras.run(RELEASE);
  motor_direita_frente.run(RELEASE);
  motor_direita_tras.run(RELEASE); 
  delay(400); 

  while(digitalRead(Sensor_meio) != HIGH) {                                    //direita
  direita_segue();
}

  re();                                                                        //re
  delay(400);

}
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void re(){

  motor_direita_tras.setSpeed(85);
  motor_direita_frente.setSpeed(85);
  motor_esquerda_frente.setSpeed(85);
  motor_esquerda_tras.setSpeed(85);

  motor_direita_frente.run(BACKWARD);  // FRENTE
  motor_direita_tras.run(BACKWARD);  // FRENTE
  motor_esquerda_frente.run(BACKWARD);  // FRENTE
  motor_esquerda_tras.run(BACKWARD);  // FRENTE

}

void frente(){

  motor_direita_tras.setSpeed(90);
  motor_direita_frente.setSpeed(90);
  motor_esquerda_frente.setSpeed(90);
  motor_esquerda_tras.setSpeed(90);
  
  motor_direita_frente.run(FORWARD);  // RE
  motor_direita_tras.run(FORWARD);  // RE
  motor_esquerda_frente.run(FORWARD);  // RE
  motor_esquerda_tras.run(FORWARD);  // RE

}
void frente_segue(){

  motor_direita_tras.setSpeed(70);
  motor_direita_frente.setSpeed(70);
  motor_esquerda_frente.setSpeed(90);
  motor_esquerda_tras.setSpeed(90);
  
  motor_direita_frente.run(FORWARD);  // RE
  motor_direita_tras.run(FORWARD);  // RE
  motor_esquerda_frente.run(FORWARD);  // RE
  motor_esquerda_tras.run(FORWARD);  // RE

}
void esquerda_segue(){

  motor_direita_tras.setSpeed(190);
  motor_direita_frente.setSpeed(190);
  motor_esquerda_frente.setSpeed(190);
  motor_esquerda_tras.setSpeed(190);

 motor_esquerda_frente.run(BACKWARD);  // FRENTE
 motor_esquerda_tras.run(BACKWARD);  // FRENTE
  motor_direita_frente.run(FORWARD);  // RE
  motor_direita_tras.run(FORWARD);  // RE

}

void direita_segue(){

  motor_direita_tras.setSpeed(190);
  motor_direita_frente.setSpeed(190);
  motor_esquerda_frente.setSpeed(190);
  motor_esquerda_tras.setSpeed(190);

  motor_esquerda_frente.run(FORWARD);  // FRENTE
  motor_esquerda_tras.run(FORWARD);  // FRENTE
  motor_direita_frente.run(BACKWARD);  // RE
  motor_direita_tras.run(BACKWARD);  // RE
}
void leitura(){
  
  sonar_frente = ultrasonicfrente.read();
  Serial.print("sonar frente cm: ");
  Serial.println(sonar_frente);
  sonar_esquerdo = ultrasonicesquerdo.read();
  Serial.print("sonar esquerdo cm: ");
  Serial.println(sonar_esquerdo);
  delay(100);
}