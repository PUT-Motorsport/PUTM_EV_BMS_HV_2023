# PUTM_EV_BMS_HV_2023
Accumulator Managment System (High Voltage Battery Managment System)

## Overview
The AMS system consists of two main parts, the master and multiple slaves.
<p align="center">
  <img src="https://github.com/user-attachments/assets/a5bbf403-06de-40c9-b362-9b193c4f06d8">
</p>
The apparatus is responsible for the managment of the battery as a whole, determining it's states like: state of charge or unsafe state plausibility. It also supervises the turning on and off of the hv bus.

## Master
The AMS Master is the center of the whole system it's responsible for most of the tasks: current measurement, high voltage relay control, slave control, high voltage measurement and communication with the car. 
<p align="center"> 
  <img src="https://github.com/user-attachments/assets/76ba6605-d5d6-49a4-94d3-47f30560dd39">
</p>
