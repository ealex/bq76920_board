EESchema Schematic File Version 4
LIBS:bq76920-cache
EELAYER 26 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 4 4
Title ""
Date ""
Rev ""
Comp ""
Comment1 ""
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
Text HLabel 1150 900  0    50   Input ~ 0
VCC_3V3
Text HLabel 3850 3550 2    50   Input ~ 0
PACK_SCL
Text HLabel 3850 3650 2    50   Input ~ 0
PACK_SDA
$Comp
L MCU_ST_STM32L0:STM32L031F4Px U?
U 1 1 5E142A54
P 3100 3250
F 0 "U?" H 2750 3950 50  0000 C CNN
F 1 "STM32L031F4Px" H 3500 2450 50  0000 C CNN
F 2 "Package_SO:TSSOP-20_4.4x6.5mm_P0.65mm" H 2700 2550 50  0001 R CNN
F 3 "http://www.st.com/st-web-ui/static/active/en/resource/technical/document/datasheet/DM00140359.pdf" H 3100 3250 50  0001 C CNN
	1    3100 3250
	1    0    0    -1  
$EndComp
$Comp
L Connector_Generic:Conn_01x05 J?
U 1 1 5E133C66
P 1350 6550
F 0 "J?" H 1270 6967 50  0000 C CNN
F 1 "Conn_01x05" H 1270 6876 50  0000 C CNN
F 2 "" H 1350 6550 50  0001 C CNN
F 3 "~" H 1350 6550 50  0001 C CNN
	1    1350 6550
	-1   0    0    -1  
$EndComp
$Comp
L Device:R_Small R?
U 1 1 5E133DEA
P 2700 6200
F 0 "R?" H 2759 6246 50  0000 L CNN
F 1 "100k" H 2759 6155 50  0000 L CNN
F 2 "" H 2700 6200 50  0001 C CNN
F 3 "~" H 2700 6200 50  0001 C CNN
	1    2700 6200
	1    0    0    -1  
$EndComp
Wire Wire Line
	2700 6350 2700 6300
$Comp
L power:+3V3 #PWR?
U 1 1 5E133EE0
P 1300 800
F 0 "#PWR?" H 1300 650 50  0001 C CNN
F 1 "+3V3" H 1315 973 50  0000 C CNN
F 2 "" H 1300 800 50  0001 C CNN
F 3 "" H 1300 800 50  0001 C CNN
	1    1300 800 
	1    0    0    -1  
$EndComp
Wire Wire Line
	1300 800  1300 900 
Wire Wire Line
	1300 900  1150 900 
$Comp
L power:+3V3 #PWR?
U 1 1 5E133F22
P 2700 6000
F 0 "#PWR?" H 2700 5850 50  0001 C CNN
F 1 "+3V3" H 2715 6173 50  0000 C CNN
F 2 "" H 2700 6000 50  0001 C CNN
F 3 "" H 2700 6000 50  0001 C CNN
	1    2700 6000
	1    0    0    -1  
$EndComp
$Comp
L Device:C_Small C?
U 1 1 5E134013
P 2700 6500
F 0 "C?" H 2792 6546 50  0000 L CNN
F 1 "1n" H 2792 6455 50  0000 L CNN
F 2 "" H 2700 6500 50  0001 C CNN
F 3 "~" H 2700 6500 50  0001 C CNN
	1    2700 6500
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR?
U 1 1 5E1340FD
P 2700 6700
F 0 "#PWR?" H 2700 6450 50  0001 C CNN
F 1 "GND" H 2705 6527 50  0000 C CNN
F 2 "" H 2700 6700 50  0001 C CNN
F 3 "" H 2700 6700 50  0001 C CNN
	1    2700 6700
	1    0    0    -1  
$EndComp
Wire Wire Line
	1550 6350 2700 6350
Wire Wire Line
	2700 6400 2700 6350
Connection ~ 2700 6350
Wire Wire Line
	2700 6700 2700 6600
$Comp
L Device:R_Small R?
U 1 1 5E134235
P 1600 6950
F 0 "R?" H 1659 6996 50  0000 L CNN
F 1 "100k" H 1659 6905 50  0000 L CNN
F 2 "" H 1600 6950 50  0001 C CNN
F 3 "~" H 1600 6950 50  0001 C CNN
	1    1600 6950
	1    0    0    -1  
$EndComp
Text Label 2300 2950 0    50   ~ 0
BOOT0
Text Label 2300 2750 0    50   ~ 0
~NRST
Wire Wire Line
	2600 2750 2300 2750
Wire Wire Line
	2600 2950 2300 2950
Text Label 1700 6350 0    50   ~ 0
~NRST
Text Label 1700 6750 0    50   ~ 0
BOOT0
Wire Wire Line
	1550 6750 1600 6750
Wire Wire Line
	2700 6000 2700 6100
$Comp
L power:GND #PWR?
U 1 1 5E134F0A
P 1600 7150
F 0 "#PWR?" H 1600 6900 50  0001 C CNN
F 1 "GND" H 1605 6977 50  0000 C CNN
F 2 "" H 1600 7150 50  0001 C CNN
F 3 "" H 1600 7150 50  0001 C CNN
	1    1600 7150
	1    0    0    -1  
$EndComp
Wire Wire Line
	1600 7150 1600 7050
Wire Wire Line
	1600 6850 1600 6750
Connection ~ 1600 6750
Wire Wire Line
	1600 6750 1700 6750
$Comp
L power:GND #PWR?
U 1 1 5E13539F
P 2100 7150
F 0 "#PWR?" H 2100 6900 50  0001 C CNN
F 1 "GND" H 2105 6977 50  0000 C CNN
F 2 "" H 2100 7150 50  0001 C CNN
F 3 "" H 2100 7150 50  0001 C CNN
	1    2100 7150
	1    0    0    -1  
$EndComp
Wire Wire Line
	1550 6650 2100 6650
Wire Wire Line
	2100 6650 2100 7150
Wire Wire Line
	1550 6550 1700 6550
Wire Wire Line
	1550 6450 1700 6450
Text Label 3850 2950 0    50   ~ 0
USART2_TX
Text Label 3850 3050 0    50   ~ 0
USART2_RX
Text Label 3850 3750 0    50   ~ 0
SWDIO
Text Label 3850 3850 0    50   ~ 0
SWCLK
Wire Wire Line
	3600 3550 3850 3550
Wire Wire Line
	3600 3650 3850 3650
Wire Wire Line
	3600 3750 3850 3750
Wire Wire Line
	3600 3850 3850 3850
Text Label 1700 6450 0    50   ~ 0
SWDIO
Text Label 1700 6550 0    50   ~ 0
SWCLK
$Comp
L power:+3V3 #PWR?
U 1 1 5E1371AD
P 3100 2450
F 0 "#PWR?" H 3100 2300 50  0001 C CNN
F 1 "+3V3" H 3115 2623 50  0000 C CNN
F 2 "" H 3100 2450 50  0001 C CNN
F 3 "" H 3100 2450 50  0001 C CNN
	1    3100 2450
	1    0    0    -1  
$EndComp
Wire Wire Line
	3100 2450 3100 2500
Wire Wire Line
	3100 2500 3200 2500
Wire Wire Line
	3200 2500 3200 2550
Connection ~ 3100 2500
Wire Wire Line
	3100 2500 3100 2550
$Comp
L power:GND #PWR?
U 1 1 5E13770A
P 3100 4150
F 0 "#PWR?" H 3100 3900 50  0001 C CNN
F 1 "GND" H 3105 3977 50  0000 C CNN
F 2 "" H 3100 4150 50  0001 C CNN
F 3 "" H 3100 4150 50  0001 C CNN
	1    3100 4150
	1    0    0    -1  
$EndComp
Wire Wire Line
	3100 4050 3100 4150
Text HLabel 3850 2750 2    50   Input ~ 0
PACK_ALERT
Wire Wire Line
	3850 2750 3600 2750
$Comp
L bq769xx:ISO7021 U?
U 1 1 5E13BDED
P 6700 2850
F 0 "U?" H 7025 3115 50  0000 C CNN
F 1 "ISO7021" H 7025 3024 50  0000 C CNN
F 2 "" H 6700 2850 50  0001 C CNN
F 3 "" H 6700 2850 50  0001 C CNN
	1    6700 2850
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR?
U 1 1 5E13BED3
P 6550 3200
F 0 "#PWR?" H 6550 2950 50  0001 C CNN
F 1 "GND" H 6555 3027 50  0000 C CNN
F 2 "" H 6550 3200 50  0001 C CNN
F 3 "" H 6550 3200 50  0001 C CNN
	1    6550 3200
	1    0    0    -1  
$EndComp
Wire Wire Line
	6600 3150 6550 3150
Wire Wire Line
	6550 3200 6550 3150
$Comp
L power:+3V3 #PWR?
U 1 1 5E13D8E9
P 6550 2800
F 0 "#PWR?" H 6550 2650 50  0001 C CNN
F 1 "+3V3" H 6565 2973 50  0000 C CNN
F 2 "" H 6550 2800 50  0001 C CNN
F 3 "" H 6550 2800 50  0001 C CNN
	1    6550 2800
	1    0    0    -1  
$EndComp
Wire Wire Line
	6550 2800 6550 2850
Wire Wire Line
	6550 2850 6600 2850
$Comp
L Device:C_Small C?
U 1 1 5E13DDCE
P 1300 1050
F 0 "C?" H 1392 1096 50  0000 L CNN
F 1 "100nF" H 1392 1005 50  0000 L CNN
F 2 "" H 1300 1050 50  0001 C CNN
F 3 "~" H 1300 1050 50  0001 C CNN
	1    1300 1050
	1    0    0    -1  
$EndComp
$Comp
L Device:C_Small C?
U 1 1 5E13DE7D
P 1750 1050
F 0 "C?" H 1842 1096 50  0000 L CNN
F 1 "100nF" H 1842 1005 50  0000 L CNN
F 2 "" H 1750 1050 50  0001 C CNN
F 3 "~" H 1750 1050 50  0001 C CNN
	1    1750 1050
	1    0    0    -1  
$EndComp
$Comp
L Device:C_Small C?
U 1 1 5E13DFFD
P 2200 1050
F 0 "C?" H 2292 1096 50  0000 L CNN
F 1 "100nF" H 2292 1005 50  0000 L CNN
F 2 "" H 2200 1050 50  0001 C CNN
F 3 "~" H 2200 1050 50  0001 C CNN
	1    2200 1050
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR?
U 1 1 5E13E117
P 1300 1250
F 0 "#PWR?" H 1300 1000 50  0001 C CNN
F 1 "GND" H 1305 1077 50  0000 C CNN
F 2 "" H 1300 1250 50  0001 C CNN
F 3 "" H 1300 1250 50  0001 C CNN
	1    1300 1250
	1    0    0    -1  
$EndComp
Wire Wire Line
	1300 950  1300 900 
Connection ~ 1300 900 
Wire Wire Line
	1300 900  1750 900 
Wire Wire Line
	1750 900  1750 950 
Wire Wire Line
	1750 900  2200 900 
Wire Wire Line
	2200 900  2200 950 
Connection ~ 1750 900 
Wire Wire Line
	1300 1150 1300 1200
Wire Wire Line
	1300 1200 1750 1200
Wire Wire Line
	1750 1200 1750 1150
Connection ~ 1300 1200
Wire Wire Line
	1300 1200 1300 1250
Wire Wire Line
	1750 1200 2200 1200
Wire Wire Line
	2200 1200 2200 1150
Connection ~ 1750 1200
$Comp
L Device:C_Small C?
U 1 1 5E140D1B
P 8000 2400
F 0 "C?" H 8092 2446 50  0000 L CNN
F 1 "100nF" H 8092 2355 50  0000 L CNN
F 2 "" H 8000 2400 50  0001 C CNN
F 3 "~" H 8000 2400 50  0001 C CNN
	1    8000 2400
	1    0    0    -1  
$EndComp
$Comp
L Connector_Generic:Conn_01x02 J?
U 1 1 5E140FA3
P 4550 2950
F 0 "J?" H 4630 2942 50  0000 L CNN
F 1 "Conn_01x02" H 4630 2851 50  0000 L CNN
F 2 "" H 4550 2950 50  0001 C CNN
F 3 "~" H 4550 2950 50  0001 C CNN
	1    4550 2950
	1    0    0    -1  
$EndComp
Text HLabel 8550 2250 2    50   Input ~ 0
ISOL_VCC
Text HLabel 7550 2950 2    50   Input ~ 0
ISOL_RX
Text HLabel 7550 3050 2    50   Input ~ 0
ISOL_TX
Text HLabel 8550 2550 2    50   Input ~ 0
ISOL_GND
Wire Wire Line
	7450 2850 7650 2850
Wire Wire Line
	7650 2850 7650 2250
Wire Wire Line
	7650 2250 8000 2250
Wire Wire Line
	8000 2300 8000 2250
Connection ~ 8000 2250
Wire Wire Line
	8000 2250 8550 2250
Wire Wire Line
	8000 2500 8000 2550
Wire Wire Line
	8000 2550 8550 2550
Wire Wire Line
	8000 2550 8000 3150
Wire Wire Line
	8000 3150 7450 3150
Connection ~ 8000 2550
Wire Wire Line
	7450 2950 7550 2950
Wire Wire Line
	7450 3050 7550 3050
Text Label 6050 3050 0    50   ~ 0
USART2_TX
Text Label 5900 2950 0    50   ~ 0
USART2_RX
Wire Wire Line
	3600 2950 4350 2950
Wire Wire Line
	3600 3050 4350 3050
Wire Wire Line
	5900 2950 6600 2950
Wire Wire Line
	6600 3050 6050 3050
$EndSCHEMATC
