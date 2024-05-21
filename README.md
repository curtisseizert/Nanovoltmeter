# Nanovoltmeter
A low noise nanovoltmeter design files and code

The design includes five boards:
1. The nanovoltmeter main board
2. A SMPS daughter board to downconvert the battery voltage to the various power rails used in the design
3. A battery board with BMS for 4S 21700 cells
4. A rear panel board with battery charger
5. A front panel

This repository will also include the source code for the STM32U575 microcontroller that interfaces with the various peripherals.

![ADR1399-boardfront](https://github.com/curtisseizert/Nanovoltmeter/assets/22351001/9ea7e242-64c5-4fc7-a24f-2e9ce9876d46)
![ADR1399-boardrear](https://github.com/curtisseizert/Nanovoltmeter/assets/22351001/88aedb9b-be14-4447-87e4-bf99c72b94a3)


Curent Status
-------------
Version 2.0 of the FW improves handling of results and user inputs, as well as reduces the load on the CPU by making better use of DMA. Unit testing is ongoing and some features are not yet implemented, but they will be coming soon. The command structure uses a SCPI-like syntax but is not fully SCPI-compliant. The improved FW should facilitate more performance testing.

I have built two of these boards, one with an LTC6655 reference, the other with an ADR1399. I have tested the noise and offset performance of the latter both with internal shorts and an external 1 mV reference. Getting both boards to work has required some changes, and I have made the appropriate edits to a revision C schematic though I have not laid this out. The noise and temperature sensitivity of the LTC6655 board is superior for internal shorts, but it seems to have some issue that degrades its linearity, though I don't attribute this to the reference. The design, while complex, appears to meet the goals of low noise, low bias current, negligible offset, and low power consumption. 

Design Background
-----------------

A proof of concept model of the input stage was previously prepared, which showed a flat NSD of approximately 1.2 nV/sqrt(Hz). At 1 sample per second, the peak to peak noise was about 15 nV. The temperature coefficient of the meter was approximately 1 nV/K, but sensitivity to temperature fluctuations was evident and the change in power dissipation as the battery discharged led to a drift of ca. 1 nV/h. This prototype also had a bias current of ~3 nA due to charge injection from the input modulator switch. This revision seeks to change those issues as follows:

1. The main power rails of the board are generated using low noise buck converters (LT8608S) and a Cuk converter on a shielded daughterboard so that the dropout of the on-board LDOs remains consistent through battery discharge
2. Improved layout reduced sensitivity to temperature changes. The input stage is contained in a shielding enclosure and is surrounded by isolation slots. Additionally, the largest power dissipators have been placed outside this shield on opposite sides.
3. The input switching is now handled by a low-capacitance quad MOSFET array (PE4140) using gate drive voltages independently generated with a quad DAC. In a model experiment, it has proven feasible to adjust the DAC switching levels and deadtimes to reduce bias current to <5 pA, though I need to do more work to optimize this aspect.
4. A fast, precision ADC (AD4030-24) now measures the offset error between switching cycles so a 16-bit DAC can control the offset voltage of the input differential amplifier by modulating the channel currents of the input JFETs. In the schematic, the trim range of the DAC is approximately +/-625uV (LSB = 20nV). The low gain of the trimming differential amplifier means the transconductance drops by <1% at the input extremes. This should allow measurement of the trim gain during instrument warmup for single-cycle settling of the control loop.
5. Digital implementation of the control loop also allows one to turn off autozeroing or run the input switching at very low frequencies to minimize charge injection.

Some additional features are:
1. Footprints for two types of voltage references: an ADR1399 for lowest noise/highest stability and an LTC6655 for lower power consumption
2. An optically isolated external trigger input for e.g., synchronizing clocking to powerline cycles.
3. Input protection that engages current limiting to 10 mA (typical, max: 15 mA) at a differential voltage of 2 V for protection against accidentally connecting up to 100V across the terminals. A GDT is included to provide transient protection against higher voltages.
4. Two input ranges: +/-2 mV and +/-20 mV.
5. Reduced power consumption (with LTC6655)
6. Ability to digitize low-level DC coupled signals at up to 500 kSPS (2 MSPS with AD4030-24) with an LSB size of 0.24 nV (at 24 bits).

Principle of Operation
----------------------

<img width="1753" alt="SimplifiedSchematic" src="https://github.com/curtisseizert/Nanovoltmeter/assets/22351001/f38c8695-773f-48de-b3a6-2627330c2b3a">

An input modulator (SW1) switch connects input and feedback signals alternately to the terminals of a high-gain, low-noise discrete JFET differential amplifier. The outputs of the differential amplifier are connected to the terminals of an operational amplifier (U10) via a synchronous demodulator (SW2). The output of the frontend is taken from this op amp. The ADC reads the output voltage from each phase of the modulator. If the difference between the two readings is larger than a deadband value, the controller increments or decrements the Vos DAC (U44) as needed to adjust the channel currents in the input differential amplifier to null the offset of the differential amplifier. The channel currents are controlled by a low-gain transconductance stage formed from U20. To null the offset and 1/f noise of the ADC and associated signal conditioning circuitry, a switch at the inputs to the ADC driver reverses the inputs to this block such that the modulator/demodulator operates at an integer multiple of the input switches for the ADC.

This topology has the effect of modulating the offset voltage (and 1/f noise) of the input stage up to the switching frequency but not modulating the input signal itself. This modulated error signal is minimized by the offset-nulling feedback loop, which dramatically reduces the power at the chopping frequency, and filtered using a cascaded integrator-comb (sinc) filter of user-selectable order (from 1 to 3). Because the input capacitance of the input stage JFETs is fairly large (ca. 75pF), nulling the offset of the differential amplifier also reduces current pulsation at the chopping frequency.

As such, the only theoretical source of offset, drift, or 1/f noise is the op amp connected to the demodulated differential amp outputs, and all these error sources are attentuated by the gain of the differential amplifier, which is about 3500. The input JFETs are paired with PNP BJTs Q16 and Q21 in a Szlikai-like topology to increase the transconductance of the input amplifier to enable it to operate at high gain. The value of drain resistors R91 and R100 is a compromise between noise, gain, and stability; at 133R, each of the eight JFETs operates with a drain current of ca. 1 mA, and the BJTs operate with a collector current of about 1 mA each. Larger resistor values slightly increase moise, increase gain, and decrease phase margin of the overall composite amplifier due to the increase in loop gain.  The op amp used in the design (an ADA4625-1) is a precision, low noise part with low offset and drift, and these error sources are negligible when attenuated by a factor of 3500. With typical spec sheet values, this op amp should contribute about 4 nV offset, 0.06 nV/K temperature coefficient, and give a 1/f noise corner of ca. 0.1 mHz. In practice, the effect of parasitics, especially thermal EMF proves to be a much larger error source, with an uncorrected offset voltage at the front panel of about 250 nV and a 1/f corner of slightly less than 1 mHz (depending on the stability of the ambient temperature). The NSD when measuring the (internally) shorted inputs is <1.2 nV/rt Hz, and with 10s sample periods I have observed p-p noise of just 1.36 nV over 10000 seconds.

![LF ShortNoise](https://github.com/curtisseizert/Nanovoltmeter/assets/22351001/e69d9c2a-2de0-4f51-8ca4-e8019d776dae)
![10mHz ShortNoise](https://github.com/curtisseizert/Nanovoltmeter/assets/22351001/acbbcb22-a177-4077-bb84-48284c870213)
![10kS_short_0p1SPS](https://github.com/curtisseizert/Nanovoltmeter/assets/22351001/19846efc-9486-4ee4-9806-4a2467401a33)

Issues
------

The design in rev B does not give this performance without a few bodges to fix some oscillation issues I encountered (and these are eliminated in the revision that I am currently working on). The protection of the power rails has proven inadequate, and there are certain fault conditions that can cause many components to fail, notably including the expensive and painful to replace ADC. I have added clamps on the 1V8 and 5V4 rails to deal with this issue. 

It would be nice to be able to utilize hardware triggers and NCS for the SPI bus that communicates with the ADC so that conversion reads do not needs to be handled in an interrupt service routine.

The ADR1399 takes a lot of power to keep warm, and this makes the overall design more sensitive to environmental variations. It is not clear to me that the juice is worth the squeeze for this reference in such a high-gain application, as it increases the power dissipation on the board by at least 50% and it seems likely that the stability of the resistive divider setting the front end gain will not be sufficient to see any improvement over the LTC6655.

The noise of the ADC and driver circuitry is inexplicably high, and this actually degrades the resolution on the +/-20mV range at low (500kSPS) ADC sample rates. The reason for this is unclear at present, but optimizing the values used in the charge-kickback RC network at the inputs helps.

There is some issue with plugging an input in on the front panel leading to a significant shift (ca. 200 nV) of the input offset voltage with an internal short. Wrapping the input cable around a high permeability toroidal core to make a CM choke helps with this, but the root cause is not clear as the interfaces are optically isolated and the instrument runs from battery power.

