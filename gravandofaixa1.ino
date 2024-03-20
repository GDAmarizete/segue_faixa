#include <QTRSensors.h>
#include <EEPROM.h>

QTRSensors qtr;

const uint8_t SensorCount = 8;
uint16_t position = 0;
uint16_t sensorValues[SensorCount];

uint16_t minValues[SensorCount];
uint16_t maxValues[SensorCount];

bool calibrationDone = false;

void setup() {
  Serial.begin(9600);

  loadCalibrationValues();

  qtr.setTypeAnalog();
  uint8_t sensorPins[SensorCount] = {A0, A1, A2, A3, A4, A5, A6, A7}; // Use os pinos digitais adequados
  qtr.setSensorPins(sensorPins, SensorCount);
  qtr.setEmitterPin(2); // Pino do emissor (LED)

  delay(500);
  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, HIGH);

  Serial.println("Deseja calibrar os sensores? Pressione C para calibrar ou P para pular a calibração.");

  while (!Serial.available()) {
    delay(100);
  }
  char userInput = Serial.read(); // Ler a entrada do usuário

  if (userInput == 'C' || userInput == 'c') {
    Serial.println("Iniciando a calibração dos sensores...");
    calibrateSensors();
    saveCalibrationValues();
    calibrationDone = true;
    Serial.println("Calibração concluída. Utilizando valores calibrados.");
  } else if (userInput == 'P' || userInput == 'p') {
    Serial.println("Calibração pulada. Utilizando valores da EEPROM.");
    loadCalibrationValues();
    calibrationDone = true;
  } else {
    Serial.println("Opção inválida. Utilizando valores da EEPROM.");
    calibrationDone = true;
  }

  Serial.println("Valores de calibração:");
  for (uint8_t i = 0; i < SensorCount; i++) {
    Serial.print(minValues[i]);
    Serial.print(' ');
  }
  Serial.println();

  for (uint8_t i = 0; i < SensorCount; i++) {
    Serial.print(maxValues[i]);
    Serial.print(' ');
  }
  Serial.println();
  Serial.println();
  delay(1000);
}

void loop() {
  if (calibrationDone && Serial.available()) {
    char userInput = Serial.read();
    if (userInput == 'R' || userInput == 'r') {
      readSensors(); // Chama a função para ler os sensores
    }
  }

  delay(1000);
}

void calibrateSensors() {
  for (uint16_t i = 0; i < 400; i++) {
    qtr.calibrate(); // Chama a função de calibração sem argumentos
  }

  for (uint8_t j = 0; j < SensorCount; j++) {
    minValues[j] = qtr.calibrationOn.minimum[j];
    maxValues[j] = qtr.calibrationOn.maximum[j];
  }
   for (uint16_t i = 0; i < SensorCount; i++) {
    minValues[i] = qtr.calibrationOn.minimum[i];
    maxValues[i] = qtr.calibrationOn.maximum[i];
  }
 
  digitalWrite(LED_BUILTIN, LOW);
}

void readSensors() {
  
  
  // Sempre leia os sensores, mesmo que a calibração tenha sido pulada
  qtr.read(sensorValues);

  position = qtr.readLineBlack(sensorValues);

  if (position < 1000)
    {
      Serial.println("Valores quando o sensor está na linha branca:");
    }
    else
    {
      Serial.println("Valores quando o sensor está na linha preta:");
    }
  for (uint16_t i = 0; i < SensorCount; i++) {
    Serial.print(sensorValues[i]);
    Serial.print('\t');
  }
  Serial.println();
}

void saveCalibrationValues() {
  for (uint8_t j = 0; j < SensorCount; j++) {
    EEPROM.put(j * sizeof(uint16_t) * 2, minValues[j]);
    EEPROM.put(j * sizeof(uint16_t) * 2 + sizeof(uint16_t), maxValues[j]);
   
   for (uint16_t i = 0; i < SensorCount; i++) {
    EEPROM.get(i * sizeof(uint16_t) * 2, minValues[i]);
    EEPROM.get(i * sizeof(uint16_t) * 2 + sizeof(uint16_t), maxValues[i]);
  }
  }
}

void loadCalibrationValues() {
  for (uint16_t i = 0; i < SensorCount; i++) {
    EEPROM.get(i * sizeof(uint16_t) * 2, minValues[i]);
    EEPROM.get(i * sizeof(uint16_t) * 2 + sizeof(uint16_t), maxValues[i]);
  }
}
