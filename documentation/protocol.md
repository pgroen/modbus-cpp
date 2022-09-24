# MODBUS Application Protocol SPecification V1.1b3

## Introduction

MODBUS is an application layer messaging protocol for client/server communication between
devices connected on different types of buses or networks.

It is currently implemented using:

* TCP/IP over Ethernet. See MODBUS Messaging Implementation Guide V1.0a.
* Asynchronous serial transmission over a variety of media (wire : EIA/TIA -232-E, EIA-422,
EIA/TIA-485-A; fiber, radio, etc.)
* MODBUS PLUS, a high speed token passing network.

## Abbreviations

|Abbreviation |Description |
|---|--------------------|
| ADU | Application Data Unit
| HDLC | High Level Data Link Control |
| HMI | Human Machine Interface |
| IETF | Internet Engineering Task Force |
| I/O | Input / Output |
| IP | Internet Protocol |
| MAC | Media Access Control |
| MB | MODBUS Protocol |
| MBAP | MODBUS Application Protocol |
| PDU | Protocol Data Unit |
| PLC | Programmable Logic Controller |
| TCP | Transmission Control Protocol |

## Context
The MODBUS protocol allows an easy communication within all types of network architectures. Every type of devices (PLC, HMI, Control Panel, Driver, Motion control, I/O Device...) can use MODBUS protocol to initiate a remote operation.
The same communication can be done as well on serial line as on Ethernet TCP/IP networks. Gateways allow a communication between several types of buses or network using the MODBUS protocol.

## General Description

### Protocol description
The MODBUS protocol defines a simple protocol data unit (PDU) independent of the underlying communication layers. The mapping of MODBUS protocol on specific buses or network ccan introduce some additional fields on the Application Data Unit (ADU).

```
                                        ADU
<-------------------------------------------------------------------------------->
+--------------------+  +---------------+ +---------------------+  +-------------+
| Additional address |  | Function code | |         Data        |  | Error check |
+--------------------+  +---------------+ +---------------------+  +-------------+
                        <--------------------------------------->
                                        PDU
General MODBUS frame
```

The MODBUS application data unit is built by the client that initiates a MODBUS transaction. The function indicates to the server what kind of action to perform. The MODBUS application protocol establishes the format of a request initiated by a client.
The function code field of a MODBUS data unit is coded in one byte. Valid codes are in the range of 1..255 decimal ( where the range 128 - 255 is reserved and used for exception responses.) When a message is sent from a Client to a Server device the function code field tells the server what kind of action to perform. Function code "0" is not valid.

Sub function codes are added to some function codes to define multiple actions.
The data field of messages sent from a client to server devices contains additional information that the server uses to take the action defined by the function code. This can include items like discrete and register addresses, the quantity of items to be handled, ad the count of actual data bytes in the field. The data field may be non-existent (of zero-length) in certain kinds of requests, in this case the server does not require any additional information. The function code alone specifies the action.

If no error occurs related to the MODBUS function requested in a properly received MODBUS
ADU the data field of a response from a server to a client contains the data requested. If an
error related to the MODBUS function requested occurs, the field contains an exception code
that the server application can use to determine the next action to be taken.
For example a client can read the ON / OFF states of a group of discrete outputs or inputs or
it can read/write the data contents of a group of registers.
When the server responds to the client, it uses the function code field to indicate either a
normal (error-free) response or that some kind of error occurred (called an exception
response). For a normal response, the server simply echoes to the request the original
function code.

For an exception response, the server returns a code that is equivalent to the original function
code from the request PDU with its most significant bit set to logic 1.

The size of the MODBUS PDU is limited by the size constraint inherited from the first
MODBUS implementation on Serial Line network (max. RS485 ADU = 256 bytes).

Therefore: <br>
MODBUS PDU for serial line communication = 256 - Server address (1 byte) - CRC (2
bytes) = 253 bytes.

Consequently:<br>
RS232 / RS485 ADU = 253 bytes + Server address (1 byte) + CRC (2 bytes) = 256 bytes.
TCP MODBUS ADU = 253 bytes + MBAP (7 bytes) = 260 bytes.
The MODBUS protocol defines three PDUs. They are :<br>

| Full name | PDU | Definition | Description |
|-----------|-----|------------|-------------|
| MODBUS Request PDU | mb_req_pdu | {function_code, request_data} | function_code = [1 byte] MODBUS function code<br> request_data = [n bytes] This field is function code dependent and usually contains information such as variable references, variable counts, data offsets, sub-function codes etc |
| MODBUS Response PDU | mb_rsp_pdu | {function_code, response_data}| function_code = [1 byte] MODBUS function code <br> response_data = [n bytes] This field is function code dependent and usually contains information such as variable references, variable counts, data offsets, sub-function codes, etc. |
| MODBUS Exception Response PDU | mb_excep_rsp_pdu | {exception-function_code, request_data} | exception-function_code = [1 byte] MODBUS function code + 0x80 <br> exception_code = [1 byte] MODBUS Exception Code Defined in table "MODBUS Exception Codes" (see section 7 ). |


### Data Encoding

 MODBUS uses a ‘big-Endian’ representation for addresses and data items. This means
that when a numerical quantity larger than a single byte is transmitted, the most significant
byte is sent first. So for example
Register size
 value
16 - bits
 0x1234
 Note: For more details, see [1] .
April 26, 2012
the first byte sent is
 0x12
http://www.modbus.org
then 0x34