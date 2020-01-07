EESchema Schematic File Version 4
EELAYER 30 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 2 4
Title ""
Date ""
Rev ""
Comp ""
Comment1 ""
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
$Comp
L bq76920-rescue:bq76920-bq769xx U1
U 1 1 5D3344F1
P 3350 1350
AR Path="/5D3344F1" Ref="U1"  Part="1" 
AR Path="/5D32E153/5D3344F1" Ref="U1"  Part="1" 
F 0 "U1" H 3700 1615 50  0000 C CNN
F 1 "bq76920" H 3700 1524 50  0000 C CNN
F 2 "Package_SO:TSSOP-20_4.4x6.5mm_P0.65mm" H 4800 1400 50  0001 C CNN
F 3 "" H 4800 1400 50  0001 C CNN
	1    3350 1350
	1    0    0    -1  
$EndComp
Text HLabel 2800 1350 0    50   Input ~ 0
BAL_C5
Text HLabel 2800 1500 0    50   Input ~ 0
BAL_C4
Text HLabel 2800 1650 0    50   Input ~ 0
BAL_C3
Text HLabel 2800 1800 0    50   Input ~ 0
BAL_C2
Text HLabel 2800 1950 0    50   Input ~ 0
BAL_C1
Text HLabel 2800 2100 0    50   Input ~ 0
BAL_C0
Wire Wire Line
	2800 1350 3250 1350
Wire Wire Line
	2800 1500 3250 1500
Wire Wire Line
	3250 1650 2800 1650
Wire Wire Line
	2800 1800 3250 1800
Wire Wire Line
	3250 1950 2800 1950
Wire Wire Line
	2800 2100 3250 2100
$Comp
L Device:R_Small R5
U 1 1 5D4BB4AA
P 2600 5850
F 0 "R5" V 2700 5850 50  0000 C CNN
F 1 "WSHP28185L000FEA" V 2800 5850 50  0000 C CNN
F 2 "bq76920:WSHP28185L000FEA" H 2600 5850 50  0001 C CNN
F 3 "~" H 2600 5850 50  0001 C CNN
	1    2600 5850
	0    1    1    0   
$EndComp
Text HLabel 1600 5850 0    50   Input ~ 0
BATT-
$Comp
L Device:C_Small C1
U 1 1 5D4BE1A9
P 2150 5250
F 0 "C1" V 1921 5250 50  0000 C CNN
F 1 "100n" V 2012 5250 50  0000 C CNN
F 2 "Capacitor_SMD:C_0805_2012Metric_Pad1.15x1.40mm_HandSolder" H 2150 5250 50  0001 C CNN
F 3 "~" H 2150 5250 50  0001 C CNN
	1    2150 5250
	0    1    1    0   
$EndComp
$Comp
L Device:C_Small C2
U 1 1 5D4BF012
P 2600 5250
F 0 "C2" V 2371 5250 50  0000 C CNN
F 1 "100n" V 2462 5250 50  0000 C CNN
F 2 "Capacitor_SMD:C_0805_2012Metric_Pad1.15x1.40mm_HandSolder" H 2600 5250 50  0001 C CNN
F 3 "~" H 2600 5250 50  0001 C CNN
	1    2600 5250
	0    1    1    0   
$EndComp
$Comp
L Device:C_Small C3
U 1 1 5D4BF1AC
P 3000 5250
F 0 "C3" V 2771 5250 50  0000 C CNN
F 1 "100n" V 2862 5250 50  0000 C CNN
F 2 "Capacitor_SMD:C_0805_2012Metric_Pad1.15x1.40mm_HandSolder" H 3000 5250 50  0001 C CNN
F 3 "~" H 3000 5250 50  0001 C CNN
	1    3000 5250
	0    1    1    0   
$EndComp
Wire Wire Line
	2700 5850 2800 5850
$Comp
L power:GND #PWR05
U 1 1 5D4BFC28
P 2000 5300
F 0 "#PWR05" H 2000 5050 50  0001 C CNN
F 1 "GND" H 2005 5127 50  0000 C CNN
F 2 "" H 2000 5300 50  0001 C CNN
F 3 "" H 2000 5300 50  0001 C CNN
	1    2000 5300
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR07
U 1 1 5D4C049B
P 3150 5300
F 0 "#PWR07" H 3150 5050 50  0001 C CNN
F 1 "GND" H 3155 5127 50  0000 C CNN
F 2 "" H 3150 5300 50  0001 C CNN
F 3 "" H 3150 5300 50  0001 C CNN
	1    3150 5300
	1    0    0    -1  
$EndComp
Wire Wire Line
	2050 5250 2000 5250
Wire Wire Line
	2000 5250 2000 5300
Wire Wire Line
	3100 5250 3150 5250
Wire Wire Line
	3150 5250 3150 5300
Wire Wire Line
	2250 5250 2400 5250
Wire Wire Line
	2700 5250 2800 5250
$Comp
L Device:R_Small R6
U 1 1 5D4C87EC
P 2800 5500
F 0 "R6" H 2859 5546 50  0000 L CNN
F 1 "100" H 2859 5455 50  0000 L CNN
F 2 "Resistor_SMD:R_0805_2012Metric_Pad1.15x1.40mm_HandSolder" H 2800 5500 50  0001 C CNN
F 3 "~" H 2800 5500 50  0001 C CNN
	1    2800 5500
	1    0    0    -1  
$EndComp
Wire Wire Line
	2400 5600 2400 5850
Connection ~ 2400 5850
Wire Wire Line
	2400 5850 2500 5850
Connection ~ 2400 5250
Wire Wire Line
	2400 5250 2500 5250
Wire Wire Line
	2800 5400 2800 5250
Connection ~ 2800 5250
Wire Wire Line
	2800 5250 2900 5250
Wire Wire Line
	2800 5600 2800 5850
Wire Wire Line
	2400 2250 3250 2250
Wire Wire Line
	2800 2400 3250 2400
$Comp
L Device:R_Small R7
U 1 1 5D4CD997
P 3050 3550
F 0 "R7" H 3109 3596 50  0000 L CNN
F 1 "500k" H 3109 3505 50  0000 L CNN
F 2 "Resistor_SMD:R_0805_2012Metric_Pad1.15x1.40mm_HandSolder" H 3050 3550 50  0001 C CNN
F 3 "~" H 3050 3550 50  0001 C CNN
	1    3050 3550
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR06
U 1 1 5D4D1CE5
P 3050 3750
F 0 "#PWR06" H 3050 3500 50  0001 C CNN
F 1 "GND" H 3055 3577 50  0000 C CNN
F 2 "" H 3050 3750 50  0001 C CNN
F 3 "" H 3050 3750 50  0001 C CNN
	1    3050 3750
	1    0    0    -1  
$EndComp
Wire Wire Line
	3050 3650 3050 3700
Wire Wire Line
	3050 3700 3400 3700
Wire Wire Line
	3400 3700 3400 3650
Connection ~ 3050 3700
Wire Wire Line
	3050 3700 3050 3750
$Comp
L Device:R_Small R8
U 1 1 5D4D325D
P 3700 3350
F 0 "R8" V 3504 3350 50  0000 C CNN
F 1 "100" V 3595 3350 50  0000 C CNN
F 2 "Resistor_SMD:R_0805_2012Metric_Pad1.15x1.40mm_HandSolder" H 3700 3350 50  0001 C CNN
F 3 "~" H 3700 3350 50  0001 C CNN
	1    3700 3350
	0    1    1    0   
$EndComp
Text HLabel 3950 3350 2    50   Input ~ 0
~ALERT
Wire Wire Line
	3600 3350 3400 3350
Wire Wire Line
	3050 3350 3050 3450
Wire Wire Line
	3400 3450 3400 3350
Connection ~ 3400 3350
Wire Wire Line
	3400 3350 3050 3350
Wire Wire Line
	3800 3350 3950 3350
Wire Wire Line
	3050 3350 3050 2550
Wire Wire Line
	3050 2550 3250 2550
Connection ~ 3050 3350
$Comp
L Device:R_Small R4
U 1 1 5D4DA9CC
P 2550 650
F 0 "R4" V 2354 650 50  0000 C CNN
F 1 "10k" V 2445 650 50  0000 C CNN
F 2 "Resistor_SMD:R_0805_2012Metric_Pad1.15x1.40mm_HandSolder" H 2550 650 50  0001 C CNN
F 3 "~" H 2550 650 50  0001 C CNN
	1    2550 650 
	0    1    1    0   
$EndComp
Text HLabel 1650 950  0    50   Input ~ 0
BATT+
Wire Wire Line
	1650 950  2200 950 
Wire Wire Line
	2450 650  2200 650 
Wire Wire Line
	2200 650  2200 950 
Connection ~ 2200 950 
Wire Wire Line
	2200 950  2450 950 
$Comp
L Device:R_Small R10
U 1 1 5D4DC99C
P 4250 950
F 0 "R10" V 4054 950 50  0000 C CNN
F 1 "100" V 4145 950 50  0000 C CNN
F 2 "Resistor_SMD:R_0805_2012Metric_Pad1.15x1.40mm_HandSolder" H 4250 950 50  0001 C CNN
F 3 "~" H 4250 950 50  0001 C CNN
	1    4250 950 
	0    1    1    0   
$EndComp
$Comp
L Device:C_Small C5
U 1 1 5D4DECDB
P 4950 1100
F 0 "C5" H 4858 1054 50  0000 R CNN
F 1 "C1206C475K5RACTU" H 4858 1145 50  0000 R CNN
F 2 "Capacitor_SMD:C_1206_3216Metric_Pad1.42x1.75mm_HandSolder" H 4950 1100 50  0001 C CNN
F 3 "~" H 4950 1100 50  0001 C CNN
	1    4950 1100
	-1   0    0    1   
$EndComp
Wire Wire Line
	4150 1350 4450 1350
Wire Wire Line
	4450 1350 4450 950 
Wire Wire Line
	4450 950  4350 950 
Wire Wire Line
	4150 950  2950 950 
Wire Wire Line
	2650 650  2950 650 
Wire Wire Line
	2950 650  2950 950 
Connection ~ 2950 950 
Wire Wire Line
	2400 2250 2400 5250
Wire Wire Line
	2800 5250 2800 2400
Wire Wire Line
	4150 1500 4450 1500
Wire Wire Line
	4450 1500 4450 1350
Connection ~ 4450 1350
Wire Wire Line
	4150 2700 4400 2700
Wire Wire Line
	4150 2550 4500 2550
$Comp
L power:GND #PWR08
U 1 1 5D4EB710
P 4650 2550
F 0 "#PWR08" H 4650 2300 50  0001 C CNN
F 1 "GND" H 4655 2377 50  0000 C CNN
F 2 "" H 4650 2550 50  0001 C CNN
F 3 "" H 4650 2550 50  0001 C CNN
	1    4650 2550
	1    0    0    -1  
$EndComp
Wire Wire Line
	4150 2400 4650 2400
Wire Wire Line
	4650 2400 4650 2550
Wire Wire Line
	4150 2250 4800 2250
Wire Wire Line
	4800 2250 4800 3200
Wire Wire Line
	4150 2100 4900 2100
Wire Wire Line
	4900 2100 4900 3100
$Comp
L Device:R_Small R14
U 1 1 5D4F0850
P 7950 2900
F 0 "R14" H 7891 2854 50  0000 R CNN
F 1 "10k" H 7891 2945 50  0000 R CNN
F 2 "Resistor_SMD:R_0805_2012Metric_Pad1.15x1.40mm_HandSolder" H 7950 2900 50  0001 C CNN
F 3 "~" H 7950 2900 50  0001 C CNN
	1    7950 2900
	-1   0    0    1   
$EndComp
$Comp
L Device:R_Small R15
U 1 1 5D4F0CC1
P 8200 2900
F 0 "R15" H 8141 2854 50  0000 R CNN
F 1 "10k" H 8141 2945 50  0000 R CNN
F 2 "Resistor_SMD:R_0805_2012Metric_Pad1.15x1.40mm_HandSolder" H 8200 2900 50  0001 C CNN
F 3 "~" H 8200 2900 50  0001 C CNN
	1    8200 2900
	-1   0    0    1   
$EndComp
Text HLabel 10050 3100 2    50   Input ~ 0
SCL
Text HLabel 10050 3200 2    50   Input ~ 0
SDA
Wire Wire Line
	8200 3000 8200 3100
Wire Wire Line
	7950 3000 7950 3200
Text HLabel 5400 1950 2    50   Input ~ 0
BOOT
Text HLabel 5400 2050 2    50   Input ~ 0
BAT_THERM
$Comp
L Device:C_Small C6
U 1 1 5D4F54CC
P 5050 2200
F 0 "C6" H 4958 2154 50  0000 R CNN
F 1 "1n" H 4958 2245 50  0000 R CNN
F 2 "Capacitor_SMD:C_0805_2012Metric_Pad1.15x1.40mm_HandSolder" H 5050 2200 50  0001 C CNN
F 3 "~" H 5050 2200 50  0001 C CNN
	1    5050 2200
	-1   0    0    1   
$EndComp
$Comp
L power:GND #PWR010
U 1 1 5D4F63B5
P 5050 2400
F 0 "#PWR010" H 5050 2150 50  0001 C CNN
F 1 "GND" H 5055 2227 50  0000 C CNN
F 2 "" H 5050 2400 50  0001 C CNN
F 3 "" H 5050 2400 50  0001 C CNN
	1    5050 2400
	1    0    0    -1  
$EndComp
Wire Wire Line
	5050 2300 5050 2400
Wire Wire Line
	4150 1950 5050 1950
Wire Wire Line
	5050 1950 5050 2100
Wire Wire Line
	5050 1950 5300 1950
Connection ~ 5050 1950
Wire Wire Line
	5400 2050 5300 2050
Wire Wire Line
	5300 2050 5300 1950
Connection ~ 5300 1950
Wire Wire Line
	5300 1950 5400 1950
$Comp
L power:GND #PWR012
U 1 1 5D4FE6A8
P 6000 2200
F 0 "#PWR012" H 6000 1950 50  0001 C CNN
F 1 "GND" H 6005 2027 50  0000 C CNN
F 2 "" H 6000 2200 50  0001 C CNN
F 3 "" H 6000 2200 50  0001 C CNN
	1    6000 2200
	1    0    0    -1  
$EndComp
Wire Wire Line
	4150 1800 6000 1800
Wire Wire Line
	6000 1800 6000 1900
Wire Wire Line
	6000 2100 6000 2200
Wire Wire Line
	7950 1650 7950 2650
Wire Wire Line
	8200 2800 8200 2650
Wire Wire Line
	8200 2650 7950 2650
Connection ~ 7950 2650
Wire Wire Line
	7950 2650 7950 2800
Connection ~ 7950 1650
Text HLabel 10050 1650 2    50   Input ~ 0
REGOUT
$Comp
L power:GND #PWR014
U 1 1 5D508F7D
P 8550 2200
F 0 "#PWR014" H 8550 1950 50  0001 C CNN
F 1 "GND" H 8555 2027 50  0000 C CNN
F 2 "" H 8550 2200 50  0001 C CNN
F 3 "" H 8550 2200 50  0001 C CNN
	1    8550 2200
	1    0    0    -1  
$EndComp
Wire Wire Line
	8550 1900 8550 1650
Connection ~ 8550 1650
Wire Wire Line
	8550 2200 8550 2100
$Comp
L power:GND #PWR09
U 1 1 5D51670C
P 4950 1300
F 0 "#PWR09" H 4950 1050 50  0001 C CNN
F 1 "GND" H 4955 1127 50  0000 C CNN
F 2 "" H 4950 1300 50  0001 C CNN
F 3 "" H 4950 1300 50  0001 C CNN
	1    4950 1300
	1    0    0    -1  
$EndComp
Wire Wire Line
	4950 1200 4950 1300
Wire Wire Line
	4450 950  4950 950 
Wire Wire Line
	4950 950  4950 1000
Connection ~ 4450 950 
Connection ~ 2800 5850
$Comp
L bq76920-rescue:PSMN2R6-40YS-bq769xx Q1
U 1 1 5D528049
P 4400 5850
AR Path="/5D528049" Ref="Q1"  Part="1" 
AR Path="/5D32E153/5D528049" Ref="Q1"  Part="1" 
F 0 "Q1" H 4400 5527 50  0000 C CNN
F 1 "PSMN2R6-40YS" H 4400 5436 50  0000 C CNN
F 2 "Package_TO_SOT_SMD:LFPAK56" H 4300 6400 50  0001 C CNN
F 3 "" H 4400 5850 50  0001 C CNN
	1    4400 5850
	1    0    0    -1  
$EndComp
$Comp
L bq76920-rescue:PSMN2R6-40YS-bq769xx Q3
U 1 1 5D528754
P 5450 5850
AR Path="/5D528754" Ref="Q3"  Part="1" 
AR Path="/5D32E153/5D528754" Ref="Q3"  Part="1" 
F 0 "Q3" H 5450 5527 50  0000 C CNN
F 1 "PSMN2R6-40YS" H 5450 5436 50  0000 C CNN
F 2 "Package_TO_SOT_SMD:LFPAK56" H 5350 6400 50  0001 C CNN
F 3 "" H 5450 5850 50  0001 C CNN
	1    5450 5850
	-1   0    0    -1  
$EndComp
$Comp
L Device:R_Small R9
U 1 1 5D530EEA
P 3950 5600
F 0 "R9" H 4009 5646 50  0000 L CNN
F 1 "1Meg" H 4009 5555 50  0000 L CNN
F 2 "Resistor_SMD:R_0805_2012Metric_Pad1.15x1.40mm_HandSolder" H 3950 5600 50  0001 C CNN
F 3 "~" H 3950 5600 50  0001 C CNN
	1    3950 5600
	1    0    0    -1  
$EndComp
$Comp
L Device:R_Small R11
U 1 1 5D53266A
P 4400 5200
F 0 "R11" H 4459 5246 50  0000 L CNN
F 1 "10k" H 4459 5155 50  0000 L CNN
F 2 "Resistor_SMD:R_0805_2012Metric_Pad1.15x1.40mm_HandSolder" H 4400 5200 50  0001 C CNN
F 3 "~" H 4400 5200 50  0001 C CNN
	1    4400 5200
	1    0    0    -1  
$EndComp
Wire Wire Line
	4150 6050 4100 6050
Wire Wire Line
	4100 6050 4100 5950
Wire Wire Line
	2800 5850 3950 5850
Wire Wire Line
	3950 5700 3950 5850
Connection ~ 3950 5850
Wire Wire Line
	3950 5850 4100 5850
Wire Wire Line
	4150 5850 4100 5850
Connection ~ 4100 5850
Wire Wire Line
	4150 5950 4100 5950
Connection ~ 4100 5950
Wire Wire Line
	4100 5950 4100 5850
Wire Wire Line
	4400 5700 4400 5400
Wire Wire Line
	3950 5500 3950 5400
Wire Wire Line
	3950 5400 4400 5400
Connection ~ 4400 5400
Wire Wire Line
	4400 5400 4400 5300
Wire Wire Line
	4400 2700 4400 5100
$Comp
L Device:R_Small R13
U 1 1 5D5484F7
P 5850 5600
F 0 "R13" H 5909 5646 50  0000 L CNN
F 1 "1Meg" H 5909 5555 50  0000 L CNN
F 2 "Resistor_SMD:R_0805_2012Metric_Pad1.15x1.40mm_HandSolder" H 5850 5600 50  0001 C CNN
F 3 "~" H 5850 5600 50  0001 C CNN
	1    5850 5600
	1    0    0    -1  
$EndComp
$Comp
L Device:R_Small R12
U 1 1 5D548AEC
P 5450 5000
F 0 "R12" H 5509 5046 50  0000 L CNN
F 1 "1Meg" H 5509 4955 50  0000 L CNN
F 2 "Resistor_SMD:R_0805_2012Metric_Pad1.15x1.40mm_HandSolder" H 5450 5000 50  0001 C CNN
F 3 "~" H 5450 5000 50  0001 C CNN
	1    5450 5000
	1    0    0    -1  
$EndComp
$Comp
L Diode:1N4148 D2
U 1 1 5D54AC81
P 5800 4950
F 0 "D2" V 5846 4871 50  0000 R CNN
F 1 "PMEG3010BEA,115" V 5755 4871 50  0000 R CNN
F 2 "Diode_SMD:D_SOD-323_HandSoldering" H 5800 4775 50  0001 C CNN
F 3 "https://assets.nexperia.com/documents/data-sheet/1N4148_1N4448.pdf" H 5800 4950 50  0001 C CNN
	1    5800 4950
	0    -1   -1   0   
$EndComp
Wire Wire Line
	5200 5850 4650 5850
Wire Wire Line
	5450 5400 5450 5700
Wire Wire Line
	5700 5850 5750 5850
Wire Wire Line
	5850 5850 5850 5700
Wire Wire Line
	5850 5500 5850 5400
Wire Wire Line
	5850 5400 5450 5400
Wire Wire Line
	5450 5100 5450 5200
Connection ~ 5450 5400
Wire Wire Line
	5800 5100 5800 5200
Wire Wire Line
	5800 5200 5450 5200
Connection ~ 5450 5200
Wire Wire Line
	5450 5200 5450 5400
Wire Wire Line
	5800 4800 5800 4700
Wire Wire Line
	5800 4700 5450 4700
Wire Wire Line
	5450 4700 5450 4900
Wire Wire Line
	5700 5950 5750 5950
Wire Wire Line
	5750 5950 5750 5850
Connection ~ 5750 5850
Wire Wire Line
	5750 5850 5850 5850
Wire Wire Line
	5750 5950 5750 6050
Wire Wire Line
	5750 6050 5700 6050
Connection ~ 5750 5950
Wire Wire Line
	5850 5850 6600 5850
Connection ~ 5850 5850
Text HLabel 6600 5850 2    50   Input ~ 0
PACK-
$Comp
L Device:Q_PMOS_GSD Q2
U 1 1 5D5759F6
P 5350 4200
F 0 "Q2" H 5556 4154 50  0000 L CNN
F 1 "SI2337DS-T1-E3" H 5556 4245 50  0000 L CNN
F 2 "Package_TO_SOT_SMD:SOT-23" H 5550 4300 50  0001 C CNN
F 3 "~" H 5350 4200 50  0001 C CNN
	1    5350 4200
	1    0    0    1   
$EndComp
$Comp
L power:GND #PWR011
U 1 1 5D578E4E
P 5050 4300
F 0 "#PWR011" H 5050 4050 50  0001 C CNN
F 1 "GND" H 5055 4127 50  0000 C CNN
F 2 "" H 5050 4300 50  0001 C CNN
F 3 "" H 5050 4300 50  0001 C CNN
	1    5050 4300
	1    0    0    -1  
$EndComp
Wire Wire Line
	5050 4300 5050 4200
Wire Wire Line
	5050 4200 5150 4200
Wire Wire Line
	5450 4400 5450 4700
Connection ~ 5450 4700
Wire Wire Line
	5450 4000 5450 3850
Wire Wire Line
	5450 3850 4500 3850
Wire Wire Line
	4500 2550 4500 3850
Text Notes 2150 6450 0    50   ~ 0
rsense 5mohms, range +/- 200mV for 40A\n
$Comp
L Device:C_Small C4
U 1 1 5D4D0180
P 3400 3550
F 0 "C4" H 3308 3504 50  0000 R CNN
F 1 "1n" H 3308 3595 50  0000 R CNN
F 2 "Capacitor_SMD:C_0805_2012Metric_Pad1.15x1.40mm_HandSolder" H 3400 3550 50  0001 C CNN
F 3 "~" H 3400 3550 50  0001 C CNN
	1    3400 3550
	-1   0    0    1   
$EndComp
$Comp
L Device:C_Small C7
U 1 1 5D5401EB
P 6000 2000
F 0 "C7" H 5908 1954 50  0000 R CNN
F 1 "C1206C475K5RACTU" H 5950 2100 50  0000 R CNN
F 2 "Capacitor_SMD:C_1206_3216Metric_Pad1.42x1.75mm_HandSolder" H 6000 2000 50  0001 C CNN
F 3 "~" H 6000 2000 50  0001 C CNN
	1    6000 2000
	-1   0    0    1   
$EndComp
$Comp
L Device:C_Small C8
U 1 1 5D540575
P 8550 2000
F 0 "C8" H 8458 1954 50  0000 R CNN
F 1 "C1206C475K5RACTU" H 8458 2045 50  0000 R CNN
F 2 "Capacitor_SMD:C_1206_3216Metric_Pad1.42x1.75mm_HandSolder" H 8550 2000 50  0001 C CNN
F 3 "~" H 8550 2000 50  0001 C CNN
	1    8550 2000
	-1   0    0    1   
$EndComp
Wire Wire Line
	7950 1650 8550 1650
$Comp
L Diode:1N4148 D1
U 1 1 5D545BA2
P 2600 950
F 0 "D1" H 2700 850 50  0000 R CNN
F 1 "PMEG3010BEA,115" H 2900 1050 50  0000 R CNN
F 2 "Diode_SMD:D_SOD-323_HandSoldering" H 2600 775 50  0001 C CNN
F 3 "https://assets.nexperia.com/documents/data-sheet/1N4148_1N4448.pdf" H 2600 950 50  0001 C CNN
	1    2600 950 
	-1   0    0    1   
$EndComp
Wire Wire Line
	2750 950  2950 950 
Wire Wire Line
	2400 5400 2400 5250
$Comp
L Device:R_Small R3
U 1 1 5D4C7783
P 2400 5500
F 0 "R3" H 2459 5546 50  0000 L CNN
F 1 "100" H 2459 5455 50  0000 L CNN
F 2 "Resistor_SMD:R_0805_2012Metric_Pad1.15x1.40mm_HandSolder" H 2400 5500 50  0001 C CNN
F 3 "~" H 2400 5500 50  0001 C CNN
	1    2400 5500
	1    0    0    -1  
$EndComp
Wire Wire Line
	4900 3100 8200 3100
Wire Wire Line
	4800 3200 7950 3200
Wire Wire Line
	4150 1650 7950 1650
Wire Wire Line
	7950 3200 10050 3200
Connection ~ 7950 3200
Wire Wire Line
	8200 3100 10050 3100
Connection ~ 8200 3100
Wire Wire Line
	8550 1650 10050 1650
Wire Wire Line
	1600 5850 2400 5850
$EndSCHEMATC
