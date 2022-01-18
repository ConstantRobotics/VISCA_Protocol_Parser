***
![VCODEC](_static/VISCA_logo_with_borders.png)
***


## 
## OVERVIEW
C++ library **VISCA_ProtocolParser_lib** version **1.0.0** is designed for parsing VISCA (trademark of Sony Corporation) protocol messages. The library is designed according to the VISCA protocol description for the camera **Sony FCB-EV7520A**. The library allows you to use it to control other cameras that support the VISCA protocol. The library is an early version and may contain bugs. Before encoding and decoding specific commands please check the source code of the library for the corresponding command according to the technical description of your camera.

The library provides:
* VISCA message encoding
* Decoding VISCA messages
* Searching for messages in a continuous data set

The library contains a description of the **ViscaProtocolParser** class, which contains only two methods: message encoding (**encodeCommand(...)**) and decoding (**decodeData(...)**). Simple interface for easy use:


```c++
namespace  cr
{
namespace visca
{
    class ViscaProtocolParser
    {
    public:

        ViscaProtocolParser();

        ~ViscaProtocolParser();

        bool encodeCommand(
            visca::ViscaPackets command_ID,
            uint8_t* packet,
            uint32_t& packet_size,
            uint32_t camera_address,
            uint32_t param_1 = 0,
            uint32_t param_2 = 0,
            uint32_t param_3 = 0,
            uint32_t param_4 = 0,
            uint32_t param_5 = 0,
            uint32_t param_6 = 0,
            uint32_t param_7 = 0,
            uint32_t param_8 = 0,
            uint32_t param_9 = 0,
            uint32_t param_10 = 0);

        visca::ViscaPackets decodeData(
            uint8_t next_byte,
            uint32_t camera_address,
            uint32_t& param_1,
            uint32_t& param_2,
            uint32_t& param_3,
            uint32_t& param_4,
            uint32_t& param_5,
            uint32_t& param_6,
            uint32_t& param_7,
            uint32_t& param_8,
            uint32_t& param_9,
            uint32_t& param_10);

        static std::string getVersion();      
    };
}
}
```

***
### COMMAND ENCODING
To encode commands, you must use the **encodeData(...)***. The method has the following parameters:
* **visca::ViscaPackets command_ID** - The identifier of the command according to the enumeration **ViscaPackets** declared in the file **ViscaProtocolParserDataStructures.h**. The structure contains identifiers of all VISCA protocol packets.
* **uint8_t*** **packet** - Pointer to the packet buffer to be filled by the method. The size of the buffer must be at least **24 bytes**.
* **uint32_t& packet_size** - Output value of size of encoded packet.
* **uint32_t camera_address** - Camera address. Usually equals 1 or can be reassigned with the command **visca::ViscaPackets::COMMAND_AddressSet**. The camera address can be in the range from 1 to 7.
* **param_1 - param_10** - Parameters to include in the package. The value of each parameter depends on the **command_ID**. A description of the parameter values for each package type is contained in the enumeration **ViscaPackets** declared in the file **ViscaProtocolParserDataStructures.h**. Please also check the library source code for the corresponding VISCA command.

The method returns **TRUE** if the package was created successfully or returns **FALSE** in case of any error.

Command encoding example:
```c++
// Encoding
uint8_t packet_data[24];
uint32_t packet_size = 0;
visca_protocol_parser.encodeCommand(cr::visca::ViscaPackets::INQUIRY_CAM_ZoomPosInq, packet_data, packet_size, 1, 1);

// Sending
serial_port.SendData(packet_data, packet_size);
```

***
### DECODING MESSAGES
The decoding of the data is done using the method **decodeData(...)**. Data is decoded one byte at a time. This is done in order to detect connected packets in the data from the serial port. The method has the following parameters:
* **uint8_t next_byte** - Next byte in data to decode.
* **uint32_t camera_address** - Camera address. Usually equals 1 or can be reassigned with the command **visca::ViscaPackets::COMMAND_AddressSet**. The camera address can be in the range from 1 to 7.
* **param_1 - param_10** - Output parameters from decoded message. The value of each parameter depends on the **command_ID**. A description of the parameter values for each package type is contained in the enumeration **ViscaPackets** declared in the file **ViscaProtocolParserDataStructures.h**. Please also check the library source code for the corresponding VISCA message.

The method returs ID of message accoding to enumeration **ViscaPackets** declared in the file **ViscaProtocolParserDataStructures.h**. If the method decoded a message, it returns the message identifier. If no message is decoded, the method returns the identifier **visca::ViscaPackets::UNDEFINED_PACKET**.

Message decoding example:
```c++
// Read data.
int number_of_bytes = serial_port.ReadData(packet_data, packet_size);
// Decode data.
if (number_of_bytes <= 0)
{
    std::cout << "No response" << std::endl;
}
else
{
    for (int i = 0; i < number_of_bytes; ++i)
    {
        switch(visca_protocol_parser.decodeData(packet_data[i], 1, param_1, param_2, param_3, param_4, param_5, param_6, param_7, param_8, param_9, param_10))
        {
        case cr::visca::ViscaPackets::ACKNOWLEDGE:
            std::cout << "ACKNOWLEDGE" << std::endl;
            break;
        case cr::visca::ViscaPackets::COMPLETION_COMMANDS:
            std::cout << "COMPLETION_COMMANDS" << std::endl;
            break;
        case cr::visca::ViscaPackets::COMPLETION_INQUIRY:
            std::cout << "COMPLETION_INQUIRY" << std::endl;
            break;
        case cr::visca::ViscaPackets::REPLY_CAM_ZoomPos:
            std::cout << "ZOOM POSITION" << std::endl;
            break;
        default:
            break;
        }
    }
}
```

Examples and demo application you can find in **ViscaProtocolParserTests** folder.
