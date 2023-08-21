# TEMT6000
This repo contains TEMT6000 sensor calculation based on the datasheet using Arduino Uno

# Datasheet Interpretation

Based on the TEMT6000 datasheet by SparkFun (https://www.sparkfun.com/datasheets/Sensors/Imaging/TEMT6000.pdf) we infer the exact value of TEMT6000 illuminance as follows.

Figure 1. Collector Light Current vs. Illuminance of the TEMT6000 datasheet shows a logarithmic plot as given below.

![Screenshot from 2023-08-21 17-26-27](https://github.com/ParthaPRay/TEMT6000/assets/1689639/6c47f4e7-e6fd-4d25-b4b5-26beb0129442)

In the above plot, we can see a linear relationship between I<sub>ca</sub> and E<sub>v</sub>. That suggests a power-law elationship, which can be described as:
I=k×L<sup>m</sup> 

 



