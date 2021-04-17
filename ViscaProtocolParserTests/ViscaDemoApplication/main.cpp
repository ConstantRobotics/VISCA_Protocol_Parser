#include <iostream>
#include <cstring>
#include <cstdint>
#include <ctime>
#include <chrono>
#include <cstdlib>
#include <thread>
#include <fstream>
#include <mutex>
#include <atomic>
#include <condition_variable>
#include <opencv2/opencv.hpp>
#include "SerialPort.h"
#include "ViscaProtocolParser.h"



// Entry point.
int main(void)
{
    // Camera num dialog.
    int camera_num = 0;
    std::cout << "Enter camera num: ";
    std::cin >> camera_num;

    // Open camera.
    cv::VideoCapture camera;
    if (!camera.open(camera_num))
    {
        std::cout << "Camera not open" << std::endl;
        std::this_thread::sleep_for(std::chrono::seconds(1));
        return -1;
    }
    std::cout << "Camera open" << std::endl;

    int serial_port_num = 0;
    std::cout << "Enter serial port number: ";
    std::cin >> serial_port_num;

    int serial_port_baudrate = 0;
    std::cout << "Enter serial port baudrate (bps): ";
    std::cin >> serial_port_baudrate;

    std::string serial_port_name = "\\\\.\\COM" + std::to_string(serial_port_num);
    clib::SerialPort serial_port;
    if (!serial_port.Open(serial_port_name.c_str(), serial_port_baudrate, 10))
    {
        std::cout << serial_port_name << " not open. Exit..." << std::endl;
        std::this_thread::sleep_for(std::chrono::seconds(1));
        return -1;
    }
    std::cout << serial_port_name << " open" << std::endl;

    // Init variables.
    cv::Mat frame;
    visca::ViscaProtocolParser protocol_parser;

    uint8_t input_serial_data[128];
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

    uint8_t zoom_commands[41][9] =	// Array of ZOOM commands.
        {
            {0x81, 0x01, 0x04, 0x47, 0x00, 0x00, 0x00, 0x00, 0xFF},
            {0x81, 0x01, 0x04, 0x47, 0x01, 0x06, 0x0A, 0x01, 0xFF},
            {0x81, 0x01, 0x04, 0x47, 0x02, 0x00, 0x06, 0x03, 0xFF},
            {0x81, 0x01, 0x04, 0x47, 0x02, 0x06, 0x02, 0x08, 0xFF},
            {0x81, 0x01, 0x04, 0x47, 0x02, 0x0A, 0x01, 0x0D, 0xFF},
            {0x81, 0x01, 0x04, 0x47, 0x02, 0x0D, 0x01, 0x03, 0xFF},
            {0x81, 0x01, 0x04, 0x47, 0x02, 0x0F, 0x06, 0x0D, 0xFF},
            {0x81, 0x01, 0x04, 0x47, 0x03, 0x01, 0x06, 0x01, 0xFF},
            {0x81, 0x01, 0x04, 0x47, 0x03, 0x03, 0x00, 0x0D, 0xFF},
            {0x81, 0x01, 0x04, 0x47, 0x03, 0x04, 0x08, 0x06, 0xFF},
            {0x81, 0x01, 0x04, 0x47, 0x03, 0x05, 0x0D, 0x07, 0xFF},
            {0x81, 0x01, 0x04, 0x47, 0x03, 0x07, 0x00, 0x09, 0xFF},
            {0x81, 0x01, 0x04, 0x47, 0x03, 0x08, 0x02, 0x00, 0xFF},
            {0x81, 0x01, 0x04, 0x47, 0x03, 0x09, 0x02, 0x00, 0xFF},
            {0x81, 0x01, 0x04, 0x47, 0x03, 0x0A, 0x00, 0x0A, 0xFF},
            {0x81, 0x01, 0x04, 0x47, 0x03, 0x0A, 0x0D, 0x0D, 0xFF},
            {0x81, 0x01, 0x04, 0x47, 0x03, 0x0B, 0x09, 0x0C, 0xFF},
            {0x81, 0x01, 0x04, 0x47, 0x03, 0x0C, 0x04, 0x06, 0xFF},
            {0x81, 0x01, 0x04, 0x47, 0x03, 0x0C, 0x0D, 0x0C, 0xFF},
            {0x81, 0x01, 0x04, 0x47, 0x03, 0x0D, 0x06, 0x00, 0xFF},
            {0x81, 0x01, 0x04, 0x47, 0x03, 0x0D, 0x0D, 0x04, 0xFF},
            {0x81, 0x01, 0x04, 0x47, 0x03, 0x0E, 0x03, 0x09, 0xFF},
            {0x81, 0x01, 0x04, 0x47, 0x03, 0x0E, 0x09, 0x00, 0xFF},
            {0x81, 0x01, 0x04, 0x47, 0x03, 0x0E, 0x0D, 0x0C, 0xFF},
            {0x81, 0x01, 0x04, 0x47, 0x03, 0x0F, 0x01, 0x0E, 0xFF},
            {0x81, 0x01, 0x04, 0x47, 0x03, 0x0F, 0x05, 0x07, 0xFF},
            {0x81, 0x01, 0x04, 0x47, 0x03, 0x0F, 0x08, 0x0A, 0xFF},
            {0x81, 0x01, 0x04, 0x47, 0x03, 0x0F, 0x0B, 0x06, 0xFF},
            {0x81, 0x01, 0x04, 0x47, 0x03, 0x0F, 0x0D, 0x0C, 0xFF},
            {0x81, 0x01, 0x04, 0x47, 0x04, 0x00, 0x00, 0x00, 0xFF},
            {0x81, 0x01, 0x04, 0x47, 0x06, 0x00, 0x00, 0x00, 0xFF},
            {0x81, 0x01, 0x04, 0x47, 0x06, 0x0A, 0x08, 0x00, 0xFF},
            {0x81, 0x01, 0x04, 0x47, 0x07, 0x00, 0x00, 0x00, 0xFF},
            {0x81, 0x01, 0x04, 0x47, 0x07, 0x03, 0x00, 0x00, 0xFF},
            {0x81, 0x01, 0x04, 0x47, 0x07, 0x05, 0x04, 0x00, 0xFF},
            {0x81, 0x01, 0x04, 0x47, 0x07, 0x06, 0x0C, 0x00, 0xFF},
            {0x81, 0x01, 0x04, 0x47, 0x07, 0x08, 0x00, 0x00, 0xFF},
            {0x81, 0x01, 0x04, 0x47, 0x07, 0x08, 0x0C, 0x00, 0xFF},
            {0x81, 0x01, 0x04, 0x47, 0x07, 0x09, 0x08, 0x00, 0xFF},
            {0x81, 0x01, 0x04, 0x47, 0x07, 0x0A, 0x00, 0x00, 0xFF},
            {0x81, 0x01, 0x04, 0x47, 0x07, 0x0A, 0x0C, 0x00, 0xFF}
        };
    int32_t zoom_index = 0;

    // Main loop.
    while (true)
    {
        // Capture next frame.
        camera >> frame;
        if (frame.empty())
        {
            camera.set(cv::CAP_PROP_POS_FRAMES, 1);
            continue;
        }


        // Read data.
        int number_of_bytes = serial_port.ReadData(input_serial_data, 128);

        // Decode data.
        if (number_of_bytes > 0)
        {
            for (int i = 0; i < number_of_bytes; ++i)
            {
                switch(protocol_parser.Decode_Data(input_serial_data[i], 1, param_1, param_2, param_3, param_4, param_5, param_6, param_7, param_8, param_9, param_10))
                {
                case visca::ViscaPackets::ACKNOWLEDGE:
                    std::cout << "ACKNOWLEDGE" << std::endl;
                    break;
                case visca::ViscaPackets::COMPLETION_COMMANDS:
                    std::cout << "COMPLETION_COMMANDS" << std::endl;
                    break;
                case visca::ViscaPackets::COMPLETION_INQUIRY:
                    std::cout << "COMPLETION_INQUIRY" << std::endl;
                    break;
                case visca::ViscaPackets::REPLY_CAM_ContinuousZoomPos:
                    std::cout << "CONTINUOUS ZOOM POSITION" << std::endl;
                    break;
                default:
                    break;
                }
            }
        }



        // Draw zoom index.
        cv::putText(frame, std::to_string(zoom_index), cv::Point(5, 25), cv::FONT_HERSHEY_SIMPLEX, 0.5, cv::Scalar(255, 255, 0));

        // Show image.
        cv::imshow("CAMERA", frame);

        // Process keyboard events.
        switch (cv::waitKey(1))
        {
        case 27:// ESC - EXIT.
        {
            std::cout << "EXIT" << std::endl;
            exit(0);
        }

        case 49:// 1 - Activate combine zoom mode.
        {
            // Encode command.
            uint8_t serial_data[128];
            uint32_t data_size = 0;
            protocol_parser.Encode_Command(visca::ViscaPackets::COMMAND_CAM_DZoom_Combine_Mode, serial_data, data_size, 1);

            // Send command.
            serial_port.SendData(serial_data, data_size);

        }
        break;

        case 50:// 2 - +ZOOM
        {
            ++zoom_index;
            if (zoom_index > 40)
                zoom_index = 40;

            // Encode command.
            uint8_t serial_data[128];
            uint32_t data_size = 0;
            protocol_parser.Encode_Command(visca::ViscaPackets::COMMAND_CAM_Zoom_Direct, serial_data, data_size, 1,
                    zoom_commands[zoom_index][4],
                    zoom_commands[zoom_index][5],
                    zoom_commands[zoom_index][6],
                    zoom_commands[zoom_index][7]);

            // Send command.
            serial_port.SendData(serial_data, data_size);

        }
        break;

        case 51:// 3 - -ZOOM
        {
            --zoom_index;
            if (zoom_index < 0)
                zoom_index = 0;

            // Encode command.
            uint8_t serial_data[128];
            uint32_t data_size = 0;
            protocol_parser.Encode_Command(visca::ViscaPackets::COMMAND_CAM_Zoom_Direct, serial_data, data_size, 1,
                    zoom_commands[zoom_index][4],
                    zoom_commands[zoom_index][5],
                    zoom_commands[zoom_index][6],
                    zoom_commands[zoom_index][7]);

            // Send command.
            serial_port.SendData(serial_data, data_size);

        }
        break;

        case 52:// 4 - Camera stabilization ON
        {
            // Encode command.
            uint8_t serial_data[128];
            uint32_t data_size = 0;
            protocol_parser.Encode_Command(visca::ViscaPackets::COMMAND_CAM_Stabilizer_On, serial_data, data_size, 1);

            // Send command.
            serial_port.SendData(serial_data, data_size);

        }
        break;

        case 53:// 5 - Camera stabilization OFF
        {
            // Encode command.
            uint8_t serial_data[128];
            uint32_t data_size = 0;
            protocol_parser.Encode_Command(visca::ViscaPackets::COMMAND_CAM_Stabilizer_Off, serial_data, data_size, 1);

            // Send command.
            serial_port.SendData(serial_data, data_size);

        }
        break;

        }
    }


    return 1;
}


