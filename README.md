# Nanovoltmeter
A low noise nanovoltmeter design files and code

The design includes five boards:
1. The nanovoltmeter main board
2. A SMPS daughter board to downconvert the battery voltage to the various power rails used in the design
3. A battery board with BMS for 4S 21700 cells
4. A rear panel board with battery charger
5. A front panel

This repository will also include the source code for the STM32U575 microcontroller that interfaces with the various peripherals.

<img width="1339" alt="Main board render (top)" src="https://github.com/curtisseizert/Nanovoltmeter/assets/22351001/bd294c93-2309-4054-af25-7efb0ccb30b2">
<img width="1295" alt="Main board render (bottom)" src="https://github.com/curtisseizert/Nanovoltmeter/assets/22351001/6c3817a4-bf96-47ec-aa63-08649612dcaf">


A proof of concept model of the input stage was previously prepared, which showed a flat NSD of approximately 1.2 nV/sqrt(Hz). At 1 sample per second, the peak to peak noise was about 15 nV. The temperature coefficient of the meter was approximately 1 nV/K, but sensitivity to temperature fluctuations was evident and the change in power dissipation as the battery discharged led to a drift of ca. 1 nV/h. This prototype also had a bias current of ~3 nA due to charge injection from the input modulator switch. This revision seeks to change those issues as follows:

1. The main power rails of the board are generated using low noise buck converters (LT8608S) and a Cuk converter on a shielded daughterboard so that the dropout of the on-board LDOs remains consistent through battery discharge
2. Improved layout will (hopefully) reduce sensitivity to temperature changes. The input stage is contained in a shielding enclosure and is surrounded by isolation slots. Additionally, the largest power dissipators have been placed outside this shield on opposite sides.
3. The input switching is now handled by a low-capacitance quad MOSFET array (PE4140) using gate drive voltages independently generated with a quad DAC. In a model experiment, it was feasible to reduce bias current to <5 pA in this way.
4. A fast, precision ADC (AD4032-24) now measures the offset error between switching cycles so a 16-bit DAC can control the offset voltage of the input differential amplifier by modulating the channel currents of the input JFETs. In the schematic, the trim range of the DAC is approximately +/-625uV (LSB = 20nV). The low gain of the trimming differential amplifier means the transconductance drops by <1% at the input extremes. This should allow measurement of the trim gain during instrument warmup for single-cycle settling of the control loop.
5. Digital implementation of the control loop also allows one to turn off autozeroing or run the input switching at very low frequencies to minimize charge injection.

Some additional features are:
1. Footprints for two types of voltage references: an ADR1399 for lowest noise/highest stability and an LTC6655 for lower power consumption
2. An optically isolated external trigger input for e.g., synchronizing clocking to powerline cycles.
3. Input protection that engages current limiting to 10 mA (typical, max: 15 mA) at a differential voltage of 2 V for protection against accidentally connecting up to 100V across the terminals. A GDT is included to provide transient protection against higher voltages.
4. Two input ranges: +/-2 mV and +/-20 mV.
5. Reduced power consumption (with LTC6655)
6. Ability to digitize low-level DC coupled signals at up to 500 kSPS (2 MSPS with AD4030-24) with an LSB size of 0.24 nV (at 24 bits).

