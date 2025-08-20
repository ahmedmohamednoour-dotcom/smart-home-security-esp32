#include <BluetoothSerial.h>
#include <DHT.h>

#define DHTPIN 13              // Pin connected to DHT22
#define DHTTYPE DHT22         // DHT22 sensor type
#define MQ2PIN 14             // Analog pin for MQ-3 alcohol sensor
#define LDRPIN 12             // Analog pin for LDR (light sensor)
#define flamePin 26             // Analog pin for LDR (light sensor)
#define fanPin 15             // buzzer

                                                                                                       
BluetoothSerial BTSerial;             

DHT dht(DHTPIN, DHTTYPE); 

void setup() {
  Serial.begin(115200);
  dht.begin();
  
  pinMode(MQ2PIN, INPUT);
  pinMode(LDRPIN, INPUT);

  pinMode(fanPin, OUTPUT);

  // Initialize Bluetooth Serial
  if (BTSerial.begin("ESP32_Monitor")) {

    Serial.println("Bluetooth initialized, discoverable as ESP32_Monitor");

  }else{

    Serial.println("Bluetooth initialization failed");
    return;

  }
  
}

void loop() {
  // Gather data from sensors
  float temperature = dht.readTemperature();
  float humidity = dht.readHumidity();

  float butaneRate = analogRead(MQ2PIN);   // Raw reading from MQ-3 sensor
  int lightIntensity = analogRead(LDRPIN); // Raw reading from LDR sensor
  int fanstate = digitalRead(fanPin); // Raw reading from LDR sensor

  lightIntensity = map(lightIntensity, 4095, 0, 0 , 100);
  butaneRate = map(butaneRate, 10, 3480, 0 , 100);

  if (temperature > 25 || temperature < 20) {
    digitalWrite(fanstate, LOW);
    
  }else{
    digitalWrite(fanstate, HIGH);
  }

  
  // Format data as CSV and send over Bluetooth

  String dataString = String(temperature) + ", " + String(humidity) + ", " + String(butaneRate) + ", " + String(lightIntensity) + "\n"; //
  
  BTSerial.print(dataString); // Send data via Bluetooth

  // Optional: Print data to Serial Monitor for debugging
  Serial.print("Sent data: ");
  Serial.print(dataString);


  delay(5000); // Transmit every 5 seconds
}
 