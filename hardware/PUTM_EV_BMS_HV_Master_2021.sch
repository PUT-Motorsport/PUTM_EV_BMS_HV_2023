EESchema Schematic File Version 4
EELAYER 30 0
EELAYER END
$Descr A2 23386 16535
encoding utf-8
Sheet 1 1
Title "PUTM_EV_BMS_HV_Master"
Date "2021-01-26"
Rev "1.0"
Comp "PUT Motorsport"
Comment1 ""
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
$Comp
L Connector_Generic:Conn_01x04 J2
U 1 1 601325A2
P 1500 1250
F 0 "J2" H 1580 1242 50  0000 L CNN
F 1 "Conn_01x04" H 1580 1151 50  0000 L CNN
F 2 "TerminalBlock_MetzConnect:TerminalBlock_MetzConnect_Type086_RT03404HBLC_1x04_P3.81mm_Horizontal" H 1500 1250 50  0001 C CNN
F 3 "~" H 1500 1250 50  0001 C CNN
	1    1500 1250
	1    0    0    -1  
$EndComp
Text Label 1300 1250 2    50   ~ 0
SENSOR_REF
Text Label 1300 1350 2    50   ~ 0
SENSOR_SIGNAL
$Comp
L power:GND #PWR04
U 1 1 601330DC
P 1250 1500
F 0 "#PWR04" H 1250 1250 50  0001 C CNN
F 1 "GND" H 1255 1327 50  0000 C CNN
F 2 "" H 1250 1500 50  0001 C CNN
F 3 "" H 1250 1500 50  0001 C CNN
	1    1250 1500
	1    0    0    -1  
$EndComp
Wire Wire Line
	1300 1450 1250 1450
Wire Wire Line
	1250 1450 1250 1500
$Comp
L power:+5V #PWR03
U 1 1 60133671
P 1250 800
F 0 "#PWR03" H 1250 650 50  0001 C CNN
F 1 "+5V" H 1265 973 50  0000 C CNN
F 2 "" H 1250 800 50  0001 C CNN
F 3 "" H 1250 800 50  0001 C CNN
	1    1250 800 
	1    0    0    -1  
$EndComp
Wire Wire Line
	1300 1150 1250 1150
Wire Wire Line
	1250 1150 1250 1050
$Comp
L Connector_Generic:Conn_01x02 J3
U 1 1 60135D41
P 1500 5000
F 0 "J3" H 1580 4992 50  0000 L CNN
F 1 "Conn_01x02" H 1580 4901 50  0000 L CNN
F 2 "TerminalBlock_MetzConnect:TerminalBlock_MetzConnect_Type086_RT03402HBLC_1x02_P3.81mm_Horizontal" H 1500 5000 50  0001 C CNN
F 3 "~" H 1500 5000 50  0001 C CNN
	1    1500 5000
	1    0    0    -1  
$EndComp
$Comp
L Connector_Generic:Conn_01x02 J4
U 1 1 6013625E
P 1500 5300
F 0 "J4" H 1580 5292 50  0000 L CNN
F 1 "Conn_01x02" H 1580 5201 50  0000 L CNN
F 2 "TerminalBlock_MetzConnect:TerminalBlock_MetzConnect_Type086_RT03402HBLC_1x02_P3.81mm_Horizontal" H 1500 5300 50  0001 C CNN
F 3 "~" H 1500 5300 50  0001 C CNN
	1    1500 5300
	1    0    0    -1  
$EndComp
$Comp
L Connector_Generic:Conn_01x02 J5
U 1 1 60136589
P 1500 5600
F 0 "J5" H 1580 5592 50  0000 L CNN
F 1 "Conn_01x02" H 1580 5501 50  0000 L CNN
F 2 "TerminalBlock_MetzConnect:TerminalBlock_MetzConnect_Type086_RT03402HBLC_1x02_P3.81mm_Horizontal" H 1500 5600 50  0001 C CNN
F 3 "~" H 1500 5600 50  0001 C CNN
	1    1500 5600
	1    0    0    -1  
$EndComp
Wire Wire Line
	1300 5600 1250 5600
Wire Wire Line
	1250 5600 1250 5700
Wire Wire Line
	1250 5700 1300 5700
Wire Wire Line
	1250 5700 1250 5750
Connection ~ 1250 5700
Wire Wire Line
	1300 5300 1250 5300
Wire Wire Line
	1250 5300 1250 5350
Wire Wire Line
	1250 5400 1300 5400
Wire Wire Line
	1300 5000 1250 5000
Wire Wire Line
	1250 5000 1250 5050
Wire Wire Line
	1250 5100 1300 5100
Wire Wire Line
	1250 5050 1200 5050
Connection ~ 1250 5050
Wire Wire Line
	1250 5050 1250 5100
Wire Wire Line
	1250 5350 1200 5350
Connection ~ 1250 5350
Wire Wire Line
	1250 5350 1250 5400
Text Label 1200 5050 2    50   ~ 0
HV_ACU_VOLTAGE
Text Label 1200 5350 2    50   ~ 0
HV_CAR_VOLTAGE
$Comp
L Device:R R?
U 1 1 60156E47
P 2250 4400
AR Path="/600380E4/60156E47" Ref="R?"  Part="1" 
AR Path="/60156E47" Ref="R3"  Part="1" 
F 0 "R3" V 2043 4400 50  0000 C CNN
F 1 "200k" V 2134 4400 50  0000 C CNN
F 2 "Resistor_SMD:R_1206_3216Metric" V 2180 4400 50  0001 C CNN
F 3 "~" H 2250 4400 50  0001 C CNN
	1    2250 4400
	0    1    1    0   
$EndComp
$Comp
L Device:R R?
U 1 1 60156E4D
P 2600 4400
AR Path="/600380E4/60156E4D" Ref="R?"  Part="1" 
AR Path="/60156E4D" Ref="R5"  Part="1" 
F 0 "R5" V 2393 4400 50  0000 C CNN
F 1 "200k" V 2484 4400 50  0000 C CNN
F 2 "Resistor_SMD:R_1206_3216Metric" V 2530 4400 50  0001 C CNN
F 3 "~" H 2600 4400 50  0001 C CNN
	1    2600 4400
	0    1    1    0   
$EndComp
$Comp
L Device:R R?
U 1 1 60156E53
P 2950 4400
AR Path="/600380E4/60156E53" Ref="R?"  Part="1" 
AR Path="/60156E53" Ref="R7"  Part="1" 
F 0 "R7" V 2743 4400 50  0000 C CNN
F 1 "200k" V 2834 4400 50  0000 C CNN
F 2 "Resistor_SMD:R_1206_3216Metric" V 2880 4400 50  0001 C CNN
F 3 "~" H 2950 4400 50  0001 C CNN
	1    2950 4400
	0    1    1    0   
$EndComp
$Comp
L Device:R R?
U 1 1 60156E59
P 3200 4600
AR Path="/600380E4/60156E59" Ref="R?"  Part="1" 
AR Path="/60156E59" Ref="R9"  Part="1" 
F 0 "R9" H 3130 4554 50  0000 R CNN
F 1 "2,2k" H 3130 4645 50  0000 R CNN
F 2 "Resistor_SMD:R_0603_1608Metric" V 3130 4600 50  0001 C CNN
F 3 "~" H 3200 4600 50  0001 C CNN
	1    3200 4600
	-1   0    0    1   
$EndComp
$Comp
L Device:R R?
U 1 1 60156E77
P 3250 6950
AR Path="/600380E4/60156E77" Ref="R?"  Part="1" 
AR Path="/60156E77" Ref="R10"  Part="1" 
F 0 "R10" H 3180 6904 50  0000 R CNN
F 1 "2,2k" H 3180 6995 50  0000 R CNN
F 2 "Resistor_SMD:R_0603_1608Metric" V 3180 6950 50  0001 C CNN
F 3 "~" H 3250 6950 50  0001 C CNN
	1    3250 6950
	-1   0    0    1   
$EndComp
$Comp
L Device:C C?
U 1 1 60156ED1
P 5550 7700
AR Path="/600380E4/60156ED1" Ref="C?"  Part="1" 
AR Path="/60156ED1" Ref="C14"  Part="1" 
F 0 "C14" H 5665 7746 50  0000 L CNN
F 1 "100nF" H 5665 7655 50  0000 L CNN
F 2 "Capacitor_SMD:C_0603_1608Metric" H 5588 7550 50  0001 C CNN
F 3 "~" H 5550 7700 50  0001 C CNN
	1    5550 7700
	1    0    0    -1  
$EndComp
$Comp
L Device:C C?
U 1 1 60156EDD
P 8050 5500
AR Path="/600380E4/60156EDD" Ref="C?"  Part="1" 
AR Path="/60156EDD" Ref="C19"  Part="1" 
F 0 "C19" H 8165 5546 50  0000 L CNN
F 1 "100nF" H 8165 5455 50  0000 L CNN
F 2 "Capacitor_SMD:C_0603_1608Metric" H 8088 5350 50  0001 C CNN
F 3 "~" H 8050 5500 50  0001 C CNN
	1    8050 5500
	1    0    0    -1  
$EndComp
Text Notes 8325 7050 0    50   ~ 0
Fc=1kHz
Wire Wire Line
	3200 4400 3200 4450
Wire Wire Line
	3200 4400 3500 4400
Wire Wire Line
	4200 4400 3500 4400
Connection ~ 3500 4400
Wire Wire Line
	4200 4800 3950 4800
Wire Wire Line
	3250 6750 3250 6800
Wire Wire Line
	3250 6750 3550 6750
Wire Wire Line
	3550 6750 4250 6750
Connection ~ 3550 6750
Wire Wire Line
	3550 7150 3250 7150
Wire Wire Line
	3250 7150 3250 7100
Connection ~ 3550 7150
Wire Wire Line
	4250 6950 4000 6950
Wire Wire Line
	4000 6950 4000 7150
Connection ~ 4000 7150
Wire Wire Line
	4000 7150 3550 7150
Wire Wire Line
	4200 4600 3950 4600
Wire Wire Line
	3950 4600 3950 4800
Wire Wire Line
	3950 4800 3500 4800
Wire Wire Line
	3200 4800 3200 4750
Connection ~ 3950 4800
Connection ~ 3500 4800
Wire Wire Line
	3500 4800 3200 4800
$Comp
L PUTM_EV_BMS_library:AMC1311DWV U?
U 1 1 60156F50
P 4750 4600
AR Path="/600380E4/60156F50" Ref="U?"  Part="1" 
AR Path="/60156F50" Ref="U2"  Part="1" 
F 0 "U2" H 4750 5115 50  0000 C CNN
F 1 "AMC1311DWV" H 4750 5024 50  0000 C CNN
F 2 "Package_SO:SOIC-8_7.5x5.85mm_P1.27mm" H 4800 4250 50  0001 C CNN
F 3 "https://www.ti.com/lit/ds/symlink/amc1311.pdf?ts=1610792186113&ref_url=https%253A%252F%252Fwww.google.com%252F" H 4700 5300 50  0001 C CNN
	1    4750 4600
	1    0    0    -1  
$EndComp
$Comp
L PUTM_EV_BMS_library:AMC1311DWV U?
U 1 1 60156F56
P 4800 6950
AR Path="/600380E4/60156F56" Ref="U?"  Part="1" 
AR Path="/60156F56" Ref="U3"  Part="1" 
F 0 "U3" H 4800 7465 50  0000 C CNN
F 1 "AMC1311DWV" H 4800 7374 50  0000 C CNN
F 2 "Package_SO:SOIC-8_7.5x5.85mm_P1.27mm" H 4850 6600 50  0001 C CNN
F 3 "https://www.ti.com/lit/ds/symlink/amc1311.pdf?ts=1610792186113&ref_url=https%253A%252F%252Fwww.google.com%252F" H 4750 7650 50  0001 C CNN
	1    4800 6950
	1    0    0    -1  
$EndComp
$Comp
L MCU_ST_STM32F4:STM32F446RETx U?
U 1 1 60188A8F
P 18300 6050
AR Path="/60056272/60188A8F" Ref="U?"  Part="1" 
AR Path="/60188A8F" Ref="U19"  Part="1" 
F 0 "U19" H 18800 4300 50  0000 C CNN
F 1 "STM32F446RETx" H 18300 6050 50  0000 C CNN
F 2 "Package_QFP:LQFP-64_10x10mm_P0.5mm" H 17700 4350 50  0001 R CNN
F 3 "http://www.st.com/st-web-ui/static/active/en/resource/technical/document/datasheet/DM00141306.pdf" H 18300 6050 50  0001 C CNN
	1    18300 6050
	1    0    0    -1  
$EndComp
$Comp
L PUTM_EV_BMS_library:AT45DB641E-SHN-T U?
U 1 1 60188A95
P 20300 1800
AR Path="/60056272/60188A95" Ref="U?"  Part="1" 
AR Path="/60188A95" Ref="U20"  Part="1" 
F 0 "U20" H 20300 2215 50  0000 C CNN
F 1 "AT45DB641E-SHN-T" H 20300 2124 50  0000 C CNN
F 2 "Package_SO:SOIC-8_5.23x5.23mm_P1.27mm" H 20300 1500 50  0001 C CNN
F 3 "https://www.tme.eu/Document/f45b2c566e3fa2479856fbfc9ee4fea2/AT45DB641E-DTE.pdf" H 20300 1750 50  0001 C CNN
	1    20300 1800
	1    0    0    -1  
$EndComp
$Comp
L Device:C_Small C?
U 1 1 60188A9B
P 21350 1800
AR Path="/60056272/60188A9B" Ref="C?"  Part="1" 
AR Path="/60188A9B" Ref="C56"  Part="1" 
F 0 "C56" H 21442 1846 50  0000 L CNN
F 1 "1uF" H 21442 1755 50  0000 L CNN
F 2 "Capacitor_SMD:C_0603_1608Metric" H 21350 1800 50  0001 C CNN
F 3 "~" H 21350 1800 50  0001 C CNN
	1    21350 1800
	1    0    0    -1  
$EndComp
$Comp
L Device:R_Small R?
U 1 1 60188AA1
P 21100 1400
AR Path="/60056272/60188AA1" Ref="R?"  Part="1" 
AR Path="/60188AA1" Ref="R89"  Part="1" 
F 0 "R89" H 21159 1446 50  0000 L CNN
F 1 "10k" H 21159 1355 50  0000 L CNN
F 2 "Resistor_SMD:R_0603_1608Metric" H 21100 1400 50  0001 C CNN
F 3 "~" H 21100 1400 50  0001 C CNN
	1    21100 1400
	1    0    0    -1  
$EndComp
$Comp
L Device:R_Small R?
U 1 1 60188AA7
P 20850 1400
AR Path="/60056272/60188AA7" Ref="R?"  Part="1" 
AR Path="/60188AA7" Ref="R88"  Part="1" 
F 0 "R88" H 20909 1446 50  0000 L CNN
F 1 "10k" H 20909 1355 50  0000 L CNN
F 2 "Resistor_SMD:R_0603_1608Metric" H 20850 1400 50  0001 C CNN
F 3 "~" H 20850 1400 50  0001 C CNN
	1    20850 1400
	1    0    0    -1  
$EndComp
$Comp
L Device:C_Small C?
U 1 1 60188AAD
P 19750 3700
AR Path="/60056272/60188AAD" Ref="C?"  Part="1" 
AR Path="/60188AAD" Ref="C54"  Part="1" 
F 0 "C54" H 19842 3746 50  0000 L CNN
F 1 "100nF" H 19842 3655 50  0000 L CNN
F 2 "Capacitor_SMD:C_0603_1608Metric" H 19750 3700 50  0001 C CNN
F 3 "~" H 19750 3700 50  0001 C CNN
	1    19750 3700
	1    0    0    -1  
$EndComp
$Comp
L Device:C_Small C?
U 1 1 60188AB3
P 19350 3700
AR Path="/60056272/60188AB3" Ref="C?"  Part="1" 
AR Path="/60188AB3" Ref="C52"  Part="1" 
F 0 "C52" H 19442 3746 50  0000 L CNN
F 1 "100nF" H 19442 3655 50  0000 L CNN
F 2 "Capacitor_SMD:C_0603_1608Metric" H 19350 3700 50  0001 C CNN
F 3 "~" H 19350 3700 50  0001 C CNN
	1    19350 3700
	1    0    0    -1  
$EndComp
$Comp
L Device:C_Small C?
U 1 1 60188AB9
P 18950 3700
AR Path="/60056272/60188AB9" Ref="C?"  Part="1" 
AR Path="/60188AB9" Ref="C51"  Part="1" 
F 0 "C51" H 19042 3746 50  0000 L CNN
F 1 "100nF" H 19042 3655 50  0000 L CNN
F 2 "Capacitor_SMD:C_0603_1608Metric" H 18950 3700 50  0001 C CNN
F 3 "~" H 18950 3700 50  0001 C CNN
	1    18950 3700
	1    0    0    -1  
$EndComp
$Comp
L Device:C_Small C?
U 1 1 60188ABF
P 18550 3700
AR Path="/60056272/60188ABF" Ref="C?"  Part="1" 
AR Path="/60188ABF" Ref="C50"  Part="1" 
F 0 "C50" H 18642 3746 50  0000 L CNN
F 1 "100nF" H 18642 3655 50  0000 L CNN
F 2 "Capacitor_SMD:C_0603_1608Metric" H 18550 3700 50  0001 C CNN
F 3 "~" H 18550 3700 50  0001 C CNN
	1    18550 3700
	1    0    0    -1  
$EndComp
$Comp
L Device:C_Small C?
U 1 1 60188AC5
P 20600 4050
AR Path="/60056272/60188AC5" Ref="C?"  Part="1" 
AR Path="/60188AC5" Ref="C55"  Part="1" 
F 0 "C55" H 20692 4096 50  0000 L CNN
F 1 "10uF" H 20692 4005 50  0000 L CNN
F 2 "Capacitor_SMD:C_0805_2012Metric" H 20600 4050 50  0001 C CNN
F 3 "~" H 20600 4050 50  0001 C CNN
	1    20600 4050
	1    0    0    -1  
$EndComp
$Comp
L Device:C_Small C?
U 1 1 60188ACB
P 17700 4050
AR Path="/60056272/60188ACB" Ref="C?"  Part="1" 
AR Path="/60188ACB" Ref="C48"  Part="1" 
F 0 "C48" H 17792 4096 50  0000 L CNN
F 1 "4.7uF" H 17792 4005 50  0000 L CNN
F 2 "Capacitor_SMD:C_0603_1608Metric" H 17700 4050 50  0001 C CNN
F 3 "~" H 17700 4050 50  0001 C CNN
	1    17700 4050
	1    0    0    -1  
$EndComp
Wire Wire Line
	20700 1750 20850 1750
Wire Wire Line
	20850 1750 20850 1500
Wire Wire Line
	20700 1850 21100 1850
Wire Wire Line
	21100 1850 21100 1500
Wire Wire Line
	20700 1650 21350 1650
Wire Wire Line
	21350 1650 21350 1700
Wire Wire Line
	21350 1650 21350 1250
Wire Wire Line
	21350 1250 21100 1250
Wire Wire Line
	20850 1250 20850 1300
Connection ~ 21350 1650
Wire Wire Line
	21100 1300 21100 1250
Connection ~ 21100 1250
Wire Wire Line
	21100 1250 20850 1250
Wire Wire Line
	21350 1900 21350 1950
Wire Wire Line
	21350 1950 21100 1950
$Comp
L Device:L_Small L?
U 1 1 60188AE0
P 20950 3900
AR Path="/60056272/60188AE0" Ref="L?"  Part="1" 
AR Path="/60188AE0" Ref="L4"  Part="1" 
F 0 "L4" V 21135 3900 50  0000 C CNN
F 1 "NLV32T-220J-PF" V 21044 3900 50  0000 C CNN
F 2 "Inductor_SMD:L_1210_3225Metric" H 20950 3900 50  0001 C CNN
F 3 "~" H 20950 3900 50  0001 C CNN
	1    20950 3900
	0    -1   -1   0   
$EndComp
$Comp
L Device:Crystal_Small Y?
U 1 1 60188AE6
P 17000 5600
AR Path="/60056272/60188AE6" Ref="Y?"  Part="1" 
AR Path="/60188AE6" Ref="Y2"  Part="1" 
F 0 "Y2" V 16954 5688 50  0000 L CNN
F 1 "8MHz" V 17045 5688 50  0000 L CNN
F 2 "Crystal:Crystal_HC49-4H_Vertical" H 17000 5600 50  0001 C CNN
F 3 "~" H 17000 5600 50  0001 C CNN
	1    17000 5600
	0    1    1    0   
$EndComp
Wire Wire Line
	16850 5750 17000 5750
Wire Wire Line
	17000 5750 17000 5700
Wire Wire Line
	17000 5500 17000 5450
Wire Wire Line
	17000 5450 16850 5450
Connection ~ 17000 5450
Connection ~ 17000 5750
Wire Wire Line
	16650 5450 16450 5450
Wire Wire Line
	16450 5450 16450 5600
Wire Wire Line
	16450 5750 16650 5750
$Comp
L power:GND #PWR?
U 1 1 60188B07
P 16400 5600
AR Path="/60056272/60188B07" Ref="#PWR?"  Part="1" 
AR Path="/60188B07" Ref="#PWR091"  Part="1" 
F 0 "#PWR091" H 16400 5350 50  0001 C CNN
F 1 "GND" V 16405 5472 50  0000 R CNN
F 2 "" H 16400 5600 50  0001 C CNN
F 3 "" H 16400 5600 50  0001 C CNN
	1    16400 5600
	0    1    1    0   
$EndComp
Wire Wire Line
	16400 5600 16450 5600
Connection ~ 16450 5600
Wire Wire Line
	16450 5600 16450 5750
$Comp
L Switch:SW_Push SW?
U 1 1 60188B10
P 16250 4650
AR Path="/60056272/60188B10" Ref="SW?"  Part="1" 
AR Path="/60188B10" Ref="SW1"  Part="1" 
F 0 "SW1" V 16296 4602 50  0000 R CNN
F 1 "RESET" V 16205 4602 50  0000 R CNN
F 2 "Button_Switch_THT:SW_PUSH_6mm_H5mm" H 16250 4850 50  0001 C CNN
F 3 "~" H 16250 4850 50  0001 C CNN
	1    16250 4650
	0    -1   -1   0   
$EndComp
$Comp
L Device:C_Small C?
U 1 1 60188B16
P 16700 4650
AR Path="/60056272/60188B16" Ref="C?"  Part="1" 
AR Path="/60188B16" Ref="C42"  Part="1" 
F 0 "C42" H 16792 4696 50  0000 L CNN
F 1 "100nF" H 16792 4605 50  0000 L CNN
F 2 "Capacitor_SMD:C_0603_1608Metric" H 16700 4650 50  0001 C CNN
F 3 "~" H 16700 4650 50  0001 C CNN
	1    16700 4650
	1    0    0    -1  
$EndComp
$Comp
L Device:R_Small R?
U 1 1 60188B1C
P 16250 4250
AR Path="/60056272/60188B1C" Ref="R?"  Part="1" 
AR Path="/60188B1C" Ref="R75"  Part="1" 
F 0 "R75" H 16309 4296 50  0000 L CNN
F 1 "10k" H 16309 4205 50  0000 L CNN
F 2 "Resistor_SMD:R_0603_1608Metric" H 16250 4250 50  0001 C CNN
F 3 "~" H 16250 4250 50  0001 C CNN
	1    16250 4250
	1    0    0    -1  
$EndComp
$Comp
L Diode:BAT54C D?
U 1 1 60188B22
P 18100 3550
AR Path="/60056272/60188B22" Ref="D?"  Part="1" 
AR Path="/60188B22" Ref="D8"  Part="1" 
F 0 "D8" H 18100 3775 50  0000 C CNN
F 1 "BAT54C" H 18100 3684 50  0000 C CNN
F 2 "Package_TO_SOT_SMD:SOT-23" H 18175 3675 50  0001 L CNN
F 3 "http://www.diodes.com/_files/datasheets/ds11005.pdf" H 18020 3550 50  0001 C CNN
	1    18100 3550
	1    0    0    -1  
$EndComp
$Comp
L Device:Battery_Cell BT?
U 1 1 60188B28
P 17300 3850
AR Path="/60056272/60188B28" Ref="BT?"  Part="1" 
AR Path="/60188B28" Ref="BT1"  Part="1" 
F 0 "BT1" H 17418 3946 50  0000 L CNN
F 1 "KEYSTONE 103" H 17418 3855 50  0000 L CNN
F 2 "Battery:BatteryHolder_Keystone_103_1x20mm" V 17300 3910 50  0001 C CNN
F 3 "~" V 17300 3910 50  0001 C CNN
	1    17300 3850
	1    0    0    -1  
$EndComp
$Comp
L Device:R_Small R?
U 1 1 60188B2E
P 21350 3900
AR Path="/60056272/60188B2E" Ref="R?"  Part="1" 
AR Path="/60188B2E" Ref="R90"  Part="1" 
F 0 "R90" V 21275 3875 50  0000 L CNN
F 1 "0" V 21425 3875 50  0000 L CNN
F 2 "Resistor_SMD:R_0603_1608Metric" H 21350 3900 50  0001 C CNN
F 3 "~" H 21350 3900 50  0001 C CNN
	1    21350 3900
	0    1    1    0   
$EndComp
Text Notes 20850 4300 0    50   ~ 0
2L/R^2 < C
Wire Wire Line
	20600 3900 20600 3950
Wire Wire Line
	20600 3900 20850 3900
Wire Wire Line
	21050 3900 21250 3900
Wire Wire Line
	18400 7850 18400 7950
Wire Wire Line
	18400 7950 18300 7950
Wire Wire Line
	18100 7950 18100 7850
Wire Wire Line
	18200 7850 18200 7950
Connection ~ 18200 7950
Wire Wire Line
	18200 7950 18100 7950
Connection ~ 18300 7950
Wire Wire Line
	18300 7850 18300 7950
$Comp
L power:GND #PWR?
U 1 1 60188B4D
P 18200 8050
AR Path="/60056272/60188B4D" Ref="#PWR?"  Part="1" 
AR Path="/60188B4D" Ref="#PWR0103"  Part="1" 
F 0 "#PWR0103" H 18200 7800 50  0001 C CNN
F 1 "GND" H 18205 7877 50  0000 C CNN
F 2 "" H 18200 8050 50  0001 C CNN
F 3 "" H 18200 8050 50  0001 C CNN
	1    18200 8050
	1    0    0    -1  
$EndComp
$Comp
L power:+3.3V #PWR?
U 1 1 60188B69
P 21500 3700
AR Path="/60056272/60188B69" Ref="#PWR?"  Part="1" 
AR Path="/60188B69" Ref="#PWR0123"  Part="1" 
F 0 "#PWR0123" H 21500 3550 50  0001 C CNN
F 1 "+3.3V" H 21515 3873 50  0000 C CNN
F 2 "" H 21500 3700 50  0001 C CNN
F 3 "" H 21500 3700 50  0001 C CNN
	1    21500 3700
	1    0    0    -1  
$EndComp
Wire Wire Line
	21500 3900 21450 3900
$Comp
L power:+3.3VA #PWR?
U 1 1 60188B70
P 20600 3700
AR Path="/60056272/60188B70" Ref="#PWR?"  Part="1" 
AR Path="/60188B70" Ref="#PWR0115"  Part="1" 
F 0 "#PWR0115" H 20600 3550 50  0001 C CNN
F 1 "+3.3VA" H 20615 3873 50  0000 C CNN
F 2 "" H 20600 3700 50  0001 C CNN
F 3 "" H 20600 3700 50  0001 C CNN
	1    20600 3700
	1    0    0    -1  
$EndComp
Wire Wire Line
	20600 3700 20600 3900
Connection ~ 20600 3900
$Comp
L power:+3.3VA #PWR?
U 1 1 60188B78
P 18600 4250
AR Path="/60056272/60188B78" Ref="#PWR?"  Part="1" 
AR Path="/60188B78" Ref="#PWR0107"  Part="1" 
F 0 "#PWR0107" H 18600 4100 50  0001 C CNN
F 1 "+3.3VA" H 18615 4423 50  0000 C CNN
F 2 "" H 18600 4250 50  0001 C CNN
F 3 "" H 18600 4250 50  0001 C CNN
	1    18600 4250
	1    0    0    -1  
$EndComp
Wire Wire Line
	18600 4250 18600 4350
Wire Wire Line
	21500 3700 21500 3900
$Comp
L power:+3.3V #PWR?
U 1 1 60188B80
P 19750 3500
AR Path="/60056272/60188B80" Ref="#PWR?"  Part="1" 
AR Path="/60188B80" Ref="#PWR0110"  Part="1" 
F 0 "#PWR0110" H 19750 3350 50  0001 C CNN
F 1 "+3.3V" H 19765 3673 50  0000 C CNN
F 2 "" H 19750 3500 50  0001 C CNN
F 3 "" H 19750 3500 50  0001 C CNN
	1    19750 3500
	1    0    0    -1  
$EndComp
Wire Wire Line
	19750 3500 19750 3550
Wire Wire Line
	19750 3550 19350 3550
Wire Wire Line
	18550 3550 18550 3600
Wire Wire Line
	18950 3600 18950 3550
Connection ~ 18950 3550
Wire Wire Line
	18950 3550 18550 3550
Wire Wire Line
	19350 3600 19350 3550
Connection ~ 19350 3550
Wire Wire Line
	19350 3550 18950 3550
Wire Wire Line
	19750 3600 19750 3550
Connection ~ 19750 3550
$Comp
L power:GND #PWR?
U 1 1 60188B91
P 19750 3900
AR Path="/60056272/60188B91" Ref="#PWR?"  Part="1" 
AR Path="/60188B91" Ref="#PWR0111"  Part="1" 
F 0 "#PWR0111" H 19750 3650 50  0001 C CNN
F 1 "GND" H 19755 3727 50  0000 C CNN
F 2 "" H 19750 3900 50  0001 C CNN
F 3 "" H 19750 3900 50  0001 C CNN
	1    19750 3900
	1    0    0    -1  
$EndComp
Wire Wire Line
	19750 3800 19750 3850
Wire Wire Line
	19750 3850 19350 3850
Wire Wire Line
	18550 3850 18550 3800
Connection ~ 19750 3850
Wire Wire Line
	19750 3850 19750 3900
Wire Wire Line
	18950 3800 18950 3850
Connection ~ 18950 3850
Wire Wire Line
	18950 3850 18550 3850
Wire Wire Line
	19350 3800 19350 3850
Connection ~ 19350 3850
Wire Wire Line
	19350 3850 18950 3850
$Comp
L power:+3.3V #PWR?
U 1 1 60188BA2
P 18300 4250
AR Path="/60056272/60188BA2" Ref="#PWR?"  Part="1" 
AR Path="/60188BA2" Ref="#PWR0104"  Part="1" 
F 0 "#PWR0104" H 18300 4100 50  0001 C CNN
F 1 "+3.3V" H 18315 4423 50  0000 C CNN
F 2 "" H 18300 4250 50  0001 C CNN
F 3 "" H 18300 4250 50  0001 C CNN
	1    18300 4250
	1    0    0    -1  
$EndComp
Wire Wire Line
	18500 4350 18400 4350
Connection ~ 18300 4350
Wire Wire Line
	18300 4350 18200 4350
Connection ~ 18400 4350
Wire Wire Line
	18400 4350 18300 4350
Wire Wire Line
	18300 4350 18300 4250
Wire Wire Line
	18400 3550 18550 3550
Connection ~ 18550 3550
Wire Wire Line
	18100 3750 18100 3900
Wire Wire Line
	17700 3950 17700 3900
Wire Wire Line
	17700 3900 18100 3900
Connection ~ 18100 3900
Wire Wire Line
	18100 3900 18100 4350
$Comp
L power:GND #PWR?
U 1 1 60188BB5
P 17700 4150
AR Path="/60056272/60188BB5" Ref="#PWR?"  Part="1" 
AR Path="/60188BB5" Ref="#PWR099"  Part="1" 
F 0 "#PWR099" H 17700 3900 50  0001 C CNN
F 1 "GND" H 17705 3977 50  0000 C CNN
F 2 "" H 17700 4150 50  0001 C CNN
F 3 "" H 17700 4150 50  0001 C CNN
	1    17700 4150
	1    0    0    -1  
$EndComp
Wire Wire Line
	17300 3650 17300 3550
Wire Wire Line
	17300 3550 17800 3550
Wire Wire Line
	17300 3950 17300 4150
Wire Wire Line
	17300 4150 17700 4150
Connection ~ 17700 4150
Text Notes 20450 4550 0    50   ~ 0
RLC lowpass filter for analog 3.3V
$Comp
L power:+3.3V #PWR?
U 1 1 60188BC1
P 21100 1150
AR Path="/60056272/60188BC1" Ref="#PWR?"  Part="1" 
AR Path="/60188BC1" Ref="#PWR0119"  Part="1" 
F 0 "#PWR0119" H 21100 1000 50  0001 C CNN
F 1 "+3.3V" H 21115 1323 50  0000 C CNN
F 2 "" H 21100 1150 50  0001 C CNN
F 3 "" H 21100 1150 50  0001 C CNN
	1    21100 1150
	1    0    0    -1  
$EndComp
Wire Wire Line
	21100 1150 21100 1250
$Comp
L power:GND #PWR?
U 1 1 60188BC8
P 21100 2050
AR Path="/60056272/60188BC8" Ref="#PWR?"  Part="1" 
AR Path="/60188BC8" Ref="#PWR0120"  Part="1" 
F 0 "#PWR0120" H 21100 1800 50  0001 C CNN
F 1 "GND" H 21105 1877 50  0000 C CNN
F 2 "" H 21100 2050 50  0001 C CNN
F 3 "" H 21100 2050 50  0001 C CNN
	1    21100 2050
	1    0    0    -1  
$EndComp
Wire Wire Line
	21100 2050 21100 1950
Connection ~ 21100 1950
Wire Wire Line
	21100 1950 20700 1950
Wire Wire Line
	18200 7950 18300 7950
Wire Wire Line
	18200 8050 18200 7950
Wire Wire Line
	16250 4450 16250 4400
Wire Wire Line
	16250 4400 16700 4400
Wire Wire Line
	16700 4400 16700 4550
Wire Wire Line
	17600 4550 17100 4550
Wire Wire Line
	17100 4550 17100 4400
Wire Wire Line
	17100 4400 16700 4400
Connection ~ 16700 4400
Wire Wire Line
	16250 4850 16250 4900
Wire Wire Line
	16250 4900 16700 4900
Wire Wire Line
	16700 4900 16700 4750
Wire Wire Line
	16250 4350 16250 4400
Connection ~ 16250 4400
Wire Wire Line
	16250 4150 16250 4100
$Comp
L power:+3.3V #PWR?
U 1 1 60188BE0
P 16250 4100
AR Path="/60056272/60188BE0" Ref="#PWR?"  Part="1" 
AR Path="/60188BE0" Ref="#PWR087"  Part="1" 
F 0 "#PWR087" H 16250 3950 50  0001 C CNN
F 1 "+3.3V" H 16265 4273 50  0000 C CNN
F 2 "" H 16250 4100 50  0001 C CNN
F 3 "" H 16250 4100 50  0001 C CNN
	1    16250 4100
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR?
U 1 1 60188BE6
P 16250 4900
AR Path="/60056272/60188BE6" Ref="#PWR?"  Part="1" 
AR Path="/60188BE6" Ref="#PWR088"  Part="1" 
F 0 "#PWR088" H 16250 4650 50  0001 C CNN
F 1 "GND" H 16255 4727 50  0000 C CNN
F 2 "" H 16250 4900 50  0001 C CNN
F 3 "" H 16250 4900 50  0001 C CNN
	1    16250 4900
	1    0    0    -1  
$EndComp
Connection ~ 16250 4900
$Comp
L PUTM_EV_BMS_library:USB_+5V #PWR?
U 1 1 601A9E78
P 1225 14675
AR Path="/601B5445/601A9E78" Ref="#PWR?"  Part="1" 
AR Path="/601A9E78" Ref="#PWR01"  Part="1" 
F 0 "#PWR01" H 1225 14525 50  0001 C CNN
F 1 "USB_+5V" H 1240 14848 50  0000 C CNN
F 2 "" H 1225 14675 50  0001 C CNN
F 3 "" H 1225 14675 50  0001 C CNN
	1    1225 14675
	1    0    0    -1  
$EndComp
$Comp
L PUTM_EV_BMS_library:USB_GND #PWR?
U 1 1 601A9E7E
P 1225 15275
AR Path="/601B5445/601A9E7E" Ref="#PWR?"  Part="1" 
AR Path="/601A9E7E" Ref="#PWR02"  Part="1" 
F 0 "#PWR02" H 1225 15025 50  0001 C CNN
F 1 "USB_GND" H 1230 15102 50  0000 C CNN
F 2 "" H 1225 15275 50  0001 C CNN
F 3 "" H 1225 15275 50  0001 C CNN
	1    1225 15275
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR?
U 1 1 601A9E84
P 2550 12800
AR Path="/601B5445/601A9E84" Ref="#PWR?"  Part="1" 
AR Path="/601A9E84" Ref="#PWR09"  Part="1" 
F 0 "#PWR09" H 2550 12550 50  0001 C CNN
F 1 "GND" H 2555 12627 50  0000 C CNN
F 2 "" H 2550 12800 50  0001 C CNN
F 3 "" H 2550 12800 50  0001 C CNN
	1    2550 12800
	1    0    0    -1  
$EndComp
$Comp
L power:+24V #PWR?
U 1 1 601A9E8A
P 2550 11950
AR Path="/601B5445/601A9E8A" Ref="#PWR?"  Part="1" 
AR Path="/601A9E8A" Ref="#PWR08"  Part="1" 
F 0 "#PWR08" H 2550 11800 50  0001 C CNN
F 1 "+24V" H 2565 12123 50  0000 C CNN
F 2 "" H 2550 11950 50  0001 C CNN
F 3 "" H 2550 11950 50  0001 C CNN
	1    2550 11950
	1    0    0    -1  
$EndComp
$Comp
L power:+5V #PWR?
U 1 1 601A9E90
P 4850 12050
AR Path="/601B5445/601A9E90" Ref="#PWR?"  Part="1" 
AR Path="/601A9E90" Ref="#PWR025"  Part="1" 
F 0 "#PWR025" H 4850 11900 50  0001 C CNN
F 1 "+5V" H 4865 12223 50  0000 C CNN
F 2 "" H 4850 12050 50  0001 C CNN
F 3 "" H 4850 12050 50  0001 C CNN
	1    4850 12050
	1    0    0    -1  
$EndComp
$Comp
L power:+3.3V #PWR?
U 1 1 601A9E96
P 6275 14325
AR Path="/601B5445/601A9E96" Ref="#PWR?"  Part="1" 
AR Path="/601A9E96" Ref="#PWR036"  Part="1" 
F 0 "#PWR036" H 6275 14175 50  0001 C CNN
F 1 "+3.3V" H 6290 14498 50  0000 C CNN
F 2 "" H 6275 14325 50  0001 C CNN
F 3 "" H 6275 14325 50  0001 C CNN
	1    6275 14325
	1    0    0    -1  
$EndComp
$Comp
L Device:R_Small R73
U 1 1 601BA694
P 16100 12850
F 0 "R73" H 16159 12896 50  0000 L CNN
F 1 "20k" H 16159 12805 50  0000 L CNN
F 2 "Resistor_SMD:R_0805_2012Metric" H 16100 12850 50  0001 C CNN
F 3 "~" H 16100 12850 50  0001 C CNN
	1    16100 12850
	1    0    0    -1  
$EndComp
$Comp
L Device:R_Small R74
U 1 1 601BA69A
P 16100 13300
F 0 "R74" H 16159 13346 50  0000 L CNN
F 1 "10k" H 16159 13255 50  0000 L CNN
F 2 "Resistor_SMD:R_0603_1608Metric" H 16100 13300 50  0001 C CNN
F 3 "~" H 16100 13300 50  0001 C CNN
	1    16100 13300
	1    0    0    -1  
$EndComp
$Comp
L Device:R_Small R77
U 1 1 601BA6A0
P 17050 13600
F 0 "R77" V 16854 13600 50  0000 C CNN
F 1 "10k" V 16945 13600 50  0000 C CNN
F 2 "Resistor_SMD:R_0603_1608Metric" H 17050 13600 50  0001 C CNN
F 3 "~" H 17050 13600 50  0001 C CNN
	1    17050 13600
	0    1    1    0   
$EndComp
$Comp
L Device:R_Small R79
U 1 1 601BA6A6
P 17400 13200
F 0 "R79" V 17204 13200 50  0000 C CNN
F 1 "100" V 17295 13200 50  0000 C CNN
F 2 "Resistor_SMD:R_0603_1608Metric" H 17400 13200 50  0001 C CNN
F 3 "~" H 17400 13200 50  0001 C CNN
	1    17400 13200
	0    1    1    0   
$EndComp
$Comp
L Device:C_Small C47
U 1 1 601BA6AC
P 17600 13400
F 0 "C47" H 17692 13446 50  0000 L CNN
F 1 "10uF" H 17692 13355 50  0000 L CNN
F 2 "Capacitor_SMD:C_0805_2012Metric" H 17600 13400 50  0001 C CNN
F 3 "~" H 17600 13400 50  0001 C CNN
	1    17600 13400
	1    0    0    -1  
$EndComp
$Comp
L Device:C_Small C39
U 1 1 601BA6B2
P 15825 13300
F 0 "C39" H 15917 13346 50  0000 L CNN
F 1 "1uF" H 15917 13255 50  0000 L CNN
F 2 "Capacitor_SMD:C_0603_1608Metric" H 15825 13300 50  0001 C CNN
F 3 "~" H 15825 13300 50  0001 C CNN
	1    15825 13300
	1    0    0    -1  
$EndComp
$Comp
L Device:C_Small C37
U 1 1 601BA6B8
P 15100 13050
F 0 "C37" H 15192 13096 50  0000 L CNN
F 1 "100nF" H 15192 13005 50  0000 L CNN
F 2 "Capacitor_SMD:C_0603_1608Metric" H 15100 13050 50  0001 C CNN
F 3 "~" H 15100 13050 50  0001 C CNN
	1    15100 13050
	1    0    0    -1  
$EndComp
$Comp
L Device:C_Small C46
U 1 1 601BA6DC
P 17400 15200
F 0 "C46" H 17492 15246 50  0000 L CNN
F 1 "10uF" H 17492 15155 50  0000 L CNN
F 2 "Capacitor_SMD:C_0805_2012Metric" H 17400 15200 50  0001 C CNN
F 3 "~" H 17400 15200 50  0001 C CNN
	1    17400 15200
	1    0    0    -1  
$EndComp
Text Notes 17725 12975 0    50   ~ 0
LEM reference voltage 1V
Text Notes 15525 14125 0    50   ~ 0
LEM signal = V_REF + 1.25 * CURRENT / 200A
Text Notes 15175 14350 0    50   ~ 0
first stage lowpass filter
Text Notes 16925 14350 0    50   ~ 0
second stage lowpass filter
$Comp
L Regulator_Switching:LM2596S-5 U1
U 1 1 6014F405
P 3750 12200
F 0 "U1" H 3750 12567 50  0000 C CNN
F 1 "LM2596S-5" H 3750 12476 50  0000 C CNN
F 2 "Package_TO_SOT_SMD:TO-263-5_TabPin3" H 3800 11950 50  0001 L CIN
F 3 "http://www.ti.com/lit/ds/symlink/lm2596.pdf" H 3750 12200 50  0001 C CNN
	1    3750 12200
	1    0    0    -1  
$EndComp
$Comp
L Device:CP_Small C3
U 1 1 6017F1DB
P 2550 12350
F 0 "C3" H 2638 12396 50  0000 L CNN
F 1 "680uF/35V" H 2638 12305 50  0000 L CNN
F 2 "Capacitor_THT:CP_Radial_D10.0mm_P5.00mm" H 2550 12350 50  0001 C CNN
F 3 "~" H 2550 12350 50  0001 C CNN
	1    2550 12350
	1    0    0    -1  
$EndComp
$Comp
L Device:CP_Small C11
U 1 1 60181301
P 4850 12500
F 0 "C11" H 4938 12546 50  0000 L CNN
F 1 "220uF/10V" H 4938 12455 50  0000 L CNN
F 2 "Capacitor_SMD:CP_Elec_6.3x7.7" H 4850 12500 50  0001 C CNN
F 3 "~" H 4850 12500 50  0001 C CNN
	1    4850 12500
	1    0    0    -1  
$EndComp
$Comp
L Device:D_Schottky_Small_ALT D2
U 1 1 60183145
P 4350 12500
F 0 "D2" V 4350 12600 50  0000 C CNN
F 1 "SS24T3G" V 4350 12386 50  0000 C CNN
F 2 "Diode_SMD:D_SMB" V 4350 12500 50  0001 C CNN
F 3 "~" V 4350 12500 50  0001 C CNN
	1    4350 12500
	0    1    1    0   
$EndComp
$Comp
L Device:L_Small L3
U 1 1 60197E13
P 4550 12300
F 0 "L3" V 4500 12250 50  0000 C CNN
F 1 "33uH" V 4644 12300 50  0000 C CNN
F 2 "Inductor_SMD:L_12x12mm_H8mm" H 4550 12300 50  0001 C CNN
F 3 "~" H 4550 12300 50  0001 C CNN
	1    4550 12300
	0    -1   -1   0   
$EndComp
Wire Wire Line
	4250 12300 4350 12300
Wire Wire Line
	4350 12400 4350 12300
Connection ~ 4350 12300
Wire Wire Line
	4350 12300 4450 12300
Wire Wire Line
	4650 12300 4850 12300
Wire Wire Line
	4850 12300 4850 12400
Wire Wire Line
	4250 12100 4850 12100
Wire Wire Line
	4850 12100 4850 12300
Connection ~ 4850 12300
Wire Wire Line
	4850 12050 4850 12100
Connection ~ 4850 12100
Wire Wire Line
	3250 12300 3200 12300
Wire Wire Line
	3200 12300 3200 12700
Wire Wire Line
	3200 12700 3750 12700
Wire Wire Line
	3750 12700 3750 12500
Wire Wire Line
	3750 12700 4350 12700
Wire Wire Line
	4350 12700 4350 12600
Connection ~ 3750 12700
Wire Wire Line
	4350 12700 4850 12700
Wire Wire Line
	4850 12700 4850 12600
Connection ~ 4350 12700
Wire Wire Line
	3250 12100 2550 12100
Wire Wire Line
	2550 12100 2550 12250
Wire Wire Line
	2550 12450 2550 12700
Wire Wire Line
	2550 12700 3200 12700
Connection ~ 3200 12700
Wire Wire Line
	2550 12800 2550 12700
Connection ~ 2550 12700
Wire Wire Line
	2550 11950 2550 12100
Connection ~ 2550 12100
$Comp
L Regulator_Linear:LM1117-3.3 U5
U 1 1 6020FC52
P 5475 14425
F 0 "U5" H 5475 14667 50  0000 C CNN
F 1 "LM1117-3.3" H 5475 14576 50  0000 C CNN
F 2 "Package_TO_SOT_SMD:SOT-223-3_TabPin2" H 5475 14425 50  0001 C CNN
F 3 "http://www.ti.com/lit/ds/symlink/lm1117.pdf" H 5475 14425 50  0001 C CNN
	1    5475 14425
	1    0    0    -1  
$EndComp
$Comp
L Device:C_Small C12
U 1 1 602103E7
P 4875 14625
F 0 "C12" H 4967 14671 50  0000 L CNN
F 1 "1uF" H 4967 14580 50  0000 L CNN
F 2 "Capacitor_SMD:C_0603_1608Metric" H 4875 14625 50  0001 C CNN
F 3 "~" H 4875 14625 50  0001 C CNN
	1    4875 14625
	1    0    0    -1  
$EndComp
$Comp
L Device:C_Small C15
U 1 1 60211C86
P 5875 14625
F 0 "C15" H 5967 14671 50  0000 L CNN
F 1 "1uF" H 5967 14580 50  0000 L CNN
F 2 "Capacitor_SMD:C_0603_1608Metric" H 5875 14625 50  0001 C CNN
F 3 "~" H 5875 14625 50  0001 C CNN
	1    5875 14625
	1    0    0    -1  
$EndComp
$Comp
L Device:C_Small C16
U 1 1 60212208
P 6275 14625
F 0 "C16" H 6367 14671 50  0000 L CNN
F 1 "100nF" H 6367 14580 50  0000 L CNN
F 2 "Capacitor_SMD:C_0603_1608Metric" H 6275 14625 50  0001 C CNN
F 3 "~" H 6275 14625 50  0001 C CNN
	1    6275 14625
	1    0    0    -1  
$EndComp
$Comp
L PUTM_EV_BMS_library:AM1LS-0505S-NZ P?
U 1 1 6021BEC9
P 2775 14975
AR Path="/600380E4/6021BEC9" Ref="P?"  Part="1" 
AR Path="/6021BEC9" Ref="P1"  Part="1" 
F 0 "P1" H 2775 15440 50  0000 C CNN
F 1 "AM1LS-0505S-NZ" H 2775 15349 50  0000 C CNN
F 2 "PUTM_EV_BMS_footprint:AM1LS" H 2775 14975 50  0001 C CNN
F 3 "https://www.tme.eu/Document/eb524b8882472c891796e11a1a1007e6/am1ls-%28j%29nz.pdf" H 2775 14975 50  0001 C CNN
	1    2775 14975
	1    0    0    -1  
$EndComp
$Comp
L Device:C_Small C1
U 1 1 6021DBE5
P 1975 14975
F 0 "C1" H 2067 15021 50  0000 L CNN
F 1 "4.7uF" H 2067 14930 50  0000 L CNN
F 2 "Capacitor_SMD:C_0603_1608Metric" H 1975 14975 50  0001 C CNN
F 3 "~" H 1975 14975 50  0001 C CNN
	1    1975 14975
	1    0    0    -1  
$EndComp
$Comp
L Device:C_Small C8
U 1 1 6021E5CB
P 3725 14975
F 0 "C8" H 3817 15021 50  0000 L CNN
F 1 "10uF" H 3817 14930 50  0000 L CNN
F 2 "Capacitor_SMD:C_0805_2012Metric" H 3725 14975 50  0001 C CNN
F 3 "~" H 3725 14975 50  0001 C CNN
	1    3725 14975
	1    0    0    -1  
$EndComp
Wire Wire Line
	1225 14675 1225 14775
Wire Wire Line
	1975 14775 1975 14875
Wire Wire Line
	1975 14775 2275 14775
Wire Wire Line
	2275 15175 1975 15175
Wire Wire Line
	1225 15175 1225 15275
Wire Wire Line
	1975 15175 1975 15075
Connection ~ 1975 15175
Wire Wire Line
	1975 15175 1225 15175
Wire Wire Line
	3725 14775 3725 14875
Wire Wire Line
	3725 15075 3725 15175
Wire Wire Line
	3725 15175 3275 15175
Text Notes 2425 14425 0    50   ~ 0
minimal current 20mA
$Comp
L Device:R R?
U 1 1 603038D3
P 4075 14975
AR Path="/600380E4/603038D3" Ref="R?"  Part="1" 
AR Path="/603038D3" Ref="R13"  Part="1" 
F 0 "R13" H 4005 14929 50  0000 R CNN
F 1 "220" H 4005 15020 50  0000 R CNN
F 2 "Resistor_SMD:R_1206_3216Metric" V 4005 14975 50  0001 C CNN
F 3 "~" H 4075 14975 50  0001 C CNN
	1    4075 14975
	-1   0    0    1   
$EndComp
Wire Wire Line
	3725 14775 4075 14775
Wire Wire Line
	4075 14775 4075 14825
Wire Wire Line
	3725 15175 4075 15175
Wire Wire Line
	4075 15175 4075 15125
Connection ~ 3725 15175
$Comp
L Device:L L?
U 1 1 6031D288
P 1675 14775
AR Path="/600380E4/6031D288" Ref="L?"  Part="1" 
AR Path="/6031D288" Ref="L1"  Part="1" 
F 0 "L1" V 1865 14775 50  0000 C CNN
F 1 "6.8uH" V 1774 14775 50  0000 C CNN
F 2 "Inductor_SMD:L_1206_3216Metric" H 1675 14775 50  0001 C CNN
F 3 "~" H 1675 14775 50  0001 C CNN
	1    1675 14775
	0    -1   -1   0   
$EndComp
Wire Wire Line
	3325 14775 3275 14775
Wire Wire Line
	3625 14775 3725 14775
Connection ~ 3725 14775
Connection ~ 4075 15175
Wire Wire Line
	4075 15175 4075 15275
$Comp
L power:GND #PWR?
U 1 1 6039877A
P 4075 15275
AR Path="/601B5445/6039877A" Ref="#PWR?"  Part="1" 
AR Path="/6039877A" Ref="#PWR017"  Part="1" 
F 0 "#PWR017" H 4075 15025 50  0001 C CNN
F 1 "GND" H 4080 15102 50  0000 C CNN
F 2 "" H 4075 15275 50  0001 C CNN
F 3 "" H 4075 15275 50  0001 C CNN
	1    4075 15275
	1    0    0    -1  
$EndComp
Text Notes 3375 15875 0    50   ~ 0
5V from computer USB, \nonly for MCU and \nneccesary periferal
$Comp
L power:GND #PWR?
U 1 1 603A8D9C
P 5475 14875
AR Path="/601B5445/603A8D9C" Ref="#PWR?"  Part="1" 
AR Path="/603A8D9C" Ref="#PWR028"  Part="1" 
F 0 "#PWR028" H 5475 14625 50  0001 C CNN
F 1 "GND" H 5480 14702 50  0000 C CNN
F 2 "" H 5475 14875 50  0001 C CNN
F 3 "" H 5475 14875 50  0001 C CNN
	1    5475 14875
	1    0    0    -1  
$EndComp
Wire Wire Line
	6275 14725 6275 14825
Wire Wire Line
	6275 14825 5875 14825
Wire Wire Line
	4875 14825 4875 14725
Wire Wire Line
	5475 14875 5475 14825
Connection ~ 5475 14825
Wire Wire Line
	5475 14825 4875 14825
Wire Wire Line
	5475 14725 5475 14825
Wire Wire Line
	5875 14725 5875 14825
Connection ~ 5875 14825
Wire Wire Line
	5875 14825 5475 14825
Wire Wire Line
	5775 14425 5875 14425
Wire Wire Line
	6275 14425 6275 14525
Wire Wire Line
	5875 14525 5875 14425
Connection ~ 5875 14425
Wire Wire Line
	5875 14425 6275 14425
Wire Wire Line
	5175 14425 4875 14425
Wire Wire Line
	4875 14425 4875 14525
$Comp
L power:+5V #PWR?
U 1 1 60416F96
P 4475 14075
AR Path="/601B5445/60416F96" Ref="#PWR?"  Part="1" 
AR Path="/60416F96" Ref="#PWR020"  Part="1" 
F 0 "#PWR020" H 4475 13925 50  0001 C CNN
F 1 "+5V" H 4490 14248 50  0000 C CNN
F 2 "" H 4475 14075 50  0001 C CNN
F 3 "" H 4475 14075 50  0001 C CNN
	1    4475 14075
	1    0    0    -1  
$EndComp
$Comp
L Diode:BAT54C D3
U 1 1 60425188
P 4475 14425
F 0 "D3" V 4429 14513 50  0000 L CNN
F 1 "BAT54C" V 4520 14513 50  0000 L CNN
F 2 "Package_TO_SOT_SMD:SOT-23" H 4550 14550 50  0001 L CNN
F 3 "http://www.diodes.com/_files/datasheets/ds11005.pdf" H 4395 14425 50  0001 C CNN
	1    4475 14425
	0    -1   -1   0   
$EndComp
Wire Wire Line
	4475 14125 4475 14075
Wire Wire Line
	4075 14775 4475 14775
Wire Wire Line
	4475 14775 4475 14725
Connection ~ 4075 14775
Wire Wire Line
	4675 14425 4875 14425
Connection ~ 4875 14425
Wire Wire Line
	6275 14325 6275 14425
Connection ~ 6275 14425
Text Notes 3450 11700 0    50   ~ 0
24V car LV to 5V
Wire Wire Line
	1975 14775 1825 14775
Connection ~ 1975 14775
Wire Wire Line
	1525 14775 1225 14775
$Comp
L Device:R R?
U 1 1 60517817
P 3900 10250
AR Path="/600380E4/60517817" Ref="R?"  Part="1" 
AR Path="/60517817" Ref="R12"  Part="1" 
F 0 "R12" V 4000 10300 50  0000 R CNN
F 1 "0" V 3800 10275 50  0000 R CNN
F 2 "Resistor_SMD:R_0603_1608Metric" V 3830 10250 50  0001 C CNN
F 3 "~" H 3900 10250 50  0001 C CNN
	1    3900 10250
	0    -1   -1   0   
$EndComp
Connection ~ 2300 10250
Wire Wire Line
	2150 10250 2300 10250
Wire Wire Line
	1850 10250 1700 10250
Connection ~ 4600 10250
Wire Wire Line
	4600 10300 4600 10250
Connection ~ 4250 10250
Wire Wire Line
	4250 10250 4600 10250
Connection ~ 4250 10650
Wire Wire Line
	4600 10650 4600 10750
Connection ~ 4600 10650
Wire Wire Line
	4600 10650 4250 10650
Wire Wire Line
	4600 10600 4600 10650
Text Notes 2400 9700 0    50   ~ 0
power supply for hv voltage measurement section
Wire Wire Line
	4250 10250 4250 10350
Wire Wire Line
	4050 10250 4250 10250
Wire Wire Line
	3600 10250 3750 10250
$Comp
L Device:L L?
U 1 1 603408C5
P 2000 10250
AR Path="/600380E4/603408C5" Ref="L?"  Part="1" 
AR Path="/603408C5" Ref="L2"  Part="1" 
F 0 "L2" V 2190 10250 50  0000 C CNN
F 1 "6.8uH" V 2099 10250 50  0000 C CNN
F 2 "Inductor_SMD:L_1206_3216Metric" H 2000 10250 50  0001 C CNN
F 3 "~" H 2000 10250 50  0001 C CNN
	1    2000 10250
	0    -1   -1   0   
$EndComp
Wire Wire Line
	4600 10050 4600 10250
$Comp
L Device:R R?
U 1 1 60302876
P 4600 10450
AR Path="/600380E4/60302876" Ref="R?"  Part="1" 
AR Path="/60302876" Ref="R15"  Part="1" 
F 0 "R15" H 4530 10404 50  0000 R CNN
F 1 "220" H 4530 10495 50  0000 R CNN
F 2 "Resistor_SMD:R_1206_3216Metric" V 4530 10450 50  0001 C CNN
F 3 "~" H 4600 10450 50  0001 C CNN
	1    4600 10450
	-1   0    0    1   
$EndComp
Text Notes 2750 9850 0    50   ~ 0
minimal current 20mA
$Comp
L power:+5V #PWR?
U 1 1 602B1507
P 1700 10150
AR Path="/601B5445/602B1507" Ref="#PWR?"  Part="1" 
AR Path="/602B1507" Ref="#PWR06"  Part="1" 
F 0 "#PWR06" H 1700 10000 50  0001 C CNN
F 1 "+5V" H 1715 10323 50  0000 C CNN
F 2 "" H 1700 10150 50  0001 C CNN
F 3 "" H 1700 10150 50  0001 C CNN
	1    1700 10150
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR?
U 1 1 602B0B1E
P 1700 10750
AR Path="/601B5445/602B0B1E" Ref="#PWR?"  Part="1" 
AR Path="/602B0B1E" Ref="#PWR07"  Part="1" 
F 0 "#PWR07" H 1700 10500 50  0001 C CNN
F 1 "GND" H 1705 10577 50  0000 C CNN
F 2 "" H 1700 10750 50  0001 C CNN
F 3 "" H 1700 10750 50  0001 C CNN
	1    1700 10750
	1    0    0    -1  
$EndComp
Wire Wire Line
	4250 10650 3600 10650
Wire Wire Line
	4250 10550 4250 10650
Wire Wire Line
	2300 10650 1700 10650
Connection ~ 2300 10650
Wire Wire Line
	2300 10650 2300 10550
Wire Wire Line
	1700 10650 1700 10750
Wire Wire Line
	2600 10650 2300 10650
Wire Wire Line
	2300 10250 2600 10250
Wire Wire Line
	2300 10250 2300 10350
Wire Wire Line
	1700 10150 1700 10250
$Comp
L Device:C_Small C9
U 1 1 602A63B7
P 4250 10450
F 0 "C9" H 4342 10496 50  0000 L CNN
F 1 "10uF" H 4342 10405 50  0000 L CNN
F 2 "Capacitor_SMD:C_0805_2012Metric" H 4250 10450 50  0001 C CNN
F 3 "~" H 4250 10450 50  0001 C CNN
	1    4250 10450
	1    0    0    -1  
$EndComp
$Comp
L Device:C_Small C2
U 1 1 602A63B1
P 2300 10450
F 0 "C2" H 2392 10496 50  0000 L CNN
F 1 "4.7uF" H 2392 10405 50  0000 L CNN
F 2 "Capacitor_SMD:C_0603_1608Metric" H 2300 10450 50  0001 C CNN
F 3 "~" H 2300 10450 50  0001 C CNN
	1    2300 10450
	1    0    0    -1  
$EndComp
$Comp
L PUTM_EV_BMS_library:AM1LS-0505S-NZ P?
U 1 1 602A63AB
P 3100 10450
AR Path="/600380E4/602A63AB" Ref="P?"  Part="1" 
AR Path="/602A63AB" Ref="P2"  Part="1" 
F 0 "P2" H 3100 10915 50  0000 C CNN
F 1 "AM1LS-0505S-NZ" H 3100 10824 50  0000 C CNN
F 2 "PUTM_EV_BMS_footprint:AM1LS" H 3100 10450 50  0001 C CNN
F 3 "https://www.tme.eu/Document/eb524b8882472c891796e11a1a1007e6/am1ls-%28j%29nz.pdf" H 3100 10450 50  0001 C CNN
	1    3100 10450
	1    0    0    -1  
$EndComp
$Comp
L PUTM_EV_BMS_library:ISO_GND #PWR?
U 1 1 601A9E72
P 4600 10750
AR Path="/601B5445/601A9E72" Ref="#PWR?"  Part="1" 
AR Path="/601A9E72" Ref="#PWR023"  Part="1" 
F 0 "#PWR023" H 4600 10500 50  0001 C CNN
F 1 "ISO_GND" H 4605 10577 50  0000 C CNN
F 2 "" H 4600 10750 50  0001 C CNN
F 3 "" H 4600 10750 50  0001 C CNN
	1    4600 10750
	1    0    0    -1  
$EndComp
$Comp
L PUTM_EV_BMS_library:ISO_+5V #PWR?
U 1 1 601A9E6C
P 4600 10050
AR Path="/601B5445/601A9E6C" Ref="#PWR?"  Part="1" 
AR Path="/601A9E6C" Ref="#PWR022"  Part="1" 
F 0 "#PWR022" H 4600 9900 50  0001 C CNN
F 1 "ISO_+5V" H 4615 10223 50  0000 C CNN
F 2 "" H 4600 10050 50  0001 C CNN
F 3 "" H 4600 10050 50  0001 C CNN
	1    4600 10050
	1    0    0    -1  
$EndComp
$Comp
L Device:R R?
U 1 1 60554788
P 3475 14775
AR Path="/600380E4/60554788" Ref="R?"  Part="1" 
AR Path="/60554788" Ref="R11"  Part="1" 
F 0 "R11" V 3575 14825 50  0000 R CNN
F 1 "0" V 3375 14850 50  0000 R CNN
F 2 "Resistor_SMD:R_0603_1608Metric" V 3405 14775 50  0001 C CNN
F 3 "~" H 3475 14775 50  0001 C CNN
	1    3475 14775
	0    -1   -1   0   
$EndComp
$Comp
L power:+3.3V #PWR?
U 1 1 6058040B
P 15100 12950
AR Path="/60056272/6058040B" Ref="#PWR?"  Part="1" 
AR Path="/6058040B" Ref="#PWR080"  Part="1" 
F 0 "#PWR080" H 15100 12800 50  0001 C CNN
F 1 "+3.3V" H 15115 13123 50  0000 C CNN
F 2 "" H 15100 12950 50  0001 C CNN
F 3 "" H 15100 12950 50  0001 C CNN
	1    15100 12950
	1    0    0    -1  
$EndComp
Wire Wire Line
	16100 12950 16100 13100
Connection ~ 16100 13100
Wire Wire Line
	16100 13100 16100 13200
Wire Wire Line
	16550 13100 16100 13100
Wire Wire Line
	16100 13100 15825 13100
Wire Wire Line
	15825 13100 15825 13200
Wire Wire Line
	15825 13475 16100 13475
Wire Wire Line
	16100 13475 16100 13400
Wire Wire Line
	15825 13400 15825 13475
Wire Wire Line
	16100 13475 16100 13575
Connection ~ 16100 13475
$Comp
L power:+3.3V #PWR?
U 1 1 60630F4F
P 16100 12675
AR Path="/60056272/60630F4F" Ref="#PWR?"  Part="1" 
AR Path="/60630F4F" Ref="#PWR084"  Part="1" 
F 0 "#PWR084" H 16100 12525 50  0001 C CNN
F 1 "+3.3V" H 16115 12848 50  0000 C CNN
F 2 "" H 16100 12675 50  0001 C CNN
F 3 "" H 16100 12675 50  0001 C CNN
	1    16100 12675
	1    0    0    -1  
$EndComp
Wire Wire Line
	16100 12750 16100 12675
Wire Wire Line
	16950 13600 16500 13600
Wire Wire Line
	16500 13600 16500 13300
Wire Wire Line
	16500 13300 16550 13300
Wire Wire Line
	17150 13600 17200 13600
Wire Wire Line
	17200 13600 17200 13200
Wire Wire Line
	17200 13200 17150 13200
Wire Wire Line
	17200 13200 17300 13200
Connection ~ 17200 13200
Wire Wire Line
	17500 13200 17600 13200
Wire Wire Line
	17600 13200 17600 13300
$Comp
L power:GND #PWR?
U 1 1 6069FFC5
P 15100 13150
AR Path="/60056272/6069FFC5" Ref="#PWR?"  Part="1" 
AR Path="/6069FFC5" Ref="#PWR081"  Part="1" 
F 0 "#PWR081" H 15100 12900 50  0001 C CNN
F 1 "GND" H 15105 12977 50  0000 C CNN
F 2 "" H 15100 13150 50  0001 C CNN
F 3 "" H 15100 13150 50  0001 C CNN
	1    15100 13150
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR?
U 1 1 606A0D2B
P 16100 13575
AR Path="/60056272/606A0D2B" Ref="#PWR?"  Part="1" 
AR Path="/606A0D2B" Ref="#PWR085"  Part="1" 
F 0 "#PWR085" H 16100 13325 50  0001 C CNN
F 1 "GND" H 16105 13402 50  0000 C CNN
F 2 "" H 16100 13575 50  0001 C CNN
F 3 "" H 16100 13575 50  0001 C CNN
	1    16100 13575
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR?
U 1 1 606A14BC
P 17600 13700
AR Path="/60056272/606A14BC" Ref="#PWR?"  Part="1" 
AR Path="/606A14BC" Ref="#PWR098"  Part="1" 
F 0 "#PWR098" H 17600 13450 50  0001 C CNN
F 1 "GND" H 17605 13527 50  0000 C CNN
F 2 "" H 17600 13700 50  0001 C CNN
F 3 "" H 17600 13700 50  0001 C CNN
	1    17600 13700
	1    0    0    -1  
$EndComp
$Comp
L Device:R_Small R76
U 1 1 607AE7E6
P 16650 15300
F 0 "R76" V 16846 15300 50  0000 C CNN
F 1 "10k" V 16755 15300 50  0000 C CNN
F 2 "Resistor_SMD:R_0603_1608Metric" H 16650 15300 50  0001 C CNN
F 3 "~" H 16650 15300 50  0001 C CNN
	1    16650 15300
	0    -1   -1   0   
$EndComp
$Comp
L power:GND #PWR?
U 1 1 6085722B
P 17400 15400
AR Path="/60056272/6085722B" Ref="#PWR?"  Part="1" 
AR Path="/6085722B" Ref="#PWR097"  Part="1" 
F 0 "#PWR097" H 17400 15150 50  0001 C CNN
F 1 "GND" H 17405 15227 50  0000 C CNN
F 2 "" H 17400 15400 50  0001 C CNN
F 3 "" H 17400 15400 50  0001 C CNN
	1    17400 15400
	1    0    0    -1  
$EndComp
Text Notes 19850 1075 0    50   ~ 0
64Mbit SPI flash memory
$Comp
L Device:R R?
U 1 1 6098589A
P 2650 6750
AR Path="/600380E4/6098589A" Ref="R?"  Part="1" 
AR Path="/6098589A" Ref="R6"  Part="1" 
F 0 "R6" V 2443 6750 50  0000 C CNN
F 1 "200k" V 2534 6750 50  0000 C CNN
F 2 "Resistor_SMD:R_1206_3216Metric" V 2580 6750 50  0001 C CNN
F 3 "~" H 2650 6750 50  0001 C CNN
	1    2650 6750
	0    1    1    0   
$EndComp
$Comp
L Device:R R?
U 1 1 609858A0
P 3000 6750
AR Path="/600380E4/609858A0" Ref="R?"  Part="1" 
AR Path="/609858A0" Ref="R8"  Part="1" 
F 0 "R8" V 2793 6750 50  0000 C CNN
F 1 "200k" V 2884 6750 50  0000 C CNN
F 2 "Resistor_SMD:R_1206_3216Metric" V 2930 6750 50  0001 C CNN
F 3 "~" H 3000 6750 50  0001 C CNN
	1    3000 6750
	0    1    1    0   
$EndComp
Wire Wire Line
	3500 4750 3500 4800
Wire Wire Line
	3500 4400 3500 4450
$Comp
L Device:C C?
U 1 1 60156ECB
P 3500 4600
AR Path="/600380E4/60156ECB" Ref="C?"  Part="1" 
AR Path="/60156ECB" Ref="C6"  Part="1" 
F 0 "C6" H 3615 4646 50  0000 L CNN
F 1 "1nF/1kV" H 3615 4555 50  0000 L CNN
F 2 "Capacitor_SMD:C_1206_3216Metric" H 3538 4450 50  0001 C CNN
F 3 "~" H 3500 4600 50  0001 C CNN
	1    3500 4600
	1    0    0    -1  
$EndComp
Wire Wire Line
	3550 7150 3550 7100
Wire Wire Line
	3550 6750 3550 6800
$Comp
L Device:C C?
U 1 1 60156EC5
P 3550 6950
AR Path="/600380E4/60156EC5" Ref="C?"  Part="1" 
AR Path="/60156EC5" Ref="C7"  Part="1" 
F 0 "C7" H 3665 6996 50  0000 L CNN
F 1 "1nF/1kV" H 3665 6905 50  0000 L CNN
F 2 "Capacitor_SMD:C_1206_3216Metric" H 3588 6800 50  0001 C CNN
F 3 "~" H 3550 6950 50  0001 C CNN
	1    3550 6950
	1    0    0    -1  
$EndComp
$Comp
L Device:C C?
U 1 1 60156EBF
P 3250 7950
AR Path="/600380E4/60156EBF" Ref="C?"  Part="1" 
AR Path="/60156EBF" Ref="C5"  Part="1" 
F 0 "C5" H 3365 7996 50  0000 L CNN
F 1 "100nF" H 3365 7905 50  0000 L CNN
F 2 "Capacitor_SMD:C_0603_1608Metric" H 3288 7800 50  0001 C CNN
F 3 "~" H 3250 7950 50  0001 C CNN
	1    3250 7950
	1    0    0    -1  
$EndComp
$Comp
L PUTM_EV_BMS_library:ISO_+5V #PWR?
U 1 1 60A84A58
P 3250 7800
AR Path="/601B5445/60A84A58" Ref="#PWR?"  Part="1" 
AR Path="/60A84A58" Ref="#PWR013"  Part="1" 
F 0 "#PWR013" H 3250 7650 50  0001 C CNN
F 1 "ISO_+5V" H 3265 7973 50  0000 C CNN
F 2 "" H 3250 7800 50  0001 C CNN
F 3 "" H 3250 7800 50  0001 C CNN
	1    3250 7800
	1    0    0    -1  
$EndComp
$Comp
L PUTM_EV_BMS_library:ISO_GND #PWR?
U 1 1 60A8583D
P 3250 8100
AR Path="/601B5445/60A8583D" Ref="#PWR?"  Part="1" 
AR Path="/60A8583D" Ref="#PWR014"  Part="1" 
F 0 "#PWR014" H 3250 7850 50  0001 C CNN
F 1 "ISO_GND" H 3255 7927 50  0000 C CNN
F 2 "" H 3250 8100 50  0001 C CNN
F 3 "" H 3250 8100 50  0001 C CNN
	1    3250 8100
	1    0    0    -1  
$EndComp
$Comp
L Device:C C?
U 1 1 60AAF29D
P 2750 5500
AR Path="/600380E4/60AAF29D" Ref="C?"  Part="1" 
AR Path="/60AAF29D" Ref="C4"  Part="1" 
F 0 "C4" H 2865 5546 50  0000 L CNN
F 1 "100nF" H 2865 5455 50  0000 L CNN
F 2 "Capacitor_SMD:C_0603_1608Metric" H 2788 5350 50  0001 C CNN
F 3 "~" H 2750 5500 50  0001 C CNN
	1    2750 5500
	1    0    0    -1  
$EndComp
$Comp
L PUTM_EV_BMS_library:ISO_+5V #PWR?
U 1 1 60AAF2A3
P 2750 5350
AR Path="/601B5445/60AAF2A3" Ref="#PWR?"  Part="1" 
AR Path="/60AAF2A3" Ref="#PWR011"  Part="1" 
F 0 "#PWR011" H 2750 5200 50  0001 C CNN
F 1 "ISO_+5V" H 2765 5523 50  0000 C CNN
F 2 "" H 2750 5350 50  0001 C CNN
F 3 "" H 2750 5350 50  0001 C CNN
	1    2750 5350
	1    0    0    -1  
$EndComp
$Comp
L PUTM_EV_BMS_library:ISO_GND #PWR?
U 1 1 60AAF2A9
P 2750 5650
AR Path="/601B5445/60AAF2A9" Ref="#PWR?"  Part="1" 
AR Path="/60AAF2A9" Ref="#PWR012"  Part="1" 
F 0 "#PWR012" H 2750 5400 50  0001 C CNN
F 1 "ISO_GND" H 2755 5477 50  0000 C CNN
F 2 "" H 2750 5650 50  0001 C CNN
F 3 "" H 2750 5650 50  0001 C CNN
	1    2750 5650
	1    0    0    -1  
$EndComp
$Comp
L PUTM_EV_BMS_library:ISO_+5V #PWR?
U 1 1 60AC281A
P 4150 4200
AR Path="/601B5445/60AC281A" Ref="#PWR?"  Part="1" 
AR Path="/60AC281A" Ref="#PWR018"  Part="1" 
F 0 "#PWR018" H 4150 4050 50  0001 C CNN
F 1 "ISO_+5V" H 4165 4373 50  0000 C CNN
F 2 "" H 4150 4200 50  0001 C CNN
F 3 "" H 4150 4200 50  0001 C CNN
	1    4150 4200
	1    0    0    -1  
$EndComp
$Comp
L PUTM_EV_BMS_library:ISO_+5V #PWR?
U 1 1 60AEE842
P 4150 6500
AR Path="/601B5445/60AEE842" Ref="#PWR?"  Part="1" 
AR Path="/60AEE842" Ref="#PWR019"  Part="1" 
F 0 "#PWR019" H 4150 6350 50  0001 C CNN
F 1 "ISO_+5V" H 4165 6673 50  0000 C CNN
F 2 "" H 4150 6500 50  0001 C CNN
F 3 "" H 4150 6500 50  0001 C CNN
	1    4150 6500
	1    0    0    -1  
$EndComp
$Comp
L PUTM_EV_BMS_library:ISO_GND #PWR?
U 1 1 60AEF33B
P 3950 4950
AR Path="/601B5445/60AEF33B" Ref="#PWR?"  Part="1" 
AR Path="/60AEF33B" Ref="#PWR015"  Part="1" 
F 0 "#PWR015" H 3950 4700 50  0001 C CNN
F 1 "ISO_GND" H 3955 4777 50  0000 C CNN
F 2 "" H 3950 4950 50  0001 C CNN
F 3 "" H 3950 4950 50  0001 C CNN
	1    3950 4950
	1    0    0    -1  
$EndComp
$Comp
L PUTM_EV_BMS_library:ISO_GND #PWR?
U 1 1 60AF0070
P 4000 7300
AR Path="/601B5445/60AF0070" Ref="#PWR?"  Part="1" 
AR Path="/60AF0070" Ref="#PWR016"  Part="1" 
F 0 "#PWR016" H 4000 7050 50  0001 C CNN
F 1 "ISO_GND" H 4005 7127 50  0000 C CNN
F 2 "" H 4000 7300 50  0001 C CNN
F 3 "" H 4000 7300 50  0001 C CNN
	1    4000 7300
	1    0    0    -1  
$EndComp
Wire Wire Line
	4250 7150 4000 7150
Wire Wire Line
	4000 7300 4000 7150
$Comp
L power:+5V #PWR?
U 1 1 60B313FE
P 5550 7550
AR Path="/601B5445/60B313FE" Ref="#PWR?"  Part="1" 
AR Path="/60B313FE" Ref="#PWR033"  Part="1" 
F 0 "#PWR033" H 5550 7400 50  0001 C CNN
F 1 "+5V" H 5565 7723 50  0000 C CNN
F 2 "" H 5550 7550 50  0001 C CNN
F 3 "" H 5550 7550 50  0001 C CNN
	1    5550 7550
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR?
U 1 1 60B324F7
P 5550 7850
AR Path="/601B5445/60B324F7" Ref="#PWR?"  Part="1" 
AR Path="/60B324F7" Ref="#PWR034"  Part="1" 
F 0 "#PWR034" H 5550 7600 50  0001 C CNN
F 1 "GND" H 5555 7677 50  0000 C CNN
F 2 "" H 5550 7850 50  0001 C CNN
F 3 "" H 5550 7850 50  0001 C CNN
	1    5550 7850
	1    0    0    -1  
$EndComp
$Comp
L Device:R_Small R29
U 1 1 60BF99A0
P 7800 6800
F 0 "R29" V 7604 6800 50  0000 C CNN
F 1 "100" V 7695 6800 50  0000 C CNN
F 2 "Resistor_SMD:R_0603_1608Metric" H 7800 6800 50  0001 C CNN
F 3 "~" H 7800 6800 50  0001 C CNN
	1    7800 6800
	0    1    1    0   
$EndComp
$Comp
L Device:C_Small C20
U 1 1 60BFC513
P 8050 7000
F 0 "C20" H 8142 7046 50  0000 L CNN
F 1 "1uF" H 8142 6955 50  0000 L CNN
F 2 "Capacitor_SMD:C_0603_1608Metric" H 8050 7000 50  0001 C CNN
F 3 "~" H 8050 7000 50  0001 C CNN
	1    8050 7000
	1    0    0    -1  
$EndComp
$Comp
L Device:R_Small R20
U 1 1 60C83B93
P 6300 6700
F 0 "R20" V 6104 6700 50  0000 C CNN
F 1 "10k" V 6195 6700 50  0000 C CNN
F 2 "Resistor_SMD:R_0603_1608Metric" H 6300 6700 50  0001 C CNN
F 3 "~" H 6300 6700 50  0001 C CNN
	1    6300 6700
	0    1    1    0   
$EndComp
$Comp
L Device:R_Small R26
U 1 1 60C84995
P 7200 6400
F 0 "R26" V 7004 6400 50  0000 C CNN
F 1 "20k" V 7095 6400 50  0000 C CNN
F 2 "Resistor_SMD:R_0805_2012Metric" H 7200 6400 50  0001 C CNN
F 3 "~" H 7200 6400 50  0001 C CNN
	1    7200 6400
	0    1    1    0   
$EndComp
Wire Wire Line
	7400 6400 7400 6800
Wire Wire Line
	7400 6800 7700 6800
Wire Wire Line
	6650 6400 6650 6700
$Comp
L Device:R_Small R24
U 1 1 60CF73CE
P 6650 7150
F 0 "R24" H 6591 7104 50  0000 R CNN
F 1 "20k" H 6591 7195 50  0000 R CNN
F 2 "Resistor_SMD:R_0805_2012Metric" H 6650 7150 50  0001 C CNN
F 3 "~" H 6650 7150 50  0001 C CNN
	1    6650 7150
	-1   0    0    1   
$EndComp
$Comp
L Device:R_Small R21
U 1 1 60CF7CDB
P 6300 7000
F 0 "R21" V 6104 7000 50  0000 C CNN
F 1 "10k" V 6195 7000 50  0000 C CNN
F 2 "Resistor_SMD:R_0603_1608Metric" H 6300 7000 50  0001 C CNN
F 3 "~" H 6300 7000 50  0001 C CNN
	1    6300 7000
	0    1    1    0   
$EndComp
$Comp
L power:GND #PWR?
U 1 1 60D8B70C
P 6650 7350
AR Path="/601B5445/60D8B70C" Ref="#PWR?"  Part="1" 
AR Path="/60D8B70C" Ref="#PWR038"  Part="1" 
F 0 "#PWR038" H 6650 7100 50  0001 C CNN
F 1 "GND" H 6655 7177 50  0000 C CNN
F 2 "" H 6650 7350 50  0001 C CNN
F 3 "" H 6650 7350 50  0001 C CNN
	1    6650 7350
	1    0    0    -1  
$EndComp
$Comp
L power:+5V #PWR?
U 1 1 60DA5D6F
P 5500 6550
AR Path="/601B5445/60DA5D6F" Ref="#PWR?"  Part="1" 
AR Path="/60DA5D6F" Ref="#PWR030"  Part="1" 
F 0 "#PWR030" H 5500 6400 50  0001 C CNN
F 1 "+5V" H 5515 6723 50  0000 C CNN
F 2 "" H 5500 6550 50  0001 C CNN
F 3 "" H 5500 6550 50  0001 C CNN
	1    5500 6550
	1    0    0    -1  
$EndComp
$Comp
L Device:C C?
U 1 1 60E6803E
P 5550 5450
AR Path="/600380E4/60E6803E" Ref="C?"  Part="1" 
AR Path="/60E6803E" Ref="C13"  Part="1" 
F 0 "C13" H 5665 5496 50  0000 L CNN
F 1 "100nF" H 5665 5405 50  0000 L CNN
F 2 "Capacitor_SMD:C_0603_1608Metric" H 5588 5300 50  0001 C CNN
F 3 "~" H 5550 5450 50  0001 C CNN
	1    5550 5450
	1    0    0    -1  
$EndComp
Text Notes 8275 4700 0    50   ~ 0
Fc=1kHz
$Comp
L power:+5V #PWR?
U 1 1 60E68045
P 5550 5300
AR Path="/601B5445/60E68045" Ref="#PWR?"  Part="1" 
AR Path="/60E68045" Ref="#PWR031"  Part="1" 
F 0 "#PWR031" H 5550 5150 50  0001 C CNN
F 1 "+5V" H 5565 5473 50  0000 C CNN
F 2 "" H 5550 5300 50  0001 C CNN
F 3 "" H 5550 5300 50  0001 C CNN
	1    5550 5300
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR?
U 1 1 60E6804B
P 5550 5600
AR Path="/601B5445/60E6804B" Ref="#PWR?"  Part="1" 
AR Path="/60E6804B" Ref="#PWR032"  Part="1" 
F 0 "#PWR032" H 5550 5350 50  0001 C CNN
F 1 "GND" H 5555 5427 50  0000 C CNN
F 2 "" H 5550 5600 50  0001 C CNN
F 3 "" H 5550 5600 50  0001 C CNN
	1    5550 5600
	1    0    0    -1  
$EndComp
$Comp
L Device:R_Small R27
U 1 1 60E68051
P 7700 4450
F 0 "R27" V 7504 4450 50  0000 C CNN
F 1 "100" V 7595 4450 50  0000 C CNN
F 2 "Resistor_SMD:R_0603_1608Metric" H 7700 4450 50  0001 C CNN
F 3 "~" H 7700 4450 50  0001 C CNN
	1    7700 4450
	0    1    1    0   
$EndComp
$Comp
L Device:C_Small C18
U 1 1 60E68057
P 8050 4700
F 0 "C18" H 8142 4746 50  0000 L CNN
F 1 "1uF" H 8142 4655 50  0000 L CNN
F 2 "Capacitor_SMD:C_0603_1608Metric" H 8050 4700 50  0001 C CNN
F 3 "~" H 8050 4700 50  0001 C CNN
	1    8050 4700
	1    0    0    -1  
$EndComp
$Comp
L Device:R_Small R18
U 1 1 60E68062
P 6250 4350
F 0 "R18" V 6054 4350 50  0000 C CNN
F 1 "10k" V 6145 4350 50  0000 C CNN
F 2 "Resistor_SMD:R_0603_1608Metric" H 6250 4350 50  0001 C CNN
F 3 "~" H 6250 4350 50  0001 C CNN
	1    6250 4350
	0    1    1    0   
$EndComp
$Comp
L Device:R_Small R25
U 1 1 60E68068
P 7100 4050
F 0 "R25" V 6904 4050 50  0000 C CNN
F 1 "20k" V 6995 4050 50  0000 C CNN
F 2 "Resistor_SMD:R_0805_2012Metric" H 7100 4050 50  0001 C CNN
F 3 "~" H 7100 4050 50  0001 C CNN
	1    7100 4050
	0    1    1    0   
$EndComp
Wire Wire Line
	7350 4050 7350 4450
Wire Wire Line
	6600 4050 6600 4350
$Comp
L Device:R_Small R23
U 1 1 60E68077
P 6600 4800
F 0 "R23" H 6541 4754 50  0000 R CNN
F 1 "20k" H 6541 4845 50  0000 R CNN
F 2 "Resistor_SMD:R_0805_2012Metric" H 6600 4800 50  0001 C CNN
F 3 "~" H 6600 4800 50  0001 C CNN
	1    6600 4800
	-1   0    0    1   
$EndComp
$Comp
L Device:R_Small R19
U 1 1 60E6807D
P 6250 4650
F 0 "R19" V 6054 4650 50  0000 C CNN
F 1 "10k" V 6145 4650 50  0000 C CNN
F 2 "Resistor_SMD:R_0603_1608Metric" H 6250 4650 50  0001 C CNN
F 3 "~" H 6250 4650 50  0001 C CNN
	1    6250 4650
	0    1    1    0   
$EndComp
$Comp
L power:GND #PWR?
U 1 1 60E68093
P 6600 5000
AR Path="/601B5445/60E68093" Ref="#PWR?"  Part="1" 
AR Path="/60E68093" Ref="#PWR037"  Part="1" 
F 0 "#PWR037" H 6600 4750 50  0001 C CNN
F 1 "GND" H 6605 4827 50  0000 C CNN
F 2 "" H 6600 5000 50  0001 C CNN
F 3 "" H 6600 5000 50  0001 C CNN
	1    6600 5000
	1    0    0    -1  
$EndComp
$Comp
L power:+5V #PWR?
U 1 1 60E68099
P 5500 4200
AR Path="/601B5445/60E68099" Ref="#PWR?"  Part="1" 
AR Path="/60E68099" Ref="#PWR029"  Part="1" 
F 0 "#PWR029" H 5500 4050 50  0001 C CNN
F 1 "+5V" H 5515 4373 50  0000 C CNN
F 2 "" H 5500 4200 50  0001 C CNN
F 3 "" H 5500 4200 50  0001 C CNN
	1    5500 4200
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR?
U 1 1 60EA9BBC
P 8050 5650
AR Path="/601B5445/60EA9BBC" Ref="#PWR?"  Part="1" 
AR Path="/60EA9BBC" Ref="#PWR046"  Part="1" 
F 0 "#PWR046" H 8050 5400 50  0001 C CNN
F 1 "GND" H 8055 5477 50  0000 C CNN
F 2 "" H 8050 5650 50  0001 C CNN
F 3 "" H 8050 5650 50  0001 C CNN
	1    8050 5650
	1    0    0    -1  
$EndComp
$Comp
L power:+3.3V #PWR045
U 1 1 60ECA12F
P 8050 5350
F 0 "#PWR045" H 8050 5200 50  0001 C CNN
F 1 "+3.3V" H 8065 5523 50  0000 C CNN
F 2 "" H 8050 5350 50  0001 C CNN
F 3 "" H 8050 5350 50  0001 C CNN
	1    8050 5350
	1    0    0    -1  
$EndComp
$Comp
L PUTM_EV_BMS_library:LTC6820IMS U12
U 1 1 60FD71DE
P 11950 13050
F 0 "U12" H 11950 13625 50  0000 C CNN
F 1 "LTC6820IMS" H 11950 13534 50  0000 C CNN
F 2 "Package_SO:MSOP-16_3x4.039mm_P0.5mm" H 11950 12500 50  0001 C CNN
F 3 "" H 12150 12750 50  0001 C CNN
	1    11950 13050
	1    0    0    -1  
$EndComp
Text Notes 11575 12375 0    50   ~ 0
isoSPI communication
$Comp
L PUTM_EV_BMS_library:ISO_GND #PWR?
U 1 1 602FEAAF
P 1250 5750
AR Path="/601B5445/602FEAAF" Ref="#PWR?"  Part="1" 
AR Path="/602FEAAF" Ref="#PWR05"  Part="1" 
F 0 "#PWR05" H 1250 5500 50  0001 C CNN
F 1 "ISO_GND" H 1255 5577 50  0000 C CNN
F 2 "" H 1250 5750 50  0001 C CNN
F 3 "" H 1250 5750 50  0001 C CNN
	1    1250 5750
	1    0    0    -1  
$EndComp
Text Label 1600 4400 2    50   ~ 0
HV_ACU_VOLTAGE
Text Label 18150 13200 0    50   ~ 0
SENSOR_REF
Wire Wire Line
	17600 13200 18100 13200
Connection ~ 17600 13200
Wire Wire Line
	17400 15400 17400 15300
$Comp
L Device:R_Small R70
U 1 1 601BA6E3
P 15300 15100
F 0 "R70" H 15241 15054 50  0000 R CNN
F 1 "100k" H 15241 15145 50  0000 R CNN
F 2 "Resistor_SMD:R_1206_3216Metric" H 15300 15100 50  0001 C CNN
F 3 "~" H 15300 15100 50  0001 C CNN
	1    15300 15100
	-1   0    0    1   
$EndComp
$Comp
L Device:C_Small C38
U 1 1 601BA6C4
P 15700 15100
F 0 "C38" H 15792 15146 50  0000 L CNN
F 1 "10uF" H 15792 15055 50  0000 L CNN
F 2 "Capacitor_SMD:C_0805_2012Metric" H 15700 15100 50  0001 C CNN
F 3 "~" H 15700 15100 50  0001 C CNN
	1    15700 15100
	1    0    0    -1  
$EndComp
$Comp
L Device:R_Small R68
U 1 1 601BA6BE
P 15100 14850
F 0 "R68" V 14904 14850 50  0000 C CNN
F 1 "100" V 14995 14850 50  0000 C CNN
F 2 "Resistor_SMD:R_0603_1608Metric" H 15100 14850 50  0001 C CNN
F 3 "~" H 15100 14850 50  0001 C CNN
	1    15100 14850
	0    1    1    0   
$EndComp
$Comp
L Device:R_Small R78
U 1 1 601BA6D6
P 17100 14950
F 0 "R78" V 17296 14950 50  0000 C CNN
F 1 "100" V 17205 14950 50  0000 C CNN
F 2 "Resistor_SMD:R_0603_1608Metric" H 17100 14950 50  0001 C CNN
F 3 "~" H 17100 14950 50  0001 C CNN
	1    17100 14950
	0    -1   -1   0   
$EndComp
Wire Wire Line
	17400 14950 17400 15100
Text Label 14350 14850 0    50   ~ 0
SENSOR_SIGNAL
Text Label 19900 1650 2    50   ~ 0
SPI1_MOSI
Text Label 19900 1750 2    50   ~ 0
SPI1_MISO
Text Label 19900 1850 2    50   ~ 0
SPI1_SCK
Text Label 19900 1950 2    50   ~ 0
SPI1_~CS
Text Label 19000 5250 0    50   ~ 0
SPI1_MOSI
Text Label 19000 5150 0    50   ~ 0
SPI1_MISO
Text Label 19000 5050 0    50   ~ 0
SPI1_SCK
Text Label 19000 4950 0    50   ~ 0
SPI1_~CS
Text Label 19000 4550 0    50   ~ 0
SENSOR_REF
Text Label 17600 14950 0    50   ~ 0
SENSOR_SIGNAL_MCU
Text Label 19000 4650 0    50   ~ 0
SENSOR_SIGNAL_MCU
$Comp
L Relay:FINDER-30.22 K4
U 1 1 605D32BE
P 12850 1800
F 0 "K4" V 13617 1800 50  0000 C CNN
F 1 "FINDER-30.22" V 13526 1800 50  0000 C CNN
F 2 "Relay_THT:Relay_DPDT_Finder_30.22" H 14200 1770 50  0001 C CNN
F 3 "http://gfinder.findernet.com/assets/Series/354/S30EN.pdf" H 12850 1800 50  0001 C CNN
	1    12850 1800
	0    -1   -1   0   
$EndComp
$Comp
L Device:R_Small R57
U 1 1 60631AC0
P 12600 12700
F 0 "R57" V 12404 12700 50  0000 C CNN
F 1 "1K" V 12495 12700 50  0000 C CNN
F 2 "Resistor_SMD:R_0603_1608Metric" H 12600 12700 50  0001 C CNN
F 3 "~" H 12600 12700 50  0001 C CNN
	1    12600 12700
	0    1    1    0   
$EndComp
$Comp
L Device:R_Small R48
U 1 1 607291AF
P 9700 15400
F 0 "R48" H 9759 15446 50  0000 L CNN
F 1 "10k" H 9759 15355 50  0000 L CNN
F 2 "Resistor_SMD:R_0603_1608Metric" H 9700 15400 50  0001 C CNN
F 3 "~" H 9700 15400 50  0001 C CNN
	1    9700 15400
	1    0    0    -1  
$EndComp
$Comp
L Device:R_Small R47
U 1 1 6072BFEE
P 9700 15100
F 0 "R47" H 9759 15146 50  0000 L CNN
F 1 "10k" H 9759 15055 50  0000 L CNN
F 2 "Resistor_SMD:R_0603_1608Metric" H 9700 15100 50  0001 C CNN
F 3 "~" H 9700 15100 50  0001 C CNN
	1    9700 15100
	1    0    0    -1  
$EndComp
Wire Wire Line
	9700 15200 9700 15250
Wire Wire Line
	9700 15250 9750 15250
Connection ~ 9700 15250
Wire Wire Line
	9700 15250 9700 15300
$Comp
L Device:R_Small R42
U 1 1 60779C89
P 9300 15400
F 0 "R42" H 9359 15446 50  0000 L CNN
F 1 "10k" H 9359 15355 50  0000 L CNN
F 2 "Resistor_SMD:R_0603_1608Metric" H 9300 15400 50  0001 C CNN
F 3 "~" H 9300 15400 50  0001 C CNN
	1    9300 15400
	1    0    0    -1  
$EndComp
$Comp
L Device:R_Small R41
U 1 1 60779C8F
P 9300 15100
F 0 "R41" H 9359 15146 50  0000 L CNN
F 1 "10k" H 9359 15055 50  0000 L CNN
F 2 "Resistor_SMD:R_0603_1608Metric" H 9300 15100 50  0001 C CNN
F 3 "~" H 9300 15100 50  0001 C CNN
	1    9300 15100
	1    0    0    -1  
$EndComp
Wire Wire Line
	9300 15200 9300 15250
Wire Wire Line
	9300 15250 9350 15250
Connection ~ 9300 15250
Wire Wire Line
	9300 15250 9300 15300
$Comp
L Device:R_Small R38
U 1 1 6079F9A9
P 8750 15400
F 0 "R38" H 8809 15446 50  0000 L CNN
F 1 "10k" H 8809 15355 50  0000 L CNN
F 2 "Resistor_SMD:R_0603_1608Metric" H 8750 15400 50  0001 C CNN
F 3 "~" H 8750 15400 50  0001 C CNN
	1    8750 15400
	1    0    0    -1  
$EndComp
$Comp
L Device:R_Small R37
U 1 1 6079F9AF
P 8750 15100
F 0 "R37" H 8809 15146 50  0000 L CNN
F 1 "10k" H 8809 15055 50  0000 L CNN
F 2 "Resistor_SMD:R_0603_1608Metric" H 8750 15100 50  0001 C CNN
F 3 "~" H 8750 15100 50  0001 C CNN
	1    8750 15100
	1    0    0    -1  
$EndComp
Wire Wire Line
	8750 15200 8750 15250
Wire Wire Line
	8750 15250 8800 15250
Connection ~ 8750 15250
Wire Wire Line
	8750 15250 8750 15300
$Comp
L Device:R_Small R36
U 1 1 607C56DB
P 8300 15400
F 0 "R36" H 8359 15446 50  0000 L CNN
F 1 "10k" H 8359 15355 50  0000 L CNN
F 2 "Resistor_SMD:R_0603_1608Metric" H 8300 15400 50  0001 C CNN
F 3 "~" H 8300 15400 50  0001 C CNN
	1    8300 15400
	1    0    0    -1  
$EndComp
$Comp
L Device:R_Small R35
U 1 1 607C56E1
P 8300 15100
F 0 "R35" H 8359 15146 50  0000 L CNN
F 1 "10k" H 8359 15055 50  0000 L CNN
F 2 "Resistor_SMD:R_0603_1608Metric" H 8300 15100 50  0001 C CNN
F 3 "~" H 8300 15100 50  0001 C CNN
	1    8300 15100
	1    0    0    -1  
$EndComp
Wire Wire Line
	8300 15200 8300 15250
Wire Wire Line
	8300 15250 8350 15250
Connection ~ 8300 15250
Wire Wire Line
	8300 15250 8300 15300
$Comp
L power:+3.3V #PWR?
U 1 1 6083D9BB
P 9050 14950
AR Path="/60056272/6083D9BB" Ref="#PWR?"  Part="1" 
AR Path="/6083D9BB" Ref="#PWR049"  Part="1" 
F 0 "#PWR049" H 9050 14800 50  0001 C CNN
F 1 "+3.3V" H 9065 15123 50  0000 C CNN
F 2 "" H 9050 14950 50  0001 C CNN
F 3 "" H 9050 14950 50  0001 C CNN
	1    9050 14950
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR?
U 1 1 6083E62C
P 9050 15650
AR Path="/60056272/6083E62C" Ref="#PWR?"  Part="1" 
AR Path="/6083E62C" Ref="#PWR050"  Part="1" 
F 0 "#PWR050" H 9050 15400 50  0001 C CNN
F 1 "GND" H 9055 15477 50  0000 C CNN
F 2 "" H 9050 15650 50  0001 C CNN
F 3 "" H 9050 15650 50  0001 C CNN
	1    9050 15650
	1    0    0    -1  
$EndComp
Text Label 8350 15250 0    50   ~ 0
POL
Text Label 8800 15250 0    50   ~ 0
PHA
Text Label 9350 15250 0    50   ~ 0
MSTR
Text Label 9750 15250 0    50   ~ 0
SLOW
Wire Wire Line
	9700 15000 9700 14950
Wire Wire Line
	9700 14950 9300 14950
Wire Wire Line
	8300 14950 8300 15000
Connection ~ 9050 14950
Wire Wire Line
	9050 14950 8750 14950
Wire Wire Line
	8750 15000 8750 14950
Connection ~ 8750 14950
Wire Wire Line
	8750 14950 8300 14950
Wire Wire Line
	9300 15000 9300 14950
Connection ~ 9300 14950
Wire Wire Line
	9300 14950 9050 14950
Wire Wire Line
	8300 15500 8300 15600
Wire Wire Line
	8300 15600 8750 15600
Wire Wire Line
	9700 15600 9700 15500
Wire Wire Line
	9300 15500 9300 15600
Connection ~ 9300 15600
Wire Wire Line
	9300 15600 9700 15600
Wire Wire Line
	8750 15500 8750 15600
Connection ~ 8750 15600
Wire Wire Line
	8750 15600 9050 15600
Wire Wire Line
	9050 15600 9050 15650
Connection ~ 9050 15600
Wire Wire Line
	9050 15600 9300 15600
Text Label 12350 13000 0    50   ~ 0
SLOW
Text Label 12350 13100 0    50   ~ 0
MSTR
Text Label 11550 13300 2    50   ~ 0
POL
Text Label 11550 13400 2    50   ~ 0
PHA
Text Label 3050 1100 0    50   ~ 0
AMS_SAFETY_1
Text Label 3050 1200 0    50   ~ 0
AMS_SAFETY_2
Text Label 3050 1300 0    50   ~ 0
AMS_FAULT_COCKPIT
Text Label 12450 1300 2    50   ~ 0
AMS_SAFETY_1
Wire Wire Line
	12450 1300 12550 1300
Text Label 13250 1400 0    50   ~ 0
AMS_SAFETY_2
Wire Wire Line
	13250 1400 13150 1400
Wire Wire Line
	13150 1800 13800 1800
Text Label 12450 1900 2    50   ~ 0
AMS_FAULT_COCKPIT
Wire Wire Line
	12450 1900 12550 1900
Wire Wire Line
	12550 2200 11550 2200
Wire Wire Line
	11550 2200 11550 1150
$Comp
L power:+5V #PWR?
U 1 1 60AC75F5
P 11550 1150
AR Path="/601B5445/60AC75F5" Ref="#PWR?"  Part="1" 
AR Path="/60AC75F5" Ref="#PWR062"  Part="1" 
F 0 "#PWR062" H 11550 1000 50  0001 C CNN
F 1 "+5V" H 11565 1323 50  0000 C CNN
F 2 "" H 11550 1150 50  0001 C CNN
F 3 "" H 11550 1150 50  0001 C CNN
	1    11550 1150
	1    0    0    -1  
$EndComp
Wire Wire Line
	13150 2200 13300 2200
Wire Wire Line
	13300 2200 13300 2600
$Comp
L Transistor_FET:2N7002 Q4
U 1 1 60AF62E7
P 13200 2800
F 0 "Q4" H 13404 2846 50  0000 L CNN
F 1 "2N7002" H 13404 2755 50  0000 L CNN
F 2 "Package_TO_SOT_SMD:SOT-23" H 13400 2725 50  0001 L CIN
F 3 "https://www.fairchildsemi.com/datasheets/2N/2N7002.pdf" H 13200 2800 50  0001 L CNN
	1    13200 2800
	1    0    0    -1  
$EndComp
$Comp
L Device:R_Small R61
U 1 1 60AFB560
P 12900 3000
F 0 "R61" H 12959 3046 50  0000 L CNN
F 1 "10k" H 12959 2955 50  0000 L CNN
F 2 "Resistor_SMD:R_0603_1608Metric" H 12900 3000 50  0001 C CNN
F 3 "~" H 12900 3000 50  0001 C CNN
	1    12900 3000
	1    0    0    -1  
$EndComp
$Comp
L Device:R_Small R59
U 1 1 60AFC4A9
P 12650 2800
F 0 "R59" V 12454 2800 50  0000 C CNN
F 1 "100" V 12545 2800 50  0000 C CNN
F 2 "Resistor_SMD:R_0603_1608Metric" H 12650 2800 50  0001 C CNN
F 3 "~" H 12650 2800 50  0001 C CNN
	1    12650 2800
	0    1    1    0   
$EndComp
Wire Wire Line
	13000 2800 12900 2800
Wire Wire Line
	12900 2800 12900 2900
Connection ~ 12900 2800
Wire Wire Line
	12900 2800 12750 2800
Wire Wire Line
	12900 3100 12900 3150
Wire Wire Line
	12900 3150 13300 3150
Wire Wire Line
	13300 3150 13300 3000
Wire Wire Line
	13300 3150 13300 3200
Connection ~ 13300 3150
Wire Wire Line
	12550 2800 12250 2800
$Comp
L power:GND #PWR?
U 1 1 60C0DB22
P 13300 3200
AR Path="/601B5445/60C0DB22" Ref="#PWR?"  Part="1" 
AR Path="/60C0DB22" Ref="#PWR074"  Part="1" 
F 0 "#PWR074" H 13300 2950 50  0001 C CNN
F 1 "GND" H 13305 3027 50  0000 C CNN
F 2 "" H 13300 3200 50  0001 C CNN
F 3 "" H 13300 3200 50  0001 C CNN
	1    13300 3200
	1    0    0    -1  
$EndComp
$Comp
L Device:R_Small R62
U 1 1 6063322C
P 13000 12900
F 0 "R62" H 12941 12854 50  0000 R CNN
F 1 "1K" H 12941 12945 50  0000 R CNN
F 2 "Resistor_SMD:R_0603_1608Metric" H 13000 12900 50  0001 C CNN
F 3 "~" H 13000 12900 50  0001 C CNN
	1    13000 12900
	-1   0    0    1   
$EndComp
Wire Wire Line
	12350 12700 12500 12700
Wire Wire Line
	13000 12800 13000 12700
Wire Wire Line
	13000 12700 12700 12700
Wire Wire Line
	12350 12800 13000 12800
Connection ~ 13000 12800
Wire Wire Line
	13000 13000 13000 13050
Wire Wire Line
	12350 12900 12850 12900
Wire Wire Line
	12850 12900 12850 13050
Wire Wire Line
	12850 13050 13000 13050
Connection ~ 13000 13050
Wire Wire Line
	13000 13050 13000 13500
$Comp
L power:GND #PWR?
U 1 1 60F31D02
P 13000 13550
AR Path="/60056272/60F31D02" Ref="#PWR?"  Part="1" 
AR Path="/60F31D02" Ref="#PWR072"  Part="1" 
F 0 "#PWR072" H 13000 13300 50  0001 C CNN
F 1 "GND" H 13005 13377 50  0000 C CNN
F 2 "" H 13000 13550 50  0001 C CNN
F 3 "" H 13000 13550 50  0001 C CNN
	1    13000 13550
	1    0    0    -1  
$EndComp
Text Label 11550 12800 2    50   ~ 0
LTC_MOSI
Text Label 11550 12900 2    50   ~ 0
LTC_MISO
Text Label 11550 13000 2    50   ~ 0
LTC_SCK
Text Label 11550 13100 2    50   ~ 0
LTC_1_~CS
Text Label 19000 7650 0    50   ~ 0
LTC_MOSI
Text Label 19000 7550 0    50   ~ 0
LTC_MISO
Text Label 19000 7450 0    50   ~ 0
LTC_SCK
Text Label 17600 6850 2    50   ~ 0
LTC_1_~CS
Text Label 17600 6750 2    50   ~ 0
LTC_2_~CS
$Comp
L PUTM_EV_BMS_library:LTC6820IMS U13
U 1 1 60F910F9
P 11950 14850
F 0 "U13" H 11950 15425 50  0000 C CNN
F 1 "LTC6820IMS" H 11950 15334 50  0000 C CNN
F 2 "Package_SO:MSOP-16_3x4.039mm_P0.5mm" H 11950 14300 50  0001 C CNN
F 3 "" H 12150 14550 50  0001 C CNN
	1    11950 14850
	1    0    0    -1  
$EndComp
$Comp
L Device:R_Small R58
U 1 1 60F910FF
P 12600 14500
F 0 "R58" V 12404 14500 50  0000 C CNN
F 1 "1K" V 12495 14500 50  0000 C CNN
F 2 "Resistor_SMD:R_0603_1608Metric" H 12600 14500 50  0001 C CNN
F 3 "~" H 12600 14500 50  0001 C CNN
	1    12600 14500
	0    1    1    0   
$EndComp
Text Label 12350 14800 0    50   ~ 0
SLOW
Text Label 12350 14900 0    50   ~ 0
MSTR
Text Label 11550 15100 2    50   ~ 0
POL
Text Label 11550 15200 2    50   ~ 0
PHA
$Comp
L Device:R_Small R63
U 1 1 60F91109
P 13000 14700
F 0 "R63" H 12941 14654 50  0000 R CNN
F 1 "1K" H 12941 14745 50  0000 R CNN
F 2 "Resistor_SMD:R_0603_1608Metric" H 13000 14700 50  0001 C CNN
F 3 "~" H 13000 14700 50  0001 C CNN
	1    13000 14700
	-1   0    0    1   
$EndComp
Wire Wire Line
	12350 14500 12500 14500
Wire Wire Line
	13000 14600 13000 14500
Wire Wire Line
	13000 14500 12700 14500
Wire Wire Line
	12350 14600 13000 14600
Connection ~ 13000 14600
Wire Wire Line
	13000 14800 13000 14850
Wire Wire Line
	12350 14700 12850 14700
Wire Wire Line
	12850 14700 12850 14850
Wire Wire Line
	12850 14850 13000 14850
Connection ~ 13000 14850
Wire Wire Line
	13000 14850 13000 15350
$Comp
L power:GND #PWR?
U 1 1 60F9111A
P 13000 15400
AR Path="/60056272/60F9111A" Ref="#PWR?"  Part="1" 
AR Path="/60F9111A" Ref="#PWR073"  Part="1" 
F 0 "#PWR073" H 13000 15150 50  0001 C CNN
F 1 "GND" H 13005 15227 50  0000 C CNN
F 2 "" H 13000 15400 50  0001 C CNN
F 3 "" H 13000 15400 50  0001 C CNN
	1    13000 15400
	1    0    0    -1  
$EndComp
Text Label 11550 14600 2    50   ~ 0
LTC_MOSI
Text Label 11550 14700 2    50   ~ 0
LTC_MISO
Text Label 11550 14800 2    50   ~ 0
LTC_SCK
Text Label 11550 14900 2    50   ~ 0
LTC_2_~CS
Text Label 12350 13200 0    50   ~ 0
LTC_1_IP
Text Label 12350 13300 0    50   ~ 0
LTC_1_IM
Text Label 12350 15000 0    50   ~ 0
LTC_2_IP
Text Label 12350 15100 0    50   ~ 0
LTC_2_IM
Wire Wire Line
	12350 15200 13350 15200
Wire Wire Line
	13350 15200 13350 14950
Wire Wire Line
	12350 13400 13350 13400
Wire Wire Line
	13350 13400 13350 13150
$Comp
L power:+3.3V #PWR?
U 1 1 6109BEB1
P 13350 12600
AR Path="/60056272/6109BEB1" Ref="#PWR?"  Part="1" 
AR Path="/6109BEB1" Ref="#PWR075"  Part="1" 
F 0 "#PWR075" H 13350 12450 50  0001 C CNN
F 1 "+3.3V" H 13365 12773 50  0000 C CNN
F 2 "" H 13350 12600 50  0001 C CNN
F 3 "" H 13350 12600 50  0001 C CNN
	1    13350 12600
	1    0    0    -1  
$EndComp
$Comp
L power:+3.3V #PWR?
U 1 1 6109C41E
P 13350 14400
AR Path="/60056272/6109C41E" Ref="#PWR?"  Part="1" 
AR Path="/6109C41E" Ref="#PWR076"  Part="1" 
F 0 "#PWR076" H 13350 14250 50  0001 C CNN
F 1 "+3.3V" H 13365 14573 50  0000 C CNN
F 2 "" H 13350 14400 50  0001 C CNN
F 3 "" H 13350 14400 50  0001 C CNN
	1    13350 14400
	1    0    0    -1  
$EndComp
$Comp
L power:+3.3V #PWR?
U 1 1 6109C9ED
P 11000 14350
AR Path="/60056272/6109C9ED" Ref="#PWR?"  Part="1" 
AR Path="/6109C9ED" Ref="#PWR059"  Part="1" 
F 0 "#PWR059" H 11000 14200 50  0001 C CNN
F 1 "+3.3V" H 11015 14523 50  0000 C CNN
F 2 "" H 11000 14350 50  0001 C CNN
F 3 "" H 11000 14350 50  0001 C CNN
	1    11000 14350
	1    0    0    -1  
$EndComp
Wire Wire Line
	11550 14500 11000 14500
Wire Wire Line
	11000 14500 11000 14350
Wire Wire Line
	11550 15000 11000 15000
Wire Wire Line
	11000 15000 11000 14500
Connection ~ 11000 14500
$Comp
L power:+3.3V #PWR?
U 1 1 610FBB51
P 11000 12550
AR Path="/60056272/610FBB51" Ref="#PWR?"  Part="1" 
AR Path="/610FBB51" Ref="#PWR058"  Part="1" 
F 0 "#PWR058" H 11000 12400 50  0001 C CNN
F 1 "+3.3V" H 11015 12723 50  0000 C CNN
F 2 "" H 11000 12550 50  0001 C CNN
F 3 "" H 11000 12550 50  0001 C CNN
	1    11000 12550
	1    0    0    -1  
$EndComp
Wire Wire Line
	11550 12700 11000 12700
Wire Wire Line
	11000 12700 11000 12550
Wire Wire Line
	11550 13200 11000 13200
Wire Wire Line
	11000 13200 11000 12700
Connection ~ 11000 12700
$Comp
L Connector:Micro_SD_Card_Det_Hirose_DM3AT J15
U 1 1 606E638F
P 21050 10650
F 0 "J15" H 21000 11467 50  0000 C CNN
F 1 "Micro_SD_Card_Det_Hirose_DM3AT" H 21000 11376 50  0000 C CNN
F 2 "Connector_Card:microSD_HC_Hirose_DM3AT-SF-PEJM5" H 23100 11350 50  0001 C CNN
F 3 "https://www.hirose.com/product/en/download_file/key_name/DM3/category/Catalog/doc_file_id/49662/?file_category_id=4&item_id=195&is_series=1" H 21050 10750 50  0001 C CNN
	1    21050 10650
	1    0    0    -1  
$EndComp
$Comp
L Device:R_Small R67
U 1 1 606E85F7
P 13800 2050
F 0 "R67" H 13859 2096 50  0000 L CNN
F 1 "1k" H 13859 2005 50  0000 L CNN
F 2 "Resistor_SMD:R_0805_2012Metric" H 13800 2050 50  0001 C CNN
F 3 "~" H 13800 2050 50  0001 C CNN
	1    13800 2050
	1    0    0    -1  
$EndComp
$Comp
L 74xGxx:74LVC1G79 U14
U 1 1 606EDAE5
P 12000 2900
F 0 "U14" H 12000 3217 50  0000 C CNN
F 1 "74LVC1G79GV.125" H 12000 3126 50  0000 C CNN
F 2 "Package_TO_SOT_SMD:SOT-23-5" H 12000 2900 50  0001 C CNN
F 3 "http://www.ti.com/lit/sg/scyt129e/scyt129e.pdf" H 12000 2900 50  0001 C CNN
	1    12000 2900
	1    0    0    -1  
$EndComp
$Comp
L Device:C_Small C25
U 1 1 606F0DBA
P 10750 2700
F 0 "C25" V 10521 2700 50  0000 C CNN
F 1 "4.7uF" V 10612 2700 50  0000 C CNN
F 2 "Capacitor_SMD:C_0603_1608Metric" H 10750 2700 50  0001 C CNN
F 3 "~" H 10750 2700 50  0001 C CNN
	1    10750 2700
	0    1    1    0   
$EndComp
$Comp
L Device:R_Small R51
U 1 1 606F3CBF
P 10750 3000
F 0 "R51" V 10554 3000 50  0000 C CNN
F 1 "100k" V 10645 3000 50  0000 C CNN
F 2 "Resistor_SMD:R_1206_3216Metric" H 10750 3000 50  0001 C CNN
F 3 "~" H 10750 3000 50  0001 C CNN
	1    10750 3000
	0    1    1    0   
$EndComp
$Comp
L Device:R_Small R52
U 1 1 606F42EC
P 10900 3150
F 0 "R52" H 10841 3104 50  0000 R CNN
F 1 "10k" H 10841 3195 50  0000 R CNN
F 2 "Resistor_SMD:R_0603_1608Metric" H 10900 3150 50  0001 C CNN
F 3 "~" H 10900 3150 50  0001 C CNN
	1    10900 3150
	-1   0    0    1   
$EndComp
$Comp
L Device:C_Small C30
U 1 1 6093F04E
P 12500 3400
F 0 "C30" H 12408 3354 50  0000 R CNN
F 1 "100nF" H 12408 3445 50  0000 R CNN
F 2 "Capacitor_SMD:C_0603_1608Metric" H 12500 3400 50  0001 C CNN
F 3 "~" H 12500 3400 50  0001 C CNN
	1    12500 3400
	-1   0    0    1   
$EndComp
$Comp
L power:+3.3V #PWR?
U 1 1 6093FF4F
P 12500 3250
AR Path="/60056272/6093FF4F" Ref="#PWR?"  Part="1" 
AR Path="/6093FF4F" Ref="#PWR068"  Part="1" 
F 0 "#PWR068" H 12500 3100 50  0001 C CNN
F 1 "+3.3V" H 12515 3423 50  0000 C CNN
F 2 "" H 12500 3250 50  0001 C CNN
F 3 "" H 12500 3250 50  0001 C CNN
	1    12500 3250
	1    0    0    -1  
$EndComp
Wire Wire Line
	12500 3250 12500 3300
Wire Wire Line
	12500 3500 12500 3550
$Comp
L power:GND #PWR?
U 1 1 609A2F44
P 12500 3550
AR Path="/601B5445/609A2F44" Ref="#PWR?"  Part="1" 
AR Path="/609A2F44" Ref="#PWR069"  Part="1" 
F 0 "#PWR069" H 12500 3300 50  0001 C CNN
F 1 "GND" H 12505 3377 50  0000 C CNN
F 2 "" H 12500 3550 50  0001 C CNN
F 3 "" H 12500 3550 50  0001 C CNN
	1    12500 3550
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR?
U 1 1 609A326D
P 12000 3150
AR Path="/601B5445/609A326D" Ref="#PWR?"  Part="1" 
AR Path="/609A326D" Ref="#PWR066"  Part="1" 
F 0 "#PWR066" H 12000 2900 50  0001 C CNN
F 1 "GND" H 12005 2977 50  0000 C CNN
F 2 "" H 12000 3150 50  0001 C CNN
F 3 "" H 12000 3150 50  0001 C CNN
	1    12000 3150
	1    0    0    -1  
$EndComp
Wire Wire Line
	12000 3050 12000 3150
Wire Wire Line
	12000 2750 12000 2500
$Comp
L power:+3.3V #PWR?
U 1 1 60A0696E
P 12000 2500
AR Path="/60056272/60A0696E" Ref="#PWR?"  Part="1" 
AR Path="/60A0696E" Ref="#PWR065"  Part="1" 
F 0 "#PWR065" H 12000 2350 50  0001 C CNN
F 1 "+3.3V" H 12015 2673 50  0000 C CNN
F 2 "" H 12000 2500 50  0001 C CNN
F 3 "" H 12000 2500 50  0001 C CNN
	1    12000 2500
	1    0    0    -1  
$EndComp
Wire Wire Line
	11750 3000 11650 3000
Wire Wire Line
	11650 3000 11650 3700
Wire Wire Line
	11650 3700 11000 3700
$Comp
L power:GND #PWR?
U 1 1 60ACC55B
P 10900 3300
AR Path="/601B5445/60ACC55B" Ref="#PWR?"  Part="1" 
AR Path="/60ACC55B" Ref="#PWR060"  Part="1" 
F 0 "#PWR060" H 10900 3050 50  0001 C CNN
F 1 "GND" H 10905 3127 50  0000 C CNN
F 2 "" H 10900 3300 50  0001 C CNN
F 3 "" H 10900 3300 50  0001 C CNN
	1    10900 3300
	1    0    0    -1  
$EndComp
Wire Wire Line
	10900 3300 10900 3250
Wire Wire Line
	10850 3000 10900 3000
Wire Wire Line
	10900 3000 10900 3050
Wire Wire Line
	10850 2700 10900 2700
Wire Wire Line
	10900 2700 10900 3000
Connection ~ 10900 3000
Wire Wire Line
	11750 2800 11400 2800
Wire Wire Line
	11400 2800 11400 2700
Wire Wire Line
	11400 2700 11200 2700
Connection ~ 10900 2700
Wire Wire Line
	10650 3000 10550 3000
Wire Wire Line
	10550 3000 10550 2700
Wire Wire Line
	10550 2700 10650 2700
Wire Wire Line
	10550 2700 10550 2450
Connection ~ 10550 2700
$Comp
L power:+3.3V #PWR?
U 1 1 60C387F8
P 10550 2450
AR Path="/60056272/60C387F8" Ref="#PWR?"  Part="1" 
AR Path="/60C387F8" Ref="#PWR057"  Part="1" 
F 0 "#PWR057" H 10550 2300 50  0001 C CNN
F 1 "+3.3V" H 10565 2623 50  0000 C CNN
F 2 "" H 10550 2450 50  0001 C CNN
F 3 "" H 10550 2450 50  0001 C CNN
	1    10550 2450
	1    0    0    -1  
$EndComp
$Comp
L Device:R_Small R87
U 1 1 60C6DD51
P 19700 10000
F 0 "R87" H 19759 10046 50  0000 L CNN
F 1 "10k" H 19759 9955 50  0000 L CNN
F 2 "Resistor_SMD:R_0603_1608Metric" H 19700 10000 50  0001 C CNN
F 3 "~" H 19700 10000 50  0001 C CNN
	1    19700 10000
	1    0    0    -1  
$EndComp
Wire Wire Line
	20150 10950 19450 10950
Wire Wire Line
	20150 11050 19700 11050
Wire Wire Line
	19700 11050 19700 10100
Connection ~ 19450 10950
Wire Wire Line
	19450 10950 17650 10950
Wire Wire Line
	19700 11050 17650 11050
Connection ~ 19700 11050
Wire Wire Line
	20150 10750 20050 10750
Wire Wire Line
	20050 10750 20050 11150
Wire Wire Line
	20050 11150 20150 11150
Wire Wire Line
	20050 11150 20050 11400
Wire Wire Line
	20050 11400 21900 11400
Wire Wire Line
	21900 11400 21900 11150
Wire Wire Line
	21900 11150 21850 11150
Connection ~ 20050 11150
Wire Wire Line
	20050 11400 20050 11450
Connection ~ 20050 11400
Wire Wire Line
	18450 10350 17650 10350
Connection ~ 18450 10350
Wire Wire Line
	18450 10100 18450 10350
Wire Wire Line
	18700 10450 17650 10450
Connection ~ 18700 10450
Wire Wire Line
	18700 10100 18700 10450
Wire Wire Line
	18950 10650 17650 10650
Connection ~ 18950 10650
Wire Wire Line
	18950 10100 18950 10650
Wire Wire Line
	19200 10850 17650 10850
Connection ~ 19200 10850
Wire Wire Line
	19200 10100 19200 10850
Wire Wire Line
	19450 10100 19450 10950
Wire Wire Line
	20150 10850 19200 10850
Wire Wire Line
	20150 10650 18950 10650
Wire Wire Line
	20150 10450 18700 10450
Wire Wire Line
	20150 10350 18450 10350
Wire Wire Line
	20150 10250 18200 10250
$Comp
L Device:R_Small R82
U 1 1 60CA56D7
P 18450 10000
F 0 "R82" H 18509 10046 50  0000 L CNN
F 1 "10k" H 18509 9955 50  0000 L CNN
F 2 "Resistor_SMD:R_0603_1608Metric" H 18450 10000 50  0001 C CNN
F 3 "~" H 18450 10000 50  0001 C CNN
	1    18450 10000
	1    0    0    -1  
$EndComp
$Comp
L Device:R_Small R83
U 1 1 60CA3FB0
P 18700 10000
F 0 "R83" H 18759 10046 50  0000 L CNN
F 1 "10k" H 18759 9955 50  0000 L CNN
F 2 "Resistor_SMD:R_0603_1608Metric" H 18700 10000 50  0001 C CNN
F 3 "~" H 18700 10000 50  0001 C CNN
	1    18700 10000
	1    0    0    -1  
$EndComp
$Comp
L Device:R_Small R84
U 1 1 60C6F176
P 18950 10000
F 0 "R84" H 19009 10046 50  0000 L CNN
F 1 "10k" H 19009 9955 50  0000 L CNN
F 2 "Resistor_SMD:R_0603_1608Metric" H 18950 10000 50  0001 C CNN
F 3 "~" H 18950 10000 50  0001 C CNN
	1    18950 10000
	1    0    0    -1  
$EndComp
$Comp
L Device:R_Small R85
U 1 1 60C6EE1B
P 19200 10000
F 0 "R85" H 19259 10046 50  0000 L CNN
F 1 "10k" H 19259 9955 50  0000 L CNN
F 2 "Resistor_SMD:R_0603_1608Metric" H 19200 10000 50  0001 C CNN
F 3 "~" H 19200 10000 50  0001 C CNN
	1    19200 10000
	1    0    0    -1  
$EndComp
$Comp
L Device:R_Small R86
U 1 1 60C6EA5C
P 19450 10000
F 0 "R86" H 19509 10046 50  0000 L CNN
F 1 "10k" H 19509 9955 50  0000 L CNN
F 2 "Resistor_SMD:R_0603_1608Metric" H 19450 10000 50  0001 C CNN
F 3 "~" H 19450 10000 50  0001 C CNN
	1    19450 10000
	1    0    0    -1  
$EndComp
Wire Wire Line
	20150 10550 20050 10550
Wire Wire Line
	20050 10550 20050 9850
Wire Wire Line
	20050 9850 19700 9850
Wire Wire Line
	18450 9850 18450 9900
Wire Wire Line
	18700 9900 18700 9850
Connection ~ 18700 9850
Wire Wire Line
	18700 9850 18450 9850
Wire Wire Line
	18950 9900 18950 9850
Connection ~ 18950 9850
Wire Wire Line
	18950 9850 18700 9850
Wire Wire Line
	19200 9900 19200 9850
Connection ~ 19200 9850
Wire Wire Line
	19200 9850 18950 9850
Wire Wire Line
	19450 9900 19450 9850
Connection ~ 19450 9850
Wire Wire Line
	19450 9850 19200 9850
Wire Wire Line
	19700 9900 19700 9850
Connection ~ 19700 9850
Wire Wire Line
	19700 9850 19450 9850
$Comp
L power:GND #PWR?
U 1 1 611FEAC2
P 20050 11450
AR Path="/60056272/611FEAC2" Ref="#PWR?"  Part="1" 
AR Path="/611FEAC2" Ref="#PWR0113"  Part="1" 
F 0 "#PWR0113" H 20050 11200 50  0001 C CNN
F 1 "GND" H 20055 11277 50  0000 C CNN
F 2 "" H 20050 11450 50  0001 C CNN
F 3 "" H 20050 11450 50  0001 C CNN
	1    20050 11450
	1    0    0    -1  
$EndComp
$Comp
L power:+3.3V #PWR?
U 1 1 611FEF11
P 20050 9800
AR Path="/60056272/611FEF11" Ref="#PWR?"  Part="1" 
AR Path="/611FEF11" Ref="#PWR0112"  Part="1" 
F 0 "#PWR0112" H 20050 9650 50  0001 C CNN
F 1 "+3.3V" H 20065 9973 50  0000 C CNN
F 2 "" H 20050 9800 50  0001 C CNN
F 3 "" H 20050 9800 50  0001 C CNN
	1    20050 9800
	1    0    0    -1  
$EndComp
Wire Wire Line
	20050 9800 20050 9850
Connection ~ 20050 9850
Text Label 17650 11050 0    50   ~ 0
CARD_DETECT
Text Label 17650 10950 0    50   ~ 0
CARD_D1
Text Label 17650 10850 0    50   ~ 0
CARD_D0
Text Label 17650 10650 0    50   ~ 0
CARD_CLK
Text Label 17650 10450 0    50   ~ 0
CARD_CMD
Text Label 17650 10350 0    50   ~ 0
CARD_D3
Text Label 17650 10250 0    50   ~ 0
CARD_D2
$Comp
L power:+3.3V #PWR?
U 1 1 61282C15
P 19550 11400
AR Path="/60056272/61282C15" Ref="#PWR?"  Part="1" 
AR Path="/61282C15" Ref="#PWR0108"  Part="1" 
F 0 "#PWR0108" H 19550 11250 50  0001 C CNN
F 1 "+3.3V" H 19565 11573 50  0000 C CNN
F 2 "" H 19550 11400 50  0001 C CNN
F 3 "" H 19550 11400 50  0001 C CNN
	1    19550 11400
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR?
U 1 1 6128325C
P 19550 11700
AR Path="/60056272/6128325C" Ref="#PWR?"  Part="1" 
AR Path="/6128325C" Ref="#PWR0109"  Part="1" 
F 0 "#PWR0109" H 19550 11450 50  0001 C CNN
F 1 "GND" H 19555 11527 50  0000 C CNN
F 2 "" H 19550 11700 50  0001 C CNN
F 3 "" H 19550 11700 50  0001 C CNN
	1    19550 11700
	1    0    0    -1  
$EndComp
$Comp
L Device:C_Small C53
U 1 1 61283595
P 19550 11550
F 0 "C53" H 19642 11596 50  0000 L CNN
F 1 "1uF" H 19642 11505 50  0000 L CNN
F 2 "Capacitor_SMD:C_0603_1608Metric" H 19550 11550 50  0001 C CNN
F 3 "~" H 19550 11550 50  0001 C CNN
	1    19550 11550
	1    0    0    -1  
$EndComp
Wire Wire Line
	19550 11450 19550 11400
Wire Wire Line
	19550 11650 19550 11700
Text Label 11000 3700 0    50   ~ 0
AMS_FAULT_MCU
$Comp
L Device:C_Small C35
U 1 1 61488C8D
P 13550 15150
F 0 "C35" H 13642 15196 50  0000 L CNN
F 1 "100nF" H 13642 15105 50  0000 L CNN
F 2 "Capacitor_SMD:C_0603_1608Metric" H 13550 15150 50  0001 C CNN
F 3 "~" H 13550 15150 50  0001 C CNN
	1    13550 15150
	1    0    0    -1  
$EndComp
Wire Wire Line
	13000 15350 13550 15350
Wire Wire Line
	13550 15350 13550 15250
Connection ~ 13000 15350
Wire Wire Line
	13000 15350 13000 15400
Wire Wire Line
	13550 15050 13550 14950
Wire Wire Line
	13550 14950 13350 14950
Connection ~ 13350 14950
Wire Wire Line
	13350 14950 13350 14400
$Comp
L Device:C_Small C34
U 1 1 61542E1C
P 13550 13350
F 0 "C34" H 13642 13396 50  0000 L CNN
F 1 "100nF" H 13642 13305 50  0000 L CNN
F 2 "Capacitor_SMD:C_0603_1608Metric" H 13550 13350 50  0001 C CNN
F 3 "~" H 13550 13350 50  0001 C CNN
	1    13550 13350
	1    0    0    -1  
$EndComp
Wire Wire Line
	13000 13500 13550 13500
Wire Wire Line
	13550 13500 13550 13450
Connection ~ 13000 13500
Wire Wire Line
	13000 13500 13000 13550
Wire Wire Line
	13550 13250 13550 13150
Wire Wire Line
	13550 13150 13350 13150
Connection ~ 13350 13150
Wire Wire Line
	13350 13150 13350 12600
$Comp
L Device:R_Small R80
U 1 1 616045A6
P 18200 10000
F 0 "R80" H 18259 10046 50  0000 L CNN
F 1 "10k" H 18259 9955 50  0000 L CNN
F 2 "Resistor_SMD:R_0603_1608Metric" H 18200 10000 50  0001 C CNN
F 3 "~" H 18200 10000 50  0001 C CNN
	1    18200 10000
	1    0    0    -1  
$EndComp
Wire Wire Line
	18450 9850 18200 9850
Wire Wire Line
	18200 9850 18200 9900
Connection ~ 18450 9850
Wire Wire Line
	18200 10100 18200 10250
Connection ~ 18200 10250
Wire Wire Line
	18200 10250 17650 10250
$Comp
L Device:Fuse_Small F1
U 1 1 616CAB60
P 1250 950
F 0 "F1" V 1204 998 50  0000 L CNN
F 1 "0.5A" V 1295 998 50  0000 L CNN
F 2 "Fuse:Fuse_1206_3216Metric" H 1250 950 50  0001 C CNN
F 3 "~" H 1250 950 50  0001 C CNN
	1    1250 950 
	0    1    1    0   
$EndComp
Wire Wire Line
	1250 850  1250 800 
$Comp
L Device:D_TVS D4
U 1 1 616CCF04
P 14700 15100
F 0 "D4" V 14654 15179 50  0000 L CNN
F 1 "D_TVS 5V" V 14745 15179 50  0000 L CNN
F 2 "Diode_SMD:D_SMA" H 14700 15100 50  0001 C CNN
F 3 "~" H 14700 15100 50  0001 C CNN
	1    14700 15100
	0    1    1    0   
$EndComp
Wire Wire Line
	14700 14950 14700 14850
Wire Wire Line
	14700 14850 15000 14850
Wire Wire Line
	15200 14850 15300 14850
Wire Wire Line
	15300 15000 15300 14850
Connection ~ 15300 14850
Wire Wire Line
	15300 14850 15700 14850
Wire Wire Line
	15700 15000 15700 14850
Wire Wire Line
	15300 15200 15300 15350
Wire Wire Line
	15300 15350 15700 15350
Wire Wire Line
	15700 15350 15700 15200
Wire Wire Line
	15300 15350 14700 15350
Wire Wire Line
	14700 15350 14700 15250
Connection ~ 15300 15350
$Comp
L power:GND #PWR?
U 1 1 6195AEBA
P 15700 15400
AR Path="/60056272/6195AEBA" Ref="#PWR?"  Part="1" 
AR Path="/6195AEBA" Ref="#PWR083"  Part="1" 
F 0 "#PWR083" H 15700 15150 50  0001 C CNN
F 1 "GND" H 15705 15227 50  0000 C CNN
F 2 "" H 15700 15400 50  0001 C CNN
F 3 "" H 15700 15400 50  0001 C CNN
	1    15700 15400
	1    0    0    -1  
$EndComp
Wire Wire Line
	15700 15350 15700 15400
Connection ~ 15700 15350
$Comp
L Device:D_TVS D1
U 1 1 61B720CB
P 2150 12400
F 0 "D1" V 2104 12479 50  0000 L CNN
F 1 "D_TVS 30V" V 2195 12479 50  0000 L CNN
F 2 "Diode_SMD:D_SMA" H 2150 12400 50  0001 C CNN
F 3 "~" H 2150 12400 50  0001 C CNN
	1    2150 12400
	0    1    1    0   
$EndComp
Wire Wire Line
	2550 12100 2150 12100
Wire Wire Line
	2150 12250 2150 12100
Connection ~ 2150 12100
Wire Wire Line
	2150 12100 2000 12100
Wire Wire Line
	2550 12700 2150 12700
Wire Wire Line
	2150 12700 2150 12550
$Comp
L Device:Fuse_Small F2
U 1 1 61C8C6EF
P 1900 12100
F 0 "F2" H 1900 11915 50  0000 C CNN
F 1 "1A" H 1900 12006 50  0000 C CNN
F 2 "Fuse:Fuse_1206_3216Metric" H 1900 12100 50  0001 C CNN
F 3 "~" H 1900 12100 50  0001 C CNN
	1    1900 12100
	-1   0    0    1   
$EndComp
Connection ~ 2150 12700
$Comp
L Connector_Generic:Conn_01x02 J1
U 1 1 61D1934C
P 1250 12100
F 0 "J1" H 1330 12092 50  0000 L CNN
F 1 "PWR" H 1330 12001 50  0000 L CNN
F 2 "TerminalBlock_MetzConnect:TerminalBlock_MetzConnect_Type086_RT03402HBLC_1x02_P3.81mm_Horizontal" H 1250 12100 50  0001 C CNN
F 3 "~" H 1250 12100 50  0001 C CNN
	1    1250 12100
	-1   0    0    -1  
$EndComp
Wire Wire Line
	1800 12100 1450 12100
Wire Wire Line
	1450 12200 1500 12200
Wire Wire Line
	1500 12200 1500 12700
Wire Wire Line
	1500 12700 2150 12700
Wire Wire Line
	2650 2350 2800 2350
Wire Wire Line
	2650 2350 2650 2450
$Comp
L power:GND #PWR010
U 1 1 6226D17C
P 2650 2450
F 0 "#PWR010" H 2650 2200 50  0001 C CNN
F 1 "GND" H 2655 2277 50  0000 C CNN
F 2 "" H 2650 2450 50  0001 C CNN
F 3 "" H 2650 2450 50  0001 C CNN
	1    2650 2450
	1    0    0    -1  
$EndComp
Wire Wire Line
	2800 2250 2300 2250
Wire Wire Line
	2800 2150 2300 2150
Wire Wire Line
	2800 2050 2300 2050
Text Notes 4650 700  0    50   ~ 0
AIRs
Text Label 1600 6750 2    50   ~ 0
HV_CAR_VOLTAGE
$Comp
L Device:R R?
U 1 1 60985894
P 2300 6750
AR Path="/600380E4/60985894" Ref="R?"  Part="1" 
AR Path="/60985894" Ref="R4"  Part="1" 
F 0 "R4" V 2093 6750 50  0000 C CNN
F 1 "200k" V 2184 6750 50  0000 C CNN
F 2 "Resistor_SMD:R_1206_3216Metric" V 2230 6750 50  0001 C CNN
F 3 "~" H 2300 6750 50  0001 C CNN
	1    2300 6750
	0    1    1    0   
$EndComp
$Comp
L Device:R R?
U 1 1 6098588E
P 1950 6750
AR Path="/600380E4/6098588E" Ref="R?"  Part="1" 
AR Path="/6098588E" Ref="R2"  Part="1" 
F 0 "R2" V 1743 6750 50  0000 C CNN
F 1 "200k" V 1834 6750 50  0000 C CNN
F 2 "Resistor_SMD:R_1206_3216Metric" V 1880 6750 50  0001 C CNN
F 3 "~" H 1950 6750 50  0001 C CNN
	1    1950 6750
	0    1    1    0   
$EndComp
Wire Wire Line
	18100 13250 18100 13200
Connection ~ 18100 13200
Wire Wire Line
	18100 13200 18150 13200
$Comp
L Isolator:PC817 U8
U 1 1 60995F3F
P 8900 11900
F 0 "U8" H 8900 12225 50  0000 C CNN
F 1 "PC817" H 8900 12134 50  0000 C CNN
F 2 "Package_DIP:DIP-4_W7.62mm" H 8700 11700 50  0001 L CIN
F 3 "http://www.soselectronic.cz/a_info/resource/d/pc817.pdf" H 8900 11900 50  0001 L CNN
	1    8900 11900
	1    0    0    -1  
$EndComp
$Comp
L Isolator:PC817 U9
U 1 1 6099841A
P 8900 12450
F 0 "U9" H 8900 12775 50  0000 C CNN
F 1 "PC817" H 8900 12684 50  0000 C CNN
F 2 "Package_DIP:DIP-4_W7.62mm" H 8700 12250 50  0001 L CIN
F 3 "http://www.soselectronic.cz/a_info/resource/d/pc817.pdf" H 8900 12450 50  0001 L CNN
	1    8900 12450
	1    0    0    -1  
$EndComp
$Comp
L Device:R R31
U 1 1 60999DE0
P 8300 11800
F 0 "R31" V 8093 11800 50  0000 C CNN
F 1 "3.3k" V 8184 11800 50  0000 C CNN
F 2 "Resistor_SMD:R_0603_1608Metric" V 8230 11800 50  0001 C CNN
F 3 "~" H 8300 11800 50  0001 C CNN
	1    8300 11800
	0    1    1    0   
$EndComp
Wire Wire Line
	8600 11800 8450 11800
Wire Wire Line
	8600 12000 8500 12000
$Comp
L power:GND #PWR?
U 1 1 60A31724
P 8500 13700
AR Path="/601B5445/60A31724" Ref="#PWR?"  Part="1" 
AR Path="/60A31724" Ref="#PWR048"  Part="1" 
F 0 "#PWR048" H 8500 13450 50  0001 C CNN
F 1 "GND" H 8505 13527 50  0000 C CNN
F 2 "" H 8500 13700 50  0001 C CNN
F 3 "" H 8500 13700 50  0001 C CNN
	1    8500 13700
	1    0    0    -1  
$EndComp
Wire Wire Line
	8600 12550 8500 12550
Wire Wire Line
	8500 12550 8500 13100
Connection ~ 8500 12550
Wire Wire Line
	8500 12000 8500 12550
Wire Wire Line
	8600 12350 8450 12350
$Comp
L Device:R R32
U 1 1 60B63821
P 8300 12350
F 0 "R32" V 8093 12350 50  0000 C CNN
F 1 "3.3k" V 8184 12350 50  0000 C CNN
F 2 "Resistor_SMD:R_0603_1608Metric" V 8230 12350 50  0001 C CNN
F 3 "~" H 8300 12350 50  0001 C CNN
	1    8300 12350
	0    1    1    0   
$EndComp
Wire Wire Line
	8150 11800 8050 11800
Wire Wire Line
	8150 12350 8050 12350
Text Label 8050 11800 2    50   ~ 0
DIN_1
Text Label 8050 12350 2    50   ~ 0
DIN_2
Text Label 9750 11800 0    50   ~ 0
DIN_1_MCU
$Comp
L Device:R R40
U 1 1 60C01C32
P 9300 11550
F 0 "R40" H 9230 11504 50  0000 R CNN
F 1 "10k" H 9230 11595 50  0000 R CNN
F 2 "Resistor_SMD:R_0603_1608Metric" V 9230 11550 50  0001 C CNN
F 3 "~" H 9300 11550 50  0001 C CNN
	1    9300 11550
	-1   0    0    1   
$EndComp
$Comp
L Device:R R45
U 1 1 60C027AF
P 9600 11550
F 0 "R45" H 9530 11504 50  0000 R CNN
F 1 "10k" H 9530 11595 50  0000 R CNN
F 2 "Resistor_SMD:R_0603_1608Metric" V 9530 11550 50  0001 C CNN
F 3 "~" H 9600 11550 50  0001 C CNN
	1    9600 11550
	-1   0    0    1   
$EndComp
Wire Wire Line
	9750 11800 9300 11800
Connection ~ 9300 11800
Wire Wire Line
	9300 11800 9200 11800
Wire Wire Line
	9300 11700 9300 11800
Wire Wire Line
	9600 11700 9600 12350
Wire Wire Line
	9600 12350 9200 12350
Wire Wire Line
	9200 12000 9300 12000
Wire Wire Line
	9300 12000 9300 12550
Wire Wire Line
	9200 12550 9300 12550
Connection ~ 9300 12550
Wire Wire Line
	9300 12550 9300 13100
$Comp
L power:GND #PWR?
U 1 1 60E1EE6D
P 9300 13700
AR Path="/601B5445/60E1EE6D" Ref="#PWR?"  Part="1" 
AR Path="/60E1EE6D" Ref="#PWR052"  Part="1" 
F 0 "#PWR052" H 9300 13450 50  0001 C CNN
F 1 "GND" H 9305 13527 50  0000 C CNN
F 2 "" H 9300 13700 50  0001 C CNN
F 3 "" H 9300 13700 50  0001 C CNN
	1    9300 13700
	1    0    0    -1  
$EndComp
Wire Wire Line
	9600 12350 9750 12350
Connection ~ 9600 12350
Text Label 9750 12350 0    50   ~ 0
DIN_2_MCU
Text Label 6800 12150 0    50   ~ 0
DIN_1
$Comp
L power:+3.3V #PWR?
U 1 1 610F9BFE
P 9450 11300
AR Path="/60056272/610F9BFE" Ref="#PWR?"  Part="1" 
AR Path="/610F9BFE" Ref="#PWR053"  Part="1" 
F 0 "#PWR053" H 9450 11150 50  0001 C CNN
F 1 "+3.3V" H 9465 11473 50  0000 C CNN
F 2 "" H 9450 11300 50  0001 C CNN
F 3 "" H 9450 11300 50  0001 C CNN
	1    9450 11300
	1    0    0    -1  
$EndComp
Wire Wire Line
	9300 11400 9300 11350
Wire Wire Line
	9300 11350 9450 11350
Wire Wire Line
	9600 11350 9600 11400
Wire Wire Line
	9450 11350 9450 11300
Connection ~ 9450 11350
Wire Wire Line
	9450 11350 9600 11350
Text Label 19000 6750 0    50   ~ 0
DIN_1_MCU
Text Label 19000 6650 0    50   ~ 0
DIN_2_MCU
Text Label 19000 5350 0    50   ~ 0
CARD_DETECT
Text Label 17600 7050 2    50   ~ 0
CARD_D1
Text Label 17600 6950 2    50   ~ 0
CARD_D0
Text Label 17600 7350 2    50   ~ 0
CARD_CLK
Text Label 17600 5950 2    50   ~ 0
CARD_CMD
Text Label 17600 7250 2    50   ~ 0
CARD_D3
Text Label 17600 7150 2    50   ~ 0
CARD_D2
Text Label 16850 4400 0    50   ~ 0
NRST
$Comp
L Isolator:PC817 U10
U 1 1 61430ACF
P 8900 13000
F 0 "U10" H 8900 13325 50  0000 C CNN
F 1 "PC817" H 8900 13234 50  0000 C CNN
F 2 "Package_DIP:DIP-4_W7.62mm" H 8700 12800 50  0001 L CIN
F 3 "http://www.soselectronic.cz/a_info/resource/d/pc817.pdf" H 8900 13000 50  0001 L CNN
	1    8900 13000
	1    0    0    -1  
$EndComp
$Comp
L Device:R R33
U 1 1 615760ED
P 8300 12900
F 0 "R33" V 8093 12900 50  0000 C CNN
F 1 "3.3k" V 8184 12900 50  0000 C CNN
F 2 "Resistor_SMD:R_0603_1608Metric" V 8230 12900 50  0001 C CNN
F 3 "~" H 8300 12900 50  0001 C CNN
	1    8300 12900
	0    1    1    0   
$EndComp
Wire Wire Line
	8600 12900 8450 12900
Wire Wire Line
	8150 12900 8050 12900
Wire Wire Line
	8600 13100 8500 13100
Connection ~ 8500 13100
Wire Wire Line
	8500 13100 8500 13650
Wire Wire Line
	9200 13100 9300 13100
Connection ~ 9300 13100
Wire Wire Line
	9300 13100 9300 13650
Wire Wire Line
	9200 12900 9750 12900
Text Label 9750 12900 0    50   ~ 0
NRST
$Comp
L Connector_Generic:Conn_01x04 J9
U 1 1 61810303
P 6600 12350
F 0 "J9" H 6518 11925 50  0000 C CNN
F 1 "Conn_01x04" H 6518 12016 50  0000 C CNN
F 2 "TerminalBlock_MetzConnect:TerminalBlock_MetzConnect_Type086_RT03404HBLC_1x04_P3.81mm_Horizontal" H 6600 12350 50  0001 C CNN
F 3 "~" H 6600 12350 50  0001 C CNN
	1    6600 12350
	-1   0    0    1   
$EndComp
Text Label 6800 12250 0    50   ~ 0
DIN_2
Text Label 8050 12900 2    50   ~ 0
EXT_RESET
Text Label 6800 12450 0    50   ~ 0
EXT_RESET
$Comp
L PUTM_EV_BMS_library:HX1188NL T1
U 1 1 61A0F174
P 12750 10550
F 0 "T1" H 12675 11175 50  0000 C CNN
F 1 "HX1188NL" H 12675 11084 50  0000 C CNN
F 2 "Transformer_SMD:Transformer_Pulse_H1100NL" H 12750 11450 50  0001 C CNN
F 3 "" H 12750 11450 50  0001 C CNN
	1    12750 10550
	1    0    0    -1  
$EndComp
$Comp
L Device:R_Small R65
U 1 1 61B74ADC
P 13100 11050
F 0 "R65" H 13041 11004 50  0000 R CNN
F 1 "10M" H 13041 11095 50  0000 R CNN
F 2 "Resistor_SMD:R_0603_1608Metric" H 13100 11050 50  0001 C CNN
F 3 "~" H 13100 11050 50  0001 C CNN
	1    13100 11050
	-1   0    0    1   
$EndComp
$Comp
L Device:R_Small R66
U 1 1 6273F9D3
P 13400 11050
F 0 "R66" H 13341 11004 50  0000 R CNN
F 1 "10M" H 13341 11095 50  0000 R CNN
F 2 "Resistor_SMD:R_0603_1608Metric" H 13400 11050 50  0001 C CNN
F 3 "~" H 13400 11050 50  0001 C CNN
	1    13400 11050
	-1   0    0    1   
$EndComp
Wire Wire Line
	13050 10750 13100 10750
Wire Wire Line
	13100 10750 13100 10950
Wire Wire Line
	13050 10300 13400 10300
Wire Wire Line
	13400 10300 13400 10950
Wire Wire Line
	13400 11150 13400 11200
Wire Wire Line
	13400 11200 13100 11200
Wire Wire Line
	13100 11200 13100 11150
Wire Wire Line
	13100 11200 12200 11200
Connection ~ 13100 11200
Wire Wire Line
	13700 10150 13050 10150
Wire Wire Line
	13700 10250 13550 10250
Wire Wire Line
	13550 10250 13550 10450
Wire Wire Line
	13550 10450 13050 10450
$Comp
L Connector_Generic:Conn_01x03 J13
U 1 1 629ED198
P 13900 10700
F 0 "J13" H 13980 10742 50  0000 L CNN
F 1 "Conn_01x03" H 13980 10651 50  0000 L CNN
F 2 "Connector_Molex:Molex_Micro-Fit_3.0_43650-0315_1x03_P3.00mm_Vertical" H 13900 10700 50  0001 C CNN
F 3 "~" H 13900 10700 50  0001 C CNN
	1    13900 10700
	1    0    0    1   
$EndComp
Wire Wire Line
	13700 10600 13050 10600
Wire Wire Line
	13050 10900 13550 10900
Wire Wire Line
	13550 10900 13550 10700
Wire Wire Line
	13550 10700 13700 10700
$Comp
L Device:R_Small R53
U 1 1 62BA3F0D
P 11450 10050
F 0 "R53" H 11391 10004 50  0000 R CNN
F 1 "49.9R" H 11391 10095 50  0000 R CNN
F 2 "Resistor_SMD:R_0603_1608Metric" H 11450 10050 50  0001 C CNN
F 3 "~" H 11450 10050 50  0001 C CNN
	1    11450 10050
	-1   0    0    1   
$EndComp
$Comp
L Device:R_Small R54
U 1 1 62BA5D0E
P 11450 10350
F 0 "R54" H 11391 10304 50  0000 R CNN
F 1 "49.9R" H 11391 10395 50  0000 R CNN
F 2 "Resistor_SMD:R_0603_1608Metric" H 11450 10350 50  0001 C CNN
F 3 "~" H 11450 10350 50  0001 C CNN
	1    11450 10350
	-1   0    0    1   
$EndComp
$Comp
L Device:R_Small R55
U 1 1 62C55B98
P 11450 10700
F 0 "R55" H 11391 10654 50  0000 R CNN
F 1 "49.9R" H 11391 10745 50  0000 R CNN
F 2 "Resistor_SMD:R_0603_1608Metric" H 11450 10700 50  0001 C CNN
F 3 "~" H 11450 10700 50  0001 C CNN
	1    11450 10700
	-1   0    0    1   
$EndComp
$Comp
L Device:R_Small R56
U 1 1 62C55B9E
P 11450 11000
F 0 "R56" H 11391 10954 50  0000 R CNN
F 1 "49.9R" H 11391 11045 50  0000 R CNN
F 2 "Resistor_SMD:R_0603_1608Metric" H 11450 11000 50  0001 C CNN
F 3 "~" H 11450 11000 50  0001 C CNN
	1    11450 11000
	-1   0    0    1   
$EndComp
Wire Wire Line
	11950 10450 11950 10500
Wire Wire Line
	11950 10500 11450 10500
Wire Wire Line
	11950 10450 12300 10450
Wire Wire Line
	11450 10450 11450 10500
Wire Wire Line
	11450 10150 11450 10200
Wire Wire Line
	11450 10800 11450 10850
$Comp
L Device:C_Small C29
U 1 1 630E0DE0
P 12200 11050
F 0 "C29" H 12292 11096 50  0000 L CNN
F 1 "10nF" H 12292 11005 50  0000 L CNN
F 2 "Capacitor_SMD:C_0603_1608Metric" H 12200 11050 50  0001 C CNN
F 3 "~" H 12200 11050 50  0001 C CNN
	1    12200 11050
	1    0    0    -1  
$EndComp
$Comp
L Device:C_Small C28
U 1 1 630E1E88
P 11850 11050
F 0 "C28" H 11942 11096 50  0000 L CNN
F 1 "10nF" H 11942 11005 50  0000 L CNN
F 2 "Capacitor_SMD:C_0603_1608Metric" H 11850 11050 50  0001 C CNN
F 3 "~" H 11850 11050 50  0001 C CNN
	1    11850 11050
	1    0    0    -1  
$EndComp
Wire Wire Line
	12300 10750 12200 10750
Wire Wire Line
	12200 10750 12200 10950
Wire Wire Line
	12200 11150 12200 11200
Connection ~ 12200 11200
Wire Wire Line
	12300 10300 11850 10300
Wire Wire Line
	11850 10300 11850 10950
Wire Wire Line
	11850 11200 11850 11150
Wire Wire Line
	11850 11200 12200 11200
Wire Wire Line
	12300 10600 11950 10600
Wire Wire Line
	11950 10600 11950 10550
Wire Wire Line
	11950 10550 11450 10550
Wire Wire Line
	11450 10550 11450 10600
Wire Wire Line
	11750 10150 11750 9900
Wire Wire Line
	11750 9900 11450 9900
Wire Wire Line
	11750 10150 12300 10150
Wire Wire Line
	11450 9950 11450 9900
Wire Wire Line
	12300 10900 11750 10900
Wire Wire Line
	11750 10900 11750 11150
Wire Wire Line
	11750 11150 11450 11150
Wire Wire Line
	11450 11100 11450 11150
$Comp
L Device:C_Small C27
U 1 1 634ED527
P 11350 11350
F 0 "C27" H 11442 11396 50  0000 L CNN
F 1 "10nF" H 11442 11305 50  0000 L CNN
F 2 "Capacitor_SMD:C_0603_1608Metric" H 11350 11350 50  0001 C CNN
F 3 "~" H 11350 11350 50  0001 C CNN
	1    11350 11350
	1    0    0    -1  
$EndComp
$Comp
L Device:C_Small C24
U 1 1 637927F0
P 11000 11350
F 0 "C24" H 11092 11396 50  0000 L CNN
F 1 "10nF" H 11092 11305 50  0000 L CNN
F 2 "Capacitor_SMD:C_0603_1608Metric" H 11000 11350 50  0001 C CNN
F 3 "~" H 11000 11350 50  0001 C CNN
	1    11000 11350
	1    0    0    -1  
$EndComp
Wire Wire Line
	11350 11250 11350 10850
Wire Wire Line
	11350 10850 11450 10850
Connection ~ 11450 10850
Wire Wire Line
	11450 10850 11450 10900
Wire Wire Line
	11450 10200 11000 10200
Wire Wire Line
	11000 10200 11000 11250
Connection ~ 11450 10200
Wire Wire Line
	11450 10200 11450 10250
Wire Wire Line
	11000 11450 11000 11550
Wire Wire Line
	11000 11550 11350 11550
Wire Wire Line
	11350 11550 11350 11450
Wire Wire Line
	11350 11550 11350 11600
Connection ~ 11350 11550
$Comp
L power:GND #PWR?
U 1 1 6391C1EE
P 11350 11600
AR Path="/601B5445/6391C1EE" Ref="#PWR?"  Part="1" 
AR Path="/6391C1EE" Ref="#PWR061"  Part="1" 
F 0 "#PWR061" H 11350 11350 50  0001 C CNN
F 1 "GND" H 11355 11427 50  0000 C CNN
F 2 "" H 11350 11600 50  0001 C CNN
F 3 "" H 11350 11600 50  0001 C CNN
	1    11350 11600
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR?
U 1 1 6391CDE2
P 11850 11300
AR Path="/601B5445/6391CDE2" Ref="#PWR?"  Part="1" 
AR Path="/6391CDE2" Ref="#PWR063"  Part="1" 
F 0 "#PWR063" H 11850 11050 50  0001 C CNN
F 1 "GND" H 11855 11127 50  0000 C CNN
F 2 "" H 11850 11300 50  0001 C CNN
F 3 "" H 11850 11300 50  0001 C CNN
	1    11850 11300
	1    0    0    -1  
$EndComp
Wire Wire Line
	11850 11300 11850 11200
Connection ~ 11850 11200
Wire Wire Line
	11450 11150 10900 11150
Wire Wire Line
	10900 11150 10900 10900
Wire Wire Line
	10900 10900 10800 10900
Connection ~ 11450 11150
Wire Wire Line
	11450 10550 10900 10550
Wire Wire Line
	10900 10550 10900 10800
Connection ~ 11450 10550
Wire Wire Line
	10900 10800 10800 10800
Wire Wire Line
	11450 10500 10900 10500
Wire Wire Line
	10900 10500 10900 10250
Wire Wire Line
	10900 10250 10800 10250
Connection ~ 11450 10500
Wire Wire Line
	11450 9900 10900 9900
Wire Wire Line
	10900 9900 10900 10150
Wire Wire Line
	10900 10150 10800 10150
Connection ~ 11450 9900
Text Label 10800 10250 2    50   ~ 0
LTC_1_IM
Text Label 10800 10150 2    50   ~ 0
LTC_1_IP
Text Label 10800 10900 2    50   ~ 0
LTC_2_IM
Text Label 10800 10800 2    50   ~ 0
LTC_2_IP
$Comp
L Connector_Generic:Conn_01x04 J6
U 1 1 63EB3963
P 2850 1200
F 0 "J6" H 2768 775 50  0000 C CNN
F 1 "Conn_01x04" H 2768 866 50  0000 C CNN
F 2 "TerminalBlock_MetzConnect:TerminalBlock_MetzConnect_Type086_RT03404HBLC_1x04_P3.81mm_Horizontal" H 2850 1200 50  0001 C CNN
F 3 "~" H 2850 1200 50  0001 C CNN
	1    2850 1200
	-1   0    0    1   
$EndComp
Text Label 3050 1000 0    50   ~ 0
SAFETY_AIR
$Comp
L Device:CP_Small C10
U 1 1 63F1D4C9
P 4650 1150
F 0 "C10" H 4738 1196 50  0000 L CNN
F 1 "100uF/35V" H 4738 1105 50  0000 L CNN
F 2 "Capacitor_SMD:CP_Elec_8x10" H 4650 1150 50  0001 C CNN
F 3 "~" H 4650 1150 50  0001 C CNN
	1    4650 1150
	1    0    0    -1  
$EndComp
Text Label 4550 1000 2    50   ~ 0
SAFETY_AIR
Wire Wire Line
	4550 1000 4650 1000
Wire Wire Line
	4650 1000 4650 1050
Wire Wire Line
	4650 1250 4650 1300
$Comp
L power:GND #PWR024
U 1 1 63FEF9D5
P 4650 1300
F 0 "#PWR024" H 4650 1050 50  0001 C CNN
F 1 "GND" H 4655 1127 50  0000 C CNN
F 2 "" H 4650 1300 50  0001 C CNN
F 3 "" H 4650 1300 50  0001 C CNN
	1    4650 1300
	1    0    0    -1  
$EndComp
$Comp
L PUTM_EV_BMS_library:ALDP105W K1
U 1 1 6413995F
P 6550 1300
F 0 "K1" H 6550 1867 50  0000 C CNN
F 1 "ALDP105W" H 6550 1776 50  0000 C CNN
F 2 "RELAY_ALDP105W" H 6550 1300 50  0001 L BNN
F 3 "" H 6550 1300 50  0001 L BNN
F 4 "Manufacturer Recommendations" H 6550 1300 50  0001 L BNN "STANDART"
F 5 "Panasonic" H 6550 1300 50  0001 L BNN "MF"
F 6 "N/A" H 6550 1300 50  0001 L BNN "PARTREV"
	1    6550 1300
	1    0    0    -1  
$EndComp
$Comp
L PUTM_EV_BMS_library:ALDP105W K2
U 1 1 642126C4
P 8150 1300
F 0 "K2" H 8150 1867 50  0000 C CNN
F 1 "ALDP105W" H 8150 1776 50  0000 C CNN
F 2 "RELAY_ALDP105W" H 8150 1300 50  0001 L BNN
F 3 "" H 8150 1300 50  0001 L BNN
F 4 "Manufacturer Recommendations" H 8150 1300 50  0001 L BNN "STANDART"
F 5 "Panasonic" H 8150 1300 50  0001 L BNN "MF"
F 6 "N/A" H 8150 1300 50  0001 L BNN "PARTREV"
	1    8150 1300
	1    0    0    -1  
$EndComp
$Comp
L power:+5V #PWR?
U 1 1 642E3F1A
P 6100 750
AR Path="/601B5445/642E3F1A" Ref="#PWR?"  Part="1" 
AR Path="/642E3F1A" Ref="#PWR035"  Part="1" 
F 0 "#PWR035" H 6100 600 50  0001 C CNN
F 1 "+5V" H 6115 923 50  0000 C CNN
F 2 "" H 6100 750 50  0001 C CNN
F 3 "" H 6100 750 50  0001 C CNN
	1    6100 750 
	1    0    0    -1  
$EndComp
$Comp
L power:+5V #PWR?
U 1 1 642E4973
P 7700 750
AR Path="/601B5445/642E4973" Ref="#PWR?"  Part="1" 
AR Path="/642E4973" Ref="#PWR044"  Part="1" 
F 0 "#PWR044" H 7700 600 50  0001 C CNN
F 1 "+5V" H 7715 923 50  0000 C CNN
F 2 "" H 7700 750 50  0001 C CNN
F 3 "" H 7700 750 50  0001 C CNN
	1    7700 750 
	1    0    0    -1  
$EndComp
Wire Wire Line
	7750 1000 7700 1000
Wire Wire Line
	7700 1000 7700 750 
Wire Wire Line
	6150 1000 6100 1000
Wire Wire Line
	6100 1000 6100 750 
Text Label 7000 900  1    50   ~ 0
SAFETY_AIR
Wire Wire Line
	6950 1000 7000 1000
Wire Wire Line
	7000 1000 7000 900 
Text Label 8600 900  1    50   ~ 0
SAFETY_AIR
Wire Wire Line
	8550 1000 8600 1000
Wire Wire Line
	8600 1000 8600 900 
$Comp
L Device:R_Small R43
U 1 1 64785BC2
P 9500 2350
F 0 "R43" H 9559 2396 50  0000 L CNN
F 1 "10k" H 9559 2305 50  0000 L CNN
F 2 "Resistor_SMD:R_0603_1608Metric" H 9500 2350 50  0001 C CNN
F 3 "~" H 9500 2350 50  0001 C CNN
	1    9500 2350
	1    0    0    -1  
$EndComp
$Comp
L Device:R_Small R39
U 1 1 64785BC8
P 9250 2150
F 0 "R39" V 9054 2150 50  0000 C CNN
F 1 "100" V 9145 2150 50  0000 C CNN
F 2 "Resistor_SMD:R_0603_1608Metric" H 9250 2150 50  0001 C CNN
F 3 "~" H 9250 2150 50  0001 C CNN
	1    9250 2150
	0    1    1    0   
$EndComp
Wire Wire Line
	9600 2150 9500 2150
Wire Wire Line
	9500 2150 9500 2250
Connection ~ 9500 2150
Wire Wire Line
	9500 2150 9350 2150
Wire Wire Line
	9500 2450 9500 2500
$Comp
L Transistor_FET:2N7002 Q2
U 1 1 647F736D
P 8300 2150
F 0 "Q2" H 8504 2196 50  0000 L CNN
F 1 "2N7002" H 8504 2105 50  0000 L CNN
F 2 "Package_TO_SOT_SMD:SOT-23" H 8500 2075 50  0001 L CIN
F 3 "https://www.fairchildsemi.com/datasheets/2N/2N7002.pdf" H 8300 2150 50  0001 L CNN
	1    8300 2150
	1    0    0    -1  
$EndComp
$Comp
L Device:R_Small R30
U 1 1 647F7373
P 8000 2350
F 0 "R30" H 8059 2396 50  0000 L CNN
F 1 "10k" H 8059 2305 50  0000 L CNN
F 2 "Resistor_SMD:R_0603_1608Metric" H 8000 2350 50  0001 C CNN
F 3 "~" H 8000 2350 50  0001 C CNN
	1    8000 2350
	1    0    0    -1  
$EndComp
$Comp
L Device:R_Small R28
U 1 1 647F7379
P 7750 2150
F 0 "R28" V 7554 2150 50  0000 C CNN
F 1 "100" V 7645 2150 50  0000 C CNN
F 2 "Resistor_SMD:R_0603_1608Metric" H 7750 2150 50  0001 C CNN
F 3 "~" H 7750 2150 50  0001 C CNN
	1    7750 2150
	0    1    1    0   
$EndComp
Wire Wire Line
	8100 2150 8000 2150
Wire Wire Line
	8000 2150 8000 2250
Connection ~ 8000 2150
Wire Wire Line
	8000 2150 7850 2150
Wire Wire Line
	8000 2450 8000 2500
Wire Wire Line
	8000 2500 8400 2500
Wire Wire Line
	8400 2500 8400 2350
Wire Wire Line
	8400 2500 8400 2550
Connection ~ 8400 2500
$Comp
L power:GND #PWR?
U 1 1 647F7388
P 8400 2550
AR Path="/601B5445/647F7388" Ref="#PWR?"  Part="1" 
AR Path="/647F7388" Ref="#PWR047"  Part="1" 
F 0 "#PWR047" H 8400 2300 50  0001 C CNN
F 1 "GND" H 8405 2377 50  0000 C CNN
F 2 "" H 8400 2550 50  0001 C CNN
F 3 "" H 8400 2550 50  0001 C CNN
	1    8400 2550
	1    0    0    -1  
$EndComp
$Comp
L Transistor_FET:2N7002 Q1
U 1 1 648E11D1
P 6700 2150
F 0 "Q1" H 6904 2196 50  0000 L CNN
F 1 "2N7002" H 6904 2105 50  0000 L CNN
F 2 "Package_TO_SOT_SMD:SOT-23" H 6900 2075 50  0001 L CIN
F 3 "https://www.fairchildsemi.com/datasheets/2N/2N7002.pdf" H 6700 2150 50  0001 L CNN
	1    6700 2150
	1    0    0    -1  
$EndComp
$Comp
L Device:R_Small R22
U 1 1 648E11D7
P 6400 2350
F 0 "R22" H 6459 2396 50  0000 L CNN
F 1 "10k" H 6459 2305 50  0000 L CNN
F 2 "Resistor_SMD:R_0603_1608Metric" H 6400 2350 50  0001 C CNN
F 3 "~" H 6400 2350 50  0001 C CNN
	1    6400 2350
	1    0    0    -1  
$EndComp
$Comp
L Device:R_Small R17
U 1 1 648E11DD
P 6150 2150
F 0 "R17" V 5954 2150 50  0000 C CNN
F 1 "100" V 6045 2150 50  0000 C CNN
F 2 "Resistor_SMD:R_0603_1608Metric" H 6150 2150 50  0001 C CNN
F 3 "~" H 6150 2150 50  0001 C CNN
	1    6150 2150
	0    1    1    0   
$EndComp
Wire Wire Line
	6500 2150 6400 2150
Wire Wire Line
	6400 2150 6400 2250
Connection ~ 6400 2150
Wire Wire Line
	6400 2150 6250 2150
Wire Wire Line
	6400 2450 6400 2500
Wire Wire Line
	6400 2500 6800 2500
Wire Wire Line
	6800 2500 6800 2350
Wire Wire Line
	6800 2500 6800 2550
Connection ~ 6800 2500
$Comp
L power:GND #PWR?
U 1 1 648E11EC
P 6800 2550
AR Path="/601B5445/648E11EC" Ref="#PWR?"  Part="1" 
AR Path="/648E11EC" Ref="#PWR039"  Part="1" 
F 0 "#PWR039" H 6800 2300 50  0001 C CNN
F 1 "GND" H 6805 2377 50  0000 C CNN
F 2 "" H 6800 2550 50  0001 C CNN
F 3 "" H 6800 2550 50  0001 C CNN
	1    6800 2550
	1    0    0    -1  
$EndComp
Wire Wire Line
	6100 1600 6150 1600
$Comp
L power:GND #PWR?
U 1 1 64785BD7
P 9900 2550
AR Path="/601B5445/64785BD7" Ref="#PWR?"  Part="1" 
AR Path="/64785BD7" Ref="#PWR056"  Part="1" 
F 0 "#PWR056" H 9900 2300 50  0001 C CNN
F 1 "GND" H 9905 2377 50  0000 C CNN
F 2 "" H 9900 2550 50  0001 C CNN
F 3 "" H 9900 2550 50  0001 C CNN
	1    9900 2550
	1    0    0    -1  
$EndComp
Connection ~ 9900 2500
Wire Wire Line
	9900 2500 9900 2550
Wire Wire Line
	9900 2500 9900 2350
Wire Wire Line
	9500 2500 9900 2500
$Comp
L Transistor_FET:2N7002 Q3
U 1 1 64785BBC
P 9800 2150
F 0 "Q3" H 10004 2196 50  0000 L CNN
F 1 "2N7002" H 10004 2105 50  0000 L CNN
F 2 "Package_TO_SOT_SMD:SOT-23" H 10000 2075 50  0001 L CIN
F 3 "https://www.fairchildsemi.com/datasheets/2N/2N7002.pdf" H 9800 2150 50  0001 L CNN
	1    9800 2150
	1    0    0    -1  
$EndComp
Wire Wire Line
	10100 1000 10050 1000
Wire Wire Line
	10100 900  10100 1000
Text Label 10100 900  1    50   ~ 0
SAFETY_AIR
Wire Wire Line
	9200 1000 9200 750 
Wire Wire Line
	9250 1000 9200 1000
$Comp
L power:+5V #PWR?
U 1 1 642E4EA4
P 9200 750
AR Path="/601B5445/642E4EA4" Ref="#PWR?"  Part="1" 
AR Path="/642E4EA4" Ref="#PWR051"  Part="1" 
F 0 "#PWR051" H 9200 600 50  0001 C CNN
F 1 "+5V" H 9215 923 50  0000 C CNN
F 2 "" H 9200 750 50  0001 C CNN
F 3 "" H 9200 750 50  0001 C CNN
	1    9200 750 
	1    0    0    -1  
$EndComp
$Comp
L PUTM_EV_BMS_library:ALDP105W K3
U 1 1 6413F22C
P 9650 1300
F 0 "K3" H 9650 1867 50  0000 C CNN
F 1 "ALDP105W" H 9650 1776 50  0000 C CNN
F 2 "RELAY_ALDP105W" H 9650 1300 50  0001 L BNN
F 3 "" H 9650 1300 50  0001 L BNN
F 4 "Manufacturer Recommendations" H 9650 1300 50  0001 L BNN "STANDART"
F 5 "Panasonic" H 9650 1300 50  0001 L BNN "MF"
F 6 "N/A" H 9650 1300 50  0001 L BNN "PARTREV"
	1    9650 1300
	1    0    0    -1  
$EndComp
Wire Wire Line
	9900 1950 9900 1850
Wire Wire Line
	9900 1850 9200 1850
Wire Wire Line
	9200 1850 9200 1600
Wire Wire Line
	9200 1600 9250 1600
Wire Wire Line
	8400 1950 8400 1850
Wire Wire Line
	8400 1850 7700 1850
Wire Wire Line
	7700 1850 7700 1600
Wire Wire Line
	7700 1600 7750 1600
Wire Wire Line
	6800 1950 6800 1850
Wire Wire Line
	6800 1850 6100 1850
Wire Wire Line
	6100 1850 6100 1600
Text Label 2300 2050 0    50   ~ 0
AIR_P
Text Label 2300 2150 0    50   ~ 0
AIR_M
Text Label 2300 2250 0    50   ~ 0
AIR_PRE
Text Label 6950 1600 0    50   ~ 0
AIR_P
Text Label 8550 1600 0    50   ~ 0
AIR_M
Text Label 10050 1600 0    50   ~ 0
AIR_PRE
Text Label 9150 2150 2    50   ~ 0
S_AIR_PRE
Text Label 7650 2150 2    50   ~ 0
S_AIR_M
Text Label 6050 2150 2    50   ~ 0
S_AIR_P
Text Label 17600 6150 2    50   ~ 0
S_AIR_P
Text Label 17600 6250 2    50   ~ 0
S_AIR_M
Text Label 17600 6350 2    50   ~ 0
S_AIR_PRE
Text Label 8150 4450 0    50   ~ 0
ACU_V_ADC
Text Label 8200 6800 0    50   ~ 0
CAR_V_ADC
Text Label 19000 4850 0    50   ~ 0
CAR_V_ADC
Text Label 19000 4750 0    50   ~ 0
ACU_V_ADC
$Comp
L Connector_Generic:Conn_01x05 J14
U 1 1 6572961A
P 17450 2200
F 0 "J14" H 17530 2242 50  0000 L CNN
F 1 "Conn_01x05" H 17530 2151 50  0000 L CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x05_P2.54mm_Vertical" H 17450 2200 50  0001 C CNN
F 3 "~" H 17450 2200 50  0001 C CNN
	1    17450 2200
	1    0    0    -1  
$EndComp
$Comp
L power:+3.3V #PWR?
U 1 1 6572B80A
P 17200 1900
AR Path="/60056272/6572B80A" Ref="#PWR?"  Part="1" 
AR Path="/6572B80A" Ref="#PWR095"  Part="1" 
F 0 "#PWR095" H 17200 1750 50  0001 C CNN
F 1 "+3.3V" H 17215 2073 50  0000 C CNN
F 2 "" H 17200 1900 50  0001 C CNN
F 3 "" H 17200 1900 50  0001 C CNN
	1    17200 1900
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR?
U 1 1 6572C06B
P 17200 2550
AR Path="/60056272/6572C06B" Ref="#PWR?"  Part="1" 
AR Path="/6572C06B" Ref="#PWR096"  Part="1" 
F 0 "#PWR096" H 17200 2300 50  0001 C CNN
F 1 "GND" H 17205 2377 50  0000 C CNN
F 2 "" H 17200 2550 50  0001 C CNN
F 3 "" H 17200 2550 50  0001 C CNN
	1    17200 2550
	1    0    0    -1  
$EndComp
Wire Wire Line
	17250 2200 17200 2200
Wire Wire Line
	17200 2200 17200 2550
Wire Wire Line
	17250 2000 17200 2000
Wire Wire Line
	17200 2000 17200 1900
Wire Wire Line
	17250 2100 17150 2100
Wire Wire Line
	17250 2300 17150 2300
Wire Wire Line
	17250 2400 17150 2400
Text Label 17150 2100 2    50   ~ 0
SWCLK
Text Label 17150 2300 2    50   ~ 0
SWDIO
Text Label 17150 2400 2    50   ~ 0
NRST
$Comp
L PUTM_EV_BMS_library:USB_GND #PWR?
U 1 1 65D8E92E
P 12050 9150
AR Path="/601B5445/65D8E92E" Ref="#PWR?"  Part="1" 
AR Path="/65D8E92E" Ref="#PWR067"  Part="1" 
F 0 "#PWR067" H 12050 8900 50  0001 C CNN
F 1 "USB_GND" H 12055 8977 50  0000 C CNN
F 2 "" H 12050 9150 50  0001 C CNN
F 3 "" H 12050 9150 50  0001 C CNN
	1    12050 9150
	1    0    0    -1  
$EndComp
Wire Wire Line
	11950 9050 11950 9100
Wire Wire Line
	11950 9100 12050 9100
Wire Wire Line
	12150 9100 12150 9050
Wire Wire Line
	12050 9100 12050 9150
Connection ~ 12050 9100
Wire Wire Line
	12050 9100 12150 9100
$Comp
L PUTM_EV_BMS_library:USB_+5V #PWR064
U 1 1 6610D9DA
P 11950 7450
F 0 "#PWR064" H 11950 7300 50  0001 C CNN
F 1 "USB_+5V" H 11965 7623 50  0000 C CNN
F 2 "" H 11950 7450 50  0001 C CNN
F 3 "" H 11950 7450 50  0001 C CNN
	1    11950 7450
	1    0    0    -1  
$EndComp
$Comp
L PUTM_EV_BMS_library:USB_+5V #PWR070
U 1 1 6628FC93
P 12550 6800
F 0 "#PWR070" H 12550 6650 50  0001 C CNN
F 1 "USB_+5V" H 12565 6973 50  0000 C CNN
F 2 "" H 12550 6800 50  0001 C CNN
F 3 "" H 12550 6800 50  0001 C CNN
	1    12550 6800
	1    0    0    -1  
$EndComp
$Comp
L PUTM_EV_BMS_library:USB_GND #PWR?
U 1 1 66290211
P 12550 7150
AR Path="/601B5445/66290211" Ref="#PWR?"  Part="1" 
AR Path="/66290211" Ref="#PWR071"  Part="1" 
F 0 "#PWR071" H 12550 6900 50  0001 C CNN
F 1 "USB_GND" H 12555 6977 50  0000 C CNN
F 2 "" H 12550 7150 50  0001 C CNN
F 3 "" H 12550 7150 50  0001 C CNN
	1    12550 7150
	1    0    0    -1  
$EndComp
$Comp
L Device:C_Small C31
U 1 1 66290AD9
P 12650 6950
F 0 "C31" H 12742 6996 50  0000 L CNN
F 1 "100nF" H 12742 6905 50  0000 L CNN
F 2 "Capacitor_SMD:C_0603_1608Metric" H 12650 6950 50  0001 C CNN
F 3 "~" H 12650 6950 50  0001 C CNN
	1    12650 6950
	1    0    0    -1  
$EndComp
$Comp
L Device:C_Small C32
U 1 1 66292ADF
P 13050 6950
F 0 "C32" H 13142 6996 50  0000 L CNN
F 1 "4.7uF" H 13142 6905 50  0000 L CNN
F 2 "Capacitor_SMD:C_0603_1608Metric" H 13050 6950 50  0001 C CNN
F 3 "~" H 13050 6950 50  0001 C CNN
	1    13050 6950
	1    0    0    -1  
$EndComp
Wire Wire Line
	12550 6800 12650 6800
Wire Wire Line
	13050 6800 13050 6850
Wire Wire Line
	13050 7050 13050 7100
Wire Wire Line
	13050 7100 12650 7100
Wire Wire Line
	12550 7100 12550 7150
Wire Wire Line
	12650 7100 12650 7050
Connection ~ 12650 7100
Wire Wire Line
	12650 7100 12550 7100
Wire Wire Line
	12650 6850 12650 6800
Connection ~ 12650 6800
Wire Wire Line
	12650 6800 13050 6800
$Comp
L Device:C_Small C26
U 1 1 6661FE46
P 11100 8800
F 0 "C26" H 11192 8846 50  0000 L CNN
F 1 "100nF" H 11192 8755 50  0000 L CNN
F 2 "Capacitor_SMD:C_0603_1608Metric" H 11100 8800 50  0001 C CNN
F 3 "~" H 11100 8800 50  0001 C CNN
	1    11100 8800
	1    0    0    -1  
$EndComp
Wire Wire Line
	11950 9100 11100 9100
Wire Wire Line
	11100 9100 11100 8900
Connection ~ 11950 9100
Wire Wire Line
	11350 8550 11100 8550
Wire Wire Line
	11100 8550 11100 8700
Wire Wire Line
	11350 7950 11100 7950
Wire Wire Line
	11100 7950 11100 8550
Connection ~ 11100 8550
$Comp
L Interface_USB:FT230XS U15
U 1 1 65B183E0
P 12050 8350
F 0 "U15" H 12450 8950 50  0000 C CNN
F 1 "FT230XS" H 12450 7750 50  0000 C CNN
F 2 "Package_SO:SSOP-16_3.9x4.9mm_P0.635mm" H 13050 7750 50  0001 C CNN
F 3 "https://www.ftdichip.com/Support/Documents/DataSheets/ICs/DS_FT230X.pdf" H 12050 8350 50  0001 C CNN
	1    12050 8350
	1    0    0    -1  
$EndComp
Wire Wire Line
	12150 7650 12150 7600
Wire Wire Line
	12150 7600 11100 7600
Wire Wire Line
	11100 7600 11100 7950
Connection ~ 11100 7950
$Comp
L Device:R_Small R49
U 1 1 66B5A719
P 10850 8150
F 0 "R49" V 10654 8150 50  0000 C CNN
F 1 "27R" V 10745 8150 50  0000 C CNN
F 2 "Resistor_SMD:R_0603_1608Metric" H 10850 8150 50  0001 C CNN
F 3 "~" H 10850 8150 50  0001 C CNN
	1    10850 8150
	0    1    1    0   
$EndComp
$Comp
L Device:R_Small R50
U 1 1 66B5CDB3
P 10850 8450
F 0 "R50" V 10654 8450 50  0000 C CNN
F 1 "27R" V 10745 8450 50  0000 C CNN
F 2 "Resistor_SMD:R_0603_1608Metric" H 10850 8450 50  0001 C CNN
F 3 "~" H 10850 8450 50  0001 C CNN
	1    10850 8450
	0    1    1    0   
$EndComp
Wire Wire Line
	11350 8250 11200 8250
Wire Wire Line
	11200 8250 11200 8150
Wire Wire Line
	11200 8150 10950 8150
Wire Wire Line
	11350 8350 11200 8350
Wire Wire Line
	11200 8350 11200 8450
Wire Wire Line
	11200 8450 10950 8450
$Comp
L Device:C_Small C23
U 1 1 66CF06D0
P 10700 8750
F 0 "C23" H 10792 8796 50  0000 L CNN
F 1 "27pF" H 10792 8705 50  0000 L CNN
F 2 "Capacitor_SMD:C_0805_2012Metric" H 10700 8750 50  0001 C CNN
F 3 "~" H 10700 8750 50  0001 C CNN
	1    10700 8750
	1    0    0    -1  
$EndComp
$Comp
L Device:C_Small C22
U 1 1 66CF0DE7
P 10350 8750
F 0 "C22" H 10442 8796 50  0000 L CNN
F 1 "27pF" H 10442 8705 50  0000 L CNN
F 2 "Capacitor_SMD:C_0805_2012Metric" H 10350 8750 50  0001 C CNN
F 3 "~" H 10350 8750 50  0001 C CNN
	1    10350 8750
	1    0    0    -1  
$EndComp
Wire Wire Line
	10700 8650 10700 8450
Wire Wire Line
	10700 8450 10750 8450
Wire Wire Line
	10750 8150 10350 8150
Wire Wire Line
	10350 8650 10350 8150
Connection ~ 10350 8150
Connection ~ 10700 8450
Wire Wire Line
	11100 9100 10700 9100
Wire Wire Line
	10700 9100 10700 8850
Connection ~ 11100 9100
Wire Wire Line
	10700 9100 10350 9100
Wire Wire Line
	10350 9100 10350 8850
Connection ~ 10700 9100
Wire Wire Line
	10650 7950 10450 7950
Wire Wire Line
	11950 7450 11950 7500
Wire Wire Line
	11950 7500 10650 7500
Wire Wire Line
	10650 7500 10650 7950
Connection ~ 11950 7500
Wire Wire Line
	11950 7500 11950 7650
$Comp
L Device:Ferrite_Bead_Small FB1
U 1 1 672EEBC9
P 10350 7950
F 0 "FB1" V 10113 7950 50  0000 C CNN
F 1 "ferrite_baud" V 10204 7950 50  0000 C CNN
F 2 "Inductor_SMD:L_0603_1608Metric" V 10280 7950 50  0001 C CNN
F 3 "~" H 10350 7950 50  0001 C CNN
	1    10350 7950
	0    1    1    0   
$EndComp
$Comp
L Device:C_Small C21
U 1 1 6737D8E8
P 9950 8750
F 0 "C21" H 10042 8796 50  0000 L CNN
F 1 "10nF" H 10042 8705 50  0000 L CNN
F 2 "Capacitor_SMD:C_0603_1608Metric" H 9950 8750 50  0001 C CNN
F 3 "~" H 9950 8750 50  0001 C CNN
	1    9950 8750
	1    0    0    -1  
$EndComp
Wire Wire Line
	10250 7950 9950 7950
Wire Wire Line
	9950 7950 9950 8650
Wire Wire Line
	10350 9100 9950 9100
Wire Wire Line
	9950 9100 9950 8850
Connection ~ 10350 9100
$Comp
L Connector:USB_B_Mini J10
U 1 1 6749A01A
P 9000 8150
F 0 "J10" H 9057 8617 50  0000 C CNN
F 1 "USB_B_Mini" H 9057 8526 50  0000 C CNN
F 2 "Connector_USB:USB_Mini-B_Lumberg_2486_01_Horizontal" H 9150 8100 50  0001 C CNN
F 3 "~" H 9150 8100 50  0001 C CNN
	1    9000 8150
	1    0    0    -1  
$EndComp
Connection ~ 9950 7950
Wire Wire Line
	10100 8250 10100 8150
Wire Wire Line
	10100 8150 10350 8150
Wire Wire Line
	9850 8450 9850 8150
Wire Wire Line
	9850 8450 10700 8450
Wire Wire Line
	9000 8550 9000 9100
Wire Wire Line
	9000 9100 9650 9100
Connection ~ 9950 9100
Wire Wire Line
	8900 8550 8900 9100
Wire Wire Line
	8900 9100 9000 9100
Connection ~ 9000 9100
$Comp
L Isolator:ADuM1201CR U16
U 1 1 6777A1E9
P 14350 8350
F 0 "U16" H 14350 8817 50  0000 C CNN
F 1 "ADuM1281CRZ" H 14350 8726 50  0000 C CNN
F 2 "Package_SO:SOIC-8_3.9x4.9mm_P1.27mm" H 14350 7950 50  0001 C CIN
F 3 "https://www.analog.com/static/imported-files/data_sheets/ADuM1200_1201.pdf" H 14350 8250 50  0001 C CNN
	1    14350 8350
	1    0    0    -1  
$EndComp
$Comp
L Device:C_Small C33
U 1 1 6777DF8C
P 13350 8850
F 0 "C33" H 13442 8896 50  0000 L CNN
F 1 "100nF" H 13442 8805 50  0000 L CNN
F 2 "Capacitor_SMD:C_0603_1608Metric" H 13350 8850 50  0001 C CNN
F 3 "~" H 13350 8850 50  0001 C CNN
	1    13350 8850
	1    0    0    -1  
$EndComp
Wire Wire Line
	13850 8550 13750 8550
Wire Wire Line
	13750 8550 13750 9100
Wire Wire Line
	13750 9100 13350 9100
Connection ~ 12150 9100
Wire Wire Line
	13350 8950 13350 9100
Connection ~ 13350 9100
Wire Wire Line
	13350 9100 12150 9100
Wire Wire Line
	13850 8150 13350 8150
Wire Wire Line
	13350 8150 13350 8750
Wire Wire Line
	13050 8050 13050 8250
Wire Wire Line
	13050 8250 13850 8250
Wire Wire Line
	13850 8450 13150 8450
Wire Wire Line
	13150 8450 13150 7950
Wire Wire Line
	13150 7950 13050 7950
$Comp
L Device:R_Small R60
U 1 1 67A6D042
P 12800 7750
F 0 "R60" H 12741 7704 50  0000 R CNN
F 1 "10k" H 12741 7795 50  0000 R CNN
F 2 "Resistor_SMD:R_0603_1608Metric" H 12800 7750 50  0001 C CNN
F 3 "~" H 12800 7750 50  0001 C CNN
	1    12800 7750
	-1   0    0    1   
$EndComp
$Comp
L Device:R_Small R64
U 1 1 67A6DDE7
P 13050 7750
F 0 "R64" H 12991 7704 50  0000 R CNN
F 1 "10k" H 12991 7795 50  0000 R CNN
F 2 "Resistor_SMD:R_0603_1608Metric" H 13050 7750 50  0001 C CNN
F 3 "~" H 13050 7750 50  0001 C CNN
	1    13050 7750
	-1   0    0    1   
$EndComp
Wire Wire Line
	12750 8050 12800 8050
Wire Wire Line
	13050 7850 13050 7950
Connection ~ 13050 7950
Wire Wire Line
	13050 7950 12750 7950
Wire Wire Line
	12800 7850 12800 8050
Connection ~ 12800 8050
Wire Wire Line
	12800 8050 13050 8050
Wire Wire Line
	12800 7600 12800 7650
Wire Wire Line
	13050 7650 13050 7600
Wire Wire Line
	12800 7600 13050 7600
Connection ~ 12150 7600
Connection ~ 12800 7600
Wire Wire Line
	12150 7600 12800 7600
$Comp
L power:+3.3V #PWR?
U 1 1 67F387D7
P 15050 8100
AR Path="/60056272/67F387D7" Ref="#PWR?"  Part="1" 
AR Path="/67F387D7" Ref="#PWR078"  Part="1" 
F 0 "#PWR078" H 15050 7950 50  0001 C CNN
F 1 "+3.3V" H 15065 8273 50  0000 C CNN
F 2 "" H 15050 8100 50  0001 C CNN
F 3 "" H 15050 8100 50  0001 C CNN
	1    15050 8100
	1    0    0    -1  
$EndComp
$Comp
L Device:C_Small C36
U 1 1 67F39616
P 15050 8850
F 0 "C36" H 15142 8896 50  0000 L CNN
F 1 "100nF" H 15142 8805 50  0000 L CNN
F 2 "Capacitor_SMD:C_0603_1608Metric" H 15050 8850 50  0001 C CNN
F 3 "~" H 15050 8850 50  0001 C CNN
	1    15050 8850
	1    0    0    -1  
$EndComp
Wire Wire Line
	14850 8150 15050 8150
Wire Wire Line
	15050 8150 15050 8100
Wire Wire Line
	15050 8150 15050 8750
Connection ~ 15050 8150
Wire Wire Line
	14850 8550 14900 8550
Wire Wire Line
	14900 8550 14900 9100
Wire Wire Line
	14900 9100 15050 9100
Wire Wire Line
	15050 8950 15050 9100
Wire Wire Line
	14850 8250 15200 8250
Wire Wire Line
	14850 8450 15200 8450
$Comp
L power:GND #PWR?
U 1 1 684BA0C0
P 15050 9150
AR Path="/60056272/684BA0C0" Ref="#PWR?"  Part="1" 
AR Path="/684BA0C0" Ref="#PWR079"  Part="1" 
F 0 "#PWR079" H 15050 8900 50  0001 C CNN
F 1 "GND" H 15055 8977 50  0000 C CNN
F 2 "" H 15050 9150 50  0001 C CNN
F 3 "" H 15050 9150 50  0001 C CNN
	1    15050 9150
	1    0    0    -1  
$EndComp
Wire Wire Line
	15050 9150 15050 9100
Connection ~ 15050 9100
Text Label 15200 8250 0    50   ~ 0
MCU_UART_TX
Text Label 15200 8450 0    50   ~ 0
MCU_UART_RX
Text Label 19000 6850 0    50   ~ 0
MCU_UART_TX
Text Label 19000 6950 0    50   ~ 0
MCU_UART_RX
$Comp
L Device:R_Small R46
U 1 1 68A510BC
P 9650 8750
F 0 "R46" H 9591 8704 50  0000 R CNN
F 1 "100k" H 9591 8795 50  0000 R CNN
F 2 "Resistor_SMD:R_1206_3216Metric" H 9650 8750 50  0001 C CNN
F 3 "~" H 9650 8750 50  0001 C CNN
	1    9650 8750
	-1   0    0    1   
$EndComp
Wire Wire Line
	9300 8350 9650 8350
Wire Wire Line
	9650 8350 9650 8650
Wire Wire Line
	9650 8850 9650 9100
Connection ~ 9650 9100
$Comp
L Interface_CAN_LIN:MCP2562-E-SN U21
U 1 1 68C3145B
P 20950 13250
F 0 "U21" H 21200 13600 50  0000 C CNN
F 1 "MCP2562-E-SN" H 20500 12900 50  0000 C CNN
F 2 "Package_SO:SOIC-8_3.9x4.9mm_P1.27mm" H 20950 12750 50  0001 C CIN
F 3 "http://ww1.microchip.com/downloads/en/DeviceDoc/25167A.pdf" H 20950 13250 50  0001 C CNN
	1    20950 13250
	1    0    0    -1  
$EndComp
$Comp
L Device:D_TVS_x2_AAC D10
U 1 1 68EAF359
P 22150 13250
F 0 "D10" V 22196 13329 50  0000 L CNN
F 1 "PESD2CAN.215" V 22105 13329 50  0000 L CNN
F 2 "Package_TO_SOT_SMD:SOT-23" H 22000 13250 50  0001 C CNN
F 3 "~" H 22000 13250 50  0001 C CNN
	1    22150 13250
	0    -1   1    0   
$EndComp
$Comp
L Device:R_Small R91
U 1 1 68F530F6
P 22450 13250
F 0 "R91" H 22391 13204 50  0000 R CNN
F 1 "120" H 22391 13295 50  0000 R CNN
F 2 "Resistor_SMD:R_0603_1608Metric" H 22450 13250 50  0001 C CNN
F 3 "~" H 22450 13250 50  0001 C CNN
	1    22450 13250
	-1   0    0    1   
$EndComp
Wire Wire Line
	22450 13650 22150 13650
Wire Wire Line
	21600 13650 21600 13350
Wire Wire Line
	21600 13350 21450 13350
Wire Wire Line
	22150 13600 22150 13650
Connection ~ 22150 13650
Wire Wire Line
	22150 13650 21600 13650
Wire Wire Line
	21600 13150 21600 12850
Wire Wire Line
	21600 12850 22150 12850
Wire Wire Line
	21450 13150 21600 13150
Wire Wire Line
	22150 12900 22150 12850
Connection ~ 22150 12850
Wire Wire Line
	22150 12850 22450 12850
Wire Wire Line
	22300 13250 22350 13250
Wire Wire Line
	22350 13250 22350 13750
Wire Wire Line
	20950 13650 20950 13700
$Comp
L power:GND #PWR?
U 1 1 69507916
P 20950 13750
AR Path="/60056272/69507916" Ref="#PWR?"  Part="1" 
AR Path="/69507916" Ref="#PWR0118"  Part="1" 
F 0 "#PWR0118" H 20950 13500 50  0001 C CNN
F 1 "GND" H 20955 13577 50  0000 C CNN
F 2 "" H 20950 13750 50  0001 C CNN
F 3 "" H 20950 13750 50  0001 C CNN
	1    20950 13750
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR?
U 1 1 695082FC
P 22350 13750
AR Path="/60056272/695082FC" Ref="#PWR?"  Part="1" 
AR Path="/695082FC" Ref="#PWR0124"  Part="1" 
F 0 "#PWR0124" H 22350 13500 50  0001 C CNN
F 1 "GND" H 22355 13577 50  0000 C CNN
F 2 "" H 22350 13750 50  0001 C CNN
F 3 "" H 22350 13750 50  0001 C CNN
	1    22350 13750
	1    0    0    -1  
$EndComp
Wire Wire Line
	22450 13150 22450 12850
Wire Wire Line
	22450 13350 22450 13650
Wire Wire Line
	22450 12850 22600 12850
Connection ~ 22450 12850
Wire Wire Line
	22450 13650 22600 13650
Connection ~ 22450 13650
Text Label 22600 12850 0    50   ~ 0
CAN_H
Text Label 22600 13650 0    50   ~ 0
CAN_L
Wire Wire Line
	20950 13700 20350 13700
Wire Wire Line
	20350 13700 20350 13450
Wire Wire Line
	20350 13450 20450 13450
Connection ~ 20950 13700
Wire Wire Line
	20950 13700 20950 13750
$Comp
L power:+3.3V #PWR?
U 1 1 69A2EF47
P 20350 12700
AR Path="/60056272/69A2EF47" Ref="#PWR?"  Part="1" 
AR Path="/69A2EF47" Ref="#PWR0114"  Part="1" 
F 0 "#PWR0114" H 20350 12550 50  0001 C CNN
F 1 "+3.3V" H 20365 12873 50  0000 C CNN
F 2 "" H 20350 12700 50  0001 C CNN
F 3 "" H 20350 12700 50  0001 C CNN
	1    20350 12700
	1    0    0    -1  
$EndComp
$Comp
L power:+5V #PWR?
U 1 1 69A2F84B
P 20950 12700
AR Path="/601B5445/69A2F84B" Ref="#PWR?"  Part="1" 
AR Path="/69A2F84B" Ref="#PWR0117"  Part="1" 
F 0 "#PWR0117" H 20950 12550 50  0001 C CNN
F 1 "+5V" H 20965 12873 50  0000 C CNN
F 2 "" H 20950 12700 50  0001 C CNN
F 3 "" H 20950 12700 50  0001 C CNN
	1    20950 12700
	1    0    0    -1  
$EndComp
Wire Wire Line
	20950 12700 20950 12850
$Comp
L Device:C_Small C57
U 1 1 69AD75C2
P 21400 12500
F 0 "C57" H 21492 12546 50  0000 L CNN
F 1 "100nF" H 21492 12455 50  0000 L CNN
F 2 "Capacitor_SMD:C_0603_1608Metric" H 21400 12500 50  0001 C CNN
F 3 "~" H 21400 12500 50  0001 C CNN
	1    21400 12500
	1    0    0    -1  
$EndComp
$Comp
L power:+5V #PWR?
U 1 1 69AD9098
P 21400 12400
AR Path="/601B5445/69AD9098" Ref="#PWR?"  Part="1" 
AR Path="/69AD9098" Ref="#PWR0121"  Part="1" 
F 0 "#PWR0121" H 21400 12250 50  0001 C CNN
F 1 "+5V" H 21415 12573 50  0000 C CNN
F 2 "" H 21400 12400 50  0001 C CNN
F 3 "" H 21400 12400 50  0001 C CNN
	1    21400 12400
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR?
U 1 1 69AD950A
P 21400 12600
AR Path="/60056272/69AD950A" Ref="#PWR?"  Part="1" 
AR Path="/69AD950A" Ref="#PWR0122"  Part="1" 
F 0 "#PWR0122" H 21400 12350 50  0001 C CNN
F 1 "GND" H 21405 12427 50  0000 C CNN
F 2 "" H 21400 12600 50  0001 C CNN
F 3 "" H 21400 12600 50  0001 C CNN
	1    21400 12600
	1    0    0    -1  
$EndComp
Wire Wire Line
	20350 12700 20350 13350
Wire Wire Line
	20350 13350 20450 13350
Wire Wire Line
	20450 13050 20250 13050
Wire Wire Line
	20250 13150 20450 13150
Text Label 20250 13050 2    50   ~ 0
MCU_CAN_TX
Text Label 20250 13150 2    50   ~ 0
MCU_CAN_RX
Text Label 19000 7150 0    50   ~ 0
MCU_CAN_TX
Text Label 19000 7050 0    50   ~ 0
MCU_CAN_RX
$Comp
L Device:LED_Small_ALT D7
U 1 1 69E2086A
P 15700 4900
F 0 "D7" V 15700 4832 50  0000 R CNN
F 1 "LED_Small_ALT" H 15700 5044 50  0001 C CNN
F 2 "LED_SMD:LED_0805_2012Metric" V 15700 4900 50  0001 C CNN
F 3 "~" V 15700 4900 50  0001 C CNN
	1    15700 4900
	0    -1   -1   0   
$EndComp
$Comp
L Device:LED_Small_ALT D6
U 1 1 69E22642
P 15450 4900
F 0 "D6" V 15450 4832 50  0000 R CNN
F 1 "LED_Small_ALT" H 15450 5044 50  0001 C CNN
F 2 "LED_SMD:LED_0805_2012Metric" V 15450 4900 50  0001 C CNN
F 3 "~" V 15450 4900 50  0001 C CNN
	1    15450 4900
	0    -1   -1   0   
$EndComp
$Comp
L Device:LED_Small_ALT D5
U 1 1 69E22A7A
P 15200 4900
F 0 "D5" V 15200 4832 50  0000 R CNN
F 1 "LED_Small_ALT" V 15245 4998 50  0001 L CNN
F 2 "LED_SMD:LED_0805_2012Metric" V 15200 4900 50  0001 C CNN
F 3 "~" V 15200 4900 50  0001 C CNN
	1    15200 4900
	0    -1   -1   0   
$EndComp
$Comp
L Device:R_Small R?
U 1 1 6A545D8A
P 15700 4650
AR Path="/60056272/6A545D8A" Ref="R?"  Part="1" 
AR Path="/6A545D8A" Ref="R72"  Part="1" 
F 0 "R72" H 15759 4696 50  0000 L CNN
F 1 "1k" H 15759 4605 50  0000 L CNN
F 2 "Resistor_SMD:R_0805_2012Metric" H 15700 4650 50  0001 C CNN
F 3 "~" H 15700 4650 50  0001 C CNN
	1    15700 4650
	1    0    0    -1  
$EndComp
$Comp
L Device:R_Small R?
U 1 1 6ADB13DC
P 15450 4650
AR Path="/60056272/6ADB13DC" Ref="R?"  Part="1" 
AR Path="/6ADB13DC" Ref="R71"  Part="1" 
F 0 "R71" H 15509 4696 50  0000 L CNN
F 1 "1k" H 15509 4605 50  0000 L CNN
F 2 "Resistor_SMD:R_0805_2012Metric" H 15450 4650 50  0001 C CNN
F 3 "~" H 15450 4650 50  0001 C CNN
	1    15450 4650
	1    0    0    -1  
$EndComp
$Comp
L Device:R_Small R?
U 1 1 6ADB17CB
P 15200 4650
AR Path="/60056272/6ADB17CB" Ref="R?"  Part="1" 
AR Path="/6ADB17CB" Ref="R69"  Part="1" 
F 0 "R69" H 15259 4696 50  0000 L CNN
F 1 "1k" H 15259 4605 50  0000 L CNN
F 2 "Resistor_SMD:R_0805_2012Metric" H 15200 4650 50  0001 C CNN
F 3 "~" H 15200 4650 50  0001 C CNN
	1    15200 4650
	1    0    0    -1  
$EndComp
Wire Wire Line
	15700 4800 15700 4750
Wire Wire Line
	15450 4800 15450 4750
Wire Wire Line
	15200 4800 15200 4750
Wire Wire Line
	15200 5000 15200 5050
Wire Wire Line
	15200 5050 15450 5050
Wire Wire Line
	15700 5050 15700 5000
Wire Wire Line
	15450 5000 15450 5050
Connection ~ 15450 5050
Wire Wire Line
	15450 5050 15700 5050
$Comp
L power:GND #PWR?
U 1 1 6B1A883A
P 15450 5100
AR Path="/60056272/6B1A883A" Ref="#PWR?"  Part="1" 
AR Path="/6B1A883A" Ref="#PWR082"  Part="1" 
F 0 "#PWR082" H 15450 4850 50  0001 C CNN
F 1 "GND" H 15455 4927 50  0000 C CNN
F 2 "" H 15450 5100 50  0001 C CNN
F 3 "" H 15450 5100 50  0001 C CNN
	1    15450 5100
	1    0    0    -1  
$EndComp
Wire Wire Line
	15450 5100 15450 5050
Wire Wire Line
	15700 4550 15700 4500
Wire Wire Line
	15450 4550 15450 4500
Wire Wire Line
	15200 4550 15200 4500
Text Label 15200 4500 1    50   ~ 0
MCU_LED_1
Text Label 15450 4500 1    50   ~ 0
MCU_LED_2
Text Label 15700 4500 1    50   ~ 0
MCU_LED_3
Text Label 19000 6350 0    50   ~ 0
MCU_LED_1
Text Label 19000 6450 0    50   ~ 0
MCU_LED_2
Text Label 19000 7250 0    50   ~ 0
MCU_LED_3
$Comp
L Device:C_Small C?
U 1 1 60188AF2
P 16750 5750
AR Path="/60056272/60188AF2" Ref="C?"  Part="1" 
AR Path="/60188AF2" Ref="C44"  Part="1" 
F 0 "C44" H 16842 5796 50  0000 L CNN
F 1 "22pF" H 16842 5705 50  0000 L CNN
F 2 "Capacitor_SMD:C_0805_2012Metric" H 16750 5750 50  0001 C CNN
F 3 "~" H 16750 5750 50  0001 C CNN
	1    16750 5750
	0    1    1    0   
$EndComp
$Comp
L Device:C_Small C?
U 1 1 60188AEC
P 16750 5450
AR Path="/60056272/60188AEC" Ref="C?"  Part="1" 
AR Path="/60188AEC" Ref="C43"  Part="1" 
F 0 "C43" H 16842 5496 50  0000 L CNN
F 1 "22pF" H 16842 5405 50  0000 L CNN
F 2 "Capacitor_SMD:C_0805_2012Metric" H 16750 5450 50  0001 C CNN
F 3 "~" H 16750 5450 50  0001 C CNN
	1    16750 5450
	0    -1   -1   0   
$EndComp
$Comp
L Device:Crystal_Small Y?
U 1 1 6BBC52DC
P 16750 7700
AR Path="/60056272/6BBC52DC" Ref="Y?"  Part="1" 
AR Path="/6BBC52DC" Ref="Y1"  Part="1" 
F 0 "Y1" V 16704 7788 50  0000 L CNN
F 1 "32.768kHz" V 16795 7788 50  0000 L CNN
F 2 "Crystal:Crystal_AT310_D3.0mm_L10.0mm_Vertical" H 16750 7700 50  0001 C CNN
F 3 "~" H 16750 7700 50  0001 C CNN
	1    16750 7700
	0    1    1    0   
$EndComp
Wire Wire Line
	16600 7850 16750 7850
Wire Wire Line
	16750 7850 16750 7800
Wire Wire Line
	16750 7600 16750 7550
Wire Wire Line
	16750 7550 16600 7550
Connection ~ 16750 7550
Connection ~ 16750 7850
Wire Wire Line
	16400 7550 16200 7550
Wire Wire Line
	16200 7550 16200 7700
Wire Wire Line
	16200 7850 16400 7850
$Comp
L power:GND #PWR?
U 1 1 6BBC52F1
P 16150 7700
AR Path="/60056272/6BBC52F1" Ref="#PWR?"  Part="1" 
AR Path="/6BBC52F1" Ref="#PWR086"  Part="1" 
F 0 "#PWR086" H 16150 7450 50  0001 C CNN
F 1 "GND" V 16155 7572 50  0000 R CNN
F 2 "" H 16150 7700 50  0001 C CNN
F 3 "" H 16150 7700 50  0001 C CNN
	1    16150 7700
	0    1    1    0   
$EndComp
Wire Wire Line
	16150 7700 16200 7700
Connection ~ 16200 7700
Wire Wire Line
	16200 7700 16200 7850
$Comp
L Device:C_Small C?
U 1 1 6BBC52FA
P 16500 7850
AR Path="/60056272/6BBC52FA" Ref="C?"  Part="1" 
AR Path="/6BBC52FA" Ref="C41"  Part="1" 
F 0 "C41" H 16592 7896 50  0000 L CNN
F 1 "22pF" H 16592 7805 50  0000 L CNN
F 2 "Capacitor_SMD:C_0805_2012Metric" H 16500 7850 50  0001 C CNN
F 3 "~" H 16500 7850 50  0001 C CNN
	1    16500 7850
	0    1    1    0   
$EndComp
$Comp
L Device:C_Small C?
U 1 1 6BBC5300
P 16500 7550
AR Path="/60056272/6BBC5300" Ref="C?"  Part="1" 
AR Path="/6BBC5300" Ref="C40"  Part="1" 
F 0 "C40" H 16592 7596 50  0000 L CNN
F 1 "22pF" H 16592 7505 50  0000 L CNN
F 2 "Capacitor_SMD:C_0805_2012Metric" H 16500 7550 50  0001 C CNN
F 3 "~" H 16500 7550 50  0001 C CNN
	1    16500 7550
	0    -1   -1   0   
$EndComp
$Comp
L Connector_Generic:Conn_01x02 J16
U 1 1 6BDD815D
P 21650 14250
F 0 "J16" H 21730 14242 50  0000 L CNN
F 1 "CAN" H 21730 14151 50  0000 L CNN
F 2 "TerminalBlock_MetzConnect:TerminalBlock_MetzConnect_Type086_RT03402HBLC_1x02_P3.81mm_Horizontal" H 21650 14250 50  0001 C CNN
F 3 "~" H 21650 14250 50  0001 C CNN
	1    21650 14250
	-1   0    0    -1  
$EndComp
Text Label 21850 14250 0    50   ~ 0
CAN_L
Text Label 21850 14350 0    50   ~ 0
CAN_H
Wire Wire Line
	13800 1800 13800 1950
Wire Wire Line
	13800 2150 13800 2250
$Comp
L power:GND #PWR?
U 1 1 60EB3FDD
P 13800 2250
AR Path="/601B5445/60EB3FDD" Ref="#PWR?"  Part="1" 
AR Path="/60EB3FDD" Ref="#PWR077"  Part="1" 
F 0 "#PWR077" H 13800 2000 50  0001 C CNN
F 1 "GND" H 13805 2077 50  0000 C CNN
F 2 "" H 13800 2250 50  0001 C CNN
F 3 "" H 13800 2250 50  0001 C CNN
	1    13800 2250
	1    0    0    -1  
$EndComp
Wire Wire Line
	18100 13600 18100 13550
Wire Wire Line
	17600 13600 17600 13700
Wire Wire Line
	17600 13500 17600 13600
Connection ~ 17600 13600
Wire Wire Line
	17600 13600 18100 13600
$Comp
L Device:D_TVS D9
U 1 1 616CC8FA
P 18100 13400
F 0 "D9" V 18054 13479 50  0000 L CNN
F 1 "D_TVS 5V" V 18145 13479 50  0000 L CNN
F 2 "Diode_SMD:D_SMA" H 18100 13400 50  0001 C CNN
F 3 "~" H 18100 13400 50  0001 C CNN
	1    18100 13400
	0    1    1    0   
$EndComp
Wire Wire Line
	17000 5750 17600 5750
Wire Wire Line
	17600 5650 17450 5650
Wire Wire Line
	17450 5650 17450 5450
Wire Wire Line
	17000 5450 17450 5450
Wire Wire Line
	16750 7550 17600 7550
Wire Wire Line
	17350 7650 17350 7850
Wire Wire Line
	16750 7850 17350 7850
Wire Wire Line
	17350 7650 17600 7650
$Comp
L Isolator:PC817 U4
U 1 1 6198429B
P 4900 2800
F 0 "U4" H 4900 3125 50  0000 C CNN
F 1 "PC817" H 4900 3034 50  0000 C CNN
F 2 "Package_DIP:DIP-4_W7.62mm" H 4700 2600 50  0001 L CIN
F 3 "http://www.soselectronic.cz/a_info/resource/d/pc817.pdf" H 4900 2800 50  0001 L CNN
	1    4900 2800
	1    0    0    -1  
$EndComp
Text Label 4050 2700 2    50   ~ 0
SAFETY_AIR
$Comp
L Device:R R14
U 1 1 61C3D1B7
P 4300 2700
F 0 "R14" V 4093 2700 50  0000 C CNN
F 1 "3.3k" V 4184 2700 50  0000 C CNN
F 2 "Resistor_SMD:R_0603_1608Metric" V 4230 2700 50  0001 C CNN
F 3 "~" H 4300 2700 50  0001 C CNN
	1    4300 2700
	0    1    1    0   
$EndComp
Wire Wire Line
	4050 2700 4150 2700
Wire Wire Line
	4450 2700 4600 2700
Wire Wire Line
	4600 2900 4550 2900
Wire Wire Line
	4550 2900 4550 3000
$Comp
L power:GND #PWR021
U 1 1 61E4F4F1
P 4550 3000
F 0 "#PWR021" H 4550 2750 50  0001 C CNN
F 1 "GND" H 4555 2827 50  0000 C CNN
F 2 "" H 4550 3000 50  0001 C CNN
F 3 "" H 4550 3000 50  0001 C CNN
	1    4550 3000
	1    0    0    -1  
$EndComp
$Comp
L Device:R_Small R16
U 1 1 61EFF866
P 5300 2500
F 0 "R16" H 5359 2546 50  0000 L CNN
F 1 "10k" H 5359 2455 50  0000 L CNN
F 2 "Resistor_SMD:R_0603_1608Metric" H 5300 2500 50  0001 C CNN
F 3 "~" H 5300 2500 50  0001 C CNN
	1    5300 2500
	1    0    0    -1  
$EndComp
Wire Wire Line
	5200 2900 5300 2900
Wire Wire Line
	5300 2900 5300 3000
$Comp
L power:GND #PWR027
U 1 1 61FB2288
P 5300 3000
F 0 "#PWR027" H 5300 2750 50  0001 C CNN
F 1 "GND" H 5305 2827 50  0000 C CNN
F 2 "" H 5300 3000 50  0001 C CNN
F 3 "" H 5300 3000 50  0001 C CNN
	1    5300 3000
	1    0    0    -1  
$EndComp
Wire Wire Line
	5200 2700 5300 2700
Wire Wire Line
	5300 2700 5300 2600
Wire Wire Line
	5300 2400 5300 2350
$Comp
L power:+3.3V #PWR?
U 1 1 62119BBD
P 5300 2350
AR Path="/60056272/62119BBD" Ref="#PWR?"  Part="1" 
AR Path="/62119BBD" Ref="#PWR026"  Part="1" 
F 0 "#PWR026" H 5300 2200 50  0001 C CNN
F 1 "+3.3V" H 5315 2523 50  0000 C CNN
F 2 "" H 5300 2350 50  0001 C CNN
F 3 "" H 5300 2350 50  0001 C CNN
	1    5300 2350
	1    0    0    -1  
$EndComp
Wire Wire Line
	5300 2700 5450 2700
Connection ~ 5300 2700
Text Label 5450 2700 0    50   ~ 0
SAFETY_DETECTION
Text Label 17600 6450 2    50   ~ 0
SAFETY_DETECTION
$Comp
L Device:C_Small C?
U 1 1 62285C56
P 17150 5000
AR Path="/60056272/62285C56" Ref="C?"  Part="1" 
AR Path="/62285C56" Ref="C45"  Part="1" 
F 0 "C45" H 17242 5046 50  0000 L CNN
F 1 "100nF" H 17242 4955 50  0000 L CNN
F 2 "Capacitor_SMD:C_0603_1608Metric" H 17150 5000 50  0001 C CNN
F 3 "~" H 17150 5000 50  0001 C CNN
	1    17150 5000
	1    0    0    -1  
$EndComp
Wire Wire Line
	17150 5100 17150 5150
$Comp
L power:GND #PWR?
U 1 1 624A5A4B
P 17150 5150
AR Path="/60056272/624A5A4B" Ref="#PWR?"  Part="1" 
AR Path="/624A5A4B" Ref="#PWR094"  Part="1" 
F 0 "#PWR094" H 17150 4900 50  0001 C CNN
F 1 "GND" H 17155 4977 50  0000 C CNN
F 2 "" H 17150 5150 50  0001 C CNN
F 3 "" H 17150 5150 50  0001 C CNN
	1    17150 5150
	1    0    0    -1  
$EndComp
Wire Wire Line
	17500 4950 17500 4850
Wire Wire Line
	17500 4850 17150 4850
Wire Wire Line
	17150 4850 17150 4900
Wire Wire Line
	17500 4950 17600 4950
$Comp
L Amplifier_Operational:MCP6001-OT U6
U 1 1 60B96EB5
P 6950 4450
F 0 "U6" H 7294 4496 50  0000 L CNN
F 1 "MCP6001-OT" H 7294 4405 50  0000 L CNN
F 2 "Package_TO_SOT_SMD:SOT-353_SC-70-5" H 6850 4250 50  0001 L CNN
F 3 "http://ww1.microchip.com/downloads/en/DeviceDoc/21733j.pdf" H 6950 4650 50  0001 C CNN
	1    6950 4450
	1    0    0    -1  
$EndComp
$Comp
L Amplifier_Operational:MCP6001-OT U7
U 1 1 60B9CCFB
P 7050 6800
F 0 "U7" H 7394 6846 50  0000 L CNN
F 1 "MCP6001-OT" H 7394 6755 50  0000 L CNN
F 2 "Package_TO_SOT_SMD:SOT-353_SC-70-5" H 6950 6600 50  0001 L CNN
F 3 "http://ww1.microchip.com/downloads/en/DeviceDoc/21733j.pdf" H 7050 7000 50  0001 C CNN
	1    7050 6800
	1    0    0    -1  
$EndComp
Wire Wire Line
	7350 4450 7250 4450
Wire Wire Line
	6650 4350 6600 4350
Wire Wire Line
	6650 4550 6600 4550
Wire Wire Line
	7400 6800 7350 6800
Connection ~ 7400 6800
Wire Wire Line
	6650 6900 6750 6900
Wire Wire Line
	6750 6700 6650 6700
Wire Wire Line
	7900 6800 8050 6800
Wire Wire Line
	8050 6800 8050 6900
Connection ~ 8050 6800
Wire Wire Line
	8050 6800 8200 6800
Wire Wire Line
	8050 7100 8050 7300
Wire Wire Line
	6650 7300 6650 7250
Wire Wire Line
	6650 7300 6950 7300
Wire Wire Line
	6650 7300 6650 7350
Connection ~ 6650 7300
Wire Wire Line
	6650 7300 5500 7300
Wire Wire Line
	5500 7300 5500 7150
Wire Wire Line
	5350 7150 5500 7150
Wire Wire Line
	5500 7050 5500 6550
Wire Wire Line
	5350 6850 5650 6850
Wire Wire Line
	5650 6850 5650 7000
Wire Wire Line
	5650 6700 5650 6750
Wire Wire Line
	5650 6750 5350 6750
Wire Wire Line
	4250 7050 4150 7050
Wire Wire Line
	4150 7050 4150 6500
Wire Wire Line
	3250 6750 3150 6750
Connection ~ 3250 6750
Wire Wire Line
	2850 6750 2800 6750
Wire Wire Line
	2500 6750 2450 6750
Wire Wire Line
	2150 6750 2100 6750
Wire Wire Line
	1800 6750 1600 6750
Wire Wire Line
	4150 4200 4150 4700
Wire Wire Line
	4200 4700 4150 4700
Wire Wire Line
	3950 4800 3950 4950
Wire Wire Line
	3100 4400 3200 4400
Connection ~ 3200 4400
$Comp
L Device:R R?
U 1 1 60156E41
P 1900 4400
AR Path="/600380E4/60156E41" Ref="R?"  Part="1" 
AR Path="/60156E41" Ref="R1"  Part="1" 
F 0 "R1" V 1693 4400 50  0000 C CNN
F 1 "200k" V 1784 4400 50  0000 C CNN
F 2 "Resistor_SMD:R_1206_3216Metric" V 1830 4400 50  0001 C CNN
F 3 "~" H 1900 4400 50  0001 C CNN
	1    1900 4400
	0    1    1    0   
$EndComp
Wire Wire Line
	2800 4400 2750 4400
Wire Wire Line
	2450 4400 2400 4400
Wire Wire Line
	2100 4400 2050 4400
Wire Wire Line
	1750 4400 1600 4400
Wire Wire Line
	5300 4400 5850 4400
Wire Wire Line
	5850 4400 5850 4350
Wire Wire Line
	5300 4500 5850 4500
Wire Wire Line
	5850 4500 5850 4650
Wire Wire Line
	6600 4550 6600 4650
Wire Wire Line
	5850 4350 6150 4350
Wire Wire Line
	6350 4350 6600 4350
Connection ~ 6600 4350
Wire Wire Line
	6600 4650 6350 4650
Connection ~ 6600 4650
Wire Wire Line
	6600 4650 6600 4700
Wire Wire Line
	6150 4650 5850 4650
Wire Wire Line
	6650 6900 6650 7000
Wire Wire Line
	6650 7000 6400 7000
Connection ~ 6650 7000
Wire Wire Line
	6650 7000 6650 7050
Wire Wire Line
	6650 6700 6400 6700
Connection ~ 6650 6700
Wire Wire Line
	6200 6700 5650 6700
Wire Wire Line
	6200 7000 5650 7000
$Comp
L power:+3.3V #PWR041
U 1 1 65380940
P 6950 6300
F 0 "#PWR041" H 6950 6150 50  0001 C CNN
F 1 "+3.3V" H 6965 6473 50  0000 C CNN
F 2 "" H 6950 6300 50  0001 C CNN
F 3 "" H 6950 6300 50  0001 C CNN
	1    6950 6300
	1    0    0    -1  
$EndComp
Wire Wire Line
	6950 6300 6950 6500
$Comp
L power:+3.3V #PWR040
U 1 1 65502EAC
P 6850 4000
F 0 "#PWR040" H 6850 3850 50  0001 C CNN
F 1 "+3.3V" H 6865 4173 50  0000 C CNN
F 2 "" H 6850 4000 50  0001 C CNN
F 3 "" H 6850 4000 50  0001 C CNN
	1    6850 4000
	1    0    0    -1  
$EndComp
Wire Wire Line
	6850 4000 6850 4150
Wire Wire Line
	6850 4750 6850 4950
Wire Wire Line
	8050 4600 8050 4450
Wire Wire Line
	8050 4450 8150 4450
Wire Wire Line
	6850 4950 8050 4950
Wire Wire Line
	8050 4950 8050 4800
Connection ~ 6850 4950
Wire Wire Line
	8050 4450 7800 4450
Connection ~ 8050 4450
Wire Wire Line
	7600 4450 7350 4450
Connection ~ 7350 4450
Wire Wire Line
	7000 4050 6600 4050
Wire Wire Line
	7200 4050 7350 4050
Wire Wire Line
	7400 6400 7300 6400
Wire Wire Line
	7100 6400 6650 6400
Wire Wire Line
	6950 7100 6950 7300
Connection ~ 6950 7300
Wire Wire Line
	6950 7300 8050 7300
Wire Wire Line
	6600 4900 6600 4950
Wire Wire Line
	6850 4950 6600 4950
Connection ~ 6600 4950
Wire Wire Line
	6600 4950 6600 5000
Wire Wire Line
	5500 4200 5500 4700
Wire Wire Line
	5500 4800 5500 4950
Wire Wire Line
	5500 4950 6600 4950
Wire Wire Line
	5300 4800 5500 4800
Wire Wire Line
	5300 4700 5500 4700
Wire Wire Line
	5350 7050 5500 7050
$Comp
L Device:C C?
U 1 1 674F342C
P 7500 7800
AR Path="/600380E4/674F342C" Ref="C?"  Part="1" 
AR Path="/674F342C" Ref="C17"  Part="1" 
F 0 "C17" H 7615 7846 50  0000 L CNN
F 1 "100nF" H 7615 7755 50  0000 L CNN
F 2 "Capacitor_SMD:C_0603_1608Metric" H 7538 7650 50  0001 C CNN
F 3 "~" H 7500 7800 50  0001 C CNN
	1    7500 7800
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR?
U 1 1 674F3432
P 7500 7950
AR Path="/601B5445/674F3432" Ref="#PWR?"  Part="1" 
AR Path="/674F3432" Ref="#PWR043"  Part="1" 
F 0 "#PWR043" H 7500 7700 50  0001 C CNN
F 1 "GND" H 7505 7777 50  0000 C CNN
F 2 "" H 7500 7950 50  0001 C CNN
F 3 "" H 7500 7950 50  0001 C CNN
	1    7500 7950
	1    0    0    -1  
$EndComp
$Comp
L power:+3.3V #PWR042
U 1 1 674F3438
P 7500 7650
F 0 "#PWR042" H 7500 7500 50  0001 C CNN
F 1 "+3.3V" H 7515 7823 50  0000 C CNN
F 2 "" H 7500 7650 50  0001 C CNN
F 3 "" H 7500 7650 50  0001 C CNN
	1    7500 7650
	1    0    0    -1  
$EndComp
$Comp
L Amplifier_Operational:MCP6001-OT U18
U 1 1 675B7446
P 16850 13200
F 0 "U18" H 16900 13500 50  0000 L CNN
F 1 "MCP6001-OT" H 16800 13400 50  0000 L CNN
F 2 "Package_TO_SOT_SMD:SOT-353_SC-70-5" H 16750 13000 50  0001 L CNN
F 3 "http://ww1.microchip.com/downloads/en/DeviceDoc/21733j.pdf" H 16850 13400 50  0001 C CNN
	1    16850 13200
	1    0    0    -1  
$EndComp
$Comp
L Amplifier_Operational:MCP6001-OT U17
U 1 1 675BC910
P 16450 14950
F 0 "U17" H 16500 15250 50  0000 L CNN
F 1 "MCP6001-OT" H 16450 15150 50  0000 L CNN
F 2 "Package_TO_SOT_SMD:SOT-353_SC-70-5" H 16350 14750 50  0001 L CNN
F 3 "http://ww1.microchip.com/downloads/en/DeviceDoc/21733j.pdf" H 16450 15150 50  0001 C CNN
	1    16450 14950
	1    0    0    -1  
$EndComp
Wire Wire Line
	17400 14950 17200 14950
Wire Wire Line
	17000 14950 16800 14950
Wire Wire Line
	16800 14950 16800 15300
Wire Wire Line
	16800 15300 16750 15300
Wire Wire Line
	16750 14950 16800 14950
Connection ~ 16800 14950
Wire Wire Line
	16550 15300 16100 15300
Wire Wire Line
	16100 15300 16100 15050
Wire Wire Line
	16100 15050 16150 15050
Wire Wire Line
	16150 14850 15700 14850
Connection ~ 15700 14850
Wire Wire Line
	14700 14850 14350 14850
Connection ~ 14700 14850
$Comp
L power:GND #PWR?
U 1 1 6828C1D0
P 16350 15400
AR Path="/60056272/6828C1D0" Ref="#PWR?"  Part="1" 
AR Path="/6828C1D0" Ref="#PWR090"  Part="1" 
F 0 "#PWR090" H 16350 15150 50  0001 C CNN
F 1 "GND" H 16355 15227 50  0000 C CNN
F 2 "" H 16350 15400 50  0001 C CNN
F 3 "" H 16350 15400 50  0001 C CNN
	1    16350 15400
	1    0    0    -1  
$EndComp
Wire Wire Line
	16350 15250 16350 15400
$Comp
L power:+3.3V #PWR?
U 1 1 6834E1AE
P 16350 14650
AR Path="/60056272/6834E1AE" Ref="#PWR?"  Part="1" 
AR Path="/6834E1AE" Ref="#PWR089"  Part="1" 
F 0 "#PWR089" H 16350 14500 50  0001 C CNN
F 1 "+3.3V" H 16365 14823 50  0000 C CNN
F 2 "" H 16350 14650 50  0001 C CNN
F 3 "" H 16350 14650 50  0001 C CNN
	1    16350 14650
	1    0    0    -1  
$EndComp
$Comp
L Device:C_Small C49
U 1 1 6834E6BC
P 18100 15450
F 0 "C49" H 18192 15496 50  0000 L CNN
F 1 "100nF" H 18192 15405 50  0000 L CNN
F 2 "Capacitor_SMD:C_0603_1608Metric" H 18100 15450 50  0001 C CNN
F 3 "~" H 18100 15450 50  0001 C CNN
	1    18100 15450
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR?
U 1 1 6834ECE4
P 18100 15550
AR Path="/60056272/6834ECE4" Ref="#PWR?"  Part="1" 
AR Path="/6834ECE4" Ref="#PWR0102"  Part="1" 
F 0 "#PWR0102" H 18100 15300 50  0001 C CNN
F 1 "GND" H 18105 15377 50  0000 C CNN
F 2 "" H 18100 15550 50  0001 C CNN
F 3 "" H 18100 15550 50  0001 C CNN
	1    18100 15550
	1    0    0    -1  
$EndComp
$Comp
L power:+3.3V #PWR?
U 1 1 6834F06A
P 18100 15350
AR Path="/60056272/6834F06A" Ref="#PWR?"  Part="1" 
AR Path="/6834F06A" Ref="#PWR0101"  Part="1" 
F 0 "#PWR0101" H 18100 15200 50  0001 C CNN
F 1 "+3.3V" H 18115 15523 50  0000 C CNN
F 2 "" H 18100 15350 50  0001 C CNN
F 3 "" H 18100 15350 50  0001 C CNN
	1    18100 15350
	1    0    0    -1  
$EndComp
Wire Wire Line
	17600 14950 17400 14950
Connection ~ 17400 14950
Wire Wire Line
	16750 13500 16750 13650
$Comp
L power:GND #PWR?
U 1 1 68A15CD2
P 16750 13650
AR Path="/60056272/68A15CD2" Ref="#PWR?"  Part="1" 
AR Path="/68A15CD2" Ref="#PWR093"  Part="1" 
F 0 "#PWR093" H 16750 13400 50  0001 C CNN
F 1 "GND" H 16755 13477 50  0000 C CNN
F 2 "" H 16750 13650 50  0001 C CNN
F 3 "" H 16750 13650 50  0001 C CNN
	1    16750 13650
	1    0    0    -1  
$EndComp
$Comp
L power:+3.3V #PWR?
U 1 1 68A15F29
P 16750 12850
AR Path="/60056272/68A15F29" Ref="#PWR?"  Part="1" 
AR Path="/68A15F29" Ref="#PWR092"  Part="1" 
F 0 "#PWR092" H 16750 12700 50  0001 C CNN
F 1 "+3.3V" H 16765 13023 50  0000 C CNN
F 2 "" H 16750 12850 50  0001 C CNN
F 3 "" H 16750 12850 50  0001 C CNN
	1    16750 12850
	1    0    0    -1  
$EndComp
Wire Wire Line
	16750 12850 16750 12900
Wire Wire Line
	9650 9100 9950 9100
Text Label 6800 12350 0    50   ~ 0
DIN_3
$Comp
L Isolator:PC817 U11
U 1 1 610EC634
P 8900 13550
F 0 "U11" H 8900 13875 50  0000 C CNN
F 1 "PC817" H 8900 13784 50  0000 C CNN
F 2 "Package_DIP:DIP-4_W7.62mm" H 8700 13350 50  0001 L CIN
F 3 "http://www.soselectronic.cz/a_info/resource/d/pc817.pdf" H 8900 13550 50  0001 L CNN
	1    8900 13550
	1    0    0    -1  
$EndComp
Wire Wire Line
	9200 13650 9300 13650
Connection ~ 9300 13650
Wire Wire Line
	9300 13650 9300 13700
Wire Wire Line
	9200 13450 9550 13450
$Comp
L Device:R R34
U 1 1 6126F6EA
P 8300 13450
F 0 "R34" V 8093 13450 50  0000 C CNN
F 1 "3.3k" V 8184 13450 50  0000 C CNN
F 2 "Resistor_SMD:R_0603_1608Metric" V 8230 13450 50  0001 C CNN
F 3 "~" H 8300 13450 50  0001 C CNN
	1    8300 13450
	0    1    1    0   
$EndComp
Wire Wire Line
	8600 13450 8450 13450
Wire Wire Line
	8600 13650 8500 13650
Connection ~ 8500 13650
Wire Wire Line
	8500 13650 8500 13700
Wire Wire Line
	8150 13450 8050 13450
Text Label 8050 13450 2    50   ~ 0
DIN_3
Text Label 9750 13450 0    50   ~ 0
DIN_3_MCU
$Comp
L Device:R R44
U 1 1 614B86B9
P 9550 13300
F 0 "R44" H 9480 13254 50  0000 R CNN
F 1 "10k" H 9480 13345 50  0000 R CNN
F 2 "Resistor_SMD:R_0603_1608Metric" V 9480 13300 50  0001 C CNN
F 3 "~" H 9550 13300 50  0001 C CNN
	1    9550 13300
	-1   0    0    1   
$EndComp
$Comp
L power:+3.3V #PWR?
U 1 1 614B8E55
P 9550 13150
AR Path="/60056272/614B8E55" Ref="#PWR?"  Part="1" 
AR Path="/614B8E55" Ref="#PWR054"  Part="1" 
F 0 "#PWR054" H 9550 13000 50  0001 C CNN
F 1 "+3.3V" H 9565 13323 50  0000 C CNN
F 2 "" H 9550 13150 50  0001 C CNN
F 3 "" H 9550 13150 50  0001 C CNN
	1    9550 13150
	1    0    0    -1  
$EndComp
Connection ~ 9550 13450
Wire Wire Line
	9550 13450 9750 13450
$Comp
L Connector_Generic:Conn_01x04 J7
U 1 1 615C7C55
P 3000 2150
F 0 "J7" H 3080 2142 50  0000 L CNN
F 1 "Conn_01x04" H 3080 2051 50  0000 L CNN
F 2 "TerminalBlock_MetzConnect:TerminalBlock_MetzConnect_Type086_RT03404HBLC_1x04_P3.81mm_Horizontal" H 3000 2150 50  0001 C CNN
F 3 "~" H 3000 2150 50  0001 C CNN
	1    3000 2150
	1    0    0    -1  
$EndComp
Text Label 19000 6550 0    50   ~ 0
DIN_3_MCU
$Comp
L Device:R_Small R92
U 1 1 61B459C2
P 11650 3850
F 0 "R92" H 11591 3804 50  0000 R CNN
F 1 "10k" H 11591 3895 50  0000 R CNN
F 2 "Resistor_SMD:R_0603_1608Metric" H 11650 3850 50  0001 C CNN
F 3 "~" H 11650 3850 50  0001 C CNN
	1    11650 3850
	-1   0    0    1   
$EndComp
$Comp
L power:GND #PWR?
U 1 1 61B45FA1
P 11650 4000
AR Path="/601B5445/61B45FA1" Ref="#PWR?"  Part="1" 
AR Path="/61B45FA1" Ref="#PWR0125"  Part="1" 
F 0 "#PWR0125" H 11650 3750 50  0001 C CNN
F 1 "GND" H 11655 3827 50  0000 C CNN
F 2 "" H 11650 4000 50  0001 C CNN
F 3 "" H 11650 4000 50  0001 C CNN
	1    11650 4000
	1    0    0    -1  
$EndComp
Wire Wire Line
	11650 4000 11650 3950
Wire Wire Line
	11650 3750 11650 3700
Connection ~ 11650 3700
$Comp
L Device:D_Schottky_Small_ALT D11
U 1 1 61E6BA18
P 11200 3050
F 0 "D11" V 11154 3118 50  0000 L CNN
F 1 "SD103BW" V 11245 3118 50  0000 L CNN
F 2 "Diode_SMD:D_SOD-123" V 11200 3050 50  0001 C CNN
F 3 "~" V 11200 3050 50  0001 C CNN
	1    11200 3050
	0    1    1    0   
$EndComp
Wire Wire Line
	11200 3150 11200 3300
Wire Wire Line
	11200 3300 10900 3300
Connection ~ 10900 3300
Wire Wire Line
	11200 2950 11200 2700
Connection ~ 11200 2700
Wire Wire Line
	11200 2700 10900 2700
Wire Wire Line
	18400 7950 18500 7950
Wire Wire Line
	18500 7950 18500 7850
Connection ~ 18400 7950
$Comp
L power:GND #PWR?
U 1 1 625A818C
P 20600 4150
AR Path="/60056272/625A818C" Ref="#PWR?"  Part="1" 
AR Path="/625A818C" Ref="#PWR0100"  Part="1" 
F 0 "#PWR0100" H 20600 3900 50  0001 C CNN
F 1 "GND" H 20605 3977 50  0000 C CNN
F 2 "" H 20600 4150 50  0001 C CNN
F 3 "" H 20600 4150 50  0001 C CNN
	1    20600 4150
	1    0    0    -1  
$EndComp
$Comp
L Mechanical:MountingHole H1
U 1 1 60E33967
P 14850 850
F 0 "H1" H 14950 896 50  0000 L CNN
F 1 "M3" H 14950 805 50  0000 L CNN
F 2 "MountingHole:MountingHole_3.2mm_M3" H 14850 850 50  0001 C CNN
F 3 "~" H 14850 850 50  0001 C CNN
	1    14850 850 
	1    0    0    -1  
$EndComp
$Comp
L Mechanical:MountingHole H3
U 1 1 60E36130
P 15300 850
F 0 "H3" H 15400 896 50  0000 L CNN
F 1 "M3" H 15400 805 50  0000 L CNN
F 2 "MountingHole:MountingHole_3.2mm_M3" H 15300 850 50  0001 C CNN
F 3 "~" H 15300 850 50  0001 C CNN
	1    15300 850 
	1    0    0    -1  
$EndComp
$Comp
L Mechanical:MountingHole H4
U 1 1 60E36475
P 15300 1100
F 0 "H4" H 15400 1146 50  0000 L CNN
F 1 "M3" H 15400 1055 50  0000 L CNN
F 2 "MountingHole:MountingHole_3.2mm_M3" H 15300 1100 50  0001 C CNN
F 3 "~" H 15300 1100 50  0001 C CNN
	1    15300 1100
	1    0    0    -1  
$EndComp
$Comp
L Mechanical:MountingHole H2
U 1 1 60E366BA
P 14850 1100
F 0 "H2" H 14950 1146 50  0000 L CNN
F 1 "M3" H 14950 1055 50  0000 L CNN
F 2 "MountingHole:MountingHole_3.2mm_M3" H 14850 1100 50  0001 C CNN
F 3 "~" H 14850 1100 50  0001 C CNN
	1    14850 1100
	1    0    0    -1  
$EndComp
Wire Wire Line
	9300 7950 9950 7950
Wire Wire Line
	9300 8150 9850 8150
Wire Wire Line
	9300 8250 10100 8250
Wire Wire Line
	13050 7600 13350 7600
Wire Wire Line
	13350 7600 13350 8150
Connection ~ 13050 7600
Connection ~ 13350 8150
$Comp
L Connector_Generic:Conn_01x03 J12
U 1 1 61ED3F52
P 13900 10250
F 0 "J12" H 13980 10292 50  0000 L CNN
F 1 "Conn_01x03" H 13980 10201 50  0000 L CNN
F 2 "Connector_Molex:Molex_Micro-Fit_3.0_43650-0315_1x03_P3.00mm_Vertical" H 13900 10250 50  0001 C CNN
F 3 "~" H 13900 10250 50  0001 C CNN
	1    13900 10250
	1    0    0    1   
$EndComp
Wire Wire Line
	13700 10350 13650 10350
Wire Wire Line
	13650 10800 13700 10800
Wire Wire Line
	13650 10350 13650 10800
Wire Wire Line
	13650 10800 13650 11200
Connection ~ 13650 10800
$Comp
L power:Earth #PWR0105
U 1 1 61A98629
P 13650 11250
F 0 "#PWR0105" H 13650 11000 50  0001 C CNN
F 1 "Earth" H 13650 11100 50  0001 C CNN
F 2 "" H 13650 11250 50  0001 C CNN
F 3 "~" H 13650 11250 50  0001 C CNN
	1    13650 11250
	1    0    0    -1  
$EndComp
Text Notes 13400 11450 0    50   ~ 0
CAR CHASSIS
Wire Wire Line
	13650 11200 14150 11200
Connection ~ 13650 11200
Wire Wire Line
	13650 11200 13650 11250
$Comp
L Mechanical:MountingHole_Pad H5
U 1 1 60EE119C
P 14150 11050
F 0 "H5" H 14250 11099 50  0000 L CNN
F 1 "CHASSIS" H 14250 11008 50  0000 L CNN
F 2 "Connector_Pin:Pin_D1.0mm_L10.0mm" H 14150 11050 50  0001 C CNN
F 3 "~" H 14150 11050 50  0001 C CNN
	1    14150 11050
	1    0    0    -1  
$EndComp
Wire Wire Line
	14150 11150 14150 11200
$Comp
L power:Earth #PWR055
U 1 1 61709438
P 14350 11500
F 0 "#PWR055" H 14350 11250 50  0001 C CNN
F 1 "Earth" H 14350 11350 50  0001 C CNN
F 2 "" H 14350 11500 50  0001 C CNN
F 3 "~" H 14350 11500 50  0001 C CNN
	1    14350 11500
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR?
U 1 1 61709A26
P 14650 11500
AR Path="/601B5445/61709A26" Ref="#PWR?"  Part="1" 
AR Path="/61709A26" Ref="#PWR0106"  Part="1" 
F 0 "#PWR0106" H 14650 11250 50  0001 C CNN
F 1 "GND" H 14655 11327 50  0000 C CNN
F 2 "" H 14650 11500 50  0001 C CNN
F 3 "" H 14650 11500 50  0001 C CNN
	1    14650 11500
	1    0    0    -1  
$EndComp
$Comp
L Device:R_Small R81
U 1 1 6170A02C
P 14500 11450
F 0 "R81" V 14304 11450 50  0000 C CNN
F 1 "0" V 14395 11450 50  0000 C CNN
F 2 "Resistor_SMD:R_0603_1608Metric" H 14500 11450 50  0001 C CNN
F 3 "~" H 14500 11450 50  0001 C CNN
	1    14500 11450
	0    1    1    0   
$EndComp
Wire Wire Line
	14400 11450 14350 11450
Wire Wire Line
	14350 11450 14350 11500
Wire Wire Line
	14600 11450 14650 11450
Wire Wire Line
	14650 11450 14650 11500
Text Label 17600 6550 2    50   ~ 0
AMS_FAULT_MCU
Text Label 14750 7150 0    50   ~ 0
MCU_UART_TX
Text Label 14750 7350 0    50   ~ 0
MCU_UART_RX
$Comp
L Device:R_Small R94
U 1 1 612E202A
P 14550 7000
F 0 "R94" H 14491 6954 50  0000 R CNN
F 1 "10k" H 14491 7045 50  0000 R CNN
F 2 "Resistor_SMD:R_0603_1608Metric" H 14550 7000 50  0001 C CNN
F 3 "~" H 14550 7000 50  0001 C CNN
	1    14550 7000
	-1   0    0    1   
$EndComp
$Comp
L Device:R_Small R93
U 1 1 612E24BA
P 14300 7000
F 0 "R93" H 14241 6954 50  0000 R CNN
F 1 "10k" H 14241 7045 50  0000 R CNN
F 2 "Resistor_SMD:R_0603_1608Metric" H 14300 7000 50  0001 C CNN
F 3 "~" H 14300 7000 50  0001 C CNN
	1    14300 7000
	-1   0    0    1   
$EndComp
Wire Wire Line
	14750 7150 14300 7150
Wire Wire Line
	14750 7350 14550 7350
Wire Wire Line
	14300 7100 14300 7150
Connection ~ 14300 7150
Wire Wire Line
	14300 7150 14150 7150
Wire Wire Line
	14550 7100 14550 7350
Connection ~ 14550 7350
Wire Wire Line
	14550 7350 14150 7350
Wire Wire Line
	14300 6900 14300 6850
Wire Wire Line
	14300 6850 14550 6850
Wire Wire Line
	14550 6850 14550 6900
Wire Wire Line
	14300 6850 14300 6800
Connection ~ 14300 6850
$Comp
L power:+3.3V #PWR?
U 1 1 6178DDEE
P 14300 6800
AR Path="/60056272/6178DDEE" Ref="#PWR?"  Part="1" 
AR Path="/6178DDEE" Ref="#PWR0116"  Part="1" 
F 0 "#PWR0116" H 14300 6650 50  0001 C CNN
F 1 "+3.3V" H 14315 6973 50  0000 C CNN
F 2 "" H 14300 6800 50  0001 C CNN
F 3 "" H 14300 6800 50  0001 C CNN
	1    14300 6800
	1    0    0    -1  
$EndComp
Text Label 19000 5950 0    50   ~ 0
SWCLK
Text Label 19000 5850 0    50   ~ 0
SWDIO
$Comp
L power:GND #PWR?
U 1 1 6195E312
P 17350 4750
AR Path="/60056272/6195E312" Ref="#PWR?"  Part="1" 
AR Path="/6195E312" Ref="#PWR0126"  Part="1" 
F 0 "#PWR0126" H 17350 4500 50  0001 C CNN
F 1 "GND" H 17355 4577 50  0000 C CNN
F 2 "" H 17350 4750 50  0001 C CNN
F 3 "" H 17350 4750 50  0001 C CNN
	1    17350 4750
	0    1    1    0   
$EndComp
Wire Wire Line
	17350 4750 17600 4750
$EndSCHEMATC
