EESchema Schematic File Version 4
EELAYER 30 0
EELAYER END
$Descr A3 16535 11693
encoding utf-8
Sheet 2 2
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
L Regulator_Linear:LT3093xMSE U?
U 1 1 63D5AD06
P 7375 5225
AR Path="/63D5AD06" Ref="U?"  Part="1" 
AR Path="/63D4AE42/63D5AD06" Ref="U?"  Part="1" 
AR Path="/621F15CD/63D5AD06" Ref="U6"  Part="1" 
F 0 "U6" H 7375 5692 50  0000 C CNN
F 1 "LT3093xMSE" H 7375 5601 50  0000 C CNN
F 2 "Package_SO:MSOP-12-1EP_3x4mm_P0.65mm_EP1.65x2.85mm_ThermalVias_opt" H 7375 5650 50  0001 C CNN
F 3 "https://www.analog.com/media/en/technical-documentation/data-sheets/lt3093.pdf" H 7375 5325 50  0001 C CNN
	1    7375 5225
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR?
U 1 1 63D5AD1E
P 2700 2425
AR Path="/63D5AD1E" Ref="#PWR?"  Part="1" 
AR Path="/63D4AE42/63D5AD1E" Ref="#PWR?"  Part="1" 
AR Path="/621F15CD/63D5AD1E" Ref="#PWR044"  Part="1" 
F 0 "#PWR044" H 2700 2175 50  0001 C CNN
F 1 "GND" H 2705 2252 50  0000 C CNN
F 2 "" H 2700 2425 50  0001 C CNN
F 3 "" H 2700 2425 50  0001 C CNN
	1    2700 2425
	1    0    0    -1  
$EndComp
Wire Wire Line
	6975 5025 6825 5025
Wire Wire Line
	6975 5125 6825 5125
Wire Wire Line
	6825 5125 6825 5025
Connection ~ 6825 5025
Wire Wire Line
	6975 5225 6825 5225
NoConn ~ 6975 5325
Wire Wire Line
	6975 5425 6825 5425
Wire Wire Line
	6575 5425 6575 5500
Wire Wire Line
	6575 5800 6575 5850
Wire Wire Line
	6575 5850 6825 5850
$Comp
L Device:CP1_Small C?
U 1 1 63D5AD50
P 6825 5650
AR Path="/63D5AD50" Ref="C?"  Part="1" 
AR Path="/63D4AE42/63D5AD50" Ref="C?"  Part="1" 
AR Path="/621F15CD/63D5AD50" Ref="C30"  Part="1" 
F 0 "C30" H 6600 5650 50  0000 L CNN
F 1 "22uF/50V" H 6375 5725 50  0000 L CNN
F 2 "Capacitor_Tantalum_SMD:CP_EIA-7343-31_Kemet-D" H 6825 5650 50  0001 C CNN
F 3 "~" H 6825 5650 50  0001 C CNN
	1    6825 5650
	-1   0    0    1   
$EndComp
Wire Wire Line
	6825 5850 6825 5750
Wire Wire Line
	6825 5550 6825 5425
Connection ~ 6825 5425
Wire Wire Line
	6825 5425 6575 5425
Wire Wire Line
	6950 1825 6775 1825
Wire Wire Line
	6775 1825 6775 1725
Connection ~ 6775 1725
Wire Wire Line
	6775 1725 6950 1725
$Comp
L Device:R_US R?
U 1 1 63D5AD83
P 8450 2325
AR Path="/63D5AD83" Ref="R?"  Part="1" 
AR Path="/63D4AE42/63D5AD83" Ref="R?"  Part="1" 
AR Path="/621F15CD/63D5AD83" Ref="R46"  Part="1" 
F 0 "R46" H 8518 2371 50  0000 L CNN
F 1 "30k1" H 8518 2280 50  0000 L CNN
F 2 "Resistor_SMD:R_0603_1608Metric_Outline" V 8490 2315 50  0001 C CNN
F 3 "~" H 8450 2325 50  0001 C CNN
	1    8450 2325
	1    0    0    -1  
$EndComp
Wire Wire Line
	8450 2475 8450 2525
$Comp
L Device:CP1_Small C?
U 1 1 63D5AD8A
P 7300 2550
AR Path="/63D5AD8A" Ref="C?"  Part="1" 
AR Path="/63D4AE42/63D5AD8A" Ref="C?"  Part="1" 
AR Path="/621F15CD/63D5AD8A" Ref="C31"  Part="1" 
F 0 "C31" H 7375 2575 50  0000 L CNN
F 1 "22uF/50V" H 7375 2500 50  0000 L CNN
F 2 "Capacitor_Tantalum_SMD:CP_EIA-7343-31_Kemet-D" H 7300 2550 50  0001 C CNN
F 3 "~" H 7300 2550 50  0001 C CNN
	1    7300 2550
	1    0    0    -1  
$EndComp
$Comp
L Device:R_US R?
U 1 1 63D5AD90
P 6950 2525
AR Path="/63D5AD90" Ref="R?"  Part="1" 
AR Path="/63D4AE42/63D5AD90" Ref="R?"  Part="1" 
AR Path="/621F15CD/63D5AD90" Ref="R44"  Part="1" 
F 0 "R44" H 6725 2550 50  0000 L CNN
F 1 "75k" H 6725 2475 50  0000 L CNN
F 2 "Resistor_SMD:R_0603_1608Metric_Outline" V 6990 2515 50  0001 C CNN
F 3 "~" H 6950 2525 50  0001 C CNN
	1    6950 2525
	1    0    0    -1  
$EndComp
Wire Wire Line
	6950 2675 6950 2700
Wire Wire Line
	7300 2650 7300 2700
Wire Wire Line
	6950 1925 6650 1925
Text Label 6450 1925 0    50   ~ 0
PG+
Wire Wire Line
	7775 5025 7800 5025
Wire Wire Line
	7800 5025 7800 4975
Wire Wire Line
	6150 1925 6150 1725
Wire Wire Line
	7750 1725 7750 1575
Wire Wire Line
	8450 1575 8450 1600
Wire Wire Line
	1925 1725 2275 1725
Wire Wire Line
	1925 3375 2275 3375
$Comp
L power:GND #PWR?
U 1 1 64A334B1
P 8675 5950
AR Path="/64A334B1" Ref="#PWR?"  Part="1" 
AR Path="/63D4AE42/64A334B1" Ref="#PWR?"  Part="1" 
AR Path="/621F15CD/64A334B1" Ref="#PWR048"  Part="1" 
F 0 "#PWR048" H 8675 5700 50  0001 C CNN
F 1 "GND" H 8680 5777 50  0000 C CNN
F 2 "" H 8675 5950 50  0001 C CNN
F 3 "" H 8675 5950 50  0001 C CNN
	1    8675 5950
	1    0    0    -1  
$EndComp
Wire Wire Line
	8675 4975 8675 5050
$Comp
L Device:R_US R?
U 1 1 61DA3E16
P 8450 1750
AR Path="/61DA3E16" Ref="R?"  Part="1" 
AR Path="/63D4AE42/61DA3E16" Ref="R?"  Part="1" 
AR Path="/621F15CD/61DA3E16" Ref="R45"  Part="1" 
F 0 "R45" H 8518 1796 50  0000 L CNN
F 1 "680k" H 8518 1705 50  0000 L CNN
F 2 "Resistor_SMD:R_0603_1608Metric_Outline" V 8490 1740 50  0001 C CNN
F 3 "~" H 8450 1750 50  0001 C CNN
	1    8450 1750
	1    0    0    -1  
$EndComp
$Comp
L Device:R_US R?
U 1 1 61DB8E93
P 8675 5200
AR Path="/61DB8E93" Ref="R?"  Part="1" 
AR Path="/63D4AE42/61DB8E93" Ref="R?"  Part="1" 
AR Path="/621F15CD/61DB8E93" Ref="R47"  Part="1" 
F 0 "R47" H 8743 5246 50  0000 L CNN
F 1 "680k" H 8743 5155 50  0000 L CNN
F 2 "Resistor_SMD:R_0603_1608Metric_Outline" V 8715 5190 50  0001 C CNN
F 3 "~" H 8675 5200 50  0001 C CNN
	1    8675 5200
	1    0    0    -1  
$EndComp
$Comp
L power:+7.5V #PWR049
U 1 1 6223DD7D
P 8450 1575
F 0 "#PWR049" H 8450 1425 50  0001 C CNN
F 1 "+7.5V" H 8465 1748 50  0000 C CNN
F 2 "" H 8450 1575 50  0001 C CNN
F 3 "" H 8450 1575 50  0001 C CNN
	1    8450 1575
	1    0    0    -1  
$EndComp
Connection ~ 8450 1575
$Comp
L Transistor_FET:SUD08P06-155L Q7
U 1 1 622826F9
P 3250 1825
F 0 "Q7" V 3592 1825 50  0000 C CNN
F 1 "SUD08P06-155L" V 3501 1825 50  0000 C CNN
F 2 "Package_TO_SOT_SMD:TO-252-2" H 3445 1750 50  0001 L CIN
F 3 "https://www.vishay.com/docs/62843/sud08p06-155l-ge3.pdf" H 3250 1825 50  0001 C CNN
	1    3250 1825
	0    -1   -1   0   
$EndComp
Wire Wire Line
	7300 2450 7300 2300
Wire Wire Line
	7300 2300 6950 2300
Wire Wire Line
	6950 2300 6950 2375
Wire Wire Line
	7300 2225 7300 2300
Connection ~ 7300 2300
Wire Wire Line
	6950 2025 6650 2025
Wire Wire Line
	6650 2025 6650 2300
Wire Wire Line
	6950 2700 7300 2700
$Comp
L power:GND #PWR?
U 1 1 622C2922
P 8175 2525
AR Path="/622C2922" Ref="#PWR?"  Part="1" 
AR Path="/63D4AE42/622C2922" Ref="#PWR?"  Part="1" 
AR Path="/621F15CD/622C2922" Ref="#PWR050"  Part="1" 
F 0 "#PWR050" H 8175 2275 50  0001 C CNN
F 1 "GND" H 8180 2352 50  0000 C CNN
F 2 "" H 8175 2525 50  0001 C CNN
F 3 "" H 8175 2525 50  0001 C CNN
	1    8175 2525
	1    0    0    -1  
$EndComp
Wire Wire Line
	6150 2125 6150 2300
Wire Wire Line
	6150 2300 6400 2300
$Comp
L Device:R_US R?
U 1 1 622CC356
P 3250 2275
AR Path="/622CC356" Ref="R?"  Part="1" 
AR Path="/63D4AE42/622CC356" Ref="R?"  Part="1" 
AR Path="/621F15CD/622CC356" Ref="R38"  Part="1" 
F 0 "R38" H 3318 2321 50  0000 L CNN
F 1 "330k" H 3318 2230 50  0000 L CNN
F 2 "Resistor_SMD:R_0603_1608Metric_Outline" V 3290 2265 50  0001 C CNN
F 3 "~" H 3250 2275 50  0001 C CNN
	1    3250 2275
	1    0    0    -1  
$EndComp
Wire Wire Line
	2675 1725 2875 1725
Wire Wire Line
	3450 1725 3675 1725
Wire Wire Line
	3250 2025 3250 2100
Wire Wire Line
	3250 2100 3675 2100
Wire Wire Line
	3675 2100 3675 2025
Connection ~ 3250 2100
Wire Wire Line
	3250 2100 3250 2125
Wire Wire Line
	2700 2425 3250 2425
$Comp
L Device:R_US R?
U 1 1 622EDADA
P 3250 2650
AR Path="/622EDADA" Ref="R?"  Part="1" 
AR Path="/63D4AE42/622EDADA" Ref="R?"  Part="1" 
AR Path="/621F15CD/622EDADA" Ref="R39"  Part="1" 
F 0 "R39" H 3318 2696 50  0000 L CNN
F 1 "330k" H 3318 2605 50  0000 L CNN
F 2 "Resistor_SMD:R_0603_1608Metric_Outline" V 3290 2640 50  0001 C CNN
F 3 "~" H 3250 2650 50  0001 C CNN
	1    3250 2650
	1    0    0    -1  
$EndComp
Wire Wire Line
	3250 2425 3250 2500
Wire Wire Line
	3250 2800 3250 2925
Connection ~ 3250 2425
Wire Wire Line
	2675 3375 2875 3375
Wire Wire Line
	3450 3375 3650 3375
Wire Wire Line
	3650 3075 3650 2925
Wire Wire Line
	3650 2925 3250 2925
Connection ~ 3250 2925
Wire Wire Line
	3250 2925 3250 3075
$Comp
L Diode:EDZVFHT2R6.2B D4
U 1 1 6230DC00
P 3675 1875
F 0 "D4" V 3629 1955 50  0000 L CNN
F 1 "EDZVFHT2R6.2B" V 3720 1955 50  0000 L CNN
F 2 "Diode_SMD:D_SOD-523" H 3675 1700 50  0001 C CNN
F 3 "https://www.mouser.com/datasheet/2/348/ROHM_S_A0011946602_1-2563508.pdf" H 3675 1875 50  0001 C CNN
	1    3675 1875
	0    1    1    0   
$EndComp
$Comp
L Diode:EDZVFHT2R6.2B D3
U 1 1 6230EDDC
P 3650 3225
F 0 "D3" V 3604 3305 50  0000 L CNN
F 1 "EDZVFHT2R6.2B" V 3695 3305 50  0000 L CNN
F 2 "Diode_SMD:D_SOD-523" H 3650 3050 50  0001 C CNN
F 3 "https://www.mouser.com/datasheet/2/348/ROHM_S_A0011946602_1-2563508.pdf" H 3650 3225 50  0001 C CNN
	1    3650 3225
	0    1    1    0   
$EndComp
$Comp
L Device:R_Small_US R42
U 1 1 623190C3
P 6650 1575
F 0 "R42" H 6450 1625 50  0000 L CNN
F 1 "330k" H 6400 1550 50  0000 L CNN
F 2 "Resistor_SMD:R_0603_1608Metric_Outline" H 6650 1575 50  0001 C CNN
F 3 "~" H 6650 1575 50  0001 C CNN
	1    6650 1575
	1    0    0    -1  
$EndComp
Connection ~ 6650 1925
Wire Wire Line
	6650 1925 6450 1925
Connection ~ 6575 5225
Text Label 5850 5225 0    50   ~ 0
PG-
Wire Wire Line
	6150 1725 6775 1725
Wire Wire Line
	6650 1675 6650 1925
Wire Wire Line
	6575 5225 6575 4900
Wire Wire Line
	6575 4600 6575 4700
$Comp
L Transistor_FET:BSS83P Q9
U 1 1 62358A71
P 11900 1650
F 0 "Q9" H 12104 1604 50  0000 L CNN
F 1 "BSS83P" H 12104 1695 50  0000 L CNN
F 2 "Package_TO_SOT_SMD:SOT-23" H 12100 1575 50  0001 L CIN
F 3 "http://www.farnell.com/datasheets/1835997.pdf" H 11900 1650 50  0001 L CNN
	1    11900 1650
	1    0    0    1   
$EndComp
$Comp
L Transistor_FET:BSS83P Q10
U 1 1 6235D583
P 12800 1675
F 0 "Q10" H 13004 1629 50  0000 L CNN
F 1 "BSS83P" H 13004 1720 50  0000 L CNN
F 2 "Package_TO_SOT_SMD:SOT-23" H 13000 1600 50  0001 L CIN
F 3 "http://www.farnell.com/datasheets/1835997.pdf" H 12800 1675 50  0001 L CNN
	1    12800 1675
	1    0    0    1   
$EndComp
$Comp
L Device:LED D6
U 1 1 6235E9D7
P 12375 2575
F 0 "D6" V 12414 2457 50  0000 R CNN
F 1 "LOW_BATT" V 12323 2457 50  0000 R CNN
F 2 "LED_SMD:LED_0603_1608Metric" H 12375 2575 50  0001 C CNN
F 3 "~" H 12375 2575 50  0001 C CNN
F 4 "Red" V 12250 2375 50  0000 C CNN "Field4"
	1    12375 2575
	0    -1   -1   0   
$EndComp
$Comp
L Device:R_US R49
U 1 1 62360213
P 12375 2175
F 0 "R49" H 12443 2221 50  0000 L CNN
F 1 "5k" H 12443 2130 50  0000 L CNN
F 2 "Resistor_SMD:R_0603_1608Metric_Outline" V 12415 2165 50  0001 C CNN
F 3 "~" H 12375 2175 50  0001 C CNN
	1    12375 2175
	1    0    0    -1  
$EndComp
Wire Wire Line
	12600 1675 12525 1675
Wire Wire Line
	11700 1650 11325 1650
$Comp
L power:GND #PWR?
U 1 1 6236B538
P 12375 2850
AR Path="/6236B538" Ref="#PWR?"  Part="1" 
AR Path="/63D4AE42/6236B538" Ref="#PWR?"  Part="1" 
AR Path="/621F15CD/6236B538" Ref="#PWR053"  Part="1" 
F 0 "#PWR053" H 12375 2600 50  0001 C CNN
F 1 "GND" H 12380 2677 50  0000 C CNN
F 2 "" H 12375 2850 50  0001 C CNN
F 3 "" H 12375 2850 50  0001 C CNN
	1    12375 2850
	1    0    0    -1  
$EndComp
$Comp
L Diode:1N4148WS D5
U 1 1 623743C5
P 6075 5425
F 0 "D5" V 6029 5505 50  0000 L CNN
F 1 "1N4148WS" V 6120 5505 50  0000 L CNN
F 2 "Diode_SMD:D_SOD-323" H 6075 5250 50  0001 C CNN
F 3 "https://www.vishay.com/docs/85751/1n4148ws.pdf" H 6075 5425 50  0001 C CNN
	1    6075 5425
	0    1    1    0   
$EndComp
Wire Wire Line
	6825 5025 6825 4800
Wire Wire Line
	6825 4600 6825 4375
Wire Wire Line
	6825 4375 7200 4375
Wire Wire Line
	7200 4375 7200 4400
$Comp
L power:GND #PWR?
U 1 1 62382167
P 7200 4400
AR Path="/62382167" Ref="#PWR?"  Part="1" 
AR Path="/63D4AE42/62382167" Ref="#PWR?"  Part="1" 
AR Path="/621F15CD/62382167" Ref="#PWR047"  Part="1" 
F 0 "#PWR047" H 7200 4150 50  0001 C CNN
F 1 "GND" H 7205 4227 50  0000 C CNN
F 2 "" H 7200 4400 50  0001 C CNN
F 3 "" H 7200 4400 50  0001 C CNN
	1    7200 4400
	1    0    0    -1  
$EndComp
$Comp
L Device:R_Small_US R43
U 1 1 62384FB8
P 6725 5225
F 0 "R43" V 6625 5175 50  0000 L CNN
F 1 "30k1" V 6825 5150 50  0000 L CNN
F 2 "Resistor_SMD:R_0603_1608Metric_Outline" H 6725 5225 50  0001 C CNN
F 3 "~" H 6725 5225 50  0001 C CNN
	1    6725 5225
	0    1    1    0   
$EndComp
Wire Wire Line
	6625 5225 6575 5225
Wire Wire Line
	5850 5225 6075 5225
Wire Wire Line
	6075 5725 6075 5575
Wire Wire Line
	6075 5275 6075 5225
Connection ~ 6075 5225
Wire Wire Line
	6075 5225 6575 5225
Wire Wire Line
	12900 1875 12900 1950
Wire Wire Line
	12000 1850 12000 1950
Wire Wire Line
	12375 2725 12375 2850
Wire Wire Line
	12375 2325 12375 2425
Text Label 11325 1425 0    50   ~ 0
PG-
Text Label 11325 1650 0    50   ~ 0
PG+
Wire Wire Line
	6150 1725 5900 1725
Connection ~ 6150 1725
Connection ~ 3675 1725
Wire Wire Line
	8675 4975 8675 4900
Connection ~ 8675 4975
$Comp
L Device:LED D2
U 1 1 6251FF10
P 2875 2875
F 0 "D2" V 2850 2700 50  0000 L CNN
F 1 "BATT_REV" V 2950 2400 50  0000 L CNN
F 2 "LED_SMD:LED_0603_1608Metric" H 2875 2875 50  0001 C CNN
F 3 "~" H 2875 2875 50  0001 C CNN
	1    2875 2875
	0    1    1    0   
$EndComp
$Comp
L Device:R_US R37
U 1 1 62522377
P 2875 2100
F 0 "R37" H 2943 2146 50  0000 L CNN
F 1 "2k2" H 2943 2055 50  0000 L CNN
F 2 "Resistor_SMD:R_0603_1608Metric_Outline" V 2915 2090 50  0001 C CNN
F 3 "~" H 2875 2100 50  0001 C CNN
	1    2875 2100
	1    0    0    -1  
$EndComp
Wire Wire Line
	2875 3375 2875 3025
Wire Wire Line
	2875 2725 2875 2250
Wire Wire Line
	2875 1950 2875 1725
Connection ~ 2875 3375
Wire Wire Line
	2875 3375 3050 3375
Connection ~ 2875 1725
Wire Wire Line
	2875 1725 3050 1725
$Comp
L Device:LED D8
U 1 1 62529DA4
P 13875 2275
F 0 "D8" V 13914 2157 50  0000 R CNN
F 1 "POWER" V 13823 2157 50  0000 R CNN
F 2 "LED_SMD:LED_0603_1608Metric" H 13875 2275 50  0001 C CNN
F 3 "~" H 13875 2275 50  0001 C CNN
F 4 "Green" V 13750 2050 50  0000 C CNN "Field4"
	1    13875 2275
	0    -1   -1   0   
$EndComp
$Comp
L Device:R_US R51
U 1 1 62529DAA
P 13875 1975
F 0 "R51" H 13943 2021 50  0000 L CNN
F 1 "22k" H 13943 1930 50  0000 L CNN
F 2 "Resistor_SMD:R_0603_1608Metric_Outline" V 13915 1965 50  0001 C CNN
F 3 "~" H 13875 1975 50  0001 C CNN
	1    13875 1975
	1    0    0    -1  
$EndComp
Wire Wire Line
	13875 1800 13875 1825
Wire Wire Line
	13875 2425 13875 2825
$Comp
L Transistor_FET:DMN6040SK3-13 Q8
U 1 1 6255CDFF
P 3250 3275
F 0 "Q8" V 3499 3275 50  0000 C CNN
F 1 "DMN6040SK3-13" V 3590 3275 50  0000 C CNN
F 2 "Package_TO_SOT_SMD:TO-252-2" H 3450 3200 50  0001 L CIN
F 3 "https://www.diodes.com/assets/Datasheets/DMN6040SK3.pdf" H 3250 3275 50  0001 L CNN
	1    3250 3275
	0    -1   1    0   
$EndComp
$Comp
L Connector_Generic:Conn_02x02_Odd_Even J4
U 1 1 629C7EFA
P 2125 2375
F 0 "J4" H 2175 2592 50  0000 C CNN
F 1 "Batt_Molex" H 2175 2501 50  0000 C CNN
F 2 "Connector_Molex:Molex_Mini-Fit_Jr_5569-04A2_2x02_P4.20mm_Horizontal" H 2125 2375 50  0001 C CNN
F 3 "~" H 2125 2375 50  0001 C CNN
	1    2125 2375
	1    0    0    -1  
$EndComp
Wire Wire Line
	2425 2375 2425 2425
Wire Wire Line
	2700 2425 2425 2425
Connection ~ 2700 2425
Connection ~ 2425 2425
Wire Wire Line
	2425 2425 2425 2475
Wire Wire Line
	1925 1725 1925 2375
Wire Wire Line
	1925 2475 1925 3375
$Comp
L Device:R_US R?
U 1 1 61FE483E
P 6575 5650
AR Path="/61FE483E" Ref="R?"  Part="1" 
AR Path="/63D4AE42/61FE483E" Ref="R?"  Part="1" 
AR Path="/621F15CD/61FE483E" Ref="R41"  Part="1" 
F 0 "R41" H 6350 5675 50  0000 L CNN
F 1 "75k" H 6350 5600 50  0000 L CNN
F 2 "Resistor_SMD:R_0603_1608Metric_Outline" V 6615 5640 50  0001 C CNN
F 3 "~" H 6575 5650 50  0001 C CNN
	1    6575 5650
	1    0    0    -1  
$EndComp
$Comp
L power:-7.5V #PWR051
U 1 1 61FECAFE
P 8675 4900
F 0 "#PWR051" H 8675 5000 50  0001 C CNN
F 1 "-7.5V" H 8690 5073 50  0000 C CNN
F 2 "" H 8675 4900 50  0001 C CNN
F 3 "" H 8675 4900 50  0001 C CNN
	1    8675 4900
	1    0    0    -1  
$EndComp
Wire Wire Line
	12375 2025 12375 1950
Connection ~ 12375 1950
Wire Wire Line
	12000 1275 12375 1275
Wire Wire Line
	12000 1275 12000 1450
Wire Wire Line
	12900 1275 12900 1475
Wire Wire Line
	12375 1050 12375 1275
Connection ~ 12375 1275
$Comp
L Device:C_Small C28
U 1 1 620230C6
P 6150 2025
F 0 "C28" H 6242 2116 50  0000 L CNN
F 1 "10uF/35V" H 6242 2025 50  0000 L CNN
F 2 "Capacitor_SMD:C_1210_3225Metric" H 6150 2025 50  0001 C CNN
F 3 "~" H 6150 2025 50  0001 C CNN
F 4 "X7R" H 6242 1934 50  0000 L CNN "Field4"
	1    6150 2025
	1    0    0    -1  
$EndComp
$Comp
L Device:C_Small C29
U 1 1 62023910
P 6825 4700
F 0 "C29" H 6917 4791 50  0000 L CNN
F 1 "10uF/35V" H 6917 4700 50  0000 L CNN
F 2 "Capacitor_SMD:C_1210_3225Metric" H 6825 4700 50  0001 C CNN
F 3 "~" H 6825 4700 50  0001 C CNN
F 4 "X7R" H 6917 4609 50  0000 L CNN "Field4"
	1    6825 4700
	1    0    0    -1  
$EndComp
$Comp
L Device:LED D9
U 1 1 623D34D8
P 12375 4475
F 0 "D9" V 12414 4357 50  0000 R CNN
F 1 "SW+" V 12323 4357 50  0000 R CNN
F 2 "LED_SMD:LED_0603_1608Metric" H 12375 4475 50  0001 C CNN
F 3 "~" H 12375 4475 50  0001 C CNN
F 4 "Blue" V 12250 4275 50  0000 C CNN "Field4"
	1    12375 4475
	0    -1   -1   0   
$EndComp
$Comp
L power:GND #PWR?
U 1 1 623D34E4
P 12375 4700
AR Path="/623D34E4" Ref="#PWR?"  Part="1" 
AR Path="/63D4AE42/623D34E4" Ref="#PWR?"  Part="1" 
AR Path="/621F15CD/623D34E4" Ref="#PWR054"  Part="1" 
F 0 "#PWR054" H 12375 4450 50  0001 C CNN
F 1 "GND" H 12380 4527 50  0000 C CNN
F 2 "" H 12375 4700 50  0001 C CNN
F 3 "" H 12375 4700 50  0001 C CNN
	1    12375 4700
	1    0    0    -1  
$EndComp
Wire Wire Line
	12375 1950 12000 1950
Wire Wire Line
	12375 1950 12900 1950
Wire Wire Line
	12375 1275 12900 1275
Wire Wire Line
	12525 1675 12525 1425
Wire Wire Line
	12525 1425 11325 1425
$Comp
L Device:LED D7
U 1 1 624F5D47
P 12375 4000
F 0 "D7" V 12414 3882 50  0000 R CNN
F 1 "SW-" V 12323 3882 50  0000 R CNN
F 2 "LED_SMD:LED_0603_1608Metric" H 12375 4000 50  0001 C CNN
F 3 "~" H 12375 4000 50  0001 C CNN
F 4 "Green" V 12250 3775 50  0000 C CNN "Field4"
	1    12375 4000
	0    -1   -1   0   
$EndComp
$Comp
L Device:R_US R50
U 1 1 625F2830
P 11975 4200
F 0 "R50" V 12150 4125 50  0000 L CNN
F 1 "5k" V 12075 4150 50  0000 L CNN
F 2 "Resistor_SMD:R_0603_1608Metric_Outline" V 12015 4190 50  0001 C CNN
F 3 "~" H 11975 4200 50  0001 C CNN
	1    11975 4200
	0    -1   -1   0   
$EndComp
$Comp
L Device:LED D11
U 1 1 625F5ADE
P 15250 2275
F 0 "D11" V 15289 2157 50  0000 R CNN
F 1 "IN_RES_ON" V 15198 2157 50  0000 R CNN
F 2 "LED_SMD:LED_0603_1608Metric" H 15250 2275 50  0001 C CNN
F 3 "~" H 15250 2275 50  0001 C CNN
F 4 "Amber" V 15100 2025 50  0000 C CNN "Field4"
	1    15250 2275
	0    -1   -1   0   
$EndComp
$Comp
L Device:R_US R52
U 1 1 625F5AE4
P 15250 1975
F 0 "R52" H 15318 2021 50  0000 L CNN
F 1 "5k" H 15318 1930 50  0000 L CNN
F 2 "Resistor_SMD:R_0603_1608Metric_Outline" V 15290 1965 50  0001 C CNN
F 3 "~" H 15250 1975 50  0001 C CNN
	1    15250 1975
	1    0    0    -1  
$EndComp
Wire Wire Line
	14950 2625 14575 2625
$Comp
L power:GND #PWR?
U 1 1 625F5AF2
P 15250 2825
AR Path="/625F5AF2" Ref="#PWR?"  Part="1" 
AR Path="/63D4AE42/625F5AF2" Ref="#PWR?"  Part="1" 
AR Path="/621F15CD/625F5AF2" Ref="#PWR058"  Part="1" 
F 0 "#PWR058" H 15250 2575 50  0001 C CNN
F 1 "GND" H 15255 2652 50  0000 C CNN
F 2 "" H 15250 2825 50  0001 C CNN
F 3 "" H 15250 2825 50  0001 C CNN
	1    15250 2825
	1    0    0    -1  
$EndComp
Text Label 14575 2625 0    50   ~ 0
555_OUT
$Comp
L Transistor_FET:BSS83P Q?
U 1 1 6263F5A8
P 15150 2625
AR Path="/6263F5A8" Ref="Q?"  Part="1" 
AR Path="/621F15CD/6263F5A8" Ref="Q11"  Part="1" 
F 0 "Q11" H 15354 2579 50  0000 L CNN
F 1 "BSS83P" H 15354 2670 50  0000 L CNN
F 2 "Package_TO_SOT_SMD:SOT-23" H 15350 2550 50  0001 L CIN
F 3 "http://www.farnell.com/datasheets/1835997.pdf" H 15150 2625 50  0001 L CNN
	1    15150 2625
	1    0    0    1   
$EndComp
Wire Wire Line
	15250 1800 15250 1825
$Comp
L Device:R_Small_US R40
U 1 1 62319853
P 6575 4800
F 0 "R40" H 6350 4850 50  0000 L CNN
F 1 "330k" H 6325 4775 50  0000 L CNN
F 2 "Resistor_SMD:R_0603_1608Metric_Outline" H 6575 4800 50  0001 C CNN
F 3 "~" H 6575 4800 50  0001 C CNN
	1    6575 4800
	1    0    0    -1  
$EndComp
Wire Wire Line
	7750 1575 7975 1575
$Comp
L Device:CP1_Small_Kelvin C32
U 1 1 6269A90E
P 7900 1925
F 0 "C32" H 8025 1975 50  0000 L CNN
F 1 "10uF/25V" H 8025 1900 50  0000 L CNN
F 2 "Capacitor_Tantalum_SMD:CP_EIA-3528-12_Kemet-T_Kelvin" H 7900 1925 50  0001 C CNN
F 3 "~" H 7900 1925 50  0001 C CNN
F 4 "Ta/Poly" H 8025 1825 50  0000 L CNN "Field4"
	1    7900 1925
	1    0    0    -1  
$EndComp
Wire Wire Line
	8450 1900 8450 2125
Wire Wire Line
	7750 1925 7825 1925
Wire Wire Line
	7825 2125 8450 2125
Connection ~ 8450 2125
Wire Wire Line
	8450 2125 8450 2175
Wire Wire Line
	7975 1825 7975 1575
Connection ~ 7975 1575
Wire Wire Line
	7975 1575 8450 1575
Wire Wire Line
	8675 5350 8675 5550
Wire Wire Line
	7800 4975 8075 4975
Wire Wire Line
	7775 5125 8000 5125
Wire Wire Line
	8075 5125 8075 4975
Connection ~ 8075 4975
Wire Wire Line
	8075 4975 8675 4975
$Comp
L Device:CP1_Small_Kelvin C33
U 1 1 627E3091
P 8075 5225
F 0 "C33" H 7984 5134 50  0000 R CNN
F 1 "10uF/25V" H 7984 5225 50  0000 R CNN
F 2 "Capacitor_Tantalum_SMD:CP_EIA-3528-12_Kemet-T_Kelvin" H 8075 5225 50  0001 C CNN
F 3 "~" H 8075 5225 50  0001 C CNN
F 4 "Ta/Poly" H 7984 5316 50  0000 R CNN "Field4"
	1    8075 5225
	-1   0    0    1   
$EndComp
Wire Wire Line
	7775 5225 7900 5225
Wire Wire Line
	7900 5225 7900 5550
Wire Wire Line
	7900 5550 8675 5550
Connection ~ 8675 5550
Connection ~ 7300 2700
$Comp
L power:GND #PWR?
U 1 1 636DEDFE
P 6075 5725
AR Path="/636DEDFE" Ref="#PWR?"  Part="1" 
AR Path="/63D4AE42/636DEDFE" Ref="#PWR?"  Part="1" 
AR Path="/621F15CD/636DEDFE" Ref="#PWR071"  Part="1" 
F 0 "#PWR071" H 6075 5475 50  0001 C CNN
F 1 "GND" H 6080 5552 50  0000 C CNN
F 2 "" H 6075 5725 50  0001 C CNN
F 3 "" H 6075 5725 50  0001 C CNN
	1    6075 5725
	1    0    0    -1  
$EndComp
$Comp
L Device:R_US R?
U 1 1 63D5AD3E
P 8675 5750
AR Path="/63D5AD3E" Ref="R?"  Part="1" 
AR Path="/63D4AE42/63D5AD3E" Ref="R?"  Part="1" 
AR Path="/621F15CD/63D5AD3E" Ref="R48"  Part="1" 
F 0 "R48" H 8743 5796 50  0000 L CNN
F 1 "30k1" H 8743 5705 50  0000 L CNN
F 2 "Resistor_SMD:R_0603_1608Metric_Outline" V 8715 5740 50  0001 C CNN
F 3 "~" H 8675 5750 50  0001 C CNN
	1    8675 5750
	1    0    0    -1  
$EndComp
Wire Wire Line
	8675 5550 8675 5600
Wire Wire Line
	8675 5900 8675 5925
Wire Wire Line
	8675 5925 8675 5950
Connection ~ 8675 5925
Wire Wire Line
	6825 5850 8075 5850
Wire Wire Line
	8075 5325 8075 5850
Connection ~ 6825 5850
Wire Wire Line
	8000 5925 8675 5925
$Comp
L power:GND #PWR?
U 1 1 6394F8DA
P 6400 2300
AR Path="/6394F8DA" Ref="#PWR?"  Part="1" 
AR Path="/63D4AE42/6394F8DA" Ref="#PWR?"  Part="1" 
AR Path="/621F15CD/6394F8DA" Ref="#PWR072"  Part="1" 
F 0 "#PWR072" H 6400 2050 50  0001 C CNN
F 1 "GND" H 6405 2127 50  0000 C CNN
F 2 "" H 6400 2300 50  0001 C CNN
F 3 "" H 6400 2300 50  0001 C CNN
	1    6400 2300
	1    0    0    -1  
$EndComp
Wire Wire Line
	7775 5325 8000 5325
Connection ~ 8000 5325
Wire Wire Line
	8000 5325 8000 5925
$Comp
L power:GND #PWR?
U 1 1 639AEDFB
P 7375 5625
AR Path="/639AEDFB" Ref="#PWR?"  Part="1" 
AR Path="/63D4AE42/639AEDFB" Ref="#PWR?"  Part="1" 
AR Path="/621F15CD/639AEDFB" Ref="#PWR073"  Part="1" 
F 0 "#PWR073" H 7375 5375 50  0001 C CNN
F 1 "GND" H 7380 5452 50  0000 C CNN
F 2 "" H 7375 5625 50  0001 C CNN
F 3 "" H 7375 5625 50  0001 C CNN
	1    7375 5625
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR?
U 1 1 63A61C89
P 7400 2225
AR Path="/63A61C89" Ref="#PWR?"  Part="1" 
AR Path="/63D4AE42/63A61C89" Ref="#PWR?"  Part="1" 
AR Path="/621F15CD/63A61C89" Ref="#PWR074"  Part="1" 
F 0 "#PWR074" H 7400 1975 50  0001 C CNN
F 1 "GND" H 7405 2052 50  0000 C CNN
F 2 "" H 7400 2225 50  0001 C CNN
F 3 "" H 7400 2225 50  0001 C CNN
	1    7400 2225
	1    0    0    -1  
$EndComp
Connection ~ 6400 2300
Wire Wire Line
	6400 2300 6650 2300
Connection ~ 8175 2525
Wire Wire Line
	8175 2525 8450 2525
$Comp
L Regulator_Linear:LP2985-5.0 U8
U 1 1 63AF7D30
P 7350 3475
F 0 "U8" H 7350 3817 50  0000 C CNN
F 1 "LP2985-5.0" H 7350 3726 50  0000 C CNN
F 2 "Package_TO_SOT_SMD:SOT-23-5" H 7350 3800 50  0001 C CNN
F 3 "http://www.ti.com/lit/ds/symlink/lp2985.pdf" H 7350 3475 50  0001 C CNN
	1    7350 3475
	1    0    0    -1  
$EndComp
$Comp
L Device:C_Small C43
U 1 1 63AFCA52
P 7875 3625
F 0 "C43" H 7775 3600 50  0000 R CNN
F 1 "10nF" H 7775 3675 50  0000 R CNN
F 2 "Capacitor_SMD:C_0603_1608Metric_Outline" H 7875 3625 50  0001 C CNN
F 3 "~" H 7875 3625 50  0001 C CNN
F 4 " C0G/50V" H 7875 3625 50  0001 C CNN "Field4"
	1    7875 3625
	-1   0    0    1   
$EndComp
$Comp
L Device:C_Small C44
U 1 1 63B1B715
P 8325 3625
F 0 "C44" H 8417 3716 50  0000 L CNN
F 1 "10uF/25V" H 8417 3625 50  0000 L CNN
F 2 "Capacitor_SMD:C_1206_3216Metric" H 8325 3625 50  0001 C CNN
F 3 "~" H 8325 3625 50  0001 C CNN
F 4 "X7R" H 8417 3534 50  0000 L CNN "Field4"
	1    8325 3625
	1    0    0    -1  
$EndComp
$Comp
L Device:C_Small C40
U 1 1 63B1CD04
P 6525 3625
F 0 "C40" H 6617 3716 50  0000 L CNN
F 1 "10uF/25V" H 6617 3625 50  0000 L CNN
F 2 "Capacitor_SMD:C_1206_3216Metric" H 6525 3625 50  0001 C CNN
F 3 "~" H 6525 3625 50  0001 C CNN
F 4 "X7R" H 6617 3534 50  0000 L CNN "Field4"
	1    6525 3625
	1    0    0    -1  
$EndComp
$Comp
L Device:R_US R23
U 1 1 63B1E8AC
P 6250 3375
F 0 "R23" V 6045 3375 50  0000 C CNN
F 1 "2R2" V 6136 3375 50  0000 C CNN
F 2 "Resistor_SMD:R_0603_1608Metric_Outline" V 6290 3365 50  0001 C CNN
F 3 "~" H 6250 3375 50  0001 C CNN
	1    6250 3375
	0    1    1    0   
$EndComp
Wire Wire Line
	6400 3375 6525 3375
Wire Wire Line
	6525 3525 6525 3375
Connection ~ 6525 3375
Wire Wire Line
	6525 3375 6950 3375
Wire Wire Line
	6525 3725 6525 3950
Wire Wire Line
	6525 3950 7350 3950
Wire Wire Line
	7350 3950 7350 3775
Wire Wire Line
	7750 3375 8325 3375
Wire Wire Line
	8325 3375 8325 3525
Wire Wire Line
	8325 3725 8325 3950
Connection ~ 7350 3950
Wire Wire Line
	7875 3525 7875 3475
Wire Wire Line
	7875 3475 7750 3475
Wire Wire Line
	7875 3725 7875 3950
Wire Wire Line
	7350 3950 7875 3950
Connection ~ 7875 3950
Wire Wire Line
	7875 3950 8325 3950
$Comp
L power:GND #PWR?
U 1 1 63BFDCC0
P 8325 3950
AR Path="/63BFDCC0" Ref="#PWR?"  Part="1" 
AR Path="/63D4AE42/63BFDCC0" Ref="#PWR?"  Part="1" 
AR Path="/621F15CD/63BFDCC0" Ref="#PWR076"  Part="1" 
F 0 "#PWR076" H 8325 3700 50  0001 C CNN
F 1 "GND" H 8330 3777 50  0000 C CNN
F 2 "" H 8325 3950 50  0001 C CNN
F 3 "" H 8325 3950 50  0001 C CNN
	1    8325 3950
	1    0    0    -1  
$EndComp
Connection ~ 8325 3950
$Comp
L power:+5V #PWR075
U 1 1 63BFF948
P 8325 3375
F 0 "#PWR075" H 8325 3225 50  0001 C CNN
F 1 "+5V" H 8340 3548 50  0000 C CNN
F 2 "" H 8325 3375 50  0001 C CNN
F 3 "" H 8325 3375 50  0001 C CNN
	1    8325 3375
	1    0    0    -1  
$EndComp
Connection ~ 8325 3375
Wire Wire Line
	6100 3375 5900 3375
Wire Wire Line
	5900 3375 5900 1725
Connection ~ 5900 1725
Text Label 1925 1725 0    50   ~ 0
Batt+
Text Label 1925 3375 0    50   ~ 0
Batt-
Wire Wire Line
	3675 1725 5900 1725
$Comp
L power:GND #PWR?
U 1 1 63F8A737
P 1775 8550
AR Path="/63F8A737" Ref="#PWR?"  Part="1" 
AR Path="/621F15CD/63F8A737" Ref="#PWR061"  Part="1" 
F 0 "#PWR061" H 1775 8300 50  0001 C CNN
F 1 "GND" H 1780 8377 50  0000 C CNN
F 2 "" H 1775 8550 50  0001 C CNN
F 3 "" H 1775 8550 50  0001 C CNN
	1    1775 8550
	1    0    0    -1  
$EndComp
Wire Wire Line
	3675 10275 3950 10275
Wire Wire Line
	3125 10275 3375 10275
Wire Wire Line
	4425 9500 4625 9500
Connection ~ 4425 9500
Wire Wire Line
	4425 10075 4425 9500
Wire Wire Line
	3125 10675 3950 10675
Connection ~ 4625 9500
Wire Wire Line
	4275 9500 4425 9500
Wire Wire Line
	3850 9500 3975 9500
Wire Wire Line
	3850 9300 3850 9500
Wire Wire Line
	3200 9300 3850 9300
Wire Wire Line
	2600 9300 3200 9300
Wire Wire Line
	3200 9300 3200 9400
Connection ~ 3200 9300
Wire Wire Line
	3200 9700 3200 9750
Wire Wire Line
	3200 9225 3200 9300
Wire Wire Line
	3200 8850 3200 8925
$Comp
L power:+5V #PWR064
U 1 1 63EBE843
P 3200 8850
F 0 "#PWR064" H 3200 8700 50  0001 C CNN
F 1 "+5V" H 3215 9023 50  0000 C CNN
F 2 "" H 3200 8850 50  0001 C CNN
F 3 "" H 3200 8850 50  0001 C CNN
	1    3200 8850
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR?
U 1 1 63EBE353
P 3200 9750
AR Path="/63EBE353" Ref="#PWR?"  Part="1" 
AR Path="/621F15CD/63EBE353" Ref="#PWR066"  Part="1" 
F 0 "#PWR066" H 3200 9500 50  0001 C CNN
F 1 "GND" H 3205 9577 50  0000 C CNN
F 2 "" H 3200 9750 50  0001 C CNN
F 3 "" H 3200 9750 50  0001 C CNN
	1    3200 9750
	1    0    0    -1  
$EndComp
Wire Wire Line
	2575 8450 3225 8450
Connection ~ 2575 8450
Wire Wire Line
	3650 6150 3925 6150
Connection ~ 2325 8450
Wire Wire Line
	2325 8450 2575 8450
$Comp
L Device:CP1_Small C36
U 1 1 63E61D3F
P 3550 6150
F 0 "C36" V 3778 6150 50  0000 C CNN
F 1 "100uF/16V" V 3687 6150 50  0000 C CNN
F 2 "Capacitor_Tantalum_SMD:CP_EIA-3528-12_Kemet-T" H 3550 6150 50  0001 C CNN
F 3 "~" H 3550 6150 50  0001 C CNN
	1    3550 6150
	0    -1   -1   0   
$EndComp
Wire Wire Line
	5825 8650 5825 9100
Connection ~ 5825 8650
Wire Wire Line
	5975 8650 5825 8650
Wire Wire Line
	5825 8625 5825 8650
$Comp
L power:GND #PWR?
U 1 1 63D24C76
P 5975 8850
AR Path="/63D24C76" Ref="#PWR?"  Part="1" 
AR Path="/621F15CD/63D24C76" Ref="#PWR070"  Part="1" 
F 0 "#PWR070" H 5975 8600 50  0001 C CNN
F 1 "GND" H 5980 8677 50  0000 C CNN
F 2 "" H 5975 8850 50  0001 C CNN
F 3 "" H 5975 8850 50  0001 C CNN
	1    5975 8850
	1    0    0    -1  
$EndComp
$Comp
L Device:C_Small C39
U 1 1 63D22E25
P 5975 8750
F 0 "C39" H 6067 8841 50  0000 L CNN
F 1 "1uF/16V" H 6067 8750 50  0000 L CNN
F 2 "Capacitor_SMD:C_0603_1608Metric_Outline" H 5975 8750 50  0001 C CNN
F 3 "~" H 5975 8750 50  0001 C CNN
F 4 "X7R" H 6067 8659 50  0000 L CNN "Field4"
	1    5975 8750
	1    0    0    -1  
$EndComp
$Comp
L power:+5V #PWR069
U 1 1 63CFD806
P 5825 8625
F 0 "#PWR069" H 5825 8475 50  0001 C CNN
F 1 "+5V" H 5840 8798 50  0000 C CNN
F 2 "" H 5825 8625 50  0001 C CNN
F 3 "" H 5825 8625 50  0001 C CNN
	1    5825 8625
	1    0    0    -1  
$EndComp
Text Label 8125 8850 2    50   ~ 0
555_OUT
Wire Wire Line
	6650 9500 6750 9500
Connection ~ 6650 9500
Wire Wire Line
	6650 8850 6650 9500
Wire Wire Line
	6650 8850 8125 8850
Wire Wire Line
	6325 9500 6650 9500
Text GLabel 7825 9225 2    50   Output ~ 0
K2_DRV
Text GLabel 3925 6150 2    50   Output ~ 0
K1_DRV
Wire Wire Line
	7050 9500 7075 9500
$Comp
L Device:R_US R?
U 1 1 62D516CC
P 6900 9500
AR Path="/62D516CC" Ref="R?"  Part="1" 
AR Path="/621F15CD/62D516CC" Ref="R67"  Part="1" 
F 0 "R67" V 6695 9500 50  0000 C CNN
F 1 "100R" V 6786 9500 50  0000 C CNN
F 2 "Resistor_SMD:R_0603_1608Metric_Outline" V 6940 9490 50  0001 C CNN
F 3 "~" H 6900 9500 50  0001 C CNN
	1    6900 9500
	0    1    1    0   
$EndComp
Wire Wire Line
	7750 9225 7825 9225
$Comp
L Diode:1N4148WS D?
U 1 1 62D516C5
P 7600 9225
AR Path="/62D516C5" Ref="D?"  Part="1" 
AR Path="/621F15CD/62D516C5" Ref="D16"  Part="1" 
F 0 "D16" H 7600 9008 50  0000 C CNN
F 1 "1N4148WS" H 7600 9099 50  0000 C CNN
F 2 "Diode_SMD:D_SOD-323" H 7600 9050 50  0001 C CNN
F 3 "https://www.vishay.com/docs/85751/1n4148ws.pdf" H 7600 9225 50  0001 C CNN
	1    7600 9225
	1    0    0    1   
$EndComp
Wire Wire Line
	7375 9700 7375 9750
$Comp
L power:GND #PWR?
U 1 1 62D516BE
P 7375 9750
AR Path="/62D516BE" Ref="#PWR?"  Part="1" 
AR Path="/621F15CD/62D516BE" Ref="#PWR068"  Part="1" 
F 0 "#PWR068" H 7375 9500 50  0001 C CNN
F 1 "GND" H 7380 9577 50  0000 C CNN
F 2 "" H 7375 9750 50  0001 C CNN
F 3 "" H 7375 9750 50  0001 C CNN
	1    7375 9750
	1    0    0    -1  
$EndComp
Wire Wire Line
	7375 9225 7375 9300
$Comp
L Transistor_FET:BSS123 Q?
U 1 1 62D516B7
P 7275 9500
AR Path="/62D516B7" Ref="Q?"  Part="1" 
AR Path="/621F15CD/62D516B7" Ref="Q16"  Part="1" 
F 0 "Q16" H 7479 9546 50  0000 L CNN
F 1 "BSS123" H 7479 9455 50  0000 L CNN
F 2 "Package_TO_SOT_SMD:SOT-23" H 7475 9425 50  0001 L CIN
F 3 "http://www.diodes.com/assets/Datasheets/ds30366.pdf" H 7275 9500 50  0001 L CNN
	1    7275 9500
	1    0    0    -1  
$EndComp
Wire Wire Line
	7375 9225 7450 9225
Wire Wire Line
	2325 9300 2325 8450
Connection ~ 2325 9300
Wire Wire Line
	2400 9300 2325 9300
Wire Wire Line
	2325 10275 2325 9300
Wire Wire Line
	2400 10275 2325 10275
Wire Wire Line
	3125 10275 3025 10275
Connection ~ 3125 10275
Wire Wire Line
	3125 10275 3125 10325
Wire Wire Line
	2725 10275 2600 10275
$Comp
L Device:C_Small C?
U 1 1 62D51674
P 2500 9300
AR Path="/62D51674" Ref="C?"  Part="1" 
AR Path="/621F15CD/62D51674" Ref="C34"  Part="1" 
F 0 "C34" V 2300 9375 50  0000 R CNN
F 1 "10nF" V 2375 9375 50  0000 R CNN
F 2 "Capacitor_SMD:C_0603_1608Metric_Outline" H 2500 9300 50  0001 C CNN
F 3 "~" H 2500 9300 50  0001 C CNN
F 4 " C0G/50V" H 2500 9300 50  0001 C CNN "Field4"
	1    2500 9300
	0    1    1    0   
$EndComp
$Comp
L Device:R_US R?
U 1 1 62D5166E
P 4125 9500
AR Path="/62D5166E" Ref="R?"  Part="1" 
AR Path="/621F15CD/62D5166E" Ref="R54"  Part="1" 
F 0 "R54" V 4200 9500 50  0000 C CNN
F 1 "100R" V 4275 9525 50  0000 C CNN
F 2 "Resistor_SMD:R_0603_1608Metric_Outline" V 4165 9490 50  0001 C CNN
F 3 "~" H 4125 9500 50  0001 C CNN
	1    4125 9500
	0    1    1    0   
$EndComp
$Comp
L Device:C_Small C?
U 1 1 62D51662
P 2500 10275
AR Path="/62D51662" Ref="C?"  Part="1" 
AR Path="/621F15CD/62D51662" Ref="C35"  Part="1" 
F 0 "C35" V 2300 10325 50  0000 R CNN
F 1 "10nF" V 2375 10350 50  0000 R CNN
F 2 "Capacitor_SMD:C_0603_1608Metric_Outline" H 2500 10275 50  0001 C CNN
F 3 "~" H 2500 10275 50  0001 C CNN
F 4 " C0G/50V" H 2500 10275 50  0001 C CNN "Field4"
	1    2500 10275
	0    1    1    0   
$EndComp
$Comp
L Device:R_US R?
U 1 1 62D5165C
P 2875 10275
AR Path="/62D5165C" Ref="R?"  Part="1" 
AR Path="/621F15CD/62D5165C" Ref="R55"  Part="1" 
F 0 "R55" V 2670 10275 50  0000 C CNN
F 1 "100R" V 2761 10275 50  0000 C CNN
F 2 "Resistor_SMD:R_0603_1608Metric_Outline" V 2915 10265 50  0001 C CNN
F 3 "~" H 2875 10275 50  0001 C CNN
	1    2875 10275
	0    1    1    0   
$EndComp
Wire Wire Line
	5325 9500 4625 9500
$Comp
L Diode:BAS16TW D?
U 3 1 62D5164F
P 3525 10275
AR Path="/62D5164F" Ref="D?"  Part="3" 
AR Path="/621F15CD/62D5164F" Ref="D13"  Part="3" 
F 0 "D13" H 3600 10175 50  0000 R CNN
F 1 "BAS16TW" H 3675 10100 50  0000 R CNN
F 2 "Package_TO_SOT_SMD:SOT-363_SC-70-6" H 3525 10100 50  0001 C CNN
F 3 "http://www.diodes.com/datasheets/ds30154.pdf" H 3525 10375 50  0001 C CNN
	3    3525 10275
	-1   0    0    1   
$EndComp
$Comp
L Diode:BAS16TW D?
U 2 1 62D51639
P 3200 9550
AR Path="/62D51639" Ref="D?"  Part="1" 
AR Path="/621F15CD/62D51639" Ref="D13"  Part="2" 
F 0 "D13" V 3150 9850 50  0000 R CNN
F 1 "BAS16TW" V 3225 9975 50  0000 R CNN
F 2 "Package_TO_SOT_SMD:SOT-363_SC-70-6" H 3200 9375 50  0001 C CNN
F 3 "http://www.diodes.com/datasheets/ds30154.pdf" H 3200 9650 50  0001 C CNN
	2    3200 9550
	0    1    1    0   
$EndComp
Wire Wire Line
	3950 10625 3950 10675
Wire Wire Line
	3950 10275 3950 10325
Wire Wire Line
	3950 10675 4425 10675
$Comp
L Device:R_US R?
U 1 1 62D51630
P 3950 10475
AR Path="/62D51630" Ref="R?"  Part="1" 
AR Path="/621F15CD/62D51630" Ref="R61"  Part="1" 
F 0 "R61" H 4018 10521 50  0000 L CNN
F 1 "100k" H 4018 10430 50  0000 L CNN
F 2 "Resistor_SMD:R_0603_1608Metric_Outline" V 3990 10465 50  0001 C CNN
F 3 "~" H 3950 10475 50  0001 C CNN
	1    3950 10475
	1    0    0    -1  
$EndComp
Connection ~ 4425 10675
Wire Wire Line
	4425 10675 4425 10750
Connection ~ 3950 10675
Wire Wire Line
	4425 10475 4425 10675
Wire Wire Line
	3125 10625 3125 10675
Wire Wire Line
	3950 10275 4125 10275
Connection ~ 3950 10275
$Comp
L Device:R_US R?
U 1 1 62D51617
P 3125 10475
AR Path="/62D51617" Ref="R?"  Part="1" 
AR Path="/621F15CD/62D51617" Ref="R57"  Part="1" 
F 0 "R57" H 3193 10521 50  0000 L CNN
F 1 "100k" H 3193 10430 50  0000 L CNN
F 2 "Resistor_SMD:R_0603_1608Metric_Outline" V 3165 10465 50  0001 C CNN
F 3 "~" H 3125 10475 50  0001 C CNN
	1    3125 10475
	1    0    0    -1  
$EndComp
$Comp
L Diode:BAS16TW D?
U 1 1 62D51611
P 3200 9075
AR Path="/62D51611" Ref="D?"  Part="2" 
AR Path="/621F15CD/62D51611" Ref="D13"  Part="1" 
F 0 "D13" V 3150 9375 50  0000 R CNN
F 1 "BAS16TW" V 3225 9500 50  0000 R CNN
F 2 "Package_TO_SOT_SMD:SOT-363_SC-70-6" H 3200 8900 50  0001 C CNN
F 3 "http://www.diodes.com/datasheets/ds30154.pdf" H 3200 9175 50  0001 C CNN
	1    3200 9075
	0    1    1    0   
$EndComp
Wire Wire Line
	5200 9100 5825 9100
Connection ~ 5200 9100
Wire Wire Line
	4625 9100 5200 9100
Wire Wire Line
	4625 9400 4625 9500
$Comp
L Device:R_US R?
U 1 1 62D51600
P 4625 9250
AR Path="/62D51600" Ref="R?"  Part="1" 
AR Path="/621F15CD/62D51600" Ref="R62"  Part="1" 
F 0 "R62" H 4693 9296 50  0000 L CNN
F 1 "100k" H 4693 9205 50  0000 L CNN
F 2 "Resistor_SMD:R_0603_1608Metric_Outline" V 4665 9240 50  0001 C CNN
F 3 "~" H 4625 9250 50  0001 C CNN
	1    4625 9250
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR?
U 1 1 62D515FA
P 4425 10750
AR Path="/62D515FA" Ref="#PWR?"  Part="1" 
AR Path="/621F15CD/62D515FA" Ref="#PWR065"  Part="1" 
F 0 "#PWR065" H 4425 10500 50  0001 C CNN
F 1 "GND" H 4430 10577 50  0000 C CNN
F 2 "" H 4425 10750 50  0001 C CNN
F 3 "" H 4425 10750 50  0001 C CNN
	1    4425 10750
	1    0    0    -1  
$EndComp
$Comp
L Transistor_FET:BSS123 Q?
U 1 1 62D515F2
P 4325 10275
AR Path="/62D515F2" Ref="Q?"  Part="1" 
AR Path="/621F15CD/62D515F2" Ref="Q13"  Part="1" 
F 0 "Q13" H 4529 10321 50  0000 L CNN
F 1 "BSS123" H 4529 10230 50  0000 L CNN
F 2 "Package_TO_SOT_SMD:SOT-23" H 4525 10200 50  0001 L CIN
F 3 "http://www.diodes.com/assets/Datasheets/ds30366.pdf" H 4325 10275 50  0001 L CNN
	1    4325 10275
	1    0    0    -1  
$EndComp
Wire Wire Line
	6500 10125 6500 10150
Connection ~ 6500 9900
Wire Wire Line
	6500 9900 6500 9925
Wire Wire Line
	5825 10150 6500 10150
$Comp
L Device:C_Small C?
U 1 1 62D515E8
P 6500 10025
AR Path="/62D515E8" Ref="C?"  Part="1" 
AR Path="/621F15CD/62D515E8" Ref="C42"  Part="1" 
F 0 "C42" H 6408 9979 50  0000 R CNN
F 1 "1uF" H 6408 10070 50  0000 R CNN
F 2 "Capacitor_SMD:C_1206_3216Metric" H 6500 10025 50  0001 C CNN
F 3 "~" H 6500 10025 50  0001 C CNN
	1    6500 10025
	-1   0    0    1   
$EndComp
Wire Wire Line
	4900 10050 4900 10150
Wire Wire Line
	4900 9700 4900 9850
Wire Wire Line
	5200 9900 5200 9100
Wire Wire Line
	5325 9900 5200 9900
Connection ~ 5825 10150
Wire Wire Line
	5825 10150 5825 10200
Wire Wire Line
	5825 10150 5825 10100
Wire Wire Line
	4900 10150 5825 10150
Wire Wire Line
	5325 9700 4900 9700
$Comp
L Device:C_Small C?
U 1 1 62D515D9
P 4900 9950
AR Path="/62D515D9" Ref="C?"  Part="1" 
AR Path="/621F15CD/62D515D9" Ref="C41"  Part="1" 
F 0 "C41" H 4808 9904 50  0000 R CNN
F 1 "100nF" H 4808 9995 50  0000 R CNN
F 2 "Capacitor_SMD:C_1206_3216Metric" H 4900 9950 50  0001 C CNN
F 3 "~" H 4900 9950 50  0001 C CNN
F 4 "C0G" H 4900 9950 50  0001 C CNN "Field4"
	1    4900 9950
	-1   0    0    1   
$EndComp
$Comp
L power:GND #PWR?
U 1 1 62D515D3
P 5825 10200
AR Path="/62D515D3" Ref="#PWR?"  Part="1" 
AR Path="/621F15CD/62D515D3" Ref="#PWR067"  Part="1" 
F 0 "#PWR067" H 5825 9950 50  0001 C CNN
F 1 "GND" H 5830 10027 50  0000 C CNN
F 2 "" H 5825 10200 50  0001 C CNN
F 3 "" H 5825 10200 50  0001 C CNN
	1    5825 10200
	1    0    0    -1  
$EndComp
Wire Wire Line
	6500 9700 6500 9900
Connection ~ 6500 9700
Wire Wire Line
	6500 9425 6500 9700
Wire Wire Line
	6325 9700 6500 9700
Wire Wire Line
	6500 9900 6325 9900
Wire Wire Line
	5825 9100 5825 9300
Connection ~ 5825 9100
Wire Wire Line
	6500 9100 6500 9125
Wire Wire Line
	5825 9100 6500 9100
$Comp
L Device:R_US R?
U 1 1 62D515C4
P 6500 9275
AR Path="/62D515C4" Ref="R?"  Part="1" 
AR Path="/621F15CD/62D515C4" Ref="R66"  Part="1" 
F 0 "R66" H 6275 9300 50  0000 L CNN
F 1 "10M" H 6275 9225 50  0000 L CNN
F 2 "Resistor_SMD:R_0603_1608Metric_Outline" V 6540 9265 50  0001 C CNN
F 3 "~" H 6500 9275 50  0001 C CNN
	1    6500 9275
	1    0    0    -1  
$EndComp
$Comp
L Timer:TLC555xD U?
U 1 1 62D515BD
P 5825 9700
AR Path="/62D515BD" Ref="U?"  Part="1" 
AR Path="/621F15CD/62D515BD" Ref="U7"  Part="1" 
F 0 "U7" H 5550 10150 50  0000 C CNN
F 1 "TLC555xD" H 5525 10075 50  0000 C CNN
F 2 "Package_SO:SOIC-8_3.9x4.9mm_P1.27mm" H 6675 9300 50  0001 C CNN
F 3 "http://www.ti.com/lit/ds/symlink/tlc555.pdf" H 6675 9300 50  0001 C CNN
	1    5825 9700
	1    0    0    -1  
$EndComp
Wire Wire Line
	1925 8350 1775 8350
Wire Wire Line
	1775 8550 1925 8550
$Comp
L Switch:SW_SPDT SW?
U 1 1 62D5152C
P 2125 8450
AR Path="/62D5152C" Ref="SW?"  Part="1" 
AR Path="/621F15CD/62D5152C" Ref="SW2"  Part="1" 
F 0 "SW2" H 2125 8735 50  0000 C CNN
F 1 "SW_SPDT" H 2125 8644 50  0000 C CNN
F 2 "Button_Switch_THT:SW_SPDT_4.7_mm" H 2125 8450 50  0001 C CNN
F 3 "~" H 2125 8450 50  0001 C CNN
	1    2125 8450
	-1   0    0    -1  
$EndComp
Wire Wire Line
	1900 5400 1750 5400
Wire Wire Line
	1750 5600 1900 5600
$Comp
L Switch:SW_SPDT SW4
U 1 1 624F4329
P 2100 5500
F 0 "SW4" H 2100 5785 50  0000 C CNN
F 1 "SW_SPDT" H 2100 5694 50  0000 C CNN
F 2 "Button_Switch_THT:SW_SPDT_4.7_mm" H 2100 5500 50  0001 C CNN
F 3 "~" H 2100 5500 50  0001 C CNN
	1    2100 5500
	-1   0    0    -1  
$EndComp
Wire Wire Line
	1925 4325 1775 4325
Wire Wire Line
	1775 4525 1925 4525
$Comp
L Switch:SW_SPDT SW3
U 1 1 62DDBF06
P 2125 4425
F 0 "SW3" H 2125 4710 50  0000 C CNN
F 1 "SW_SPDT" H 2125 4619 50  0000 C CNN
F 2 "Button_Switch_THT:SW_SPDT_4.7_mm" H 2125 4425 50  0001 C CNN
F 3 "~" H 2125 4425 50  0001 C CNN
	1    2125 4425
	-1   0    0    -1  
$EndComp
$Comp
L power:+5V #PWR060
U 1 1 641161EE
P 1775 8350
F 0 "#PWR060" H 1775 8200 50  0001 C CNN
F 1 "+5V" H 1790 8523 50  0000 C CNN
F 2 "" H 1775 8350 50  0001 C CNN
F 3 "" H 1775 8350 50  0001 C CNN
	1    1775 8350
	1    0    0    -1  
$EndComp
$Comp
L power:+5V #PWR043
U 1 1 64116703
P 1750 5400
F 0 "#PWR043" H 1750 5250 50  0001 C CNN
F 1 "+5V" H 1765 5573 50  0000 C CNN
F 2 "" H 1750 5400 50  0001 C CNN
F 3 "" H 1750 5400 50  0001 C CNN
	1    1750 5400
	1    0    0    -1  
$EndComp
$Comp
L power:+5V #PWR062
U 1 1 64116B26
P 1775 4325
F 0 "#PWR062" H 1775 4175 50  0001 C CNN
F 1 "+5V" H 1790 4498 50  0000 C CNN
F 2 "" H 1775 4325 50  0001 C CNN
F 3 "" H 1775 4325 50  0001 C CNN
	1    1775 4325
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR?
U 1 1 64116EFA
P 1750 5600
AR Path="/64116EFA" Ref="#PWR?"  Part="1" 
AR Path="/621F15CD/64116EFA" Ref="#PWR059"  Part="1" 
F 0 "#PWR059" H 1750 5350 50  0001 C CNN
F 1 "GND" H 1755 5427 50  0000 C CNN
F 2 "" H 1750 5600 50  0001 C CNN
F 3 "" H 1750 5600 50  0001 C CNN
	1    1750 5600
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR?
U 1 1 64117231
P 1775 4525
AR Path="/64117231" Ref="#PWR?"  Part="1" 
AR Path="/621F15CD/64117231" Ref="#PWR063"  Part="1" 
F 0 "#PWR063" H 1775 4275 50  0001 C CNN
F 1 "GND" H 1780 4352 50  0000 C CNN
F 2 "" H 1775 4525 50  0001 C CNN
F 3 "" H 1775 4525 50  0001 C CNN
	1    1775 4525
	1    0    0    -1  
$EndComp
Wire Wire Line
	12375 4625 12375 4700
Wire Wire Line
	12375 4150 12375 4200
Wire Wire Line
	11775 4200 11825 4200
Wire Wire Line
	12125 4200 12375 4200
Connection ~ 12375 4200
Wire Wire Line
	12375 4200 12375 4325
$Comp
L power:+5V #PWR084
U 1 1 641CEE3D
P 12375 3800
F 0 "#PWR084" H 12375 3650 50  0001 C CNN
F 1 "+5V" H 12390 3973 50  0000 C CNN
F 2 "" H 12375 3800 50  0001 C CNN
F 3 "" H 12375 3800 50  0001 C CNN
	1    12375 3800
	1    0    0    -1  
$EndComp
Wire Wire Line
	12375 3800 12375 3850
$Comp
L Device:LED D15
U 1 1 6421B397
P 13850 4475
F 0 "D15" V 13889 4357 50  0000 R CNN
F 1 "SW+" V 13798 4357 50  0000 R CNN
F 2 "LED_SMD:LED_0603_1608Metric" H 13850 4475 50  0001 C CNN
F 3 "~" H 13850 4475 50  0001 C CNN
F 4 "Blue" V 13725 4275 50  0000 C CNN "Field4"
	1    13850 4475
	0    -1   -1   0   
$EndComp
$Comp
L power:GND #PWR?
U 1 1 6421B39D
P 13850 4700
AR Path="/6421B39D" Ref="#PWR?"  Part="1" 
AR Path="/63D4AE42/6421B39D" Ref="#PWR?"  Part="1" 
AR Path="/621F15CD/6421B39D" Ref="#PWR086"  Part="1" 
F 0 "#PWR086" H 13850 4450 50  0001 C CNN
F 1 "GND" H 13855 4527 50  0000 C CNN
F 2 "" H 13850 4700 50  0001 C CNN
F 3 "" H 13850 4700 50  0001 C CNN
	1    13850 4700
	1    0    0    -1  
$EndComp
$Comp
L Device:LED D14
U 1 1 6421B3A3
P 13850 4000
F 0 "D14" V 13889 3882 50  0000 R CNN
F 1 "SW-" V 13798 3882 50  0000 R CNN
F 2 "LED_SMD:LED_0603_1608Metric" H 13850 4000 50  0001 C CNN
F 3 "~" H 13850 4000 50  0001 C CNN
F 4 "Green" V 13725 3775 50  0000 C CNN "Field4"
	1    13850 4000
	0    -1   -1   0   
$EndComp
$Comp
L Device:R_US R56
U 1 1 6421B3AA
P 13450 4200
F 0 "R56" V 13625 4125 50  0000 L CNN
F 1 "5k" V 13550 4150 50  0000 L CNN
F 2 "Resistor_SMD:R_0603_1608Metric_Outline" V 13490 4190 50  0001 C CNN
F 3 "~" H 13450 4200 50  0001 C CNN
	1    13450 4200
	0    -1   -1   0   
$EndComp
Wire Wire Line
	13850 4625 13850 4700
Wire Wire Line
	13850 4150 13850 4200
Wire Wire Line
	13250 4200 13300 4200
Wire Wire Line
	13600 4200 13850 4200
Connection ~ 13850 4200
Wire Wire Line
	13850 4200 13850 4325
$Comp
L power:+5V #PWR085
U 1 1 6421B3B6
P 13850 3800
F 0 "#PWR085" H 13850 3650 50  0001 C CNN
F 1 "+5V" H 13865 3973 50  0000 C CNN
F 2 "" H 13850 3800 50  0001 C CNN
F 3 "" H 13850 3800 50  0001 C CNN
	1    13850 3800
	1    0    0    -1  
$EndComp
Wire Wire Line
	13850 3800 13850 3850
$Comp
L Device:LED D12
U 1 1 6422FC76
P 15275 4475
F 0 "D12" V 15314 4357 50  0000 R CNN
F 1 "SW+" V 15223 4357 50  0000 R CNN
F 2 "LED_SMD:LED_0603_1608Metric" H 15275 4475 50  0001 C CNN
F 3 "~" H 15275 4475 50  0001 C CNN
F 4 "Blue" V 15150 4275 50  0000 C CNN "Field4"
	1    15275 4475
	0    -1   -1   0   
$EndComp
$Comp
L power:GND #PWR?
U 1 1 6422FC7C
P 15275 4700
AR Path="/6422FC7C" Ref="#PWR?"  Part="1" 
AR Path="/63D4AE42/6422FC7C" Ref="#PWR?"  Part="1" 
AR Path="/621F15CD/6422FC7C" Ref="#PWR083"  Part="1" 
F 0 "#PWR083" H 15275 4450 50  0001 C CNN
F 1 "GND" H 15280 4527 50  0000 C CNN
F 2 "" H 15275 4700 50  0001 C CNN
F 3 "" H 15275 4700 50  0001 C CNN
	1    15275 4700
	1    0    0    -1  
$EndComp
$Comp
L Device:LED D10
U 1 1 6422FC82
P 15275 4000
F 0 "D10" V 15314 3882 50  0000 R CNN
F 1 "SW-" V 15223 3882 50  0000 R CNN
F 2 "LED_SMD:LED_0603_1608Metric" H 15275 4000 50  0001 C CNN
F 3 "~" H 15275 4000 50  0001 C CNN
F 4 "Green" V 15150 3775 50  0000 C CNN "Field4"
	1    15275 4000
	0    -1   -1   0   
$EndComp
$Comp
L Device:R_US R53
U 1 1 6422FC89
P 14875 4200
F 0 "R53" V 15050 4125 50  0000 L CNN
F 1 "5k" V 14975 4150 50  0000 L CNN
F 2 "Resistor_SMD:R_0603_1608Metric_Outline" V 14915 4190 50  0001 C CNN
F 3 "~" H 14875 4200 50  0001 C CNN
	1    14875 4200
	0    -1   -1   0   
$EndComp
Wire Wire Line
	15275 4625 15275 4700
Wire Wire Line
	15275 4150 15275 4200
Wire Wire Line
	14675 4200 14725 4200
Wire Wire Line
	15025 4200 15275 4200
Connection ~ 15275 4200
Wire Wire Line
	15275 4200 15275 4325
$Comp
L power:+5V #PWR077
U 1 1 6422FC95
P 15275 3800
F 0 "#PWR077" H 15275 3650 50  0001 C CNN
F 1 "+5V" H 15290 3973 50  0000 C CNN
F 2 "" H 15275 3800 50  0001 C CNN
F 3 "" H 15275 3800 50  0001 C CNN
	1    15275 3800
	1    0    0    -1  
$EndComp
Wire Wire Line
	15275 3800 15275 3850
Wire Wire Line
	6950 3475 6950 3375
Connection ~ 6950 3375
Wire Wire Line
	3650 3375 5450 3375
Wire Wire Line
	5450 3375 5450 5025
Connection ~ 3650 3375
Wire Wire Line
	5450 5025 6825 5025
$Comp
L Transistor_FET:BSS123 Q?
U 1 1 642FBCFE
P 2675 7100
AR Path="/642FBCFE" Ref="Q?"  Part="1" 
AR Path="/621F15CD/642FBCFE" Ref="Q12"  Part="1" 
F 0 "Q12" H 2879 7146 50  0000 L CNN
F 1 "BSS123" H 2879 7055 50  0000 L CNN
F 2 "Package_TO_SOT_SMD:SOT-23" H 2875 7025 50  0001 L CIN
F 3 "http://www.diodes.com/assets/Datasheets/ds30366.pdf" H 2675 7100 50  0001 L CNN
	1    2675 7100
	-1   0    0    -1  
$EndComp
$Comp
L Diode:CD123-B140LR D17
U 1 1 643050AD
P 2575 7950
F 0 "D17" V 2625 8175 50  0000 R CNN
F 1 "CD123-B140LR" V 2550 8625 50  0000 R CNN
F 2 "Diode_SMD:D_PowerDI-123" H 2575 7775 50  0001 C CNN
F 3 "https://www.mouser.com/datasheet/2/54/bourns_CD123D-B1xR-1159223.pdf" H 2575 7950 50  0001 C CNN
	1    2575 7950
	0    -1   -1   0   
$EndComp
$Comp
L Diode:CD123-B140LR D18
U 1 1 6430641F
P 3225 7950
F 0 "D18" V 3150 8200 50  0000 R CNN
F 1 "CD123-B140LR" V 3225 8625 50  0000 R CNN
F 2 "Diode_SMD:D_PowerDI-123" H 3225 7775 50  0001 C CNN
F 3 "https://www.mouser.com/datasheet/2/54/bourns_CD123D-B1xR-1159223.pdf" H 3225 7950 50  0001 C CNN
	1    3225 7950
	0    1    1    0   
$EndComp
$Comp
L Transistor_FET:BSS84 Q14
U 1 1 64307C25
P 3325 7425
F 0 "Q14" H 3530 7471 50  0000 L CNN
F 1 "BSS84" H 3530 7380 50  0000 L CNN
F 2 "Package_TO_SOT_SMD:SOT-23" H 3525 7350 50  0001 L CIN
F 3 "http://assets.nexperia.com/documents/data-sheet/BSS84.pdf" H 3325 7425 50  0001 L CNN
	1    3325 7425
	-1   0    0    -1  
$EndComp
Wire Wire Line
	3225 8450 3225 8100
Wire Wire Line
	3225 7800 3225 7625
Connection ~ 3225 8450
Wire Wire Line
	3225 8450 3725 8450
Wire Wire Line
	2575 7300 2575 7800
Wire Wire Line
	2575 8100 2575 8450
Wire Wire Line
	2575 6900 2575 6150
Wire Wire Line
	2575 6150 3225 6150
Connection ~ 3225 6150
Wire Wire Line
	3225 6150 3450 6150
$Comp
L power:+5V #PWR087
U 1 1 643BBAF5
P 4275 6850
F 0 "#PWR087" H 4275 6700 50  0001 C CNN
F 1 "+5V" H 4290 7023 50  0000 C CNN
F 2 "" H 4275 6850 50  0001 C CNN
F 3 "" H 4275 6850 50  0001 C CNN
	1    4275 6850
	1    0    0    -1  
$EndComp
$Comp
L Device:R_US R?
U 1 1 643BC1AA
P 4275 7175
AR Path="/643BC1AA" Ref="R?"  Part="1" 
AR Path="/621F15CD/643BC1AA" Ref="R58"  Part="1" 
F 0 "R58" H 4343 7221 50  0000 L CNN
F 1 "100k" H 4343 7130 50  0000 L CNN
F 2 "Resistor_SMD:R_0603_1608Metric_Outline" V 4315 7165 50  0001 C CNN
F 3 "~" H 4275 7175 50  0001 C CNN
	1    4275 7175
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR?
U 1 1 643BCBE9
P 4275 8025
AR Path="/643BCBE9" Ref="#PWR?"  Part="1" 
AR Path="/621F15CD/643BCBE9" Ref="#PWR088"  Part="1" 
F 0 "#PWR088" H 4275 7775 50  0001 C CNN
F 1 "GND" H 4280 7852 50  0000 C CNN
F 2 "" H 4275 8025 50  0001 C CNN
F 3 "" H 4275 8025 50  0001 C CNN
	1    4275 8025
	1    0    0    -1  
$EndComp
$Comp
L Device:C_Small C?
U 1 1 6447E34F
P 4750 7950
AR Path="/6447E34F" Ref="C?"  Part="1" 
AR Path="/621F15CD/6447E34F" Ref="C45"  Part="1" 
F 0 "C45" H 4625 7925 50  0000 R CNN
F 1 "10nF" H 4625 8000 50  0000 R CNN
F 2 "Capacitor_SMD:C_0603_1608Metric_Outline" H 4750 7950 50  0001 C CNN
F 3 "~" H 4750 7950 50  0001 C CNN
F 4 " C0G/50V" H 4750 7950 50  0001 C CNN "Field4"
	1    4750 7950
	-1   0    0    1   
$EndComp
$Comp
L power:GND #PWR?
U 1 1 6447F354
P 4750 8050
AR Path="/6447F354" Ref="#PWR?"  Part="1" 
AR Path="/621F15CD/6447F354" Ref="#PWR089"  Part="1" 
F 0 "#PWR089" H 4750 7800 50  0001 C CNN
F 1 "GND" H 4755 7877 50  0000 C CNN
F 2 "" H 4750 8050 50  0001 C CNN
F 3 "" H 4750 8050 50  0001 C CNN
	1    4750 8050
	1    0    0    -1  
$EndComp
Text GLabel 2450 6600 0    50   Input ~ 0
K2_FDBK
Wire Wire Line
	3225 7225 3225 6150
Wire Wire Line
	7825 1925 7825 2125
Wire Wire Line
	7750 1825 7900 1825
Wire Wire Line
	7900 2525 7900 2025
Wire Wire Line
	7900 2525 8175 2525
Wire Wire Line
	7975 2025 7975 2700
Wire Wire Line
	7300 2700 7975 2700
$Comp
L power:+5V #PWR0103
U 1 1 64E13321
P 15250 1800
F 0 "#PWR0103" H 15250 1650 50  0001 C CNN
F 1 "+5V" H 15265 1973 50  0000 C CNN
F 2 "" H 15250 1800 50  0001 C CNN
F 3 "" H 15250 1800 50  0001 C CNN
	1    15250 1800
	1    0    0    -1  
$EndComp
$Comp
L power:+5V #PWR0104
U 1 1 64EAE816
P 6575 4600
F 0 "#PWR0104" H 6575 4450 50  0001 C CNN
F 1 "+5V" H 6590 4773 50  0000 C CNN
F 2 "" H 6575 4600 50  0001 C CNN
F 3 "" H 6575 4600 50  0001 C CNN
	1    6575 4600
	1    0    0    -1  
$EndComp
Wire Wire Line
	6650 1400 6650 1475
$Comp
L power:+5V #PWR0105
U 1 1 64EB05FE
P 6650 1400
F 0 "#PWR0105" H 6650 1250 50  0001 C CNN
F 1 "+5V" H 6665 1573 50  0000 C CNN
F 2 "" H 6650 1400 50  0001 C CNN
F 3 "" H 6650 1400 50  0001 C CNN
	1    6650 1400
	1    0    0    -1  
$EndComp
$Comp
L power:+5V #PWR0106
U 1 1 64EB0B18
P 12375 1050
F 0 "#PWR0106" H 12375 900 50  0001 C CNN
F 1 "+5V" H 12390 1223 50  0000 C CNN
F 2 "" H 12375 1050 50  0001 C CNN
F 3 "" H 12375 1050 50  0001 C CNN
	1    12375 1050
	1    0    0    -1  
$EndComp
$Comp
L power:+5V #PWR0107
U 1 1 64EB131B
P 13875 1800
F 0 "#PWR0107" H 13875 1650 50  0001 C CNN
F 1 "+5V" H 13890 1973 50  0000 C CNN
F 2 "" H 13875 1800 50  0001 C CNN
F 3 "" H 13875 1800 50  0001 C CNN
	1    13875 1800
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR?
U 1 1 64EB1800
P 13875 2825
AR Path="/64EB1800" Ref="#PWR?"  Part="1" 
AR Path="/63D4AE42/64EB1800" Ref="#PWR?"  Part="1" 
AR Path="/621F15CD/64EB1800" Ref="#PWR0108"  Part="1" 
F 0 "#PWR0108" H 13875 2575 50  0001 C CNN
F 1 "GND" H 13880 2652 50  0000 C CNN
F 2 "" H 13875 2825 50  0001 C CNN
F 3 "" H 13875 2825 50  0001 C CNN
	1    13875 2825
	1    0    0    -1  
$EndComp
$Comp
L power:+5V #PWR015
U 1 1 64F0B9BB
P 1750 6150
F 0 "#PWR015" H 1750 6000 50  0001 C CNN
F 1 "+5V" H 1765 6323 50  0000 C CNN
F 2 "" H 1750 6150 50  0001 C CNN
F 3 "" H 1750 6150 50  0001 C CNN
	1    1750 6150
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR?
U 1 1 64F223C1
P 1750 6450
AR Path="/64F223C1" Ref="#PWR?"  Part="1" 
AR Path="/621F15CD/64F223C1" Ref="#PWR028"  Part="1" 
F 0 "#PWR028" H 1750 6200 50  0001 C CNN
F 1 "GND" H 1755 6277 50  0000 C CNN
F 2 "" H 1750 6450 50  0001 C CNN
F 3 "" H 1750 6450 50  0001 C CNN
	1    1750 6450
	1    0    0    -1  
$EndComp
$Comp
L Device:C_Small C15
U 1 1 64F228ED
P 1750 6300
F 0 "C15" H 1842 6391 50  0000 L CNN
F 1 "100uF/10V" H 1842 6300 50  0000 L CNN
F 2 "Capacitor_SMD:C_1210_3225Metric" H 1750 6300 50  0001 C CNN
F 3 "~" H 1750 6300 50  0001 C CNN
F 4 "X5R" H 1842 6209 50  0000 L CNN "Field4"
	1    1750 6300
	1    0    0    -1  
$EndComp
Wire Wire Line
	1750 6450 1750 6400
Wire Wire Line
	1750 6200 1750 6150
Wire Wire Line
	2450 6600 3050 6600
Wire Wire Line
	3050 6600 3050 7100
Wire Wire Line
	3050 7100 2875 7100
Wire Wire Line
	4275 7425 4275 7575
Wire Wire Line
	3525 7425 4275 7425
Wire Wire Line
	3050 6600 4750 6600
Connection ~ 3050 6600
Connection ~ 4275 7425
$Comp
L Device:R_US R?
U 1 1 64451BCB
P 4525 6925
AR Path="/64451BCB" Ref="R?"  Part="1" 
AR Path="/621F15CD/64451BCB" Ref="R59"  Part="1" 
F 0 "R59" V 4350 6925 50  0000 C CNN
F 1 "100k" V 4425 6925 50  0000 C CNN
F 2 "Resistor_SMD:R_0603_1608Metric_Outline" V 4565 6915 50  0001 C CNN
F 3 "~" H 4525 6925 50  0001 C CNN
	1    4525 6925
	0    1    1    0   
$EndComp
$Comp
L Transistor_FET:BSS123 Q?
U 1 1 6525DBB8
P 4375 7775
AR Path="/6525DBB8" Ref="Q?"  Part="1" 
AR Path="/621F15CD/6525DBB8" Ref="Q15"  Part="1" 
F 0 "Q15" H 4579 7821 50  0000 L CNN
F 1 "BSS123" H 4579 7730 50  0000 L CNN
F 2 "Package_TO_SOT_SMD:SOT-23" H 4575 7700 50  0001 L CIN
F 3 "http://www.diodes.com/assets/Datasheets/ds30366.pdf" H 4375 7775 50  0001 L CNN
	1    4375 7775
	-1   0    0    -1  
$EndComp
Wire Wire Line
	4750 6600 4750 6925
Wire Wire Line
	4575 7775 4750 7775
Connection ~ 4750 7775
Wire Wire Line
	4750 7775 4750 7850
Wire Wire Line
	4275 6850 4275 6925
Wire Wire Line
	4275 7325 4275 7425
Wire Wire Line
	4275 6925 4375 6925
Wire Wire Line
	4675 6925 4750 6925
Connection ~ 4275 6925
Wire Wire Line
	4275 6925 4275 7025
Connection ~ 4750 6925
Wire Wire Line
	4750 6925 4750 7775
Wire Wire Line
	4275 7975 4275 8025
$Comp
L Switch:SW_DPST_x2 SW1
U 1 1 65940024
P 2475 1725
F 0 "SW1" H 2475 1960 50  0000 C CNN
F 1 "SW_DPST_x2" H 2475 1869 50  0000 C CNN
F 2 "Button_Switch_THT:SW_DPST_4.7x4.8mm" H 2475 1725 50  0001 C CNN
F 3 "~" H 2475 1725 50  0001 C CNN
	1    2475 1725
	1    0    0    -1  
$EndComp
$Comp
L Switch:SW_DPST_x2 SW1
U 2 1 65940AF7
P 2475 3375
F 0 "SW1" H 2475 3610 50  0000 C CNN
F 1 "SW_DPST_x2" H 2475 3519 50  0000 C CNN
F 2 "Button_Switch_THT:SW_DPST_4.7x4.8mm" H 2475 3375 50  0001 C CNN
F 3 "~" H 2475 3375 50  0001 C CNN
	2    2475 3375
	1    0    0    -1  
$EndComp
Wire Wire Line
	2325 4425 2800 4425
Wire Wire Line
	2300 5500 2775 5500
Text GLabel 2800 4425 2    50   Output ~ 0
SW3_OUT
Text GLabel 2775 5500 2    50   Output ~ 0
SW4_OUT
Text GLabel 11775 4200 0    50   Input ~ 0
SW2_OUT
Text GLabel 13250 4200 0    50   Input ~ 0
SW3_OUT
Text GLabel 14675 4200 0    50   Input ~ 0
SW4_OUT
Text GLabel 3725 8450 2    50   Output ~ 0
SW2_OUT
$Comp
L Regulator_Linear:LT3042xMSE U5
U 1 1 63C6E32D
P 7350 1825
F 0 "U5" H 7350 2192 50  0000 C CNN
F 1 "LT3042xMSE" H 7350 2101 50  0000 C CNN
F 2 "Package_SO:MSOP-10EP-3x3_P0.5mm_EP_thermal_vias_opt" H 7350 2150 50  0001 C CNN
F 3 "https://www.analog.com/media/en/technical-documentation/data-sheets/3042fb.pdf" H 7350 1825 50  0001 C CNN
	1    7350 1825
	1    0    0    -1  
$EndComp
$EndSCHEMATC
