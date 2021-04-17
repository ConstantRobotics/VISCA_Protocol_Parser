#pragma once
#include <cstdint>
#include "ViscaProtocolParserDataStructures.h"


namespace visca
{
    /**
     * @brief VISCA protocol parser class.
     */
    class ViscaProtocolParser
    {
    public:

        /**
         * @brief Class constructor.
         */
        ViscaProtocolParser();

        /**
         * @brief Class destructor.
         */
        ~ViscaProtocolParser();

        /**
         * @brief Method to encode COMMAND or ENQUIRY COMMAND.
         * @param command_ID ID of command.
         * @param packet Pointer to packet data buffer. Should be >= 24.
         * @param packet_size Output packet size.
         * @param camera_address Camera address.
         * @param param_1 Parameter 1. The meanimg depends from ID of command.
         * @param param_2 Parameter 2. The meanimg depends from ID of command.
         * @param param_3 Parameter 3. The meanimg depends from ID of command.
         * @param param_4 Parameter 4. The meanimg depends from ID of command.
         * @param param_5 Parameter 5. The meanimg depends from ID of command.
         * @param param_6 Parameter 6. The meanimg depends from ID of command.
         * @param param_7 Parameter 7. The meanimg depends from ID of command.
         * @param param_8 Parameter 8. The meanimg depends from ID of command.
         * @param param_9 Parameter 9. The meanimg depends from ID of command.
         * @param param_10 Parameter 10. The meanimg depends from ID of command.
         * @return TRUE if the commend was encoded or FALSE in case any errors.
         */
        bool Encode_Command(
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

        /**
         * @brief Method to decode input data byte-by-byte.
         * @param next_byte Next byte of input data.
         * @param camera_address Camera address.
         * @param param_1 Parameter 1. The meanimg depends from ID of command.
         * @param param_2 Parameter 2. The meanimg depends from ID of command.
         * @param param_3 Parameter 3. The meanimg depends from ID of command.
         * @param param_4 Parameter 4. The meanimg depends from ID of command.
         * @param param_5 Parameter 5. The meanimg depends from ID of command.
         * @param param_6 Parameter 6. The meanimg depends from ID of command.
         * @param param_7 Parameter 7. The meanimg depends from ID of command.
         * @param param_8 Parameter 8. The meanimg depends from ID of command.
         * @param param_9 Parameter 9. The meanimg depends from ID of command.
         * @param param_10 Parameter 10. The meanimg depends from ID of command. 
         * @return visca::ViscaPackets type.
         */
        visca::ViscaPackets Decode_Data(
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

    private:

        uint32_t input_data_counter;
        uint8_t input_packet_data[128];
        visca::ViscaPackets input_packet_type;
        visca::ViscaPackets last_encoded_command;

        visca::ViscaPackets Decode_Reply(
            uint8_t* packet_data,
            uint32_t packet_size,
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
            
    };
}
