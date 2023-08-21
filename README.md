# TEMT6000
This repo contains TEMT6000 sensor calculation based on the datasheet using Arduino Uno

# Datasheet Interpretation

Based on the TEMT6000 datasheet by SparkFun (https://www.sparkfun.com/datasheets/Sensors/Imaging/TEMT6000.pdf) we infer the exact value of TEMT6000 illuminance as follows.

Figure 1. Collector Light Current vs. Illuminance of the TEMT6000 datasheet shows a logarithmic plot as given below.

![Screenshot from 2023-08-21 17-26-27](https://github.com/ParthaPRay/TEMT6000/assets/1689639/6c47f4e7-e6fd-4d25-b4b5-26beb0129442)

In the above plot, we can see a linear relationship between I<sub>ca</sub> and E<sub>v</sub>. That suggests a power-law elationship, which can be described as:

I = k×L<sup>m</sup>         equation (1)

Where:
* I is the collector light current.
* L is the light intensity in lux.
* k is a proportionality constant.
* m is the exponent, which we inferred to be 1.5 based on the logarithmic plot.

On the above plot, Considering the data point provided (100 lux corresponds to 10<sup>1.5</sup> or approximately 31.62 µA), we can determine the value of k.

k = (I/L<sup>m</sup>)     equation (2)

We put: L = 100  #lux, I = 31.62 #µA, and m = 1.5 
we get, k = 0.03162 from the above formula (2).


# Arduino Code

Now, to map the current to lux values in the Arduino code, we'll use this power-law relationship. Specifically, when reading the current value from the sensor, we can determine the corresponding lux value using the inverse of the relationship:

L = (I/k)​<sup>(1/m)</sup>    equation (3)



**1. Reading Analog Value:**

int analogValue = analogRead(temt6000Pin);

Explanation:

The Arduino uses an analog-to-digital converter (ADC) to transform the analog voltage (from the TEMT6000 sensor) into a digital value. This ADC on most Arduinos is a 10-bit ADC, meaning it can represent voltages with integers ranging from 0 to 1023.

**2. Convert ADC Value to Voltage:**

float voltage = (analogValue * referenceVoltage) / 1023.0;


Given that the ADC provides values between 0 (for 0V) and 1023 (for the reference voltage, usually 5V or 3.3V), we can map the analogValue to an actual voltage using:

voltage = (analogValue × referenceVoltage)/1023
 
**3. Convert Voltage to Current:**

float currentInMicroA = voltage / resistorValue * 1E6;

The TEMT6000 provides a current output proportional to the light intensity. This current passes through a resistor (10kΩ in our case), creating a voltage drop. Ohm's Law (V = I * R) allows us to compute the current:

I = (V/R)

Here, 
I is the current, 
V is the voltage across the resistor, and 
R is the resistor value. We then multiply by 10<sup>6</sup> i.e. 1E6 to convert the current from amperes to microamperes.

**4. Calculate Illuminance using the Power-Law Relationship:**

float k = 0.03162;

float m = 1.5;

float illuminance = pow(currentInMicroA / k, 1/m);


From the logarithmic plot provided in the datasheet, we derived the power-law relationship between illuminance L (in lux) and the collector light current I (in µA) as:

I = k×L<sup>m</sup>         equation (1)
 
Given the current, we want to find the corresponding illuminance. Rearranging the above equation, we get:

L = (I/k)​<sup>(1/m)</sup>    equation (3)
​
  
Here, 
k is the proportionality constant and 

m is the exponent, which was inferred to be 1.5 based on the logarithmic plot.

**5. Constrain Illuminance:**


illuminance = constrain(illuminance, 10, 1000);

To ensure the illuminance values are realistic and within the expected range of the sensor, we use the constrain function to limit the values between 10 and 1000 lux. If the calculated illuminance is below 10, it's set to 10; if it's above 1000, it's set to 1000.

Finally, the function returns the calculated and constrained illuminance value.


