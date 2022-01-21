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
#include <opencv2/opencv.hpp>
#include "SerialPort.h"
#include "ViscaProtocolParser.h"
#include "json.hpp"
using json = nlohmann::json;
#pragma warning(disable : 4996)



// Global variables.
clib::SerialPort g_serialPort;              // Serial port.
std::mutex g_serialPortMutex;               // Mutex to protect serial port.
cv::VideoCapture g_videoSource;             // Video source.
int g_zoomPosition = 0;                     // Zoom position.
int g_focusPosition = 0;                    // Focus position.
int g_maxZoomPosition = 0;                  // Maximum zoom position.
int g_maxFocusPosition = 0;                 // Maximum zoom position.
constexpr int g_dataBufferSize = 128;       // Data buffer size.
uint8_t g_outputData[g_dataBufferSize];     // Output data.
uint32_t g_outputDataSize = 0;              // Output data size.
std::mutex g_outputDataMutex;               // Mutex to protect output data.
bool g_combineZoomModeFlag = false;         // Combine zoom mode flag.
bool g_digitalZoomModeFlag = false;         // Digital zoom mode flag.
bool g_digitalStabilizationFlag = false;    // Digitl stabilization flag.
bool g_autoFocusModeFlag = true;            // Auto focus mode flag.
bool g_autoExposureModeFlag = true;         // Auto exposure mode flag.
bool g_defogModeFlag = false;               // Defog mode flag.
bool g_zoomTeleFlag = false;                // Zoom tele flag.
bool g_zoomWideFlag = false;                // Zoom wide flag.
bool g_focusFarFlag = false;                // Focus far flag.
bool g_focusNearFlag = false;               // Focus near flag.
std::atomic<uint32_t> g_inputZoomPos;       // Input zoom position.
int g_cameraAddress = 1;                    // VISCA camera address.


/**
 * @brief Load and init params.
 * @return true if params are loaded.
 * @return false if params not loaded.
 */
bool loadAndInitParams();

/**
 * @brief Input data processing thread function.
 */
void inputDataProcessingThreadFunction();

/**
 * @brief Function to change fix focus position.
 */
static void fixFocusPositionChanging(int, void*)
{
    cr::visca::ViscaProtocolParser protocolParser;
    g_outputDataMutex.lock();
    protocolParser.encodeCommand(cr::visca::ViscaPackets::COMMAND_CAM_Focus_Direct,
                                 g_outputData, g_outputDataSize, 1, g_focusPosition);
    g_outputDataMutex.unlock();
}

/**
 * @brief Function to change fix zoom position.
 */
static void fixZoomPositionChanging(int, void*)
{
    cr::visca::ViscaProtocolParser protocolParser;
    g_outputDataMutex.lock();
    protocolParser.encodeCommand(cr::visca::ViscaPackets::COMMAND_CAM_Zoom_Direct,
                                 g_outputData, g_outputDataSize, 1, g_zoomPosition);
    g_outputDataMutex.unlock();
}

/**
 * @brief Send initial command.
 */
void sendInitialCommands();

/**
 * @brief keyboard events processing function.
 * @param key Button key.
 */
void keyboardEventsProcessingFunction(int key);



// Entry point.
int main(void)
{
    std::cout << "#######################################" << std::endl;
    std::cout << "#                                     #" << std::endl;
    std::cout << "#    VISCA demo application v" << cr::visca::ViscaProtocolParser::getVersion() << "    #" << std::endl;
    std::cout << "#                                     #" << std::endl;
    std::cout << "#######################################" << std::endl << std::endl;

    // Load and init params.
    if (!loadAndInitParams())
    {
        std::cout << "Parameters not init" << std::endl;
        std::this_thread::sleep_for(std::chrono::seconds(1));
        return -1;
    }

    // Send initial commands.
    sendInitialCommands();
    g_inputZoomPos.store(0);

    // Launch input data processing string.
    std::thread inputDataProcessingThread = std::thread(&inputDataProcessingThreadFunction);

    // Init variables.
    cv::Mat frame;
    cr::visca::ViscaProtocolParser protocolParser;

    // Create window.
    cv::namedWindow("VIDEO", cv::WINDOW_AUTOSIZE);
    cv::createTrackbar("Fix focus", "VIDEO", &g_focusPosition, g_maxZoomPosition, fixFocusPositionChanging);
    cv::createTrackbar("Fix zoom", "VIDEO", &g_zoomPosition, g_maxZoomPosition, fixZoomPositionChanging);

    // Main loop.
    while (true)
    {
        // Capture next frame.
        g_videoSource >> frame;
        if (frame.empty())
        {
            g_videoSource.set(cv::CAP_PROP_POS_FRAMES, 1);
            continue;
        }

        // Draw info.
        cv::putText(frame, "1 - Combine/Separate mode",
                    cv::Point(5, 15), cv::FONT_HERSHEY_SIMPLEX, 0.5, cv::Scalar(255, 255, 0));
        cv::putText(frame, g_combineZoomModeFlag ? "COMBINE" : "SEPARATE",
                    cv::Point(280, 15), cv::FONT_HERSHEY_SIMPLEX, 0.5,
                    cv::Scalar(0, 0, 255));

        cv::putText(frame, "2 - Digital zoom ON/OFF",
                    cv::Point(5, 40), cv::FONT_HERSHEY_SIMPLEX, 0.5, cv::Scalar(255, 255, 0));
        cv::putText(frame, g_digitalZoomModeFlag ? "ON" : "OFF",
                    cv::Point(280, 40), cv::FONT_HERSHEY_SIMPLEX, 0.5,
                    g_digitalZoomModeFlag ? cv::Scalar(0, 255, 0) : cv::Scalar(0, 0, 255));

        cv::putText(frame, "3 - Digital stabilization ON/OFF",
                    cv::Point(5, 65), cv::FONT_HERSHEY_SIMPLEX, 0.5, cv::Scalar(255, 255, 0));
        cv::putText(frame, g_digitalStabilizationFlag ? "ON" : "OFF",
                    cv::Point(280, 65), cv::FONT_HERSHEY_SIMPLEX, 0.5,
                    g_digitalStabilizationFlag ? cv::Scalar(0, 255, 0) : cv::Scalar(0, 0, 255));

        cv::putText(frame, "4 - Auto/Manual focus",
                    cv::Point(5, 90), cv::FONT_HERSHEY_SIMPLEX, 0.5, cv::Scalar(255, 255, 0));
        cv::putText(frame, g_autoFocusModeFlag ? "AUTO" : "MANUAL",
                    cv::Point(280, 90), cv::FONT_HERSHEY_SIMPLEX, 0.5, cv::Scalar(0, 0, 255));

        cv::putText(frame, "5 - Auto/Manual exposure",
                    cv::Point(5, 115), cv::FONT_HERSHEY_SIMPLEX, 0.5, cv::Scalar(255, 255, 0));
        cv::putText(frame, g_autoFocusModeFlag ? "AUTO" : "MANUAL",
                    cv::Point(280, 115), cv::FONT_HERSHEY_SIMPLEX, 0.5, cv::Scalar(0, 0, 255));

        cv::putText(frame, "6 - Defog ON/OFF",
                    cv::Point(5, 140), cv::FONT_HERSHEY_SIMPLEX, 0.5, cv::Scalar(255, 255, 0));
        cv::putText(frame, g_defogModeFlag ? "ON" : "OFF",
                    cv::Point(280, 140), cv::FONT_HERSHEY_SIMPLEX, 0.5,
                    g_defogModeFlag ? cv::Scalar(0, 255, 0) : cv::Scalar(0, 0, 255));

        cv::putText(frame, "7 - Zoom tele/stop", cv::Point(5, 165), cv::FONT_HERSHEY_SIMPLEX, 0.5, cv::Scalar(255, 255, 0));
        cv::putText(frame, "8 - Zoom wide/stop", cv::Point(5, 190), cv::FONT_HERSHEY_SIMPLEX, 0.5, cv::Scalar(255, 255, 0));
        cv::putText(frame, "9 - Focus far/stop", cv::Point(5, 215), cv::FONT_HERSHEY_SIMPLEX, 0.5, cv::Scalar(255, 255, 0));
        cv::putText(frame, "0 - Focus near/stop", cv::Point(5, 240), cv::FONT_HERSHEY_SIMPLEX, 0.5, cv::Scalar(255, 255, 0));

        // Show input zoom position.
        cv::putText(frame, "ZOOM: " + std::to_string(g_inputZoomPos.load()),
                    cv::Point(5, 265), cv::FONT_HERSHEY_SIMPLEX, 0.5, cv::Scalar(0, 0, 255));

        // Show image.
        cv::imshow("VIDEO", frame);

        // Process keyboard events.
        keyboardEventsProcessingFunction(cv::waitKey(1));
    }

    return 1;
}



// Function to load and init params.
bool loadAndInitParams()
{
    std::string params_file_name = "ViscaDemoApplication.json";
    json jsonConf;

    // Open JSON file.
    std::ifstream in(params_file_name);
    if (!in.is_open())
        return false;

    // Parse JSON.
    try {
        jsonConf = json::parse(in);
    }
    catch (json::parse_error& e)
    {
        return false;
    }

    // Read params.
    std::string videoSourceInitString = "";
    std::string serialPortName = "";
    int serialPortBaudrate = 0;
    int waitTimeoutMs = 0;
    try
    {
        json channelJson = jsonConf.at("Params");

        // Load video stabilizer params.
        videoSourceInitString = channelJson.at("videoSourceInitString").get<std::string>();
        serialPortName = channelJson.at("serialPortName").get<std::string>();
        serialPortBaudrate = channelJson.at("serialPortBaudrate").get<int>();
        waitTimeoutMs = channelJson.at("waitTimeoutMs").get<int>();
        g_maxZoomPosition = channelJson.at("maxZoomPosition").get<int>();
        g_maxFocusPosition = channelJson.at("maxFocusPosition").get<int>();
        g_cameraAddress = channelJson.at("cameraAddress").get<int>();
    }
    catch (const std::exception&)
    {
        in.close();
        return false;
    }
    in.close();

    // Init video source.
    if (videoSourceInitString.length() < 5)
    {
        g_videoSource.set(cv::CAP_PROP_BUFFERSIZE, 1);
        if (!g_videoSource.open(std::stoi(videoSourceInitString)))
        {
            std::cout << "ERROR: Video source " << videoSourceInitString << " not open" << std::endl;
            return false;
        }
        g_videoSource.set(cv::CAP_PROP_BUFFERSIZE, 1);
    }
    else
    {
        g_videoSource.set(cv::CAP_PROP_BUFFERSIZE, 1);
        if (!g_videoSource.open(videoSourceInitString))
        {
            std::cout << "ERROR: Video source " << videoSourceInitString << " not open" << std::endl;
            return false;
        }
        g_videoSource.set(cv::CAP_PROP_BUFFERSIZE, 1);
    }

    // Open serial port.
    if (!g_serialPort.Open(serialPortName.c_str(), serialPortBaudrate, waitTimeoutMs))
    {
        std::cout << "ERROR: Serial port " << serialPortName << " not open" << std::endl;
        return false;
    }

    return true;
}



// Function to process input data.
void inputDataProcessingThreadFunction()
{
    // Init variables.
    const int maxInputDataSize = 128;
    cr::visca::ViscaProtocolParser protocolParser;
    uint8_t inputData[maxInputDataSize];
    uint32_t param1, param2, param3, param4, param5, param6, param7, param8, param9, param10 = 0;

    // Prepare zoom position inqury command.
    uint8_t getZoomPosCommand[32];
    uint32_t getZoomPosCommandSize = 0;
    protocolParser.encodeCommand(cr::visca::ViscaPackets::INQUIRY_CAM_ZoomPosInq,
                                 getZoomPosCommand, getZoomPosCommandSize, g_cameraAddress);

    // Thread loop.
    while (true)
    {
        // Read data from serial port.
        int numBytes = g_serialPort.ReadData(inputData, maxInputDataSize);

        // Decode data.
        for (int i = 0; i < numBytes; ++i)
        {
            switch(protocolParser.decodeData(inputData[i], 1, param1, param2, param3, param4,
                                             param5, param6, param7, param8, param9, param10))
            {
            case cr::visca::ViscaPackets::REPLY_CAM_ContinuousZoomPos:
                std::cout << "DZOOM: " << param1 << "  ZOOM: " << param2 << std::endl;
                g_inputZoomPos.store(param2);
                break;
            case cr::visca::ViscaPackets::REPLY_CAM_ZoomPos:
                std::cout << "ZOOM: " << param1 << std::endl;
                g_inputZoomPos.store(param1);
                break;
            default: break;
            }
        }

        // Send data if it exeists.
        g_outputDataMutex.lock();
        if (g_outputDataSize > 0)
            g_serialPort.SendData(g_outputData, g_outputDataSize);
        else
            // Send zoom pos inquiry command.
            g_serialPort.SendData(getZoomPosCommand, getZoomPosCommandSize);
        g_outputDataSize = 0;
        g_outputDataMutex.unlock();
    }
}



// Function to send initial commands.
void sendInitialCommands()
{
    // Init variables.
    cr::visca::ViscaProtocolParser protocolParser;
    uint8_t serialData[32];
    uint32_t dataSize = 0;

    // Set continious zoom position reply mode.
    protocolParser.encodeCommand(cr::visca::ViscaPackets::COMMAND_CAM_ContinuousZoomPosReply_On,
                                 serialData, dataSize, g_cameraAddress);
    g_serialPort.SendData(serialData, dataSize);
    std::this_thread::sleep_for(std::chrono::milliseconds(50));

    // Set continious zoom position reply interval (1 V-cycle).
    protocolParser.encodeCommand(cr::visca::ViscaPackets::COMMAND_CAM_ZoomPosReplyIntervalTimeSet,
                                 serialData, dataSize, g_cameraAddress, 1);
    g_serialPort.SendData(serialData, dataSize);
    std::this_thread::sleep_for(std::chrono::milliseconds(50));

    // Set 0 zoom position.
    protocolParser.encodeCommand(cr::visca::ViscaPackets::COMMAND_CAM_Zoom_Direct,
                                 serialData, dataSize, g_cameraAddress, 0);
    g_serialPort.SendData(serialData, dataSize);
    std::this_thread::sleep_for(std::chrono::milliseconds(50));

    // Set zoom separate mode.
    protocolParser.encodeCommand(cr::visca::ViscaPackets::COMMAND_CAM_DZoom_Separate_Mode,
                                 serialData, dataSize, g_cameraAddress);
    g_serialPort.SendData(serialData, dataSize);
    std::this_thread::sleep_for(std::chrono::milliseconds(50));

    // Set OFF continious focus position reply mode.
    protocolParser.encodeCommand(cr::visca::ViscaPackets::COMMAND_CAM_ContinuousFocusPosReply_Off,
                                 serialData, dataSize, g_cameraAddress);
    g_serialPort.SendData(serialData, dataSize);
    std::this_thread::sleep_for(std::chrono::milliseconds(50));

    // Disable stabilization.
    protocolParser.encodeCommand(cr::visca::ViscaPackets::COMMAND_CAM_Stabilizer_Off,
                                 serialData, dataSize, g_cameraAddress);
    g_serialPort.SendData(serialData, dataSize);
    std::this_thread::sleep_for(std::chrono::milliseconds(50));

    // Set autofocus mode.
    protocolParser.encodeCommand(cr::visca::ViscaPackets::COMMAND_CAM_Focus_Auto_Focus_On,
                                 serialData, dataSize, g_cameraAddress);
    g_serialPort.SendData(serialData, dataSize);
    std::this_thread::sleep_for(std::chrono::milliseconds(50));

    // Set defog OFF.
    protocolParser.encodeCommand(cr::visca::ViscaPackets::COMMAND_CAM_Defog_Off,
                                 serialData, dataSize, g_cameraAddress);
    g_serialPort.SendData(serialData, dataSize);
    std::this_thread::sleep_for(std::chrono::milliseconds(50));

    // Set full auto exposure.
    protocolParser.encodeCommand(cr::visca::ViscaPackets::COMMAND_CAM_AE_Full_Auto,
                                 serialData, dataSize, g_cameraAddress);
    g_serialPort.SendData(serialData, dataSize);
    std::this_thread::sleep_for(std::chrono::milliseconds(50));
}



// Function to process keyboard events.
void keyboardEventsProcessingFunction(int key)
{
    // Init variables.
    cr::visca::ViscaProtocolParser protocolParser;

    // Process keyboard events.
    switch (key)
    {
    case 27:// ESC - EXIT.
    {
        std::cout << "EXIT" << std::endl;
        exit(0);
    }

    case 49:// 1 - Combine zoom mode ON/OFF.
    {
        // Encode command.
        g_outputDataMutex.lock();
        if (g_combineZoomModeFlag)
            protocolParser.encodeCommand(cr::visca::ViscaPackets::COMMAND_CAM_DZoom_Separate_Mode, g_outputData, g_outputDataSize, 1);
        else
            protocolParser.encodeCommand(cr::visca::ViscaPackets::COMMAND_CAM_DZoom_Combine_Mode, g_outputData, g_outputDataSize, 1);
        g_combineZoomModeFlag = !g_combineZoomModeFlag;
        g_outputDataMutex.unlock();
    }
    break;

    case 50:// 2 - Digital zoom ON/OFF.
    {
        // Encode command.
        g_outputDataMutex.lock();
        if (g_digitalZoomModeFlag)
            protocolParser.encodeCommand(cr::visca::ViscaPackets::COMMAND_CAM_DZoom_Off, g_outputData, g_outputDataSize, 1);
        else
            protocolParser.encodeCommand(cr::visca::ViscaPackets::COMMAND_CAM_DZoom_On, g_outputData, g_outputDataSize, 1);
        g_digitalZoomModeFlag = !g_digitalZoomModeFlag;
        g_outputDataMutex.unlock();
    }
    break;

    case 51:// 3 - Digital stabilization ON/OFF.
    {
        // Encode command.
        g_outputDataMutex.lock();
        if (g_digitalStabilizationFlag)
            protocolParser.encodeCommand(cr::visca::ViscaPackets::COMMAND_CAM_Stabilizer_Off, g_outputData, g_outputDataSize, 1);
        else
            protocolParser.encodeCommand(cr::visca::ViscaPackets::COMMAND_CAM_Stabilizer_On, g_outputData, g_outputDataSize, 1);
        g_digitalStabilizationFlag = !g_digitalStabilizationFlag;
        g_outputDataMutex.unlock();
    }
    break;

    case 52:// 4 - Auto/Manual focus.
    {
        // Encode command.
        g_outputDataMutex.lock();
        if (g_autoFocusModeFlag)
            protocolParser.encodeCommand(cr::visca::ViscaPackets::COMMAND_CAM_Focus_Manual_Focus_On, g_outputData, g_outputDataSize, 1);
        else
            protocolParser.encodeCommand(cr::visca::ViscaPackets::COMMAND_CAM_Focus_Auto_Focus_On, g_outputData, g_outputDataSize, 1);
        g_autoFocusModeFlag = !g_autoFocusModeFlag;
        g_outputDataMutex.unlock();
    }
    break;

    case 53:// 5 - Auto/Manual exposure.
    {
        // Encode command.
        g_outputDataMutex.lock();
        if (g_autoExposureModeFlag)
            protocolParser.encodeCommand(cr::visca::ViscaPackets::COMMAND_CAM_AE_Manual, g_outputData, g_outputDataSize, 1);
        else
            protocolParser.encodeCommand(cr::visca::ViscaPackets::COMMAND_CAM_AE_Full_Auto, g_outputData, g_outputDataSize, 1);
        g_autoExposureModeFlag = !g_autoExposureModeFlag;
        g_outputDataMutex.unlock();
    }
    break;

    case 54:// 6 - Defog ON/OFF.
    {
        // Encode command.
        g_outputDataMutex.lock();
        if (g_defogModeFlag)
            protocolParser.encodeCommand(cr::visca::ViscaPackets::COMMAND_CAM_Defog_Off, g_outputData, g_outputDataSize, 1);
        else
            protocolParser.encodeCommand(cr::visca::ViscaPackets::COMMAND_CAM_Defog_On, g_outputData, g_outputDataSize, 1);
        g_defogModeFlag = !g_defogModeFlag;
        g_outputDataMutex.unlock();
    }
    break;

    case 55:// 7 - Zoom tele/stop.
    {
        // Encode command.
        g_outputDataMutex.lock();
        if (g_zoomTeleFlag)
            protocolParser.encodeCommand(cr::visca::ViscaPackets::COMMAND_CAM_Zoom_Stop, g_outputData, g_outputDataSize, 1);
        else
            protocolParser.encodeCommand(cr::visca::ViscaPackets::COMMAND_CAM_Zoom_Tele, g_outputData, g_outputDataSize, 1);
        g_zoomTeleFlag = !g_zoomTeleFlag;
        g_outputDataMutex.unlock();
    }
    break;

    case 56:// 8 - Zoom wide/stop.
    {
        // Encode command.
        g_outputDataMutex.lock();
        if (g_zoomWideFlag)
            protocolParser.encodeCommand(cr::visca::ViscaPackets::COMMAND_CAM_Zoom_Stop, g_outputData, g_outputDataSize, 1);
        else
            protocolParser.encodeCommand(cr::visca::ViscaPackets::COMMAND_CAM_Zoom_Wide, g_outputData, g_outputDataSize, 1);
        g_zoomWideFlag = !g_zoomWideFlag;
        g_outputDataMutex.unlock();
    }
    break;

    case 57:// 9 - Focus far/stop.
    {
        // Encode command.
        g_outputDataMutex.lock();
        if (g_focusFarFlag)
            protocolParser.encodeCommand(cr::visca::ViscaPackets::COMMAND_CAM_Focus_Stop, g_outputData, g_outputDataSize, 1);
        else
            protocolParser.encodeCommand(cr::visca::ViscaPackets::COMMAND_CAM_Focus_Far, g_outputData, g_outputDataSize, 1);
        g_focusFarFlag = !g_focusFarFlag;
        g_outputDataMutex.unlock();
    }
    break;

    case 0:// 0 - Focus near/stop.
    {
        // Encode command.
        g_outputDataMutex.lock();
        if (g_focusNearFlag)
            protocolParser.encodeCommand(cr::visca::ViscaPackets::COMMAND_CAM_Focus_Stop, g_outputData, g_outputDataSize, 1);
        else
            protocolParser.encodeCommand(cr::visca::ViscaPackets::COMMAND_CAM_Focus_Near, g_outputData, g_outputDataSize, 1);
        g_focusNearFlag = !g_focusNearFlag;
        g_outputDataMutex.unlock();
    }
    break;

    }
}















