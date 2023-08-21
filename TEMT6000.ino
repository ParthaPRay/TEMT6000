// Partha Pratim Ray
// Date: 21 August, 2023


const int temt6000Pin = A0;
const float referenceVoltage = 5.0;  // Adjust this to 3.3 if you're using 3.3V
const float resistorValue = 10000.0;  // 10k ohms (from our earlier discussion)

void setup() {
  Serial.begin(115200);  // Set baud rate to 115200 for faster communication
  pinMode(temt6000Pin, INPUT);
}

void loop() {
  float illuminance = readIlluminance();
  Serial.print("Illuminance: ");
  Serial.print(illuminance);
  Serial.println(" lux");
  delay(100);  // Reduced delay to 100ms
}

float readIlluminance() {
  int analogValue = analogRead(temt6000Pin);
  float voltage = (analogValue * referenceVoltage) / 1023.0;
  float currentInMicroA = voltage / resistorValue * 1E6;  // Convert voltage to current in µA
  
  // Calculate illuminance using the power-law relationship
  float k = 0.03162;  // Proportionality constant
  float m = 1.5;      // Exponent from the log-log plot
  float illuminance = pow(currentInMicroA / k, 1/m);
  
  // Ensure values are within the 10 to 1000 lux range
  illuminance = constrain(illuminance, 10, 1000);  

  return illuminance;
}
