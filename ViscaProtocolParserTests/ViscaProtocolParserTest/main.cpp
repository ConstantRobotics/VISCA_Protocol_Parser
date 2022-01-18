#include <iostream>
#include <string>
#include <cstring>
#include <thread>
#include <chrono>
#include "ViscaProtocolParser.h"
#include "SerialPort.h"


int main(void)
{
    std::cout << "##########################################" << std::endl;
    std::cout << "#                                        #" << std::endl;
    std::cout << "#     VISCA Communication Test v1.0      #" << std::endl;
    std::cout << "#                                        #" << std::endl;
    std::cout << "##########################################" << std::endl << std::endl;

    int serial_port_num = 0;
    std::cout << "Enter serial port number: ";
    std::cin >> serial_port_num;

    int serial_port_baudrate = 0;
    std::cout << "Enter serial port baudrate (bps): ";
    std::cin >> serial_port_baudrate;

    clib::SerialPort serial_port;
    std::string serial_port_name = "\\\\.\\COM" + std::to_string(serial_port_num);
    if (!serial_port.Open(serial_port_name.c_str(), serial_port_baudrate, 1000))
    {
        std::cout << serial_port_name << " not open. Exit..." << std::endl;
        std::this_thread::sleep_for(std::chrono::seconds(1));
        return -1;
    }

    // Init variables.
    uint8_t packet_data[128];
    memset(packet_data, 0, 128);
    cr::visca::ViscaProtocolParser visca_protocol_parser;
    uint32_t param_1 = 0;
    uint32_t param_2 = 0;
    uint32_t param_3 = 0;
    uint32_t param_4 = 0;
    uint32_t param_5 = 0;
    uint32_t param_6 = 0;
    uint32_t param_7 = 0;
    uint32_t param_8 = 0;
    uint32_t param_9 = 0;
    uint32_t param_10 = 0;

    // Main loop.
    while (true)
    {
        // Encode command.
        uint32_t packet_size = 0;
        visca_protocol_parser.encodeCommand(cr::visca::ViscaPackets::INQUIRY_CAM_ZoomPosInq, packet_data, packet_size, 1, 1);

        std::this_thread::sleep_for(std::chrono::seconds(1));

        // Send command.
        std::cout << serial_port.SendData(packet_data, packet_size) << " bytes sent" << std::endl;

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

    }

    return 1;
}
