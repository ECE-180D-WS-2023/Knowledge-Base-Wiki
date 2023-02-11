# A Shallow Deep Dive Into the CAN Protocol

What if I told you that there exists a simple low-cost technology that you can utilize in your projects to land that much coveted summer internship?

Join me on this journey of discovering what this protocol is about and, to give a little incentive, I guide you on a simple application where we create a reflex game between two people using this technology.

You CAN do this!

## What is CAN

Controller Area Network or CAN is a network technology primarily used in embedded systems that provide fast communication amongst microcontrollers while being cost-effective. Notably, a network can function as a series of nodes and operate without a host computer [[1](https://github.com/warrenwallis/180DA-WarmUp/edit/main/misc/wiki-article-first-draft.md#links)]. 

*Ok, but what does that mean!?* It means that there isn't a central computer delegating tasks and controlling how messages are sent or received. Like some cryptocurrencies, a CAN bus is a decentralized network that is able to send messages efficiently across its network.

Some characteristics of CAN [[2](https://github.com/warrenwallis/180DA-WarmUp/edit/main/misc/wiki-article-first-draft.md#links)]:
- ~~preserving foods~~
- needs only two wires to communicate
- operates at data rates up to 1 Mb/s
- supports a max of 8 Bytes per message frame
- supports message priority
- supports ID lengths of of 11-bits and 29-bits

Some industries of where CAN is used:
- automotive (where it began)
- medical instruments
- manufacturing
- elevators and escalators (where I use it for my job :nail_care:)

Similar technologies to CAN [[4](https://github.com/warrenwallis/180DA-WarmUp/edit/main/misc/wiki-article-first-draft.md#links)]:
- ~~electric can-opener~~
- ethernet w/ TCP/IP (expensive :thumbsdown:)
- FPD-link

## Digging Deeper into :canned_food:

### Hardware Principles

As mentioned earlier, a network using CAN only needs two wires to operate:

<img width="1440" alt="image" src="https://user-images.githubusercontent.com/66290894/218182132-b87afaed-96fc-472a-818d-404dfaf79e87.png"> [[1](https://github.com/warrenwallis/180DA-WarmUp/edit/main/misc/wiki-article-first-draft.md#links)]

This significantly reduces the wires needed to connect the network, and is why it was and still is popular in the automobile industry. The motivation behind the CAN protocol was to reduce costs by reducing the use of copper wire:

![image](https://user-images.githubusercontent.com/66290894/218182038-5c71639b-a748-4b06-8a9f-f547c59a5874.png) [[2](https://github.com/warrenwallis/180DA-WarmUp/edit/main/misc/wiki-article-first-draft.md#links)]

We can break down a node into three parts:

<img width="770" alt="image" src="https://user-images.githubusercontent.com/66290894/218181390-546e2749-774b-40f2-89ee-fbb928902026.png"> [[1](https://github.com/warrenwallis/180DA-WarmUp/edit/main/misc/wiki-article-first-draft.md#links)]

1. Microprocessor
   <p>
      The microprocessor is responsible for decoding messages received and decides what messages to transmit.
   </p>
2. CAN controller
   <p>
      The controller is responsible for receiving and storing messages until a full message frame is received to process.
   </p>
4. Transceiver
   <p>
      The tranceiver converts the data from the bus to a format that the CAN controller can understand. It also converts the message from the controller to a format the bus accepts. 
   </p>
[[1](https://github.com/warrenwallis/180DA-WarmUp/edit/main/misc/wiki-article-first-draft.md#links)]

### Software Principles

*Well that's cool and all, but how CAN I use this!?* I gotchu!

There are many abstractions and API's created for the user to be able to use the CAN protocol. In my job, I am able to use CAN on python, C++, and C to interact and send signals to the elevator system.

Really, all we need to focus on as users are:
1. Message ID's
   <p>
      There exists two different standards for the protocol: Standard CAN and Extended CAN.
   
      Standard CAN has a message ID of 11 bits, therefore, we can have 2<sup>11</sup> or 2048 different identifiers from 0 to 2047.
      Extended CAN has a message ID of 29 bits, therefore, we can have 2<sup>29</sup> or 536(ish) million identifiers from 0 to 536870911 [[3](https://github.com/warrenwallis/180DA-WarmUp/edit/main/misc/wiki-article-first-draft.md#links)].
   
      Pretty crazy huh? And as programmers we can even design how we want to use these messages. Do we potentially want 536 million different nodes? Do we want to have 536 million different types of messages we can send? The skies the limit or really 2<sup>29</sup>, but you get what I mean.
   </p>
2. The actual message
   <p>
      Regardless of whether you choose standard or extended, the protocol still give us 8 bytes to send our message in.
      
      And again, as programmers we have the ability to design how we want to encode our data:
      <ol>
         <li>we can use one-hot encoding where only one of the 64 bits (8 bytes * 8 bits/byte) are set to a high</li>
         <li>we can use the whole range of the 64 bits with either binary or hexadecimal</li>
         <li>we can even send strings as longs as we bound it to 8 characters since a character will take up 1 byte each</li>
      </ol>
   </p>
3. What speed we want to send things through the bus
    <p>
        Before using a the CAN bus we must first initialize and set all nodes to read and write data at a certain speed. Remember that we are bounded by 1 Megabit per second. But somethings else that we should consider the the length of the transmission cable we are going to use. The higher the data rate, the shorter we can send data.

        A good rule of thumb to follow is that 1Mb/s can reach 40 meters while 125kb/s can reach 500 meters.
    </p>

## A Simple Walkthrough: CAN we make a :video_game:

*walkthrough of game example*

## Sealing this CAN Post

Controller Area Network is an easy and cheap solution to any type of application that needs linked communication. In this post, I have given a brief overview of what CAN is, it's components, and how we can use it.

It is a technology that is used in many of the things we interact with and now you know how to use it!

## Links

1. [Wikipedia](https://en.m.wikipedia.org/wiki/CAN_bus)
2. [CopperHillTech](https://copperhilltech.com/a-brief-introduction-to-controller-area-network/)
3. [TexasInstruments-1](https://www.ti.com/lit/an/sloa101b/sloa101b.pdf?ts=1675960976305&ref_url=https%253A%252F%252Fwww.google.com%252F)
4. [TexasInstruments-2](https://www.ti.com/lit/an/slyt560/slyt560.pdf?ts=1676009390287&ref_url=https%253A%252F%252Fwww.google.com%252F#:~:text=Still%2C%20Ethernet%20can%20transport%20data,provid%2D%20ing%20much%20more%20bandwidth)
5. [Adafruit](https://learn.adafruit.com/adafruit-feather-m4-can-express)
