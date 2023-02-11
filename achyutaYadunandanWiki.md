

# Wiki Article: Deep Dive into BLDC Control / High Level Controller Design

## Achyuta Yadunandan

As part of the Bruin Racing EV Supermileage Club, I designed a custom BLDC (brushless DC) controller to

drive the BLDC motors that make up our powertrain. BLDC motors have 3 phases that are driven, with 3

hall sensors that can be used for sensing potion feedback. The BLDC motor controller we designed

controls the 3 phases using a trapezoidal control algorithm. This wiki serves to provide a technical

explanation of this, focusing on the trapezoidal control process with high level connections to the

controller.

# Commutation Explanation


The below image is a commutation diagram for a BLDC motor. The top numbers on the diagram (1

through 6), represent which of the 6 states (or positions) the motor is in. On the left-hand side, the

letters “A”, “B”, and “C” correspond to the 3 phase wires of the BLDC, and “Sensor A”, “Sensor B”, and

“Sensor C” correspond to the 3 hall sensors of the BLDC. Next to “A”, “B”, and “C”, there are the

different voltage levels that can be provided to the phase wires: “+V”, “Float”, “-V”. Note that “-V” is

equivalent to GND, and “Float” means there is no voltage level present. Next to “Sensor A/B/C”, there

are the 2 possible values that a hall sensor can return, “H” and “L” corresponding to HIGH (+5V) and

LOW (GND) respectively.

<picture>
  <img alt"" src="https://github.com/achyuta-yadunandan/ECE180DA_lab/blob/main/im1.png">
</picture>

The general procedure for understanding and using the commutation diagram to control the BLDC

motor goes as follow:

1. Read in Sensor A, Sensor B, and Sensor C values into the microcontroller


2. Determine which state (1-6) that the motor is in, by reading in all 3 hall sensor and using

Boolean logic. For example,

    a. Motor is in State 1, if (Sensor A == HIGH & Sensor B == LOW & Sensor C == HIGH)

    b. Motor is in State 3, if (Sensor A == LOW & Sensor B == HIGH & Sensor C == HIGH)

3. After determining the state, see the corresponding voltages needed to provide to the phase

wires at that point in time. For example,

    a. If in State 1, then +V is needed at Phase A, GND is needed at Phase B, and Float is needed at Phase C

    b. If in State 3, then GND is needed at Phase A, Float is needed at Phase B, and +V is needed at Phase C

4. This process is carried out in a looping cycle in order to turn the motor. First the hall sensors are

read, then the state is determined, then the appropriate voltages are provided to the phase

wires.

# MOSFET Explanation

One of the most critical components in a BLDC controller is the MOSFET. The MOSFET is a 3-terminal

device, with pins called gate, drain, and source, such as seen below. When an “on” voltage is applied to

the gate of the MOSFET, current can between the drain and the source of the MOSFET. At 0V or “off”

applied to the gate, there is a large resistance, effectively an open circuit between the drain and source.

In order to actually achieve the +V, GND, and Float for the phase wires, the following MOSFET

configuration can be used. The MOSFETs Q1, Q3, and Q5 are the high-side MOSFETs. The MOSFETs Q2,

Q4, and Q6 are the low-side MOSFETs. The high and low-side MOSFETs are connected to +V (VDD in the

schematic) and GND respectively. Each motor phase wire (PHASE\_A, PHASE\_B, PHASE\_C), is located at

the common node between the source terminal (pin 3) of the high-side MOSFET and the drain of the

low-side MOSFET (pin 2).

<picture>
  <img alt"" src="https://github.com/achyuta-yadunandan/ECE180DA_lab/blob/main/im2.png">
</picture>

# Controlling MOSFETs for Trapezoidal Control

The below drawing shows the configuration of the MOSFETs with the appropriate gate drive signals

(+10V or GND), such that we can operate the motor when it is in State 1. In State 1, based on the

commutation diagram, Phase_A needs to be +V (or equivalently +VDD), Phase_B needs to be GND, and

Phase_C needs to be Float.

<picture>
  <img alt"" src="https://github.com/achyuta-yadunandan/ECE180DA_lab/blob/main/im3.png">
</picture>

To achieve +VDD for Phase\_A, the input signal HIGH\_A to the gate of Q1, is set to +10V,

and the input signal LOW\_A to the gate of Q2, is set to GND. Hence, Q1 turns on,

creating a short from +VDD to Phase_A, and Q2 turns off creating an open (R ~ infinity)

from GND to Phase\_A. The result is that Phase_A is now +VDD.

To achieve GND for Phase\_B, the input signal HIGH\_B to the gate of Q3, is set to GND,

and the input signal LOW\_B to the gate of Q4, is set to +10V. Hence, Q4 turns on,

creating a short from GND to Phase\_B, and Q3 turns off creating an open (R ~ infinity)

from +VDD to Phase\_B. The result is that Phase\_B is now GND.

To achieve Float for Phase\_C, the input signal HIGH\_C to the gate of Q5, is set to GND,

and the input signal LOW\_C to the gate of Q6, is also set to GND. Hence, both Q5 and

Q6 turn off creating an open (R ~ infinity) from +VDD to Phase\_C and an open (R ~

infinity) from GND to Phase\_C. The result is that Phase\_C is now Float (has no voltage

level).


<picture>
  <img alt"" src="https://github.com/achyuta-yadunandan/ECE180DA_lab/blob/main/im4.png">
</picture>


The gate drive signals to the MOSFET (HIGH\_A/B/C and LOW\_A/B/C) in the above figure are being

generated by a gate driver, such as the IR2184 or the DRV8305. This article does not into the technical

details of how the gate driver circuitry works, but on a high level, the some of the major reasons to use a

gate driver are:

1. It allows us to generate a 10V – 20V signal which is used as an input to the gate of the MOSFET,

which cannot be provided by a logic level microcontroller.

2. Gate drivers can provide large amounts of current to the MOSFETs gate, which allows for

reduced switching time / reducing switching loss.

3. Gate drivers can offer shoot-through protection by preventing both the high-side and low-side

MOSFETs from being on at the same time.



# Resources

BLDC motor simulation / explanation: [Brushless](https://www.youtube.com/watch?v=bCEiOnuODac)[ ](https://www.youtube.com/watch?v=bCEiOnuODac)[DC](https://www.youtube.com/watch?v=bCEiOnuODac)[ ](https://www.youtube.com/watch?v=bCEiOnuODac)[Motor,](https://www.youtube.com/watch?v=bCEiOnuODac)[ ](https://www.youtube.com/watch?v=bCEiOnuODac)[How](https://www.youtube.com/watch?v=bCEiOnuODac)[ ](https://www.youtube.com/watch?v=bCEiOnuODac)[it](https://www.youtube.com/watch?v=bCEiOnuODac)[ ](https://www.youtube.com/watch?v=bCEiOnuODac)[works](https://www.youtube.com/watch?v=bCEiOnuODac)[ ](https://www.youtube.com/watch?v=bCEiOnuODac)[?](https://www.youtube.com/watch?v=bCEiOnuODac)[ ](https://www.youtube.com/watch?v=bCEiOnuODac)[-](https://www.youtube.com/watch?v=bCEiOnuODac)[ ](https://www.youtube.com/watch?v=bCEiOnuODac)[YouTube](https://www.youtube.com/watch?v=bCEiOnuODac)

BLDC Motor Operation: [What](https://microcaregroup.com/how-bldc-motor-controller-works/#:~:text=A%20BLDC%20motor%20controller%20senses%20the%20position%20of,the%20relevant%20stator%20winding%20at%20the%20appropriate%20time.)[ ](https://microcaregroup.com/how-bldc-motor-controller-works/#:~:text=A%20BLDC%20motor%20controller%20senses%20the%20position%20of,the%20relevant%20stator%20winding%20at%20the%20appropriate%20time.)[is](https://microcaregroup.com/how-bldc-motor-controller-works/#:~:text=A%20BLDC%20motor%20controller%20senses%20the%20position%20of,the%20relevant%20stator%20winding%20at%20the%20appropriate%20time.)[ ](https://microcaregroup.com/how-bldc-motor-controller-works/#:~:text=A%20BLDC%20motor%20controller%20senses%20the%20position%20of,the%20relevant%20stator%20winding%20at%20the%20appropriate%20time.)[BLDC](https://microcaregroup.com/how-bldc-motor-controller-works/#:~:text=A%20BLDC%20motor%20controller%20senses%20the%20position%20of,the%20relevant%20stator%20winding%20at%20the%20appropriate%20time.)[ ](https://microcaregroup.com/how-bldc-motor-controller-works/#:~:text=A%20BLDC%20motor%20controller%20senses%20the%20position%20of,the%20relevant%20stator%20winding%20at%20the%20appropriate%20time.)[Motor](https://microcaregroup.com/how-bldc-motor-controller-works/#:~:text=A%20BLDC%20motor%20controller%20senses%20the%20position%20of,the%20relevant%20stator%20winding%20at%20the%20appropriate%20time.)[ ](https://microcaregroup.com/how-bldc-motor-controller-works/#:~:text=A%20BLDC%20motor%20controller%20senses%20the%20position%20of,the%20relevant%20stator%20winding%20at%20the%20appropriate%20time.)[Controller](https://microcaregroup.com/how-bldc-motor-controller-works/#:~:text=A%20BLDC%20motor%20controller%20senses%20the%20position%20of,the%20relevant%20stator%20winding%20at%20the%20appropriate%20time.)[ ](https://microcaregroup.com/how-bldc-motor-controller-works/#:~:text=A%20BLDC%20motor%20controller%20senses%20the%20position%20of,the%20relevant%20stator%20winding%20at%20the%20appropriate%20time.)[and](https://microcaregroup.com/how-bldc-motor-controller-works/#:~:text=A%20BLDC%20motor%20controller%20senses%20the%20position%20of,the%20relevant%20stator%20winding%20at%20the%20appropriate%20time.)[ ](https://microcaregroup.com/how-bldc-motor-controller-works/#:~:text=A%20BLDC%20motor%20controller%20senses%20the%20position%20of,the%20relevant%20stator%20winding%20at%20the%20appropriate%20time.)[How](https://microcaregroup.com/how-bldc-motor-controller-works/#:~:text=A%20BLDC%20motor%20controller%20senses%20the%20position%20of,the%20relevant%20stator%20winding%20at%20the%20appropriate%20time.)[ ](https://microcaregroup.com/how-bldc-motor-controller-works/#:~:text=A%20BLDC%20motor%20controller%20senses%20the%20position%20of,the%20relevant%20stator%20winding%20at%20the%20appropriate%20time.)[It](https://microcaregroup.com/how-bldc-motor-controller-works/#:~:text=A%20BLDC%20motor%20controller%20senses%20the%20position%20of,the%20relevant%20stator%20winding%20at%20the%20appropriate%20time.)[ ](https://microcaregroup.com/how-bldc-motor-controller-works/#:~:text=A%20BLDC%20motor%20controller%20senses%20the%20position%20of,the%20relevant%20stator%20winding%20at%20the%20appropriate%20time.)[Works](https://microcaregroup.com/how-bldc-motor-controller-works/#:~:text=A%20BLDC%20motor%20controller%20senses%20the%20position%20of,the%20relevant%20stator%20winding%20at%20the%20appropriate%20time.)[ ](https://microcaregroup.com/how-bldc-motor-controller-works/#:~:text=A%20BLDC%20motor%20controller%20senses%20the%20position%20of,the%20relevant%20stator%20winding%20at%20the%20appropriate%20time.)[(microcaregroup.com)](https://microcaregroup.com/how-bldc-motor-controller-works/#:~:text=A%20BLDC%20motor%20controller%20senses%20the%20position%20of,the%20relevant%20stator%20winding%20at%20the%20appropriate%20time.)

IRF3205 MOSFETs Datasheet: [IRF3205PbF](https://www.infineon.com/dgdl/irf3205pbf.pdf?fileId=5546d462533600a4015355def244190a)[ ](https://www.infineon.com/dgdl/irf3205pbf.pdf?fileId=5546d462533600a4015355def244190a)[Product](https://www.infineon.com/dgdl/irf3205pbf.pdf?fileId=5546d462533600a4015355def244190a)[ ](https://www.infineon.com/dgdl/irf3205pbf.pdf?fileId=5546d462533600a4015355def244190a)[Data](https://www.infineon.com/dgdl/irf3205pbf.pdf?fileId=5546d462533600a4015355def244190a)[ ](https://www.infineon.com/dgdl/irf3205pbf.pdf?fileId=5546d462533600a4015355def244190a)[Sheet](https://www.infineon.com/dgdl/irf3205pbf.pdf?fileId=5546d462533600a4015355def244190a)[ ](https://www.infineon.com/dgdl/irf3205pbf.pdf?fileId=5546d462533600a4015355def244190a)[(infineon.com)](https://www.infineon.com/dgdl/irf3205pbf.pdf?fileId=5546d462533600a4015355def244190a)

IR2184 Datasheet: [IR2184(4)(S)-600](https://www.infineon.com/dgdl/ir2184.pdf?fileId=5546d462533600a4015355c955e616d4)[ ](https://www.infineon.com/dgdl/ir2184.pdf?fileId=5546d462533600a4015355c955e616d4)[V,](https://www.infineon.com/dgdl/ir2184.pdf?fileId=5546d462533600a4015355c955e616d4)[ ](https://www.infineon.com/dgdl/ir2184.pdf?fileId=5546d462533600a4015355c955e616d4)[1.8](https://www.infineon.com/dgdl/ir2184.pdf?fileId=5546d462533600a4015355c955e616d4)[ ](https://www.infineon.com/dgdl/ir2184.pdf?fileId=5546d462533600a4015355c955e616d4)[A,](https://www.infineon.com/dgdl/ir2184.pdf?fileId=5546d462533600a4015355c955e616d4)[ ](https://www.infineon.com/dgdl/ir2184.pdf?fileId=5546d462533600a4015355c955e616d4)[half](https://www.infineon.com/dgdl/ir2184.pdf?fileId=5546d462533600a4015355c955e616d4)[ ](https://www.infineon.com/dgdl/ir2184.pdf?fileId=5546d462533600a4015355c955e616d4)[bridge](https://www.infineon.com/dgdl/ir2184.pdf?fileId=5546d462533600a4015355c955e616d4)[ ](https://www.infineon.com/dgdl/ir2184.pdf?fileId=5546d462533600a4015355c955e616d4)[gate](https://www.infineon.com/dgdl/ir2184.pdf?fileId=5546d462533600a4015355c955e616d4)[ ](https://www.infineon.com/dgdl/ir2184.pdf?fileId=5546d462533600a4015355c955e616d4)[driver](https://www.infineon.com/dgdl/ir2184.pdf?fileId=5546d462533600a4015355c955e616d4)[ ](https://www.infineon.com/dgdl/ir2184.pdf?fileId=5546d462533600a4015355c955e616d4)[with](https://www.infineon.com/dgdl/ir2184.pdf?fileId=5546d462533600a4015355c955e616d4)[ ](https://www.infineon.com/dgdl/ir2184.pdf?fileId=5546d462533600a4015355c955e616d4)[shutdown](https://www.infineon.com/dgdl/ir2184.pdf?fileId=5546d462533600a4015355c955e616d4)[ ](https://www.infineon.com/dgdl/ir2184.pdf?fileId=5546d462533600a4015355c955e616d4)[(infineon.com)](https://www.infineon.com/dgdl/ir2184.pdf?fileId=5546d462533600a4015355c955e616d4)

## Word Count: 1052
