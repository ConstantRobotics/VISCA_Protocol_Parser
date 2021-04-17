#include <cstring>
#include "ViscaProtocolParser.h"


visca::ViscaProtocolParser::ViscaProtocolParser() :
    input_data_counter(0),
    input_packet_type(visca::ViscaPackets::UNDEFINED_PACKET),
    last_encoded_command(visca::ViscaPackets::UNDEFINED_PACKET)
{
    memset(input_packet_data, 0, 128);
}


visca::ViscaProtocolParser::~ViscaProtocolParser()
{
    
}


bool visca::ViscaProtocolParser::Encode_Command(
            visca::ViscaPackets command_ID,
            uint8_t* packet,
            uint32_t& packet_size,
            uint32_t camera_address,
            uint32_t param_1,
            uint32_t param_2,
            uint32_t param_3,
            uint32_t param_4,
            uint32_t param_5,
            uint32_t param_6,
            uint32_t param_7,
            uint32_t param_8,
            uint32_t param_9,
            uint32_t param_10)
{
    // Check camera address.
    if (camera_address < 1 || camera_address > 7)
        return false;

    // Remember last encoded command for REPLY packets decoding.
    last_encoded_command = command_ID;

    // Check command ID.
    switch (command_ID)
    {
    case visca::ViscaPackets::COMMAND_AddressSet:
        packet[0] = 0x88;
        packet[1] = 0x30;
        packet[2] = (uint8_t)camera_address;
        packet[3] = 0xFF;
        packet_size = 4;
        return true;

    case visca::ViscaPackets::COMMAND_IF_Clear_Broadcast:
        packet[0] = 0x88;
        packet[1] = 0x01;
        packet[2] = 0x00;
        packet[3] = 0x01;
        packet[4] = 0xFF;
        packet_size = 5;
        return true;

    case visca::ViscaPackets::COMMAND_IF_Clear:
        packet[0] = (0x80 | (uint8_t)camera_address);
        packet[1] = 0x01;
        packet[2] = 0x00;
        packet[3] = 0x01;
        packet[4] = 0xFF;
        packet_size = 5;
        return true;

    case visca::ViscaPackets::COMMAND_CommandCancel:
        // Check socet number.
        if (param_1 != 1 && param_1 != 2)
            return false;
        packet[0] = (0x80 | (uint8_t)camera_address);
        packet[1] = (0x20 | (uint8_t)param_1);
        packet[2] = 0xFF;
        packet_size = 3;
        return true;

    case visca::ViscaPackets::COMMAND_CAM_Power_On:
        packet[0] = (0x80 | (uint8_t)camera_address);
        packet[1] = 0x01;
        packet[2] = 0x04;
        packet[3] = 0x00;
        packet[4] = 0x02;
        packet[5] = 0xFF;
        packet_size = 6;
        return true;

    case visca::ViscaPackets::COMMAND_CAM_Power_Off:
        packet[0] = (0x80 | (uint8_t)camera_address);
        packet[1] = 0x01;
        packet[2] = 0x04;
        packet[3] = 0x00;
        packet[4] = 0x03;
        packet[5] = 0xFF;
        packet_size = 6;
        return true;

    case visca::ViscaPackets::COMMAND_CAM_Zoom_Stop:
        packet[0] = (0x80 | (uint8_t)camera_address);
        packet[1] = 0x01;
        packet[2] = 0x04;
        packet[3] = 0x07;
        packet[4] = 0x00;
        packet[5] = 0xFF;
        packet_size = 6;
        return true;

    case visca::ViscaPackets::COMMAND_CAM_Zoom_Tele:
        packet[0] = (0x80 | (uint8_t)camera_address);
        packet[1] = 0x01;
        packet[2] = 0x04;
        packet[3] = 0x07;
        packet[4] = 0x02;
        packet[5] = 0xFF;
        packet_size = 6;
        return true;

    case visca::ViscaPackets::COMMAND_CAM_Zoom_Wide:
        packet[0] = (0x80 | (uint8_t)camera_address);
        packet[1] = 0x01;
        packet[2] = 0x04;
        packet[3] = 0x07;
        packet[4] = 0x03;
        packet[5] = 0xFF;
        packet_size = 6;
        return true;

    case visca::ViscaPackets::COMMAND_CAM_Zoom_Tele_Variable:
        // Check speed value.
        if (param_1 > 7)
            return false;
        packet[0] = (0x80 | (uint8_t)camera_address);
        packet[1] = 0x01;
        packet[2] = 0x04;
        packet[3] = 0x07;
        packet[4] = (0x20 | (uint8_t)param_1);
        packet[5] = 0xFF;
        packet_size = 6;
        return true;

    case visca::ViscaPackets::COMMAND_CAM_Zoom_Wide_Variable:
        // Check speed value.
        if (param_1 > 7)
            return false;
        packet[0] = (0x80 | (uint8_t)camera_address);
        packet[1] = 0x01;
        packet[2] = 0x04;
        packet[3] = 0x07;
        packet[4] = (0x30 | (uint8_t)param_1);
        packet[5] = 0xFF;
        packet_size = 6;
        return true;

    case visca::ViscaPackets::COMMAND_CAM_Zoom_Direct:
        packet[0] = (0x80 | (uint8_t)camera_address);
        packet[1] = 0x01;
        packet[2] = 0x04;
        packet[3] = 0x47;
        packet[4] = (uint8_t)param_1 & 0x0F;
        packet[5] = (uint8_t)param_2 & 0x0F;
        packet[6] = (uint8_t)param_3 & 0x0F;
        packet[7] = (uint8_t)param_4 & 0x0F;
        packet[8] = 0xFF;
        packet_size = 9;
        return true;

    case visca::ViscaPackets::COMMAND_CAM_DZoom_On:
        packet[0] = (0x80 | (uint8_t)camera_address);
        packet[1] = 0x01;
        packet[2] = 0x04;
        packet[3] = 0x06;
        packet[4] = 0x02;
        packet[5] = 0xFF;
        packet_size = 6;
        return true;

    case visca::ViscaPackets::COMMAND_CAM_DZoom_Off:
        packet[0] = (0x80 | (uint8_t)camera_address);
        packet[1] = 0x01;
        packet[2] = 0x04;
        packet[3] = 0x06;
        packet[4] = 0x03;
        packet[5] = 0xFF;
        packet_size = 6;
        return true;

    case visca::ViscaPackets::COMMAND_CAM_DZoom_Combine_Mode:
        packet[0] = (0x80 | (uint8_t)camera_address);
        packet[1] = 0x01;
        packet[2] = 0x04;
        packet[3] = 0x36;
        packet[4] = 0x00;
        packet[5] = 0xFF;
        packet_size = 6;
        return true;

    case visca::ViscaPackets::COMMAND_CAM_DZoom_Separate_Mode:
        packet[0] = (0x80 | (uint8_t)camera_address);
        packet[1] = 0x01;
        packet[2] = 0x04;
        packet[3] = 0x36;
        packet[4] = 0x01;
        packet[5] = 0xFF;
        packet_size = 6;
        return true;

    case visca::ViscaPackets::COMMAND_CAM_DZoom_Stop:
        packet[0] = (0x80 | (uint8_t)camera_address);
        packet[1] = 0x01;
        packet[2] = 0x04;
        packet[3] = 0x06;
        packet[4] = 0x00;
        packet[5] = 0xFF;
        packet_size = 6;
        return true;

    case visca::ViscaPackets::COMMAND_CAM_DZoom_Tele_Variable:
        // Check speed value.
        if (param_1 > 7)
            return false;
        packet[0] = (0x80 | (uint8_t)camera_address);
        packet[1] = 0x01;
        packet[2] = 0x04;
        packet[3] = 0x06;
        packet[4] = (0x20 | (uint8_t)param_1);
        packet[5] = 0xFF;
        packet_size = 6;
        return true;

    case visca::ViscaPackets::COMMAND_CAM_DZoom_Wide_Variable:
        // Check speed value.
        if (param_1 > 7)
            return false;
        packet[0] = (0x80 | (uint8_t)camera_address);
        packet[1] = 0x01;
        packet[2] = 0x04;
        packet[3] = 0x06;
        packet[4] = (0x30 | (uint8_t)param_1);
        packet[5] = 0xFF;
        packet_size = 6;
        return true;

    case visca::ViscaPackets::COMMAND_CAM_DZoom_Direct:
        packet[0] = (0x80 | (uint8_t)camera_address);
        packet[1] = 0x01;
        packet[2] = 0x04;
        packet[3] = 0x46;
        packet[4] = 0x00;
        packet[5] = 0x00;
        packet[6] = (uint8_t)(param_1 >> 4) & 0x0F;
        packet[7] = (uint8_t)param_1 & 0x0F;
        packet[8] = 0xFF;
        packet_size = 9;
        return true;

    case visca::ViscaPackets::COMMAND_CAM_Focus_Stop:
        packet[0] = (0x80 | (uint8_t)camera_address);
        packet[1] = 0x01;
        packet[2] = 0x04;
        packet[3] = 0x08;
        packet[4] = 0x00;
        packet[5] = 0xFF;
        packet_size = 6;
        return true;

    case visca::ViscaPackets::COMMAND_CAM_Focus_Far:
        packet[0] = (0x80 | (uint8_t)camera_address);
        packet[1] = 0x01;
        packet[2] = 0x04;
        packet[3] = 0x08;
        packet[4] = 0x02;
        packet[5] = 0xFF;
        packet_size = 6;
        return true;

    case visca::ViscaPackets::COMMAND_CAM_Focus_Near:
        packet[0] = (0x80 | (uint8_t)camera_address);
        packet[1] = 0x01;
        packet[2] = 0x04;
        packet[3] = 0x08;
        packet[4] = 0x03;
        packet[5] = 0xFF;
        packet_size = 6;
        return true;

    case visca::ViscaPackets::COMMAND_CAM_Focus_Far_Variable:
        // Check speed value.
        if (param_1 > 7)
            return false;
        packet[0] = (0x80 | (uint8_t)camera_address);
        packet[1] = 0x01;
        packet[2] = 0x04;
        packet[3] = 0x08;
        packet[4] = (0x20 | (uint8_t)param_1);
        packet[5] = 0xFF;
        packet_size = 6;
        return true;

    case visca::ViscaPackets::COMMAND_CAM_Focus_Near_Variable:
        // Check speed value.
        if (param_1 > 7)
            return false;
        packet[0] = (0x80 | (uint8_t)camera_address);
        packet[1] = 0x01;
        packet[2] = 0x04;
        packet[3] = 0x08;
        packet[4] = (0x30 | (uint8_t)param_1);
        packet[5] = 0xFF;
        packet_size = 6;
        return true;

    case visca::ViscaPackets::COMMAND_CAM_Focus_Direct:
        packet[0] = (0x80 | (uint8_t)camera_address);
        packet[1] = 0x01;
        packet[2] = 0x04;
        packet[3] = 0x48;
        packet[4] = (uint8_t)param_1 & 0x0F;
        packet[5] = (uint8_t)param_2 & 0x0F;
        packet[6] = (uint8_t)param_3 & 0x0F;
        packet[7] = (uint8_t)param_4 & 0x0F;
        packet[8] = 0xFF;
        packet_size = 9;
        return true;

    case visca::ViscaPackets::COMMAND_CAM_Focus_Auto_Focus_On:
        packet[0] = (0x80 | (uint8_t)camera_address);
        packet[1] = 0x01;
        packet[2] = 0x04;
        packet[3] = 0x38;
        packet[4] = 0x02;
        packet[5] = 0xFF;
        packet_size = 6;
        return true;

    case visca::ViscaPackets::COMMAND_CAM_Focus_Manual_Focus_On:
        packet[0] = (0x80 | (uint8_t)camera_address);
        packet[1] = 0x01;
        packet[2] = 0x04;
        packet[3] = 0x38;
        packet[4] = 0x03;
        packet[5] = 0xFF;
        packet_size = 6;
        return true;

    case visca::ViscaPackets::COMMAND_CAM_Focus_Auto_Manual:
        packet[0] = (0x80 | (uint8_t)camera_address);
        packet[1] = 0x01;
        packet[2] = 0x04;
        packet[3] = 0x38;
        packet[4] = 0x10;
        packet[5] = 0xFF;
        packet_size = 6;
        return true;

    case visca::ViscaPackets::COMMAND_CAM_Focus_One_Push_Trigger:
        packet[0] = (0x80 | (uint8_t)camera_address);
        packet[1] = 0x01;
        packet[2] = 0x04;
        packet[3] = 0x18;
        packet[4] = 0x01;
        packet[5] = 0xFF;
        packet_size = 6;
        return true;

    case visca::ViscaPackets::COMMAND_CAM_Focus_Full_Scan_One_Push_Trigger:
        packet[0] = (0x80 | (uint8_t)camera_address);
        packet[1] = 0x01;
        packet[2] = 0x04;
        packet[3] = 0x18;
        packet[4] = 0x03;
        packet[5] = 0xFF;
        packet_size = 6;
        return true;

    case visca::ViscaPackets::COMMAND_CAM_Focus_Near_Limit:
        packet[0] = (0x80 | (uint8_t)camera_address);
        packet[1] = 0x01;
        packet[2] = 0x04;
        packet[3] = 0x28;
        packet[4] = (uint8_t)(param_1 >> 12) & 0x0F;
        packet[5] = (uint8_t)(param_1 >> 8) & 0x0F;
        packet[6] = (uint8_t)(param_1 >> 4) & 0x0F;
        packet[7] = (uint8_t)param_1 & 0x0F;
        packet[8] = 0xFF;
        packet_size = 9;
        return true;

    case visca::ViscaPackets::COMMAND_CAM_AFSensitivity_Normal:
        packet[0] = (0x80 | (uint8_t)camera_address);
        packet[1] = 0x01;
        packet[2] = 0x04;
        packet[3] = 0x58;
        packet[4] = 0x02;
        packet[5] = 0xFF;
        packet_size = 6;
        return true;

    case visca::ViscaPackets::COMMAND_CAM_AFSensitivity_Low:
        packet[0] = (0x80 | (uint8_t)camera_address);
        packet[1] = 0x01;
        packet[2] = 0x04;
        packet[3] = 0x58;
        packet[4] = 0x03;
        packet[5] = 0xFF;
        packet_size = 6;
        return true;

    case visca::ViscaPackets::COMMAND_CAM_AFMode_Normal_AF:
        packet[0] = (0x80 | (uint8_t)camera_address);
        packet[1] = 0x01;
        packet[2] = 0x04;
        packet[3] = 0x57;
        packet[4] = 0x00;
        packet[5] = 0xFF;
        packet_size = 6;
        return true;

    case visca::ViscaPackets::COMMAND_CAM_AFMode_Interval_AF:
        packet[0] = (0x80 | (uint8_t)camera_address);
        packet[1] = 0x01;
        packet[2] = 0x04;
        packet[3] = 0x57;
        packet[4] = 0x01;
        packet[5] = 0xFF;
        packet_size = 6;
        return true;

    case visca::ViscaPackets::COMMAND_CAM_AFMode_Zoom_Trigger_AF:
        packet[0] = (0x80 | (uint8_t)camera_address);
        packet[1] = 0x01;
        packet[2] = 0x04;
        packet[3] = 0x57;
        packet[4] = 0x02;
        packet[5] = 0xFF;
        packet_size = 6;
        return true;

    case visca::ViscaPackets::COMMAND_CAM_AFMode_Active_or_Interval_Time:
        packet[0] = (0x80 | (uint8_t)camera_address);
        packet[1] = 0x01;
        packet[2] = 0x04;
        packet[3] = 0x27;
        packet[4] = (uint8_t)(param_1 >> 4) & 0x0F;
        packet[5] = (uint8_t)param_1 & 0x0F;
        packet[6] = (uint8_t)(param_2 >> 4) & 0x0F;
        packet[7] = (uint8_t)param_2 & 0x0F;
        packet[8] = 0xFF;
        packet_size = 9;
        return true;

    case visca::ViscaPackets::COMMAND_CAM_IRCorrection_Standard:
        packet[0] = (0x80 | (uint8_t)camera_address);
        packet[1] = 0x01;
        packet[2] = 0x04;
        packet[3] = 0x11;
        packet[4] = 0x00;
        packet[5] = 0xFF;
        packet_size = 6;
        return true;

    case visca::ViscaPackets::COMMAND_CAM_IRCorrection_IR_Light:
        packet[0] = (0x80 | (uint8_t)camera_address);
        packet[1] = 0x01;
        packet[2] = 0x04;
        packet[3] = 0x11;
        packet[4] = 0x01;
        packet[5] = 0xFF;
        packet_size = 6;
        return true;

    case visca::ViscaPackets::COMMAND_CAM_ZoomFocus_Direct:
        packet[0] = (0x80 | (uint8_t)camera_address);
        packet[1] = 0x01;
        packet[2] = 0x04;
        packet[3] = 0x47;
        packet[4] = (uint8_t)(param_1 >> 12) & 0x0F;
        packet[5] = (uint8_t)(param_1 >> 8) & 0x0F;
        packet[6] = (uint8_t)(param_1 >> 4) & 0x0F;
        packet[7] = (uint8_t)param_1 & 0x0F;
        packet[8] = (uint8_t)(param_2 >> 12) & 0x0F;
        packet[9] = (uint8_t)(param_2 >> 8) & 0x0F;
        packet[10] = (uint8_t)(param_2 >> 4) & 0x0F;
        packet[11] = (uint8_t)param_2 & 0x0F;
        packet[12] = 0xFF;
        packet_size = 13;
        return true;

    case visca::ViscaPackets::COMMAND_CAM_Initialize_Lens:
        packet[0] = (0x80 | (uint8_t)camera_address);
        packet[1] = 0x01;
        packet[2] = 0x04;
        packet[3] = 0x19;
        packet[4] = 0x01;
        packet[5] = 0xFF;
        packet_size = 6;
        return true;

    case visca::ViscaPackets::COMMAND_CAM_Initialize_Camera:
        packet[0] = (0x80 | (uint8_t)camera_address);
        packet[1] = 0x01;
        packet[2] = 0x04;
        packet[3] = 0x19;
        packet[4] = 0x03;
        packet[5] = 0xFF;
        packet_size = 6;
        return true;

    case visca::ViscaPackets::COMMAND_CAM_WB_Auto:
        packet[0] = (0x80 | (uint8_t)camera_address);
        packet[1] = 0x01;
        packet[2] = 0x04;
        packet[3] = 0x35;
        packet[4] = 0x00;
        packet[5] = 0xFF;
        packet_size = 6;
        return true;

    case visca::ViscaPackets::COMMAND_CAM_WB_Indoor:
        packet[0] = (0x80 | (uint8_t)camera_address);
        packet[1] = 0x01;
        packet[2] = 0x04;
        packet[3] = 0x35;
        packet[4] = 0x01;
        packet[5] = 0xFF;
        packet_size = 6;
        return true;

    case visca::ViscaPackets::COMMAND_CAM_WB_Outdoor:
        packet[0] = (0x80 | (uint8_t)camera_address);
        packet[1] = 0x01;
        packet[2] = 0x04;
        packet[3] = 0x35;
        packet[4] = 0x02;
        packet[5] = 0xFF;
        packet_size = 6;
        return true;

    case visca::ViscaPackets::COMMAND_CAM_WB_One_Push_WB:
        packet[0] = (0x80 | (uint8_t)camera_address);
        packet[1] = 0x01;
        packet[2] = 0x04;
        packet[3] = 0x35;
        packet[4] = 0x03;
        packet[5] = 0xFF;
        packet_size = 6;
        return true;

    case visca::ViscaPackets::COMMAND_CAM_WB_ATW:
        packet[0] = (0x80 | (uint8_t)camera_address);
        packet[1] = 0x01;
        packet[2] = 0x04;
        packet[3] = 0x35;
        packet[4] = 0x04;
        packet[5] = 0xFF;
        packet_size = 6;
        return true;

    case visca::ViscaPackets::COMMAND_CAM_WB_Manual:
        packet[0] = (0x80 | (uint8_t)camera_address);
        packet[1] = 0x01;
        packet[2] = 0x04;
        packet[3] = 0x35;
        packet[4] = 0x05;
        packet[5] = 0xFF;
        packet_size = 6;
        return true;

    case visca::ViscaPackets::COMMAND_CAM_WB_One_Push_Trigger:
        packet[0] = (0x80 | (uint8_t)camera_address);
        packet[1] = 0x01;
        packet[2] = 0x04;
        packet[3] = 0x10;
        packet[4] = 0x05;
        packet[5] = 0xFF;
        packet_size = 6;
        return true;

    case visca::ViscaPackets::COMMAND_CAM_WB_Outdoor_Auto:
        packet[0] = (0x80 | (uint8_t)camera_address);
        packet[1] = 0x01;
        packet[2] = 0x04;
        packet[3] = 0x35;
        packet[4] = 0x06;
        packet[5] = 0xFF;
        packet_size = 6;
        return true;

    case visca::ViscaPackets::COMMAND_CAM_WB_Sodium_Lamp_Auto:
        packet[0] = (0x80 | (uint8_t)camera_address);
        packet[1] = 0x01;
        packet[2] = 0x04;
        packet[3] = 0x35;
        packet[4] = 0x07;
        packet[5] = 0xFF;
        packet_size = 6;
        return true;

    case visca::ViscaPackets::COMMAND_CAM_WB_Sodium_Lamp:
        packet[0] = (0x80 | (uint8_t)camera_address);
        packet[1] = 0x01;
        packet[2] = 0x04;
        packet[3] = 0x35;
        packet[4] = 0x08;
        packet[5] = 0xFF;
        packet_size = 6;
        return true;

    case visca::ViscaPackets::COMMAND_CAM_WB_Sodium_Lamp_Outdoor_Auto:
        packet[0] = (0x80 | (uint8_t)camera_address);
        packet[1] = 0x01;
        packet[2] = 0x04;
        packet[3] = 0x35;
        packet[4] = 0x09;
        packet[5] = 0xFF;
        packet_size = 6;
        return true;

    case visca::ViscaPackets::COMMAND_CAM_RGain_Reset:
        packet[0] = (0x80 | (uint8_t)camera_address);
        packet[1] = 0x01;
        packet[2] = 0x04;
        packet[3] = 0x03;
        packet[4] = 0x00;
        packet[5] = 0xFF;
        packet_size = 6;
        return true;

    case visca::ViscaPackets::COMMAND_CAM_RGain_Up:
        packet[0] = (0x80 | (uint8_t)camera_address);
        packet[1] = 0x01;
        packet[2] = 0x04;
        packet[3] = 0x03;
        packet[4] = 0x02;
        packet[5] = 0xFF;
        packet_size = 6;
        return true;

    case visca::ViscaPackets::COMMAND_CAM_RGain_Down:
        packet[0] = (0x80 | (uint8_t)camera_address);
        packet[1] = 0x01;
        packet[2] = 0x04;
        packet[3] = 0x03;
        packet[4] = 0x03;
        packet[5] = 0xFF;
        packet_size = 6;
        return true;

    case visca::ViscaPackets::COMMAND_CAM_RGain_Direct:
        packet[0] = (0x80 | (uint8_t)camera_address);
        packet[1] = 0x01;
        packet[2] = 0x04;
        packet[3] = 0x43;
        packet[4] = 0x00;
        packet[5] = 0x00;
        packet[6] = (uint8_t)(param_1 >> 4) & 0x0F;
        packet[7] = (uint8_t)param_1 & 0x0F;
        packet[8] = 0xFF;
        packet_size = 9;
        return true;

    case visca::ViscaPackets::COMMAND_CAM_BGain_Reset:
        packet[0] = (0x80 | (uint8_t)camera_address);
        packet[1] = 0x01;
        packet[2] = 0x04;
        packet[3] = 0x04;
        packet[4] = 0x00;
        packet[5] = 0xFF;
        packet_size = 6;
        return true;

    case visca::ViscaPackets::COMMAND_CAM_BGain_Up:
        packet[0] = (0x80 | (uint8_t)camera_address);
        packet[1] = 0x01;
        packet[2] = 0x04;
        packet[3] = 0x04;
        packet[4] = 0x02;
        packet[5] = 0xFF;
        packet_size = 6;
        return true;

    case visca::ViscaPackets::COMMAND_CAM_BGain_Down:
        packet[0] = (0x80 | (uint8_t)camera_address);
        packet[1] = 0x01;
        packet[2] = 0x04;
        packet[3] = 0x04;
        packet[4] = 0x03;
        packet[5] = 0xFF;
        packet_size = 6;
        return true;

    case visca::ViscaPackets::COMMAND_CAM_BGain_Direct:
        packet[0] = (0x80 | (uint8_t)camera_address);
        packet[1] = 0x01;
        packet[2] = 0x04;
        packet[3] = 0x44;
        packet[4] = 0x00;
        packet[5] = 0x00;
        packet[6] = (uint8_t)(param_1 >> 4) & 0x0F;
        packet[7] = (uint8_t)param_1 & 0x0F;
        packet[8] = 0xFF;
        packet_size = 9;
        return true;

    case visca::ViscaPackets::COMMAND_CAM_AE_Full_Auto:
        packet[0] = (0x80 | (uint8_t)camera_address);
        packet[1] = 0x01;
        packet[2] = 0x04;
        packet[3] = 0x39;
        packet[4] = 0x00;
        packet[5] = 0xFF;
        packet_size = 6;
        return true;

    case visca::ViscaPackets::COMMAND_CAM_AE_Manual:
        packet[0] = (0x80 | (uint8_t)camera_address);
        packet[1] = 0x01;
        packet[2] = 0x04;
        packet[3] = 0x39;
        packet[4] = 0x03;
        packet[5] = 0xFF;
        packet_size = 6;
        return true;

    case visca::ViscaPackets::COMMAND_CAM_AE_Shutter_Priority:
        packet[0] = (0x80 | (uint8_t)camera_address);
        packet[1] = 0x01;
        packet[2] = 0x04;
        packet[3] = 0x39;
        packet[4] = 0x0A;
        packet[5] = 0xFF;
        packet_size = 6;
        return true;

    case visca::ViscaPackets::COMMAND_CAM_AE_Iris_Priority:
        packet[0] = (0x80 | (uint8_t)camera_address);
        packet[1] = 0x01;
        packet[2] = 0x04;
        packet[3] = 0x39;
        packet[4] = 0x0B;
        packet[5] = 0xFF;
        packet_size = 6;
        return true;

    case visca::ViscaPackets::COMMAND_CAM_AutoSlowShutter_On:
        packet[0] = (0x80 | (uint8_t)camera_address);
        packet[1] = 0x01;
        packet[2] = 0x04;
        packet[3] = 0x5A;
        packet[4] = 0x02;
        packet[5] = 0xFF;
        packet_size = 6;
        return true;

    case visca::ViscaPackets::COMMAND_CAM_AutoSlowShutter_Off:
        packet[0] = (0x80 | (uint8_t)camera_address);
        packet[1] = 0x01;
        packet[2] = 0x04;
        packet[3] = 0x5A;
        packet[4] = 0x03;
        packet[5] = 0xFF;
        packet_size = 6;
        return true;

    case visca::ViscaPackets::COMMAND_CAM_Shutter_Reset:
        packet[0] = (0x80 | (uint8_t)camera_address);
        packet[1] = 0x01;
        packet[2] = 0x04;
        packet[3] = 0x0A;
        packet[4] = 0x00;
        packet[5] = 0xFF;
        packet_size = 6;
        return true;

    case visca::ViscaPackets::COMMAND_CAM_Shutter_Up:
        packet[0] = (0x80 | (uint8_t)camera_address);
        packet[1] = 0x01;
        packet[2] = 0x04;
        packet[3] = 0x0A;
        packet[4] = 0x02;
        packet[5] = 0xFF;
        packet_size = 6;
        return true;

    case visca::ViscaPackets::COMMAND_CAM_Shutter_Down:
        packet[0] = (0x80 | (uint8_t)camera_address);
        packet[1] = 0x01;
        packet[2] = 0x04;
        packet[3] = 0x0A;
        packet[4] = 0x03;
        packet[5] = 0xFF;
        packet_size = 6;
        return true;

    case visca::ViscaPackets::COMMAND_CAM_Shutter_Direct:
        packet[0] = (0x80 | (uint8_t)camera_address);
        packet[1] = 0x01;
        packet[2] = 0x04;
        packet[3] = 0x4A;
        packet[4] = 0x00;
        packet[5] = 0x00;
        packet[6] = (uint8_t)(param_1 >> 4) & 0x0F;
        packet[7] = (uint8_t)param_1 & 0x0F;
        packet[8] = 0xFF;
        packet_size = 9;
        return true;

    case visca::ViscaPackets::COMMAND_CAM_Iris_Reset:
        packet[0] = (0x80 | (uint8_t)camera_address);
        packet[1] = 0x01;
        packet[2] = 0x04;
        packet[3] = 0x0B;
        packet[4] = 0x00;
        packet[5] = 0xFF;
        packet_size = 6;
        return true;

    case visca::ViscaPackets::COMMAND_CAM_Iris_Up:
        packet[0] = (0x80 | (uint8_t)camera_address);
        packet[1] = 0x01;
        packet[2] = 0x04;
        packet[3] = 0x0B;
        packet[4] = 0x02;
        packet[5] = 0xFF;
        packet_size = 6;
        return true;

    case visca::ViscaPackets::COMMAND_CAM_Iris_Down:
        packet[0] = (0x80 | (uint8_t)camera_address);
        packet[1] = 0x01;
        packet[2] = 0x04;
        packet[3] = 0x0B;
        packet[4] = 0x03;
        packet[5] = 0xFF;
        packet_size = 6;
        return true;

    case visca::ViscaPackets::COMMAND_CAM_Iris_Direct:
        packet[0] = (0x80 | (uint8_t)camera_address);
        packet[1] = 0x01;
        packet[2] = 0x04;
        packet[3] = 0x4B;
        packet[4] = 0x00;
        packet[5] = 0x00;
        packet[6] = (uint8_t)(param_1 >> 4) & 0x0F;
        packet[7] = (uint8_t)param_1 & 0x0F;
        packet[8] = 0xFF;
        packet_size = 9;
        return true;

    case visca::ViscaPackets::COMMAND_CAM_Gain_Reset:
        packet[0] = (0x80 | (uint8_t)camera_address);
        packet[1] = 0x01;
        packet[2] = 0x04;
        packet[3] = 0x0C;
        packet[4] = 0x00;
        packet[5] = 0xFF;
        packet_size = 6;
        return true;

    case visca::ViscaPackets::COMMAND_CAM_Gain_Up:
        packet[0] = (0x80 | (uint8_t)camera_address);
        packet[1] = 0x01;
        packet[2] = 0x04;
        packet[3] = 0x0C;
        packet[4] = 0x02;
        packet[5] = 0xFF;
        packet_size = 6;
        return true;

    case visca::ViscaPackets::COMMAND_CAM_Gain_Down:
        packet[0] = (0x80 | (uint8_t)camera_address);
        packet[1] = 0x01;
        packet[2] = 0x04;
        packet[3] = 0x0C;
        packet[4] = 0x03;
        packet[5] = 0xFF;
        packet_size = 6;
        return true;

    case visca::ViscaPackets::COMMAND_CAM_Gain_Direct:
        packet[0] = (0x80 | (uint8_t)camera_address);
        packet[1] = 0x01;
        packet[2] = 0x04;
        packet[3] = 0x4C;
        packet[4] = 0x00;
        packet[5] = 0x00;
        packet[6] = (uint8_t)(param_1 >> 4) & 0x0F;
        packet[7] = (uint8_t)param_1 & 0x0F;
        packet[8] = 0xFF;
        packet_size = 9;
        return true;

    case visca::ViscaPackets::COMMAND_CAM_Gain_Limit:
        packet[0] = (0x80 | (uint8_t)camera_address);
        packet[1] = 0x01;
        packet[2] = 0x04;
        packet[3] = 0x2C;
        packet[4] = (uint8_t)param_1 & 0x0F;
        packet[5] = 0xFF;
        packet_size = 6;
        return true;

    case visca::ViscaPackets::COMMAND_CAM_ExpComp_On:
        packet[0] = (0x80 | (uint8_t)camera_address);
        packet[1] = 0x01;
        packet[2] = 0x04;
        packet[3] = 0x3E;
        packet[4] = 0x02;
        packet[5] = 0xFF;
        packet_size = 6;
        return true;

    case visca::ViscaPackets::COMMAND_CAM_ExpComp__Off:
        packet[0] = (0x80 | (uint8_t)camera_address);
        packet[1] = 0x01;
        packet[2] = 0x04;
        packet[3] = 0x3E;
        packet[4] = 0x03;
        packet[5] = 0xFF;
        packet_size = 6;
        return true;

    case visca::ViscaPackets::COMMAND_CAM_ExpComp_Reset:
        packet[0] = (0x80 | (uint8_t)camera_address);
        packet[1] = 0x01;
        packet[2] = 0x04;
        packet[3] = 0x0E;
        packet[4] = 0x00;
        packet[5] = 0xFF;
        packet_size = 6;
        return true;

    case visca::ViscaPackets::COMMAND_CAM_ExpComp_Up:
        packet[0] = (0x80 | (uint8_t)camera_address);
        packet[1] = 0x01;
        packet[2] = 0x04;
        packet[3] = 0x0E;
        packet[4] = 0x02;
        packet[5] = 0xFF;
        packet_size = 6;
        return true;

    case visca::ViscaPackets::COMMAND_CAM_ExpComp_Down:
        packet[0] = (0x80 | (uint8_t)camera_address);
        packet[1] = 0x01;
        packet[2] = 0x04;
        packet[3] = 0x0E;
        packet[4] = 0x03;
        packet[5] = 0xFF;
        packet_size = 6;
        return true;

    case visca::ViscaPackets::COMMAND_CAM_ExpComp_Direct:
        packet[0] = (0x80 | (uint8_t)camera_address);
        packet[1] = 0x01;
        packet[2] = 0x04;
        packet[3] = 0x4E;
        packet[4] = 0x00;
        packet[5] = 0x00;
        packet[6] = (uint8_t)(param_1 >> 4) & 0x0F;
        packet[7] = (uint8_t)param_1 & 0x0F;
        packet[8] = 0xFF;
        packet_size = 9;
        return true;

    case visca::ViscaPackets::COMMAND_CAM_BackLight_On:
        packet[0] = (0x80 | (uint8_t)camera_address);
        packet[1] = 0x01;
        packet[2] = 0x04;
        packet[3] = 0x33;
        packet[4] = 0x02;
        packet[5] = 0xFF;
        packet_size = 6;
        return true;

    case visca::ViscaPackets::COMMAND_CAM_BackLight_Off:
        packet[0] = (0x80 | (uint8_t)camera_address);
        packet[1] = 0x01;
        packet[2] = 0x04;
        packet[3] = 0x33;
        packet[4] = 0x03;
        packet[5] = 0xFF;
        packet_size = 6;
        return true;

    case visca::ViscaPackets::COMMAND_CAM_SpotAE_On:
        packet[0] = (0x80 | (uint8_t)camera_address);
        packet[1] = 0x01;
        packet[2] = 0x04;
        packet[3] = 0x59;
        packet[4] = 0x02;
        packet[5] = 0xFF;
        packet_size = 6;
        return true;

    case visca::ViscaPackets::COMMAND_CAM_SpotAE_Off:
        packet[0] = (0x80 | (uint8_t)camera_address);
        packet[1] = 0x01;
        packet[2] = 0x04;
        packet[3] = 0x59;
        packet[4] = 0x03;
        packet[5] = 0xFF;
        packet_size = 6;
        return true;

    case visca::ViscaPackets::COMMAND_CAM_SpotAE_Position:
        packet[0] = (0x80 | (uint8_t)camera_address);
        packet[1] = 0x01;
        packet[2] = 0x04;
        packet[3] = 0x29;
        packet[4] = (uint8_t)(param_1 >> 12) & 0x0F;
        packet[5] = (uint8_t)(param_1 >> 8) & 0x0F;
        packet[6] = (uint8_t)(param_1 >> 4) & 0x0F;
        packet[7] = (uint8_t)param_1 & 0x0F;
        packet[8] = 0xFF;
        packet_size = 9;
        return true;

    case visca::ViscaPackets::COMMAND_CAM_AE_Response_Direct:
        packet[0] = (0x80 | (uint8_t)camera_address);
        packet[1] = 0x01;
        packet[2] = 0x04;
        packet[3] = 0x5D;
        packet[4] = (uint8_t)param_1;
        packet[5] = 0xFF;
        packet_size = 6;
        return true;

    case visca::ViscaPackets::COMMAND_CAM_VE_On:
        packet[0] = (0x80 | (uint8_t)camera_address);
        packet[1] = 0x01;
        packet[2] = 0x04;
        packet[3] = 0x3D;
        packet[4] = 0x06;
        packet[5] = 0xFF;
        packet_size = 6;
        return true;

    case visca::ViscaPackets::COMMAND_CAM_VE_Off:
        packet[0] = (0x80 | (uint8_t)camera_address);
        packet[1] = 0x01;
        packet[2] = 0x04;
        packet[3] = 0x3D;
        packet[4] = 0x03;
        packet[5] = 0xFF;
        packet_size = 6;
        return true;

    case visca::ViscaPackets::COMMAND_CAM_VE_Set_Parameter:
        // Check Display brightness level.
        if (param_1 > 6)
            return false;
        // Check Brightness compensation selection.
        if (param_2 > 3)
            return false;
        // Check Compensation leve.
        if (param_3 > 2)
            return false;
        packet[0] = (0x80 | (uint8_t)camera_address);
        packet[1] = 0x01;
        packet[2] = 0x04;
        packet[3] = 0x2D;
        packet[4] = 00;
        packet[5] = (uint8_t)param_1;
        packet[6] = (uint8_t)param_2;
        packet[7] = (uint8_t)param_3;
        packet[8] = 0x00;
        packet[9] = 0x00;
        packet[10] = 0x00;
        packet[11] = 0x00;
        packet[12] = 0xFF;
        packet_size = 13;
        return true;

    case visca::ViscaPackets::COMMAND_CAM_WD_On:
        packet[0] = (0x80 | (uint8_t)camera_address);
        packet[1] = 0x01;
        packet[2] = 0x04;
        packet[3] = 0x3D;
        packet[4] = 0x02;
        packet[5] = 0xFF;
        packet_size = 6;
        return true;

    case visca::ViscaPackets::COMMAND_CAM_WD_Off:
        packet[0] = (0x80 | (uint8_t)camera_address);
        packet[1] = 0x01;
        packet[2] = 0x04;
        packet[3] = 0x3D;
        packet[4] = 0x03;
        packet[5] = 0xFF;
        packet_size = 6;
        return true;

    case visca::ViscaPackets::COMMAND_CAM_WD_Set_Parameter:
        // Check Display brightness level.
        if (param_1 > 6)
            return false;
        // Check Brightness compensation selection.
        if (param_2 > 3)
            return false;
        // Check Compensation level.
        if (param_3 > 2)
            return false;
        packet[0] = (0x80 | (uint8_t)camera_address);
        packet[1] = 0x01;
        packet[2] = 0x04;
        packet[3] = 0x2D;
        packet[4] = 00;
        packet[5] = (uint8_t)param_1;
        packet[6] = (uint8_t)param_2;
        packet[7] = (uint8_t)param_3;
        packet[8] = 0x00;
        packet[9] = 0x00;
        packet[10] = 0x00;
        packet[11] = 0x00;
        packet[12] = 0xFF;
        packet_size = 13;
        return true;

    case visca::ViscaPackets::COMMAND_CAM_Defog_On:
        // Check defog level.
        if (param_1 < 1 || param_1 > 3)
            return false;
        packet[0] = (0x80 | (uint8_t)camera_address);
        packet[1] = 0x01;
        packet[2] = 0x04;
        packet[3] = 0x37;
        packet[4] = 0x02;
        packet[5] = (uint8_t)param_1;
        packet[6] = 0xFF;
        packet_size = 7;
        return true;

    case visca::ViscaPackets::COMMAND_CAM_Defog_Off:
        packet[0] = (0x80 | (uint8_t)camera_address);
        packet[1] = 0x01;
        packet[2] = 0x04;
        packet[3] = 0x37;
        packet[4] = 0x03;
        packet[5] = 0x00;
        packet[6] = 0xFF;
        packet_size = 7;
        return true;

    case visca::ViscaPackets::COMMAND_CAM_Aperture_Reset:
        packet[0] = (0x80 | (uint8_t)camera_address);
        packet[1] = 0x01;
        packet[2] = 0x04;
        packet[3] = 0x02;
        packet[4] = 0x00;
        packet[5] = 0xFF;
        packet_size = 6;
        return true;

    case visca::ViscaPackets::COMMAND_CAM_Aperture_Up:
        packet[0] = (0x80 | (uint8_t)camera_address);
        packet[1] = 0x01;
        packet[2] = 0x04;
        packet[3] = 0x02;
        packet[4] = 0x02;
        packet[5] = 0xFF;
        packet_size = 6;
        return true;

    case visca::ViscaPackets::COMMAND_CAM_Aperture_Down:
        packet[0] = (0x80 | (uint8_t)camera_address);
        packet[1] = 0x01;
        packet[2] = 0x04;
        packet[3] = 0x02;
        packet[4] = 0x03;
        packet[5] = 0xFF;
        packet_size = 6;
        return true;

    case visca::ViscaPackets::COMMAND_CAM_Aperture_Direct:
        // Check aperture gain.
        if (param_1 > 0x0F)
            return false;
        packet[0] = (0x80 | (uint8_t)camera_address);
        packet[1] = 0x01;
        packet[2] = 0x04;
        packet[3] = 0x42;
        packet[4] = 0x00;
        packet[5] = 0x00;
        packet[6] = 0x00;
        packet[7] = (uint8_t)param_1;
        packet[8] = 0xFF;
        packet_size = 9;
        return true;

    case visca::ViscaPackets::COMMAND_CAM_NR_Noise_Reduction:
        // Check setting.
        if (param_1 != 0x00)
        {
            if (param_1 != 0x7F)
            {
                if (param_1 < 1 || param_1 > 5)
                {
                    return false;
                }
            }
        }
        packet[0] = (0x80 | (uint8_t)camera_address);
        packet[1] = 0x01;
        packet[2] = 0x04;
        packet[3] = 0x53;
        packet[4] = (uint8_t)param_1;
        packet[5] = 0xFF;
        packet_size = 6;
        return true;

    case visca::ViscaPackets::COMMAND_CAM_NR_2D_3D_Independent_Setting:
        // Check setting.
        if (param_1 > 5)
            return false;
        if (param_2 > 5)
            return false;
        packet[0] = (0x80 | (uint8_t)camera_address);
        packet[1] = 0x01;
        packet[2] = 0x04;
        packet[3] = 0x53;
        packet[4] = (uint8_t)param_1;
        packet[5] = (uint8_t)param_2;
        packet[6] = 0xFF;
        packet_size = 7;
        return true;

    case visca::ViscaPackets::COMMAND_CAM_Gamma:
        // Check setting.
        if (param_1 != 0 && param_1 != 1)
            return false;
        packet[0] = (0x80 | (uint8_t)camera_address);
        packet[1] = 0x01;
        packet[2] = 0x04;
        packet[3] = 0x5B;
        packet[4] = (uint8_t)param_1;
        packet[5] = 0xFF;
        packet_size = 6;
        return true;

    case visca::ViscaPackets::COMMAND_CAM_HighSensitivity_On:
        packet[0] = (0x80 | (uint8_t)camera_address);
        packet[1] = 0x01;
        packet[2] = 0x04;
        packet[3] = 0x5E;
        packet[4] = 0x02;
        packet[5] = 0xFF;
        packet_size = 6;
        return true;

    case visca::ViscaPackets::COMMAND_CAM_HighSensitivity_Off:
        packet[0] = (0x80 | (uint8_t)camera_address);
        packet[1] = 0x01;
        packet[2] = 0x04;
        packet[3] = 0x5E;
        packet[4] = 0x03;
        packet[5] = 0xFF;
        packet_size = 6;
        return true;

    case visca::ViscaPackets::COMMAND_CAM_LR_Reverse_On:
        packet[0] = (0x80 | (uint8_t)camera_address);
        packet[1] = 0x01;
        packet[2] = 0x04;
        packet[3] = 0x61;
        packet[4] = 0x02;
        packet[5] = 0xFF;
        packet_size = 6;
        return true;

    case visca::ViscaPackets::COMMAND_CAM_LR_Reverse_Off:
        packet[0] = (0x80 | (uint8_t)camera_address);
        packet[1] = 0x01;
        packet[2] = 0x04;
        packet[3] = 0x61;
        packet[4] = 0x03;
        packet[5] = 0xFF;
        packet_size = 6;
        return true;

    case visca::ViscaPackets::COMMAND_CAM_Freeze_On:
        packet[0] = (0x80 | (uint8_t)camera_address);
        packet[1] = 0x01;
        packet[2] = 0x04;
        packet[3] = 0x62;
        packet[4] = 0x02;
        packet[5] = 0xFF;
        packet_size = 6;
        return true;

    case visca::ViscaPackets::COMMAND_CAM_Freeze_Off:
        packet[0] = (0x80 | (uint8_t)camera_address);
        packet[1] = 0x01;
        packet[2] = 0x04;
        packet[3] = 0x62;
        packet[4] = 0x03;
        packet[5] = 0xFF;
        packet_size = 6;
        return true;

    case visca::ViscaPackets::COMMAND_CAM_PictureEffect_Off:
        packet[0] = (0x80 | (uint8_t)camera_address);
        packet[1] = 0x01;
        packet[2] = 0x04;
        packet[3] = 0x63;
        packet[4] = 0x00;
        packet[5] = 0xFF;
        packet_size = 6;
        return true;

    case visca::ViscaPackets::COMMAND_CAM_PictureEffect_Black_and_White:
        packet[0] = (0x80 | (uint8_t)camera_address);
        packet[1] = 0x01;
        packet[2] = 0x04;
        packet[3] = 0x63;
        packet[4] = 0x04;
        packet[5] = 0xFF;
        packet_size = 6;
        return true;

    case visca::ViscaPackets::COMMAND_CAM_MinShutter_On:
        packet[0] = (0x80 | (uint8_t)camera_address);
        packet[1] = 0x01;
        packet[2] = 0x04;
        packet[3] = 0x12;
        packet[4] = 0x02;
        packet[5] = 0xFF;
        packet_size = 6;
        return true;

    case visca::ViscaPackets::COMMAND_CAM_MinShutter_Off:
        packet[0] = (0x80 | (uint8_t)camera_address);
        packet[1] = 0x01;
        packet[2] = 0x04;
        packet[3] = 0x12;
        packet[4] = 0x03;
        packet[5] = 0xFF;
        packet_size = 6;
        return true;

    case visca::ViscaPackets::COMMAND_CAM_MinShutter_Limit:
        // Check setting.
        if (param_1 < 0x05 || param_1 > 0x14)
            return false;
        packet[0] = (0x80 | (uint8_t)camera_address);
        packet[1] = 0x01;
        packet[2] = 0x04;
        packet[3] = 0x13;
        packet[4] = 0x00;
        packet[5] = 0x00;
        packet[6] = ((uint8_t)param_1 >> 4) & 0x0F;
        packet[7] = (uint8_t)param_1 & 0x0F;
        packet[8] = 0xFF;
        packet_size = 9;
        return true;

    case visca::ViscaPackets::COMMAND_CAM_PictureFlip_On:
        packet[0] = (0x80 | (uint8_t)camera_address);
        packet[1] = 0x01;
        packet[2] = 0x04;
        packet[3] = 0x66;
        packet[4] = 0x02;
        packet[5] = 0xFF;
        packet_size = 6;
        return true;

    case visca::ViscaPackets::COMMAND_CAM_PictureFlip_Off:
        packet[0] = (0x80 | (uint8_t)camera_address);
        packet[1] = 0x01;
        packet[2] = 0x04;
        packet[3] = 0x66;
        packet[4] = 0x03;
        packet[5] = 0xFF;
        packet_size = 6;
        return true;

    case visca::ViscaPackets::COMMAND_CAM_ICR_On:
        packet[0] = (0x80 | (uint8_t)camera_address);
        packet[1] = 0x01;
        packet[2] = 0x04;
        packet[3] = 0x01;
        packet[4] = 0x02;
        packet[5] = 0xFF;
        packet_size = 6;
        return true;

    case visca::ViscaPackets::COMMAND_CAM_ICR_Off:
        packet[0] = (0x80 | (uint8_t)camera_address);
        packet[1] = 0x01;
        packet[2] = 0x04;
        packet[3] = 0x01;
        packet[4] = 0x03;
        packet[5] = 0xFF;
        packet_size = 6;
        return true;

    case visca::ViscaPackets::COMMAND_CAM_AutoICR_On:
        packet[0] = (0x80 | (uint8_t)camera_address);
        packet[1] = 0x01;
        packet[2] = 0x04;
        packet[3] = 0x51;
        packet[4] = 0x02;
        packet[5] = 0xFF;
        packet_size = 6;
        return true;

    case visca::ViscaPackets::COMMAND_CAM_AutoICR_Off:
        packet[0] = (0x80 | (uint8_t)camera_address);
        packet[1] = 0x01;
        packet[2] = 0x04;
        packet[3] = 0x51;
        packet[4] = 0x03;
        packet[5] = 0xFF;
        packet_size = 6;
        return true;

    case visca::ViscaPackets::COMMAND_CAM_AutoICR_Threshold:
        packet[0] = (0x80 | (uint8_t)camera_address);
        packet[1] = 0x01;
        packet[2] = 0x04;
        packet[3] = 0x21;
        packet[4] = 0x00;
        packet[5] = 0x00;
        packet[6] = ((uint8_t)param_1 >> 4) & 0x0F;
        packet[7] = (uint8_t)param_1 & 0x0F;
        packet[8] = 0xFF;
        packet_size = 9;
        return true;

    case visca::ViscaPackets::COMMAND_CAM_AutoICRAlarmReply_On:
        packet[0] = (0x80 | (uint8_t)camera_address);
        packet[1] = 0x01;
        packet[2] = 0x04;
        packet[3] = 0x31;
        packet[4] = 0x02;
        packet[5] = 0xFF;
        packet_size = 6;
        return true;

    case visca::ViscaPackets::COMMAND_CAM_AutoICRAlarmReply_Off:
        packet[0] = (0x80 | (uint8_t)camera_address);
        packet[1] = 0x01;
        packet[2] = 0x04;
        packet[3] = 0x31;
        packet[4] = 0x03;
        packet[5] = 0xFF;
        packet_size = 6;
        return true;

    case visca::ViscaPackets::COMMAND_CAM_Stabilizer_On:
        packet[0] = (0x80 | (uint8_t)camera_address);
        packet[1] = 0x01;
        packet[2] = 0x04;
        packet[3] = 0x34;
        packet[4] = 0x02;
        packet[5] = 0xFF;
        packet_size = 6;
        return true;

    case visca::ViscaPackets::COMMAND_CAM_Stabilizer_Off:
        packet[0] = (0x80 | (uint8_t)camera_address);
        packet[1] = 0x01;
        packet[2] = 0x04;
        packet[3] = 0x34;
        packet[4] = 0x03;
        packet[5] = 0xFF;
        packet_size = 6;
        return true;

    case visca::ViscaPackets::COMMAND_CAM_Stabilizer_Hold:
        packet[0] = (0x80 | (uint8_t)camera_address);
        packet[1] = 0x01;
        packet[2] = 0x04;
        packet[3] = 0x34;
        packet[4] = 0x00;
        packet[5] = 0xFF;
        packet_size = 6;
        return true;

    case visca::ViscaPackets::COMMAND_CAM_Memory_Reset:
        // Check setting.
        if (param_1 > 0x0F)
            return false;
        packet[0] = (0x80 | (uint8_t)camera_address);
        packet[1] = 0x01;
        packet[2] = 0x04;
        packet[3] = 0x3F;
        packet[4] = 0x00;
        packet[5] = (uint8_t)param_1;
        packet[6] = 0xFF;
        packet_size = 7;
        return true;

    case visca::ViscaPackets::COMMAND_CAM_Memory_Set:
        // Check setting.
        if (param_1 > 0x0F)
            return false;
        packet[0] = (0x80 | (uint8_t)camera_address);
        packet[1] = 0x01;
        packet[2] = 0x04;
        packet[3] = 0x3F;
        packet[4] = 0x01;
        packet[5] = (uint8_t)param_1;
        packet[6] = 0xFF;
        packet_size = 7;
        return true;

    case visca::ViscaPackets::COMMAND_CAM_Memory_Recall:
        // Check setting.
        if (param_1 > 0x0F)
            return false;
        packet[0] = (0x80 | (uint8_t)camera_address);
        packet[1] = 0x01;
        packet[2] = 0x04;
        packet[3] = 0x3F;
        packet[4] = 0x02;
        packet[5] = (uint8_t)param_1;
        packet[6] = 0xFF;
        packet_size = 7;
        return true;

    case visca::ViscaPackets::COMMAND_CAM_Custom_Reset:
        packet[0] = (0x80 | (uint8_t)camera_address);
        packet[1] = 0x01;
        packet[2] = 0x04;
        packet[3] = 0x3F;
        packet[4] = 0x00;
        packet[5] = 0x7F;
        packet[6] = 0xFF;
        packet_size = 7;
        return true;

    case visca::ViscaPackets::COMMAND_CAM_Custom_Set:
        packet[0] = (0x80 | (uint8_t)camera_address);
        packet[1] = 0x01;
        packet[2] = 0x04;
        packet[3] = 0x3F;
        packet[4] = 0x01;
        packet[5] = 0x7F;
        packet[6] = 0xFF;
        packet_size = 7;
        return true;

    case visca::ViscaPackets::COMMAND_CAM_Custom_Recall:
        packet[0] = (0x80 | (uint8_t)camera_address);
        packet[1] = 0x01;
        packet[2] = 0x04;
        packet[3] = 0x3F;
        packet[4] = 0x02;
        packet[5] = 0x7F;
        packet[6] = 0xFF;
        packet_size = 7;
        return true;

    case visca::ViscaPackets::COMMAND_CAM_MemSave_Write:
        // Check setting.
        if (param_1 > 0x07)
            return false;
        if (param_2 > 0xFFFF)
            return false;
        packet[0] = (0x80 | (uint8_t)camera_address);
        packet[1] = 0x01;
        packet[2] = 0x04;
        packet[3] = 0x23;
        packet[4] = (uint8_t)param_1;
        packet[5] = (uint8_t)((uint16_t)param_2 >> 12) & 0x0F;
        packet[6] = (uint8_t)((uint16_t)param_2 >> 8) & 0x0F;
        packet[7] = (uint8_t)((uint16_t)param_2 >> 4) & 0x0F;
        packet[8] = (uint8_t)param_2 & 0x0F;
        packet[9] = 0xFF;
        packet_size = 10;
        return true;

    case visca::ViscaPackets::COMMAND_CAM_Display_On:
        packet[0] = (0x80 | (uint8_t)camera_address);
        packet[1] = 0x01;
        packet[2] = 0x04;
        packet[3] = 0x15;
        packet[4] = 0x02;
        packet[5] = 0xFF;
        packet_size = 6;
        return true;

    case visca::ViscaPackets::COMMAND_CAM_Display_Off:
        packet[0] = (0x80 | (uint8_t)camera_address);
        packet[1] = 0x01;
        packet[2] = 0x04;
        packet[3] = 0x15;
        packet[4] = 0x03;
        packet[5] = 0xFF;
        packet_size = 6;
        return true;

    case visca::ViscaPackets::COMMAND_CAM_Display_On_Off_Switch:
        packet[0] = (0x80 | (uint8_t)camera_address);
        packet[1] = 0x01;
        packet[2] = 0x04;
        packet[3] = 0x15;
        packet[4] = 0x10;
        packet[5] = 0xFF;
        packet_size = 6;
        return true;

    case visca::ViscaPackets::COMMAND_CAM_MultiLineTitle_Title_Set_1:
        // Check setting.
        if (param_1 > 0x0F)
            return false;
        if (param_2 > 0xFF)
            return false;
        if (param_3 > 0xFF)
            return false;
        if (param_4 > 0xFF)
            return false;
        packet[0] = (0x80 | (uint8_t)camera_address);
        packet[1] = 0x01;
        packet[2] = 0x04;
        packet[3] = 0x73;
        packet[4] = (uint8_t)param_1 | 0x10;
        packet[5] = 0x00;
        packet[6] = (uint8_t)param_2;
        packet[7] = (uint8_t)param_3;
        packet[8] = (uint8_t)param_4;
        packet[9] = 0x00;
        packet[10] = 0x00;
        packet[11] = 0x00;
        packet[12] = 0x00;
        packet[13] = 0x00;
        packet[14] = 0x00;
        packet[15] = 0xFF;
        packet_size = 16;
        return true;

    case visca::ViscaPackets::COMMAND_CAM_MultiLineTitle_Title_Set_2:
        // Check setting.
        if (param_1 > 0x0F)
            return false;
        if (param_2 > 0xFF)
            return false;
        if (param_3 > 0xFF)
            return false;
        if (param_4 > 0xFF)
            return false;
        if (param_5 > 0xFF)
            return false;
        if (param_6 > 0xFF)
            return false;
        if (param_7 > 0xFF)
            return false;
        if (param_8 > 0xFF)
            return false;
        if (param_9 > 0xFF)
            return false;
        if (param_10 > 0xFF)
            return false;
        packet[0] = (0x80 | (uint8_t)camera_address);
        packet[1] = 0x01;
        packet[2] = 0x04;
        packet[3] = 0x73;
        packet[4] = (uint8_t)param_1 | 0x20;
        packet[5] = 0x00;
        packet[6] = (uint8_t)param_2;
        packet[7] = (uint8_t)param_3;
        packet[8] = (uint8_t)param_4;
        packet[9] = (uint8_t)param_5;
        packet[10] = (uint8_t)param_6;
        packet[11] = (uint8_t)param_7;
        packet[12] = (uint8_t)param_8;
        packet[13] = (uint8_t)param_9;
        packet[14] = (uint8_t)param_10;
        packet[15] = 0xFF;
        packet_size = 16;
        return true;

    case visca::ViscaPackets::COMMAND_CAM_MultiLineTitle_Title_Set_3:
        // Check setting.
        if (param_1 > 0x0F)
            return false;
        if (param_2 > 0xFF)
            return false;
        if (param_3 > 0xFF)
            return false;
        if (param_4 > 0xFF)
            return false;
        if (param_5 > 0xFF)
            return false;
        if (param_6 > 0xFF)
            return false;
        if (param_7 > 0xFF)
            return false;
        if (param_8 > 0xFF)
            return false;
        if (param_9 > 0xFF)
            return false;
        if (param_10 > 0xFF)
            return false;
        packet[0] = (0x80 | (uint8_t)camera_address);
        packet[1] = 0x01;
        packet[2] = 0x04;
        packet[3] = 0x73;
        packet[4] = (uint8_t)param_1 | 0x30;
        packet[5] = 0x00;
        packet[6] = (uint8_t)param_2;
        packet[7] = (uint8_t)param_3;
        packet[8] = (uint8_t)param_4;
        packet[9] = (uint8_t)param_5;
        packet[10] = (uint8_t)param_6;
        packet[11] = (uint8_t)param_7;
        packet[12] = (uint8_t)param_8;
        packet[13] = (uint8_t)param_9;
        packet[14] = (uint8_t)param_10;
        packet[15] = 0xFF;
        packet_size = 16;
        return true;

    case visca::ViscaPackets::COMMAND_CAM_MultiLineTitle_Title_Clear:
        // Check setting.
        if (param_1 > 0x0F)
            return false;
        packet[0] = (0x80 | (uint8_t)camera_address);
        packet[1] = 0x01;
        packet[2] = 0x04;
        packet[3] = 0x74;
        packet[4] = (uint8_t)param_1 | 0x10;
        packet[5] = 0xFF;
        packet_size = 6;
        return true;

    case visca::ViscaPackets::COMMAND_CAM_MultiLineTitle_On:
        // Check setting.
        if (param_1 > 0x0F)
            return false;
        packet[0] = (0x80 | (uint8_t)camera_address);
        packet[1] = 0x01;
        packet[2] = 0x04;
        packet[3] = 0x74;
        packet[4] = (uint8_t)param_1 | 0x20;
        packet[5] = 0xFF;
        packet_size = 6;
        return true;

    case visca::ViscaPackets::COMMAND_CAM_MultiLineTitle_Off:
        // Check setting.
        if (param_1 > 0x0F)
            return false;
        packet[0] = (0x80 | (uint8_t)camera_address);
        packet[1] = 0x01;
        packet[2] = 0x04;
        packet[3] = 0x74;
        packet[4] = (uint8_t)param_1 | 0x30;
        packet[5] = 0xFF;
        packet_size = 6;
        return true;

    case visca::ViscaPackets::COMMAND_CAM_Mute_On:
        packet[0] = (0x80 | (uint8_t)camera_address);
        packet[1] = 0x01;
        packet[2] = 0x04;
        packet[3] = 0x75;
        packet[4] = 0x02;
        packet[5] = 0xFF;
        packet_size = 6;
        return true;

    case visca::ViscaPackets::COMMAND_CAM_Mute_Off:
        packet[0] = (0x80 | (uint8_t)camera_address);
        packet[1] = 0x01;
        packet[2] = 0x04;
        packet[3] = 0x75;
        packet[4] = 0x03;
        packet[5] = 0xFF;
        packet_size = 6;
        return true;

    case visca::ViscaPackets::COMMAND_CAM_Mute_On_Off:
        packet[0] = (0x80 | (uint8_t)camera_address);
        packet[1] = 0x01;
        packet[2] = 0x04;
        packet[3] = 0x75;
        packet[4] = 0x10;
        packet[5] = 0xFF;
        packet_size = 6;
        return true;

    case visca::ViscaPackets::COMMAND_CAM_PrivacyZone_SetMask:
        // Check setting.
        if (param_1 > 0xFF)
            return false;
        if (param_2 != 0x00 && param_2 != 0x01)
            return false;
        if (param_3 > 0xFF)
            return false;
        if (param_4 > 0xFF)
            return false;
        packet[0] = (0x80 | (uint8_t)camera_address);
        packet[1] = 0x01;
        packet[2] = 0x04;
        packet[3] = 0x76;
        packet[4] = (uint8_t)param_1;
        packet[5] = (uint8_t)param_2;
        packet[6] = ((uint8_t)param_3 >> 4) & 0x0F;
        packet[7] = (uint8_t)param_3 & 0x0F;
        packet[8] = ((uint8_t)param_4 >> 4) & 0x0F;
        packet[9] = (uint8_t)param_4 & 0x0F;
        packet[10] = 0xFF;
        packet_size = 11;
        return true;

    case visca::ViscaPackets::COMMAND_CAM_PrivacyZone_Display:
        // Check setting.
        if (param_1 != 0x00 && param_1 != 0x01)
            return false;
        if (param_2 != 0x00 && param_2 != 0x01)
            return false;
        if (param_3 != 0x00 && param_3 != 0x01)
            return false;
        if (param_4 != 0x00 && param_4 != 0x01)
            return false;
        if (param_5 != 0x00 && param_5 != 0x01)
            return false;
        if (param_6 != 0x00 && param_6 != 0x01)
            return false;
        if (param_7 != 0x00 && param_7 != 0x01)
            return false;
        if (param_8 != 0x00 && param_8 != 0x01)
            return false;
        packet[0] = (0x80 | (uint8_t)camera_address);
        packet[1] = 0x01;
        packet[2] = 0x04;
        packet[3] = 0x77;
        packet[4] = (((uint8_t)param_1 << 4) & 0xF0) | param_2;
        packet[5] = (((uint8_t)param_3 << 4) & 0xF0) | param_4;
        packet[6] = (((uint8_t)param_5 << 4) & 0xF0) | param_6;
        packet[7] = (((uint8_t)param_7 << 4) & 0xF0) | param_8;
        packet[8] = 0xFF;
        packet_size = 9;
        return true;

    case visca::ViscaPackets::COMMAND_CAM_PrivacyZone_SetMaskColor:
        // Check setting.
        if (param_1 != 0x00 && param_1 != 0x01)
            return false;
        if (param_2 != 0x00 && param_2 != 0x01)
            return false;
        if (param_3 != 0x00 && param_3 != 0x01)
            return false;
        if (param_4 != 0x00 && param_4 != 0x01)
            return false;
        if (param_5 != 0x00 && param_5 != 0x01)
            return false;
        if (param_6 != 0x00 && param_6 != 0x01)
            return false;
        if (param_7 != 0x00 && param_7 != 0x01)
            return false;
        if (param_8 != 0x00 && param_8 != 0x01)
            return false;
        if (param_9 < 0x00 || param_9 > 0xFF)
            return false;
        if (param_10 < 0x00 || param_10 > 0xFF)
            return false;
        packet[0] = (0x80 | (uint8_t)camera_address);
        packet[1] = 0x01;
        packet[2] = 0x04;
        packet[3] = 0x78;
        packet[4] = (((uint8_t)param_1 << 4) & 0xF0) | param_2;
        packet[5] = (((uint8_t)param_3 << 4) & 0xF0) | param_4;
        packet[6] = (((uint8_t)param_5 << 4) & 0xF0) | param_6;
        packet[7] = (((uint8_t)param_7 << 4) & 0xF0) | param_8;
        packet[8] = (uint8_t)param_9;
        packet[9] = (uint8_t)param_10;
        packet[10] = 0xFF;
        packet_size = 11;
        return true;

    case visca::ViscaPackets::COMMAND_CAM_PrivacyZone_SetPanTiltAngle:
        // Check setting.
        if (param_1 > 0xFFF)
            return false;
        if (param_2 > 0xFFF)
            return false;
        packet[0] = (0x80 | (uint8_t)camera_address);
        packet[1] = 0x01;
        packet[2] = 0x04;
        packet[3] = 0x79;
        packet[4] = (uint8_t)(((uint16_t)param_1 >> 8) & 0x000F);
        packet[5] = (uint8_t)(((uint16_t)param_1 >> 4) & 0x000F);
        packet[6] = (uint8_t)((uint16_t)param_1 & 0x000F);
        packet[7] = (uint8_t)(((uint16_t)param_2 >> 8) & 0x000F);
        packet[8] = (uint8_t)(((uint16_t)param_2 >> 4) & 0x000F);
        packet[9] = (uint8_t)((uint16_t)param_2 & 0x000F);
        packet[10] = 0xFF;
        packet_size = 11;
        return true;

    case visca::ViscaPackets::COMMAND_CAM_PrivacyZone_SetPTZMask:
        // Check settings.
        if (param_1 > 0xFF)
            return false;
        if (param_2 > 0xFFF)
            return false;
        if (param_3 > 0xFFF)
            return false;
        if (param_4 > 0xFFFF)
            return false;
        packet[0] = (0x80 | (uint8_t)camera_address);
        packet[1] = 0x01;
        packet[2] = 0x04;
        packet[3] = 0x7B;
        packet[4] = (uint8_t)param_1;
        packet[5] = (uint8_t)(((uint16_t)param_2 >> 8) & 0x000F);
        packet[6] = (uint8_t)(((uint16_t)param_2 >> 4) & 0x000F);
        packet[7] = (uint8_t)((uint16_t)param_2 & 0x000F);
        packet[8] = (uint8_t)(((uint16_t)param_3 >> 8) & 0x000F);
        packet[9] = (uint8_t)(((uint16_t)param_3 >> 4) & 0x000F);
        packet[10] = (uint8_t)((uint16_t)param_3 & 0x000F);
        packet[11] = (uint8_t)(((uint16_t)param_4 >> 12) & 0x000F);
        packet[12] = (uint8_t)(((uint16_t)param_4 >> 8) & 0x000F);
        packet[13] = (uint8_t)(((uint16_t)param_4 >> 4) & 0x000F);
        packet[14] = (uint8_t)((uint16_t)param_4 & 0x000F);
        packet[15] = 0xFF;
        packet_size = 16;
        return false;

    case visca::ViscaPackets::COMMAND_CAM_PrivacyZone_Non_InterlockMask:
        // Check parameters.
        if (param_1 > 0xFF)
            return false;
        if (param_2 > 0xFF)
            return false;
        if (param_3 > 0xFF)
            return false;
        if (param_4 > 0xFF)
            return false;
        if (param_5 > 0xFF)
            return false;
        packet[0] = (0x80 | (uint8_t)camera_address);
        packet[1] = 0x01;
        packet[2] = 0x04;
        packet[3] = 0x6F;
        packet[4] = (uint8_t)param_1;
        packet[5] = ((uint8_t)param_2 >> 4) & 0x0F;
        packet[6] = (uint8_t)param_2 & 0x0F;
        packet[7] = ((uint8_t)param_3 >> 4) & 0x0F;
        packet[8] = (uint8_t)param_3 & 0x0F;
        packet[9] = ((uint8_t)param_4 >> 4) & 0x0F;
        packet[10] = (uint8_t)param_4 & 0x0F;
        packet[11] = ((uint8_t)param_5 >> 4) & 0x0F;
        packet[12] = (uint8_t)param_5 & 0x0F; 
        packet[13] = 0xFF;
        packet_size = 14;
        return true;

    case visca::ViscaPackets::COMMAND_CAM_PrivacyZone_CenterLineOff:
        packet[0] = (0x80 | (uint8_t)camera_address);
        packet[1] = 0x01;
        packet[2] = 0x04;
        packet[3] = 0x7C;
        packet[4] = 0x03;
        packet[5] = 0xFF;
        packet_size = 6;
        return true;

    case visca::ViscaPackets::COMMAND_CAM_PrivacyZone_CenterLineOn:
        packet[0] = (0x80 | (uint8_t)camera_address);
        packet[1] = 0x01;
        packet[2] = 0x04;
        packet[3] = 0x7C;
        packet[4] = 0x04;
        packet[5] = 0xFF;
        packet_size = 6;
        return true;

    case visca::ViscaPackets::COMMAND_CAM_IDWrite:
        // Check setting.
        if (param_1 > 0xFFFF)
            return false;
        packet[0] = (0x80 | (uint8_t)camera_address);
        packet[1] = 0x01;
        packet[2] = 0x04;
        packet[3] = 0x22;
        packet[4] = (uint8_t)(((uint16_t)param_1 >> 12) & 0x000F);
        packet[5] = (uint8_t)(((uint16_t)param_1 >> 8) & 0x000F);
        packet[6] = (uint8_t)(((uint16_t)param_1 >> 4) & 0x000F);
        packet[7] = (uint8_t)param_1 & 0x0F;
        packet[8] = 0xFF;
        packet_size = 9;
        return true;

    case visca::ViscaPackets::COMMAND_CAM_MD_On:
        packet[0] = (0x80 | (uint8_t)camera_address);
        packet[1] = 0x01;
        packet[2] = 0x04;
        packet[3] = 0x1B;
        packet[4] = 0x02;
        packet[5] = 0xFF;
        packet_size = 6;
        return true;

    case visca::ViscaPackets::COMMAND_CAM_MD_Off:
        packet[0] = (0x80 | (uint8_t)camera_address);
        packet[1] = 0x01;
        packet[2] = 0x04;
        packet[3] = 0x1B;
        packet[4] = 0x03;
        packet[5] = 0xFF;
        packet_size = 6;
        return true;

    case visca::ViscaPackets::COMMAND_CAM_MD_Function_Set:
        // Check setting.
        if (param_1 > 0x0F)
            return false;
        if (param_2 > 0x0F)
            return false;
        if (param_3 > 0xFF)
            return false;
        if (param_4 > 0xFF)
            return false;
        packet[0] = (0x80 | (uint8_t)camera_address);
        packet[1] = 0x01;
        packet[2] = 0x04;
        packet[3] = 0x1C;
        packet[4] = (uint8_t)param_1 & 0x0F;
        packet[5] = (uint8_t)param_2 & 0x0F;
        packet[6] = ((uint8_t)param_3 >> 4) & 0x0F;
        packet[7] = (uint8_t)param_3 & 0x0F;
        packet[8] = ((uint8_t)param_4 >> 4) & 0x0F;
        packet[9] = (uint8_t)param_4 & 0x0F;
        packet[10] = 0xFF;
        packet_size = 11;
        return true;

    case visca::ViscaPackets::COMMAND_CAM_MD_Window_Set:
        // Check setting.
        if (param_1 > 0x0F)
            return false;
        if (param_2 > 0x10)
            return false;
        if (param_3 > 0x0E)
            return false;
        if (param_4 < 0x01 || param_4 > 0x11)
            return false;
        if (param_5 < 0x01 || param_5 > 0x0F)
            return false;
        packet[0] = (0x80 | (uint8_t)camera_address);
        packet[1] = 0x01;
        packet[2] = 0x04;
        packet[3] = 0x1D;
        packet[4] = (uint8_t)param_1;
        packet[5] = (uint8_t)param_2;
        packet[6] = (uint8_t)param_3;
        packet[7] = (uint8_t)param_4;
        packet[8] = (uint8_t)param_5;
        packet[9] = 0xFF;
        packet_size = 10;
        return true;

    case visca::ViscaPackets::COMMAND_CAM_ContinuousZoomPosReply_On:
        packet[0] = (0x80 | (uint8_t)camera_address);
        packet[1] = 0x01;
        packet[2] = 0x04;
        packet[3] = 0x69;
        packet[4] = 0x02;
        packet[5] = 0xFF;
        packet_size = 6;
        return true;

    case visca::ViscaPackets::COMMAND_CAM_ContinuousZoomPosReply_Off:
        packet[0] = (0x80 | (uint8_t)camera_address);
        packet[1] = 0x01;
        packet[2] = 0x04;
        packet[3] = 0x69;
        packet[4] = 0x03;
        packet[5] = 0xFF;
        packet_size = 6;
        return true;

    case visca::ViscaPackets::COMMAND_CAM_ZoomPosReplyIntervalTimeSet:
        // Check setting.
        if (param_1 > 0xFF)
            return false;
        packet[0] = (0x80 | (uint8_t)camera_address);
        packet[1] = 0x01;
        packet[2] = 0x04;
        packet[3] = 0x6A;
        packet[4] = 0x00;
        packet[5] = 0x00;
        packet[6] = ((uint8_t)param_1 >> 4) & 0x0F;
        packet[7] = (uint8_t)param_1 & 0x0F;
        packet[8] = 0xFF;
        packet_size = 9;
        return true;

    case visca::ViscaPackets::COMMAND_CAM_ContinuousFocusPosReply_On:
        packet[0] = (0x80 | (uint8_t)camera_address);
        packet[1] = 0x01;
        packet[2] = 0x04;
        packet[3] = 0x16;
        packet[4] = 0x02;
        packet[5] = 0xFF;
        packet_size = 6;
        return true;

    case visca::ViscaPackets::COMMAND_CAM_ContinuousFocusPosReply_Off:
        packet[0] = (0x80 | (uint8_t)camera_address);
        packet[1] = 0x01;
        packet[2] = 0x04;
        packet[3] = 0x16;
        packet[4] = 0x03;
        packet[5] = 0xFF;
        packet_size = 6;
        return true;

    case visca::ViscaPackets::COMMAND_CAM_FocusPosReplyIntervalTimeSet:
        // Check setting.
        if (param_1 > 0xFF)
            return false;
        packet[0] = (0x80 | (uint8_t)camera_address);
        packet[1] = 0x01;
        packet[2] = 0x04;
        packet[3] = 0x1A;
        packet[4] = 0x00;
        packet[5] = 0x00;
        packet[6] = ((uint8_t)param_1 >> 4) & 0x0F;
        packet[7] = (uint8_t)param_1 & 0x0F;
        packet[8] = 0xFF;
        packet_size = 9;
        return true;

    case visca::ViscaPackets::COMMAND_CAM_RegisterValue:
        // Check parameters.
        if (param_1 > 0x7F)
            return false;
        if (param_2 > 0xFF)
            return false;
        packet[0] = (0x80 | (uint8_t)camera_address);
        packet[1] = 0x01;
        packet[2] = 0x04;
        packet[3] = 0x24;
        packet[4] = (uint8_t)param_1;
        packet[5] = ((uint8_t)param_2 >> 4) & 0x0F;
        packet[6] = (uint8_t)param_2 & 0x0F;
        packet[7] = 0xFF;
        packet_size = 8;
        return true;

    case visca::ViscaPackets::COMMAND_CAM_ChromaSuppress:
        // Check parameters.
        if (param_1 > 0x03)
            return false;
        packet[0] = (0x80 | (uint8_t)camera_address);
        packet[1] = 0x01;
        packet[2] = 0x04;
        packet[3] = 0x5F;
        packet[4] = (uint8_t)param_1;
        packet[5] = 0xFF;
        packet_size = 6;
        return true;

    case visca::ViscaPackets::COMMAND_CAM_ColorGain_Direct:
        // Check parameters.
        if (param_1 > 0x0E)
            return false;
        packet[0] = (0x80 | (uint8_t)camera_address);
        packet[1] = 0x01;
        packet[2] = 0x04;
        packet[3] = 0x49;
        packet[4] = 0x00;
        packet[5] = 0x00;
        packet[6] = 0x00;
        packet[7] = (uint8_t)param_1;
        packet[8] = 0xFF;
        packet_size = 9;
        return true;

    case visca::ViscaPackets::COMMAND_CAM_ColorHue_Direct:
        // Check parameters.
        if (param_1 > 0x0E)
            return false;
        packet[0] = (0x80 | (uint8_t)camera_address);
        packet[1] = 0x01;
        packet[2] = 0x04;
        packet[3] = 0x4F;
        packet[4] = 0x00;
        packet[5] = 0x00;
        packet[6] = 0x00;
        packet[7] = (uint8_t)param_1;
        packet[8] = 0xFF;
        packet_size = 9;
        return true;

    case visca::ViscaPackets::COMMAND_CAM_GammaOffset_Direct:
        // Check parameters.
        if (param_1 != 0x00 && param_1 != 0x01)
            return false;
        if (param_2 > 0x40)
            return false;
        packet[0] = (0x80 | (uint8_t)camera_address);
        packet[1] = 0x01;
        packet[2] = 0x04;
        packet[3] = 0x1E;
        packet[4] = 0x00;
        packet[5] = 0x00;
        packet[6] = 0x00;
        packet[7] = (uint8_t)param_1;
        packet[8] = ((uint8_t)param_2 >> 4) & 0x0F;
        packet[9] = (uint8_t)param_2 & 0x0F;
        packet[10] = 0xFF;
        packet_size = 11;
        return true;

    case visca::ViscaPackets::COMMAND_CAM_ContrastAdjLevel_Direct:
        // Check parameters.
        if (param_1 > 0xFF)
            return false;
        packet[0] = (0x80 | (uint8_t)camera_address);
        packet[1] = 0x01;
        packet[2] = 0x05;
        packet[3] = 0x5D;
        packet[4] = 0x01;
        packet[5] = ((uint8_t)param_1 >> 4) & 0x0F;
        packet[6] = (uint8_t)param_1 & 0x0F;
        packet[7] = 0xFF;
        packet_size = 8;
        return true;

    case visca::ViscaPackets::COMMAND_CAM_ExExpComp_Reset:
        packet[0] = (0x80 | (uint8_t)camera_address);
        packet[1] = 0x01;
        packet[2] = 0x04;
        packet[3] = 0x1F;
        packet[4] = 0x0E;
        packet[5] = 0x00;
        packet[6] = 0x00;
        packet[7] = 0xFF;
        packet_size = 8;
        return true;

    case visca::ViscaPackets::COMMAND_CAM_ExExpComp_Up:
        // Check parameters.
        if (param_1 > 0x7F)
            return false;
        packet[0] = (0x80 | (uint8_t)camera_address);
        packet[1] = 0x01;
        packet[2] = 0x04;
        packet[3] = 0x1F;
        packet[4] = 0x0E;
        packet[5] = 0x02;
        packet[6] = (uint8_t)param_1;
        packet[7] = 0xFF;
        packet_size = 8;
        return true;

    case visca::ViscaPackets::COMMAND_CAM_ExExpComp_Down:
        // Check parameters.
        if (param_1 > 0x7F)
            return false;
        packet[0] = (0x80 | (uint8_t)camera_address);
        packet[1] = 0x01;
        packet[2] = 0x04;
        packet[3] = 0x1F;
        packet[4] = 0x0E;
        packet[5] = 0x03;
        packet[6] = (uint8_t)param_1;
        packet[7] = 0xFF;
        packet_size = 8;
        return true;

    case visca::ViscaPackets::COMMAND_CAM_ExExpComp_Direct:
        // Check parameters.
        if (param_1 > 0xFF)
            return false;
        packet[0] = (0x80 | (uint8_t)camera_address);
        packet[1] = 0x01;
        packet[2] = 0x04;
        packet[3] = 0x1F;
        packet[4] = 0x4E;
        packet[5] = 0x00;
        packet[6] = 0x00;
        packet[7] = ((uint8_t)param_1 >> 4) & 0x0F;
        packet[8] = (uint8_t)param_1 & 0x0F;
        packet[9] = 0xFF;
        packet_size = 10;
        return true;

    case visca::ViscaPackets::COMMAND_CAM_ExAperture_Reset:
        packet[0] = (0x80 | (uint8_t)camera_address);
        packet[1] = 0x01;
        packet[2] = 0x04;
        packet[3] = 0x1F;
        packet[4] = 0x02;
        packet[5] = 0x00;
        packet[6] = 0x00;
        packet[7] = 0xFF;
        packet_size = 8;
        return true;

    case visca::ViscaPackets::COMMAND_CAM_ExAperture_Up:
        // Check parameters.
        if (param_1 > 0x7F)
            return false;
        packet[0] = (0x80 | (uint8_t)camera_address);
        packet[1] = 0x01;
        packet[2] = 0x04;
        packet[3] = 0x1F;
        packet[4] = 0x02;
        packet[5] = 0x02;
        packet[6] = (uint8_t)param_1;
        packet[7] = 0xFF;
        packet_size = 8;
        return true;

    case visca::ViscaPackets::COMMAND_CAM_ExAperture_Down:
        // Check parameters.
        if (param_1 > 0x7F)
            return false;
        packet[0] = (0x80 | (uint8_t)camera_address);
        packet[1] = 0x01;
        packet[2] = 0x04;
        packet[3] = 0x1F;
        packet[4] = 0x02;
        packet[5] = 0x03;
        packet[6] = (uint8_t)param_1;
        packet[7] = 0xFF;
        packet_size = 8;
        return true;

    case visca::ViscaPackets::COMMAND_CAM_ExAperture_Direct:
        // Check parameters.
        if (param_1 > 0xFF)
            return false;
        packet[0] = (0x80 | (uint8_t)camera_address);
        packet[1] = 0x01;
        packet[2] = 0x04;
        packet[3] = 0x1F;
        packet[4] = 0x42;
        packet[5] = 0x00;
        packet[6] = 0x00;
        packet[7] = ((uint8_t)param_1 >> 4) & 0x0F;
        packet[8] = (uint8_t)param_1 & 0x0F;
        packet[9] = 0xFF;
        packet_size = 10;
        return true;

    case visca::ViscaPackets::COMMAND_CAM_ExAutoICR_Threshold:
        // Check parameters.
        if (param_1 > 0xFF)
            return false;
        packet[0] = (0x80 | (uint8_t)camera_address);
        packet[1] = 0x01;
        packet[2] = 0x04;
        packet[3] = 0x1F;
        packet[4] = 0x21;
        packet[5] = 0x00;
        packet[6] = 0x00;
        packet[7] = ((uint8_t)param_1 >> 4) & 0x0F;
        packet[8] = (uint8_t)param_1 & 0x0F;
        packet[9] = 0xFF;
        packet_size = 10;
        return true;

    case visca::ViscaPackets::COMMAND_CAM_ExAutoICR_Level:
        // Check parameters.
        if (param_1 > 0x1C)
            return false;
        packet[0] = (0x80 | (uint8_t)camera_address);
        packet[1] = 0x01;
        packet[2] = 0x04;
        packet[3] = 0x1F;
        packet[4] = 0x21;
        packet[5] = 0x01;
        packet[6] = 0x00;
        packet[7] = ((uint8_t)param_1 >> 4) & 0x0F;
        packet[8] = (uint8_t)param_1 & 0x0F;
        packet[9] = 0xFF;
        packet_size = 10;
        return true;

    case visca::ViscaPackets::COMMAND_CAM_ExColorGain_Direct:
        // Check parameters.
        if (param_1 > 0xFF)
            return false;
        packet[0] = (0x80 | (uint8_t)camera_address);
        packet[1] = 0x01;
        packet[2] = 0x04;
        packet[3] = 0x1F;
        packet[4] = 0x49;
        packet[5] = 0x00;
        packet[6] = 0x00;
        packet[7] = ((uint8_t)param_1 >> 4) & 0x0F;
        packet[8] = (uint8_t)param_1 & 0x0F;
        packet[9] = 0xFF;
        packet_size = 10;
        return true;

    case visca::ViscaPackets::COMMAND_CAM_ExColorHue_Direct:
        // Check parameters.
        if (param_1 > 0xFF)
            return false;
        packet[0] = (0x80 | (uint8_t)camera_address);
        packet[1] = 0x01;
        packet[2] = 0x04;
        packet[3] = 0x1F;
        packet[4] = 0x4F;
        packet[5] = 0x00;
        packet[6] = 0x00;
        packet[7] = ((uint8_t)param_1 >> 4) & 0x0F;
        packet[8] = (uint8_t)param_1 & 0x0F;
        packet[9] = 0xFF;
        packet_size = 10;
        return true;

    case visca::ViscaPackets::COMMAND_CAM_HLC_Parameter_Set:
        /// Check parameters.
        if (param_1 > 3)
            return false;
        if (param_2 > 3)
            return false;
        packet[0] = (0x80 | (uint8_t)camera_address);
        packet[1] = 0x01;
        packet[2] = 0x04;
        packet[3] = 0x14;
        packet[4] = (uint8_t)param_1;
        packet[5] = (uint8_t)param_2;
        packet[6] = 0xFF;
        packet_size = 7;
        return true;

    case visca::ViscaPackets::COMMAND_CAM_FlickerReduction_On:
        packet[0] = (0x80 | (uint8_t)camera_address);
        packet[1] = 0x01;
        packet[2] = 0x04;
        packet[3] = 0x32;
        packet[4] = 0x02;
        packet[5] = 0xFF;
        packet_size = 6;
        return true;

    case visca::ViscaPackets::COMMAND_CAM_FlickerReduction_Off:
        packet[0] = (0x80 | (uint8_t)camera_address);
        packet[1] = 0x01;
        packet[2] = 0x04;
        packet[3] = 0x32;
        packet[4] = 0x03;
        packet[5] = 0xFF;
        packet_size = 6;
        return true;

    /*
    ENQUIRY COMMANDS.
    */
    case visca::ViscaPackets::INQUIRY_CAM_PowerInq:
        packet[0] = (0x80 | (uint8_t)camera_address);
        packet[1] = 0x09;
        packet[2] = 0x04;
        packet[3] = 0x00;
        packet[4] = 0xFF;
        packet_size = 5;
        return true;

    case visca::ViscaPackets::INQUIRY_CAM_ZoomPosInq:
        packet[0] = (0x80 | (uint8_t)camera_address);
        packet[1] = 0x09;
        packet[2] = 0x04;
        packet[3] = 0x47;
        packet[4] = 0xFF;
        packet_size = 5;
        return true;

    case visca::ViscaPackets::INQUIRY_CAM_DZoomModeInq:
        packet[0] = (0x80 | (uint8_t)camera_address);
        packet[1] = 0x09;
        packet[2] = 0x04;
        packet[3] = 0x06;
        packet[4] = 0xFF;
        packet_size = 5;
        return true;

    case visca::ViscaPackets::INQUIRY_CAM_DZoom_C_S_ModeInq:
        packet[0] = (0x80 | (uint8_t)camera_address);
        packet[1] = 0x09;
        packet[2] = 0x04;
        packet[3] = 0x36;
        packet[4] = 0xFF;
        packet_size = 5;
        return true;

    case visca::ViscaPackets::INQUIRY_CAM_DZoomPosInq:
        packet[0] = (0x80 | (uint8_t)camera_address);
        packet[1] = 0x09;
        packet[2] = 0x04;
        packet[3] = 0x46;
        packet[4] = 0xFF;
        packet_size = 5;
        return true;

    case visca::ViscaPackets::INQUIRY_CAM_FocusModeInq:
        packet[0] = (0x80 | (uint8_t)camera_address);
        packet[1] = 0x09;
        packet[2] = 0x04;
        packet[3] = 0x38;
        packet[4] = 0xFF;
        packet_size = 5;
        return true;

    case visca::ViscaPackets::INQUIRY_CAM_FocusPosInq:
        packet[0] = (0x80 | (uint8_t)camera_address);
        packet[1] = 0x09;
        packet[2] = 0x04;
        packet[3] = 0x48;
        packet[4] = 0xFF;
        packet_size = 5;
        return true;

    case visca::ViscaPackets::INQUIRY_CAM_FocusNearLimitInq:
        packet[0] = (0x80 | (uint8_t)camera_address);
        packet[1] = 0x09;
        packet[2] = 0x04;
        packet[3] = 0x28;
        packet[4] = 0xFF;
        packet_size = 5;
        return true;

    case visca::ViscaPackets::INQUIRY_CAM_AFSensitivityInq:
        packet[0] = (0x80 | (uint8_t)camera_address);
        packet[1] = 0x09;
        packet[2] = 0x04;
        packet[3] = 0x58;
        packet[4] = 0xFF;
        packet_size = 5;
        return true;

    case visca::ViscaPackets::INQUIRY_CAM_AFModeInq:
        packet[0] = (0x80 | (uint8_t)camera_address);
        packet[1] = 0x09;
        packet[2] = 0x04;
        packet[3] = 0x57;
        packet[4] = 0xFF;
        packet_size = 5;
        return true;

    case visca::ViscaPackets::INQUIRY_CAM_AFTimeSettingInq:
        packet[0] = (0x80 | (uint8_t)camera_address);
        packet[1] = 0x09;
        packet[2] = 0x04;
        packet[3] = 0x27;
        packet[4] = 0xFF;
        packet_size = 5;
        return true;

    case visca::ViscaPackets::INQUIRY_CAM_IRCorrectionInq:
        packet[0] = (0x80 | (uint8_t)camera_address);
        packet[1] = 0x09;
        packet[2] = 0x04;
        packet[3] = 0x11;
        packet[4] = 0xFF;
        packet_size = 5;
        return true;

    case visca::ViscaPackets::INQUIRY_CAM_WBModeInq:
        packet[0] = (0x80 | (uint8_t)camera_address);
        packet[1] = 0x09;
        packet[2] = 0x04;
        packet[3] = 0x35;
        packet[4] = 0xFF;
        packet_size = 5;
        return true;

    case visca::ViscaPackets::INQUIRY_CAM_RGainInq:
        packet[0] = (0x80 | (uint8_t)camera_address);
        packet[1] = 0x09;
        packet[2] = 0x04;
        packet[3] = 0x43;
        packet[4] = 0xFF;
        packet_size = 5;
        return true;

    case visca::ViscaPackets::INQUIRY_CAM_BGainInq:
        packet[0] = (0x80 | (uint8_t)camera_address);
        packet[1] = 0x09;
        packet[2] = 0x04;
        packet[3] = 0x44;
        packet[4] = 0xFF;
        packet_size = 5;
        return true;

    case visca::ViscaPackets::INQUIRY_CAM_AEModeInq:
        packet[0] = (0x80 | (uint8_t)camera_address);
        packet[1] = 0x09;
        packet[2] = 0x04;
        packet[3] = 0x39;
        packet[4] = 0xFF;
        packet_size = 5;
        return true;

    case visca::ViscaPackets::INQUIRY_CAM_AutoSlowShutterInq:
        packet[0] = (0x80 | (uint8_t)camera_address);
        packet[1] = 0x09;
        packet[2] = 0x04;
        packet[3] = 0x5A;
        packet[4] = 0xFF;
        packet_size = 5;
        return true;

    case visca::ViscaPackets::INQUIRY_CAM_ShutterPosInq:
        packet[0] = (0x80 | (uint8_t)camera_address);
        packet[1] = 0x09;
        packet[2] = 0x04;
        packet[3] = 0x4A;
        packet[4] = 0xFF;
        packet_size = 5;
        return true;

    case visca::ViscaPackets::INQUIRY_CAM_IrisPosInq:
        packet[0] = (0x80 | (uint8_t)camera_address);
        packet[1] = 0x09;
        packet[2] = 0x04;
        packet[3] = 0x4B;
        packet[4] = 0xFF;
        packet_size = 5;
        return true;

    case visca::ViscaPackets::INQUIRY_CAM_GainPosInq:
        packet[0] = (0x80 | (uint8_t)camera_address);
        packet[1] = 0x09;
        packet[2] = 0x04;
        packet[3] = 0x4C;
        packet[4] = 0xFF;
        packet_size = 5;
        return true;

    case visca::ViscaPackets::INQUIRY_CAM_GainLimitInq:
        packet[0] = (0x80 | (uint8_t)camera_address);
        packet[1] = 0x09;
        packet[2] = 0x04;
        packet[3] = 0x2C;
        packet[4] = 0xFF;
        packet_size = 5;
        return true;

    case visca::ViscaPackets::INQUIRY_CAM_ExpCompModeInq:
        packet[0] = (0x80 | (uint8_t)camera_address);
        packet[1] = 0x09;
        packet[2] = 0x04;
        packet[3] = 0x3E;
        packet[4] = 0xFF;
        packet_size = 5;
        return true;

    case visca::ViscaPackets::INQUIRY_CAM_ExpCompPosInq:
        packet[0] = (0x80 | (uint8_t)camera_address);
        packet[1] = 0x09;
        packet[2] = 0x04;
        packet[3] = 0x4E;
        packet[4] = 0xFF;
        packet_size = 5;
        return true;

    case visca::ViscaPackets::INQUIRY_CAM_BackLightModeInq:
        packet[0] = (0x80 | (uint8_t)camera_address);
        packet[1] = 0x09;
        packet[2] = 0x04;
        packet[3] = 0x33;
        packet[4] = 0xFF;
        packet_size = 5;
        return true;

    case visca::ViscaPackets::INQUIRY_CAM_SpotAEModeInq:
        packet[0] = (0x80 | (uint8_t)camera_address);
        packet[1] = 0x09;
        packet[2] = 0x04;
        packet[3] = 0x59;
        packet[4] = 0xFF;
        packet_size = 5;
        return true;

    case visca::ViscaPackets::INQUIRY_CAM_SpotAEPosInq:
        packet[0] = (0x80 | (uint8_t)camera_address);
        packet[1] = 0x09;
        packet[2] = 0x04;
        packet[3] = 0x29;
        packet[4] = 0xFF;
        packet_size = 5;
        return true;

    case visca::ViscaPackets::INQUIRY_CAM_VEModeInq:
        packet[0] = (0x80 | (uint8_t)camera_address);
        packet[1] = 0x09;
        packet[2] = 0x04;
        packet[3] = 0x3D;
        packet[4] = 0xFF;
        packet_size = 5;
        return true;

    case visca::ViscaPackets::INQUIRY_CAM_VEParameterInq:
        packet[0] = (0x80 | (uint8_t)camera_address);
        packet[1] = 0x09;
        packet[2] = 0x04;
        packet[3] = 0x2D;
        packet[4] = 0xFF;
        packet_size = 5;
        return true;

    case visca::ViscaPackets::INQUIRY_CAM_WDModeInq:
        packet[0] = (0x80 | (uint8_t)camera_address);
        packet[1] = 0x09;
        packet[2] = 0x04;
        packet[3] = 0x3D;
        packet[4] = 0xFF;
        packet_size = 5;
        return true;

    case visca::ViscaPackets::INQUIRY_CAM_WDParameterInq:
        packet[0] = (0x80 | (uint8_t)camera_address);
        packet[1] = 0x09;
        packet[2] = 0x04;
        packet[3] = 0x2D;
        packet[4] = 0xFF;
        packet_size = 5;
        return true;

    case visca::ViscaPackets::INQUIRY_CAM_AEResponseInq:
        packet[0] = (0x80 | (uint8_t)camera_address);
        packet[1] = 0x09;
        packet[2] = 0x04;
        packet[3] = 0x5D;
        packet[4] = 0xFF;
        packet_size = 5;
        return true;

    case visca::ViscaPackets::INQUIRY_CAM_DefogInq:
        packet[0] = (0x80 | (uint8_t)camera_address);
        packet[1] = 0x09;
        packet[2] = 0x04;
        packet[3] = 0x37;
        packet[4] = 0xFF;
        packet_size = 5;
        return true;

    case visca::ViscaPackets::INQUIRY_CAM_ApertureInq:
        packet[0] = (0x80 | (uint8_t)camera_address);
        packet[1] = 0x09;
        packet[2] = 0x04;
        packet[3] = 0x42;
        packet[4] = 0xFF;
        packet_size = 5;
        return true;

    case visca::ViscaPackets::INQUIRY_CAM_NRInq:
        packet[0] = (0x80 | (uint8_t)camera_address);
        packet[1] = 0x09;
        packet[2] = 0x04;
        packet[3] = 0x53;
        packet[4] = 0xFF;
        packet_size = 5;
        return true;

    case visca::ViscaPackets::INQUIRY_CAM_NR2D3Dinq:
        packet[0] = (0x80 | (uint8_t)camera_address);
        packet[1] = 0x09;
        packet[2] = 0x05;
        packet[3] = 0x53;
        packet[4] = 0xFF;
        packet_size = 5;
        return true;
        
    case visca::ViscaPackets::INQUIRY_CAM_GammaInq:
        packet[0] = (0x80 | (uint8_t)camera_address);
        packet[1] = 0x09;
        packet[2] = 0x04;
        packet[3] = 0x5B;
        packet[4] = 0xFF;
        packet_size = 5;
        return true;

    case visca::ViscaPackets::INQUIRY_CAM_HighSensitivityInq:
        packet[0] = (0x80 | (uint8_t)camera_address);
        packet[1] = 0x09;
        packet[2] = 0x04;
        packet[3] = 0x5E;
        packet[4] = 0xFF;
        packet_size = 5;
        return true;

    case visca::ViscaPackets::INQUIRY_CAM_LR_ReverseModeInq:
        packet[0] = (0x80 | (uint8_t)camera_address);
        packet[1] = 0x09;
        packet[2] = 0x04;
        packet[3] = 0x61;
        packet[4] = 0xFF;
        packet_size = 5;
        return true;

    case visca::ViscaPackets::INQUIRY_CAM_FreezeModeInq:
        packet[0] = (0x80 | (uint8_t)camera_address);
        packet[1] = 0x09;
        packet[2] = 0x04;
        packet[3] = 0x62;
        packet[4] = 0xFF;
        packet_size = 5;
        return true;

    case visca::ViscaPackets::INQUIRY_CAM_PictureEffectModeInq:
        packet[0] = (0x80 | (uint8_t)camera_address);
        packet[1] = 0x09;
        packet[2] = 0x04;
        packet[3] = 0x63;
        packet[4] = 0xFF;
        packet_size = 5;
        return true;

    case visca::ViscaPackets::INQUIRY_CAM_PictureFlipModeInq:
        packet[0] = (0x80 | (uint8_t)camera_address);
        packet[1] = 0x09;
        packet[2] = 0x04;
        packet[3] = 0x66;
        packet[4] = 0xFF;
        packet_size = 5;
        return true;

    case visca::ViscaPackets::INQUIRY_CAM_ICRModeInq:
        packet[0] = (0x80 | (uint8_t)camera_address);
        packet[1] = 0x09;
        packet[2] = 0x04;
        packet[3] = 0x01;
        packet[4] = 0xFF;
        packet_size = 5;
        return true;

    case visca::ViscaPackets::INQUIRY_CAM_AutoICRModeInq:
        packet[0] = (0x80 | (uint8_t)camera_address);
        packet[1] = 0x09;
        packet[2] = 0x04;
        packet[3] = 0x51;
        packet[4] = 0xFF;
        packet_size = 5;
        return true;

    case visca::ViscaPackets::INQUIRY_CAM_AutoICRThresholdInq:
        packet[0] = (0x80 | (uint8_t)camera_address);
        packet[1] = 0x09;
        packet[2] = 0x04;
        packet[3] = 0x21;
        packet[4] = 0xFF;
        packet_size = 5;
        return true;

    case visca::ViscaPackets::INQUIRY_CAM_AutoICRAlarmReplyInq:
        packet[0] = (0x80 | (uint8_t)camera_address);
        packet[1] = 0x09;
        packet[2] = 0x04;
        packet[3] = 0x31;
        packet[4] = 0xFF;
        packet_size = 5;
        return true;

    case visca::ViscaPackets::INQUIRY_CAM_MemoryInq:
        packet[0] = (0x80 | (uint8_t)camera_address);
        packet[1] = 0x09;
        packet[2] = 0x04;
        packet[3] = 0x3F;
        packet[4] = 0xFF;
        packet_size = 5;
        return true;

    case visca::ViscaPackets::INQUIRY_CAM_MemSaveInq:
        // Check parameters.
        if (param_1 > 0x07)
            return false;
        packet[0] = (0x80 | (uint8_t)camera_address);
        packet[1] = 0x09;
        packet[2] = 0x04;
        packet[3] = 0x23;
        packet[4] = (uint8_t)param_1;
        packet[5] = 0xFF;
        packet_size = 6;
        return true;

    case visca::ViscaPackets::INQUIRY_CAM_DisplayModeInq:
        packet[0] = (0x80 | (uint8_t)camera_address);
        packet[1] = 0x09;
        packet[2] = 0x04;
        packet[3] = 0x15;
        packet[4] = 0xFF;
        packet_size = 5;
        return true;

    case visca::ViscaPackets::INQUIRY_CAM_StabilizerModeInq:
        packet[0] = (0x80 | (uint8_t)camera_address);
        packet[1] = 0x09;
        packet[2] = 0x04;
        packet[3] = 0x34;
        packet[4] = 0xFF;
        packet_size = 5;
        return true;

    case visca::ViscaPackets::INQUIRY_CAM_MuteModeInq:
        packet[0] = (0x80 | (uint8_t)camera_address);
        packet[1] = 0x09;
        packet[2] = 0x04;
        packet[3] = 0x75;
        packet[4] = 0xFF;
        packet_size = 5;
        return true;

    case visca::ViscaPackets::INQUIRY_CAM_PrivacyDisplayInq:
        packet[0] = (0x80 | (uint8_t)camera_address);
        packet[1] = 0x09;
        packet[2] = 0x04;
        packet[3] = 0x77;
        packet[4] = 0xFF;
        packet_size = 5;
        return true;

    case visca::ViscaPackets::INQUIRY_CAM_PrivacyPanTiltInq:
        packet[0] = (0x80 | (uint8_t)camera_address);
        packet[1] = 0x09;
        packet[2] = 0x04;
        packet[3] = 0x79;
        packet[4] = 0xFF;
        packet_size = 5;
        return true;

    case visca::ViscaPackets::INQUIRY_CAM_PrivacyPTZInq:
        // Check parameters.
        if (param_1 > 0xFF)
            return false;
        packet[0] = (0x80 | (uint8_t)camera_address);
        packet[1] = 0x09;
        packet[2] = 0x04;
        packet[3] = 0x7B;
        packet[4] = (uint8_t)param_1;
        packet[5] = 0xFF;
        packet_size = 6;
        return true;

    case visca::ViscaPackets::INQUIRY_CAM_PrivacyMonitorInq:
        packet[0] = (0x80 | (uint8_t)camera_address);
        packet[1] = 0x09;
        packet[2] = 0x04;
        packet[3] = 0x6F;
        packet[4] = 0xFF;
        packet_size = 5;
        return true;

    case visca::ViscaPackets::INQUIRY_CAM_IDInq:
        packet[0] = (0x80 | (uint8_t)camera_address);
        packet[1] = 0x09;
        packet[2] = 0x04;
        packet[3] = 0x22;
        packet[4] = 0xFF;
        packet_size = 5;
        return true;

    case visca::ViscaPackets::INQUIRY_CAM_VersionInq:
        packet[0] = (0x80 | (uint8_t)camera_address);
        packet[1] = 0x09;
        packet[2] = 0x00;
        packet[3] = 0x02;
        packet[4] = 0xFF;
        packet_size = 5;
        return true;

    case visca::ViscaPackets::INQUIRY_CAM_MDModeInq:
        packet[0] = (0x80 | (uint8_t)camera_address);
        packet[1] = 0x09;
        packet[2] = 0x04;
        packet[3] = 0x1B;
        packet[4] = 0xFF;
        packet_size = 5;
        return true;

    case visca::ViscaPackets::INQUIRY_CAM_MDFunctionInq:
        packet[0] = (0x80 | (uint8_t)camera_address);
        packet[1] = 0x09;
        packet[2] = 0x04;
        packet[3] = 0x1C;
        packet[4] = 0xFF;
        packet_size = 5;
        return true;

    case visca::ViscaPackets::INQUIRY_CAM_MDWindowInq:
        // Check parameters.
        if (param_1 > 3)
            return false;
        packet[0] = (0x80 | (uint8_t)camera_address);
        packet[1] = 0x09;
        packet[2] = 0x04;
        packet[3] = 0x1D;
        packet[4] = (uint8_t)param_1;
        packet[5] = 0xFF;
        packet_size = 6;
        return true;

    case visca::ViscaPackets::INQUIRY_CAM_ContinuousZoomPosReplyModeInq:
        packet[0] = (0x80 | (uint8_t)camera_address);
        packet[1] = 0x09;
        packet[2] = 0x04;
        packet[3] = 0x69;
        packet[4] = 0xFF;
        packet_size = 5;
        return true;

    case visca::ViscaPackets::INQUIRY_CAM_ZoomPosReplyIntervalTimeInq:
        packet[0] = (0x80 | (uint8_t)camera_address);
        packet[1] = 0x09;
        packet[2] = 0x04;
        packet[3] = 0x6A;
        packet[4] = 0xFF;
        packet_size = 5;
        return true;

    case visca::ViscaPackets::INQUIRY_CAM_ContinuousFocusPosReplyModeInq:
        packet[0] = (0x80 | (uint8_t)camera_address);
        packet[1] = 0x09;
        packet[2] = 0x04;
        packet[3] = 0x16;
        packet[4] = 0xFF;
        packet_size = 5;
        return true;

    case visca::ViscaPackets::INQUIRY_CAM_FocusReplyIntervalTimeInq:
        packet[0] = (0x80 | (uint8_t)camera_address);
        packet[1] = 0x09;
        packet[2] = 0x04;
        packet[3] = 0x1A;
        packet[4] = 0xFF;
        packet_size = 5;
        return true;

    case visca::ViscaPackets::INQUIRY_CAM_RegisterValueInq:
        // Check parameters.
        if (param_1 > 0x7F)
            return false;
        packet[0] = (0x80 | (uint8_t)camera_address);
        packet[1] = 0x09;
        packet[2] = 0x04;
        packet[3] = 0x24;
        packet[4] = (uint8_t)param_1;
        packet[5] = 0xFF;
        packet_size = 6;
        return true;

    case visca::ViscaPackets::INQUIRY_CAM_ChromaSuppressInq:
        packet[0] = (0x80 | (uint8_t)camera_address);
        packet[1] = 0x09;
        packet[2] = 0x04;
        packet[3] = 0x5F;
        packet[4] = 0xFF;
        packet_size = 5;
        return true;

    case visca::ViscaPackets::INQUIRY_CAM_ColorGainInq:
        packet[0] = (0x80 | (uint8_t)camera_address);
        packet[1] = 0x09;
        packet[2] = 0x04;
        packet[3] = 0x49;
        packet[4] = 0xFF;
        packet_size = 5;
        return true;

    case visca::ViscaPackets::INQUIRY_CAM_ColorHueInq:
        packet[0] = (0x80 | (uint8_t)camera_address);
        packet[1] = 0x09;
        packet[2] = 0x04;
        packet[3] = 0x4F;
        packet[4] = 0xFF;
        packet_size = 5;
        return true;

    case visca::ViscaPackets::INQUIRY_CAM_TempInq:
        packet[0] = (0x80 | (uint8_t)camera_address);
        packet[1] = 0x09;
        packet[2] = 0x04;
        packet[3] = 0x4F;
        packet[4] = 0xFF;
        packet_size = 5;
        return true;

    case visca::ViscaPackets::INQUIRY_CAM_GammaOffsetInq:
        packet[0] = (0x80 | (uint8_t)camera_address);
        packet[1] = 0x09;
        packet[2] = 0x04;
        packet[3] = 0x1E;
        packet[4] = 0xFF;
        packet_size = 5;
        return true;

    case visca::ViscaPackets::INQUIRY_CAM_ContrastAdjLevelInq:
        packet[0] = (0x80 | (uint8_t)camera_address);
        packet[1] = 0x09;
        packet[2] = 0x05;
        packet[3] = 0x5D;
        packet[4] = 0xFF;
        packet_size = 5;
        return true;

    case visca::ViscaPackets::INQUIRY_CAM_ExExpCompPosInq:
        packet[0] = (0x80 | (uint8_t)camera_address);
        packet[1] = 0x09;
        packet[2] = 0x04;
        packet[3] = 0x1F;
        packet[4] = 0x4E;
        packet[5] = 0xFF;
        packet_size = 6;
        return true;

    case visca::ViscaPackets::INQUIRY_CAM_ExApertureInq:
        packet[0] = (0x80 | (uint8_t)camera_address);
        packet[1] = 0x09;
        packet[2] = 0x04;
        packet[3] = 0x1F;
        packet[4] = 0x42;
        packet[5] = 0xFF;
        packet_size = 6;
        return true;

    case visca::ViscaPackets::INQUIRY_CAM_ExColorGainInq:
        packet[0] = (0x80 | (uint8_t)camera_address);
        packet[1] = 0x09;
        packet[2] = 0x04;
        packet[3] = 0x1F;
        packet[4] = 0x49;
        packet[5] = 0x00;
        packet[6] = 0xFF;
        packet_size = 7;
        return true;

    case visca::ViscaPackets::INQUIRY_CAM_ExColorHueInq:
        packet[0] = (0x80 | (uint8_t)camera_address);
        packet[1] = 0x09;
        packet[2] = 0x04;
        packet[3] = 0x1F;
        packet[4] = 0x4F;
        packet[5] = 0x00;
        packet[6] = 0xFF;
        packet_size = 7;
        return true;

    case visca::ViscaPackets::INQUIRY_CAM_ExAutoICRThresholdInq:
        packet[0] = (0x80 | (uint8_t)camera_address);
        packet[1] = 0x09;
        packet[2] = 0x04;
        packet[3] = 0x1F;
        packet[4] = 0x21;
        packet[5] = 0x00;
        packet[6] = 0xFF;
        packet_size = 7;
        return true;

    case visca::ViscaPackets::INQUIRY_CAM_ExAutoICROnLevelInq:
        packet[0] = (0x80 | (uint8_t)camera_address);
        packet[1] = 0x09;
        packet[2] = 0x04;
        packet[3] = 0x1F;
        packet[4] = 0x21;
        packet[5] = 0x01;
        packet[6] = 0xFF;
        packet_size = 7;
        return true;

    case visca::ViscaPackets::INQUIRY_CAM_MinShutterInq:
        packet[0] = (0x80 | (uint8_t)camera_address);
        packet[1] = 0x09;
        packet[2] = 0x04;
        packet[3] = 0x12;
        packet[4] = 0xFF;
        packet_size = 5;
        return true;

    case visca::ViscaPackets::INQUIRY_CAM_MinShutterLimitInq:
        packet[0] = (0x80 | (uint8_t)camera_address);
        packet[1] = 0x09;
        packet[2] = 0x04;
        packet[3] = 0x13;
        packet[4] = 0xFF;
        packet_size = 5;
        return true;

    case visca::ViscaPackets::INQUIRY_CAM_HLCInq:
        packet[0] = (0x80 | (uint8_t)camera_address);
        packet[1] = 0x09;
        packet[2] = 0x04;
        packet[3] = 0x14;
        packet[4] = 0xFF;
        packet_size = 5;
        return true;

    case visca::ViscaPackets::INQUIRY_CAM_FlickerReductionInq:
        packet[0] = (0x80 | (uint8_t)camera_address);
        packet[1] = 0x09;
        packet[2] = 0x04;
        packet[3] = 0x32;
        packet[4] = 0xFF;
        packet_size = 5;
        return true;

    case visca::ViscaPackets::INQUIRY_LenseControlSystemInq:
        packet[0] = (0x80 | (uint8_t)camera_address);
        packet[1] = 0x09;
        packet[2] = 0x7E;
        packet[3] = 0x7E;
        packet[4] = 0x00;
        packet[5] = 0xFF;
        packet_size = 6;
        return true;

    case visca::ViscaPackets::INQUIRY_CameraControlSystemInq:
        packet[0] = (0x80 | (uint8_t)camera_address);
        packet[1] = 0x09;
        packet[2] = 0x7E;
        packet[3] = 0x7E;
        packet[4] = 0x01;
        packet[5] = 0xFF;
        packet_size = 6;
        return true;

    case visca::ViscaPackets::INQUIRY_OtherDataInq:
        packet[0] = (0x80 | (uint8_t)camera_address);
        packet[1] = 0x09;
        packet[2] = 0x7E;
        packet[3] = 0x7E;
        packet[4] = 0x02;
        packet[5] = 0xFF;
        packet_size = 6;
        return true;

    case visca::ViscaPackets::INQUIRY_ExtendedFunction_1_Inq:
        packet[0] = (0x80 | (uint8_t)camera_address);
        packet[1] = 0x09;
        packet[2] = 0x7E;
        packet[3] = 0x7E;
        packet[4] = 0x03;
        packet[5] = 0xFF;
        packet_size = 6;
        return true;

    case visca::ViscaPackets::INQUIRY_ExtendedFunction_2_Inq:
        packet[0] = (0x80 | (uint8_t)camera_address);
        packet[1] = 0x09;
        packet[2] = 0x7E;
        packet[3] = 0x7E;
        packet[4] = 0x04;
        packet[5] = 0xFF;
        packet_size = 6;
        return true;

    case visca::ViscaPackets::INQUIRY_ExtendedFunction_3_Inq:
        packet[0] = (0x80 | (uint8_t)camera_address);
        packet[1] = 0x09;
        packet[2] = 0x7E;
        packet[3] = 0x7E;
        packet[4] = 0x05;
        packet[5] = 0xFF;
        packet_size = 6;
        return true;    
    
    default:
        return false;
    }

    return false;
}


visca::ViscaPackets visca::ViscaProtocolParser::Decode_Data(
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
            uint32_t& param_10)
{
    param_1 = 0;
    param_2 = 0;
    param_3 = 0;
    param_4 = 0;
    param_5 = 0;
    param_6 = 0;
    param_7 = 0;
    param_8 = 0;
    param_9 = 0;
    param_10 = 0;

    // Check camera address.
    if (camera_address < 1 || camera_address > 7)
        return visca::ViscaPackets::UNDEFINED_PACKET;

    // Check decoding stage.
    if (input_data_counter == 0)
    {
        input_packet_type = visca::ViscaPackets::UNDEFINED_PACKET;

        // Check first byte.
        uint8_t first_byte = ((uint8_t)(camera_address + 8) << 4) & 0xF0;
        if (first_byte != next_byte)
            return visca::ViscaPackets::UNDEFINED_PACKET;

        // Copy data to buffer.
        input_packet_data[input_data_counter] = next_byte;
        // Update counter.
        input_data_counter = 1;

        return visca::ViscaPackets::UNDEFINED_PACKET;
    }
    else
    {
        // Check packet index.
        if (input_data_counter == 1)
        {
            // Check Acknowledge packet.
            if ((next_byte & 0xF0) == 0x40)
            {
                // Set packet type.
                input_packet_type = visca::ViscaPackets::ACKNOWLEDGE;
                // Copy data.
                input_packet_data[input_data_counter] = next_byte;
                // Update counter.
                ++input_data_counter;

                return visca::ViscaPackets::UNDEFINED_PACKET;
            }

            // Check Completion (Commands) or Reply data (Inquiries).
            if ((next_byte & 0xF0) == 0x50)
            {
                // Set packet type.
                input_packet_type = visca::ViscaPackets::COMPLETION_COMMANDS;
                // Copy data.
                input_packet_data[input_data_counter] = next_byte;
                // Update counter.
                ++input_data_counter;

                return visca::ViscaPackets::UNDEFINED_PACKET;
            }

            // Check error messages.
            if ((next_byte & 0xF0) == 0x60)
            {
                // Set packet type.
                input_packet_type = visca::ViscaPackets::ERROR_Message_Length;
                // Copy data.
                input_packet_data[input_data_counter] = next_byte;
                // Update counter.
                ++input_data_counter;

                return visca::ViscaPackets::UNDEFINED_PACKET;
            }

            // Check Alarm and reply packets.
            if (next_byte == 0x07)
            {
                input_packet_type = visca::ViscaPackets::REPLY;
                // Copy data.
                input_packet_data[input_data_counter] = next_byte;
                // Update counter.
                ++input_data_counter;

                return visca::ViscaPackets::UNDEFINED_PACKET;
            }

            // Reset counter.
            input_data_counter = 0;

            return visca::ViscaPackets::UNDEFINED_PACKET;
        }
        else
        {
            // Check packet type.
            switch (input_packet_type)
            {
            case visca::ViscaPackets::ACKNOWLEDGE:
            {
                // Check last byte.
                if (next_byte != 0xFF)
                {
                    // Reset counter.
                    input_data_counter = 0;

                    return visca::ViscaPackets::UNDEFINED_PACKET;
                }

                // Return socket number.
                param_1 = 0x0F & input_packet_data[1];

                // Reset counter.
                input_data_counter = 0;

                // Check packet type.
                return visca::ViscaPackets::ACKNOWLEDGE;
            }

            case visca::ViscaPackets::COMPLETION_COMMANDS:
            {
                // Check last byte.
                if (next_byte == 0xFF)
                {
                    // Return socket number.
                    param_1 = 0x0F & input_packet_data[1];

                    // Reset counter.
                    input_data_counter = 0;

                    // Check packet type.
                    return visca::ViscaPackets::COMPLETION_COMMANDS;
                }

                // Check second byte.
                if (input_packet_data[1] != 0x50)
                {
                    // Reset counter.
                    input_data_counter = 0;

                    return visca::ViscaPackets::UNDEFINED_PACKET;
                }

                input_packet_type = visca::ViscaPackets::COMPLETION_INQUIRY;

                input_packet_data[input_data_counter] = next_byte;

                // Update counter.
                ++input_data_counter;

                return visca::ViscaPackets::UNDEFINED_PACKET;
            }

            case visca::ViscaPackets::COMPLETION_INQUIRY:
            {
                // Check last byte.
                if (next_byte == 0xFF)
                {
                    // Add data to bufer.
                    input_packet_data[input_data_counter] = next_byte;
                    ++input_data_counter;

                    // Decode reply.
                    return Decode_Reply(input_packet_data, input_data_counter, param_1, param_2, param_3, param_4, param_5, param_6, param_7, param_8, param_9, param_10);
                }

                // Check reply size.
                if (input_data_counter > 15)
                {
                    // Reset counter.
                    input_data_counter = 0;

                    return visca::ViscaPackets::UNDEFINED_PACKET;
                }

                input_packet_data[input_data_counter] = next_byte;

                // Update counter.
                ++input_data_counter;

                return visca::ViscaPackets::UNDEFINED_PACKET;
            }

            case visca::ViscaPackets::ERROR_Message_Length:
            {
                // Check message type.
                if (input_data_counter < 3)
                {
                    input_packet_data[input_data_counter] = next_byte;

                    // Update counter.
                    ++input_data_counter;

                    return visca::ViscaPackets::UNDEFINED_PACKET;
                }
                else
                {
                    if (next_byte != 0xFF)
                    {
                        // Reset counter.
                        input_data_counter = 0;

                        return visca::ViscaPackets::UNDEFINED_PACKET;
                    }

                    // Check error type.
                    switch (input_packet_data[2])
                    {
                    case 0x01:
                        // Reset counter.
                        input_data_counter = 0;
                        // Return result.
                        return visca::ViscaPackets::ERROR_Message_Length;
                    case 0x02:
                        // Reset counter.
                        input_data_counter = 0;
                        // Return result.
                        return visca::ViscaPackets::ERROR_Syntax;
                    case 0x03:
                        // Reset counter.
                        input_data_counter = 0;
                        // Return result.
                        return visca::ViscaPackets::ERROR_Command_Buffer_Full;
                    case 0x04:
                        // Reset counter.
                        input_data_counter = 0;
                        // Return result.
                        return visca::ViscaPackets::ERROR_Command_Canceled;
                    case 0x05:
                        // Reset counter.
                        input_data_counter = 0;
                        // Return result.
                        return visca::ViscaPackets::ERROR_No_Socket;
                    case 0x41:
                        // Reset counter.
                        input_data_counter = 0;
                        // Return result.
                        return visca::ViscaPackets::ERROR_Command_Not_Executable;
                    default:
                        // Reset counter.
                        input_data_counter = 0;
                        // Return result.
                        return visca::ViscaPackets::UNDEFINED_PACKET;
                    }

                    return visca::ViscaPackets::UNDEFINED_PACKET;
                }
            }

            case visca::ViscaPackets::REPLY:
            {
                // Check last byte.
                if (next_byte == 0xFF)
                {
                    // Add data to bufer.
                    input_packet_data[input_data_counter] = next_byte;
                    ++input_data_counter;

                    // Check packet size.
                    if (input_data_counter == 6)
                    {
                        // Check AutoICRAlarmReply On.
                        if (input_packet_data[2] == 0x04 && input_packet_data[3] == 0x31 && input_packet_data[4] == 0x02)
                        {
                            // Reset counter.
                            input_data_counter = 0;

                            return visca::ViscaPackets::REPLY_CAM_AutoICRAlarmReply_On;
                        }

                        // Check AutoICRAlarmReply Off.
                        if (input_packet_data[2] == 0x04 && input_packet_data[3] == 0x31 && input_packet_data[4] == 0x03)
                        {
                            // Reset counter.
                            input_data_counter = 0;

                            return visca::ViscaPackets::REPLY_CAM_AutoICRAlarmReply_Off;
                        }

                        // Check MD Alarm.
                        if (input_packet_data[2] == 0x04 && input_packet_data[3] == 0x1B)
                        {
                            param_1 = input_packet_data[4] & 0x0F;

                            // Reset counter.
                            input_data_counter = 0;

                            return visca::ViscaPackets::REPLY_CAM_MD_Alarm;
                        }

                        // Reset counter.
                        input_data_counter = 0;

                        return visca::ViscaPackets::UNDEFINED_PACKET;
                    }
                    else
                    {
                        if (input_data_counter == 11)
                        {
                            // Check Continious zoom position reply.
                            if (input_packet_data[2] == 0x04 && input_packet_data[3] == 0x69)
                            {
                                param_1 = input_packet_data[4] & 0x0F;
                                param_2 = input_packet_data[5] & 0x0F;
                                param_3 = input_packet_data[6] & 0x0F;
                                param_4 = input_packet_data[7] & 0x0F;
                                param_5 = input_packet_data[8] & 0x0F;
                                param_6 = input_packet_data[9] & 0x0F;

                                return visca::ViscaPackets::REPLY_CAM_ContinuousZoomPos;
                            }

                            // Check Continious focus position reply.
                            if (input_packet_data[2] == 0x04 && input_packet_data[3] == 0x16)
                            {
                                param_1 = input_packet_data[6] & 0x0F;
                                param_2 = input_packet_data[7] & 0x0F;
                                param_3 = input_packet_data[8] & 0x0F;
                                param_4 = input_packet_data[9] & 0x0F;

                                return visca::ViscaPackets::REPLY_CAM_ContinuousFocusPos;
                            }

                            // Reset counter.
                            input_data_counter = 0;

                            return visca::ViscaPackets::UNDEFINED_PACKET;
                        }
                        else
                        {
                            // Reset counter.
                            input_data_counter = 0;

                            return visca::ViscaPackets::UNDEFINED_PACKET;
                        }
                    }
                }

                // Check reply size.
                if (input_data_counter > 10)
                {
                    // Reset counter.
                    input_data_counter = 0;

                    return visca::ViscaPackets::UNDEFINED_PACKET;
                }

                input_packet_data[input_data_counter] = next_byte;

                // Update counter.
                ++input_data_counter;

                return visca::ViscaPackets::UNDEFINED_PACKET;
            }

            default:
                break;
            }

            // Reset counter.
            input_data_counter = 0;

            // Check packet type.
            return visca::ViscaPackets::UNDEFINED_PACKET;

        }

    }

    return visca::ViscaPackets::UNDEFINED_PACKET;
}


visca::ViscaPackets visca::ViscaProtocolParser::Decode_Reply(
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
    uint32_t& param_10)
{
    param_1 = 0;
    param_2 = 0;
    param_3 = 0;
    param_4 = 0;
    param_5 = 0;
    param_6 = 0;
    param_7 = 0;
    param_8 = 0;
    param_9 = 0;
    param_10 = 0;

    // Reset data counter.
    input_data_counter = 0;

    // Check last encoded command.
    switch (last_encoded_command)
    {
    /*
    ENQUIRY COMMANDS.
    */
    case visca::ViscaPackets::INQUIRY_CAM_PowerInq:
        if (packet_size != 4)
            return visca::ViscaPackets::UNDEFINED_PACKET;
        if (packet_data[2] == 0x02)
            return visca::ViscaPackets::REPLY_CAM_Power_On;
        if (packet_data[2] == 0x03)
            return visca::ViscaPackets::REPLY_CAM_Power_Off;
        return visca::ViscaPackets::UNDEFINED_PACKET;

    case visca::ViscaPackets::INQUIRY_CAM_ZoomPosInq:
        if (packet_size != 7)
            return visca::ViscaPackets::UNDEFINED_PACKET;
        param_1 = packet_data[2] & 0x0F;
        param_2 = packet_data[3] & 0x0F;
        param_3 = packet_data[4] & 0x0F;
        param_4 = packet_data[5] & 0x0F;
        return visca::ViscaPackets::REPLY_CAM_ZoomPos;

    case visca::ViscaPackets::INQUIRY_CAM_DZoomModeInq:
        if (packet_size != 4)
            return visca::ViscaPackets::UNDEFINED_PACKET;
        if (packet_data[2] == 0x02)
            return visca::ViscaPackets::REPLY_CAM_DZoomMode_On;
        if (packet_data[2] == 0x03)
            return visca::ViscaPackets::REPLY_CAM_DZoomMode_Off;
        return visca::ViscaPackets::UNDEFINED_PACKET;

    case visca::ViscaPackets::INQUIRY_CAM_DZoom_C_S_ModeInq:
        if (packet_size != 4)
            return visca::ViscaPackets::UNDEFINED_PACKET;
        if (packet_data[2] == 0x00)
            return visca::ViscaPackets::REPLY_CAM_DZoom_Combine_Mode;
        if (packet_data[2] == 0x01)
            return visca::ViscaPackets::REPLY_CAM_DZoom_Separate_Mode;
        return visca::ViscaPackets::UNDEFINED_PACKET;

    case visca::ViscaPackets::INQUIRY_CAM_DZoomPosInq:
        if (packet_size != 7)
            return visca::ViscaPackets::UNDEFINED_PACKET;
        if (packet_data[2] != 0x00 || packet_data[3] != 0x00)
            return visca::ViscaPackets::UNDEFINED_PACKET;
        param_1 = packet_data[4] & 0x0F;
        param_2 = packet_data[5] & 0x0F;
        return visca::ViscaPackets::REPLY_CAM_DZoomPos;

    case visca::ViscaPackets::INQUIRY_CAM_FocusModeInq:
        if (packet_size != 4)
            return visca::ViscaPackets::UNDEFINED_PACKET;
        if (packet_data[2] == 0x02)
            return visca::ViscaPackets::REPLY_CAM_FocusMode_Auto_Focus;
        if (packet_data[2] == 0x03)
            return visca::ViscaPackets::REPLY_CAM_FocusMode_Manual_Focus;
        return visca::ViscaPackets::UNDEFINED_PACKET;

    case visca::ViscaPackets::INQUIRY_CAM_FocusPosInq:
        if (packet_size != 7)
            return visca::ViscaPackets::UNDEFINED_PACKET;
        param_1 = packet_data[2] & 0x0F;
        param_2 = packet_data[3] & 0x0F;
        param_3 = packet_data[4] & 0x0F;
        param_4 = packet_data[5] & 0x0F;
        return visca::ViscaPackets::REPLY_CAM_FocusPos;

    case visca::ViscaPackets::INQUIRY_CAM_FocusNearLimitInq:
        if (packet_size != 7)
            return visca::ViscaPackets::UNDEFINED_PACKET;
        param_1 = packet_data[2] & 0x0F;
        param_2 = packet_data[3] & 0x0F;
        param_3 = packet_data[4] & 0x0F;
        param_4 = packet_data[5] & 0x0F;
        return visca::ViscaPackets::REPLY_CAM_FocusNearLimit;

    case visca::ViscaPackets::INQUIRY_CAM_AFSensitivityInq:
        if (packet_size != 4)
            return visca::ViscaPackets::UNDEFINED_PACKET;
        if (packet_data[2] == 0x02)
            return visca::ViscaPackets::REPLY_CAM_AFSensitivity_Normal;
        if (packet_data[2] == 0x03)
            return visca::ViscaPackets::REPLY_CAM_AFSensitivity_Low;
        return visca::ViscaPackets::UNDEFINED_PACKET;

    case visca::ViscaPackets::INQUIRY_CAM_AFModeInq:
        if (packet_size != 4)
            return visca::ViscaPackets::UNDEFINED_PACKET;
        if (packet_data[2] == 0x00)
            return visca::ViscaPackets::REPLY_CAM_AFMode_Normal_AF;
        if (packet_data[2] == 0x01)
            return visca::ViscaPackets::REPLY_CAM_AFMode_Interval_AF;
        if (packet_data[2] == 0x02)
            return visca::ViscaPackets::REPLY_CAM_AFMode_Zoom_Trigger_AF;
        return visca::ViscaPackets::UNDEFINED_PACKET;

    case visca::ViscaPackets::INQUIRY_CAM_AFTimeSettingInq:
        if (packet_size != 7)
            return visca::ViscaPackets::UNDEFINED_PACKET;
        param_1 = packet_data[2] & 0x0F;
        param_2 = packet_data[3] & 0x0F;
        param_3 = packet_data[4] & 0x0F;
        param_4 = packet_data[5] & 0x0F;
        return visca::ViscaPackets::REPLY_CAM_AFTimeSetting;

    case visca::ViscaPackets::INQUIRY_CAM_IRCorrectionInq:
        if (packet_size != 4)
            return visca::ViscaPackets::UNDEFINED_PACKET;
        if (packet_data[2] == 0x00)
            return visca::ViscaPackets::REPLY_CAM_IRCorrection_Standard;
        if (packet_data[2] == 0x01)
            return visca::ViscaPackets::REPLY_CAM_IRCorrection_IR_Light;
        return visca::ViscaPackets::UNDEFINED_PACKET;

    case visca::ViscaPackets::INQUIRY_CAM_WBModeInq:
        if (packet_size != 4)
            return visca::ViscaPackets::UNDEFINED_PACKET;
        if (packet_data[2] == 0x00)
            return visca::ViscaPackets::REPLY_CAM_WBMode_Auto;
        if (packet_data[2] == 0x01)
            return visca::ViscaPackets::REPLY_CAM_WBMode_Indoor;
        if (packet_data[2] == 0x02)
            return visca::ViscaPackets::REPLY_CAM_WBMode_Outdoor;
        if (packet_data[2] == 0x03)
            return visca::ViscaPackets::REPLY_CAM_WBMode_One_Push_WB;
        if (packet_data[2] == 0x04)
            return visca::ViscaPackets::REPLY_CAM_WBMode_ATW;
        if (packet_data[2] == 0x05)
            return visca::ViscaPackets::REPLY_CAM_WBMode_Manual;
        if (packet_data[2] == 0x06)
            return visca::ViscaPackets::REPLY_CAM_WBMode_Outdoor_Auto;
        if (packet_data[2] == 0x07)
            return visca::ViscaPackets::REPLY_CAM_WBMode_Sodium_Lamp_Auto;
        if (packet_data[2] == 0x08)
            return visca::ViscaPackets::REPLY_CAM_WBMode_Sodium_Lamp;
        if (packet_data[2] == 0x09)
            return visca::ViscaPackets::REPLY_CAM_WBMode_Sodium_Lamp_Outdoor_Auto;
        return visca::ViscaPackets::UNDEFINED_PACKET;

    case visca::ViscaPackets::INQUIRY_CAM_RGainInq:
        if (packet_size != 7)
            return visca::ViscaPackets::UNDEFINED_PACKET;
        if (packet_data[2] != 0x00 || packet_data[3] != 0x00)
            return visca::ViscaPackets::UNDEFINED_PACKET;
        param_1 = packet_data[4] & 0x0F;
        param_2 = packet_data[5] & 0x0F;
        return visca::ViscaPackets::REPLY_CAM_RGain;

    case visca::ViscaPackets::INQUIRY_CAM_BGainInq:
        if (packet_size != 7)
            return visca::ViscaPackets::UNDEFINED_PACKET;
        if (packet_data[2] != 0x00 || packet_data[3] != 0x00)
            return visca::ViscaPackets::UNDEFINED_PACKET;
        param_1 = packet_data[4] & 0x0F;
        param_2 = packet_data[5] & 0x0F;
        return visca::ViscaPackets::REPLY_CAM_BGain;

    case visca::ViscaPackets::INQUIRY_CAM_AEModeInq:
        if (packet_size != 4)
            return visca::ViscaPackets::UNDEFINED_PACKET;
        if (packet_data[2] == 0x00)
            return visca::ViscaPackets::REPLY_CAM_AEMode_Full_Auto;
        if (packet_data[2] == 0x03)
            return visca::ViscaPackets::REPLY_CAM_AEMode_Manual;
        if (packet_data[2] == 0x0A)
            return visca::ViscaPackets::REPLY_CAM_AEMode_Shutter_Priority;
        if (packet_data[2] == 0x0B)
            return visca::ViscaPackets::REPLY_CAM_AEMode_Iris_Priority;
        return visca::ViscaPackets::UNDEFINED_PACKET;

    case visca::ViscaPackets::INQUIRY_CAM_AutoSlowShutterInq:
        if (packet_size != 4)
            return visca::ViscaPackets::UNDEFINED_PACKET;
        if (packet_data[2] == 0x02)
            return visca::ViscaPackets::REPLY_CAM_AutoSlowShutter_On;
        if (packet_data[2] == 0x03)
            return visca::ViscaPackets::REPLY_CAM_AutoSlowShutter_Off;
        return visca::ViscaPackets::UNDEFINED_PACKET;

    case visca::ViscaPackets::INQUIRY_CAM_ShutterPosInq:
        if (packet_size != 7)
            return visca::ViscaPackets::UNDEFINED_PACKET;
        if (packet_data[2] != 0x00 || packet_data[3] != 0x00)
            return visca::ViscaPackets::UNDEFINED_PACKET;
        param_1 = packet_data[4] & 0x0F;
        param_2 = packet_data[5] & 0x0F;
        return visca::ViscaPackets::REPLY_CAM_ShutterPos;

    case visca::ViscaPackets::INQUIRY_CAM_IrisPosInq:
        if (packet_size != 7)
            return visca::ViscaPackets::UNDEFINED_PACKET;
        if (packet_data[2] != 0x00 || packet_data[3] != 0x00)
            return visca::ViscaPackets::UNDEFINED_PACKET;
        param_1 = packet_data[4] & 0x0F;
        param_2 = packet_data[5] & 0x0F;
        return visca::ViscaPackets::REPLY_CAM_IrisPos;

    case visca::ViscaPackets::INQUIRY_CAM_GainPosInq:
        if (packet_size != 7)
            return visca::ViscaPackets::UNDEFINED_PACKET;
        if (packet_data[2] != 0x00 || packet_data[3] != 0x00)
            return visca::ViscaPackets::UNDEFINED_PACKET;
        param_1 = packet_data[4] & 0x0F;
        param_2 = packet_data[5] & 0x0F;
        return visca::ViscaPackets::REPLY_CAM_GainPos;

    case visca::ViscaPackets::INQUIRY_CAM_GainLimitInq:
        if (packet_size != 4)
            return visca::ViscaPackets::UNDEFINED_PACKET;
        param_1 = packet_data[2] & 0x0F;
        return visca::ViscaPackets::REPLY_CAM_GainLimit;

    case visca::ViscaPackets::INQUIRY_CAM_ExpCompModeInq:
        if (packet_size != 4)
            return visca::ViscaPackets::UNDEFINED_PACKET;
        if (packet_data[2] == 0x02)
            return visca::ViscaPackets::REPLY_CAM_ExpCompMode_On;
        if (packet_data[2] == 0x03)
            return visca::ViscaPackets::REPLY_CAM_ExpCompMode_Off;
        return visca::ViscaPackets::UNDEFINED_PACKET;

    case visca::ViscaPackets::INQUIRY_CAM_ExpCompPosInq:
        if (packet_size != 7)
            return visca::ViscaPackets::UNDEFINED_PACKET;
        if (packet_data[2] != 0x00 || packet_data[3] != 0x00)
            return visca::ViscaPackets::UNDEFINED_PACKET;
        param_1 = packet_data[4] & 0x0F;
        param_2 = packet_data[5] & 0x0F;
        return visca::ViscaPackets::REPLY_CAM_ExpCompPos;

    case visca::ViscaPackets::INQUIRY_CAM_BackLightModeInq:
        if (packet_size != 4)
            return visca::ViscaPackets::UNDEFINED_PACKET;
        if (packet_data[2] == 0x02)
            return visca::ViscaPackets::REPLY_CAM_BackLightMode_On;
        if (packet_data[2] == 0x03)
            return visca::ViscaPackets::REPLY_CAM_BackLightMode_Off;
        return visca::ViscaPackets::UNDEFINED_PACKET;

    case visca::ViscaPackets::INQUIRY_CAM_SpotAEModeInq:
        if (packet_size != 4)
            return visca::ViscaPackets::UNDEFINED_PACKET;
        if (packet_data[2] == 0x02)
            return visca::ViscaPackets::REPLY_CAM_SpotAEMode_On;
        if (packet_data[2] == 0x03)
            return visca::ViscaPackets::REPLY_CAM_SpotAEMode_Off;
        return visca::ViscaPackets::UNDEFINED_PACKET;

    case visca::ViscaPackets::INQUIRY_CAM_SpotAEPosInq:
        if (packet_size != 7)
            return visca::ViscaPackets::UNDEFINED_PACKET;
        param_1 = packet_data[2] & 0x0F;
        param_2 = packet_data[3] & 0x0F;
        param_3 = packet_data[4] & 0x0F;
        param_4 = packet_data[5] & 0x0F;
        return visca::ViscaPackets::REPLY_CAM_SpotAEPos;

    case visca::ViscaPackets::INQUIRY_CAM_VEModeInq:
        if (packet_size != 4)
            return visca::ViscaPackets::UNDEFINED_PACKET;
        if (packet_data[2] == 0x03)
            return visca::ViscaPackets::REPLY_CAM_VEMode_Off;
        if (packet_data[2] == 0x06)
            return visca::ViscaPackets::REPLY_CAM_VEMode_On;
        return visca::ViscaPackets::UNDEFINED_PACKET;

    case visca::ViscaPackets::INQUIRY_CAM_VEParameterInq:
        if (packet_size != 11)
            return visca::ViscaPackets::UNDEFINED_PACKET;
        if (packet_data[2] != 0 || packet_data[8] != 0 || packet_data[9] != 0)
            return visca::ViscaPackets::UNDEFINED_PACKET;
        param_1 = packet_data[3] & 0x0F;
        param_2 = packet_data[4] & 0x0F;
        param_3 = packet_data[5] & 0x0F;
        param_4 = packet_data[6] & 0x0F;
        param_5 = packet_data[7] & 0x0F;
        return visca::ViscaPackets::REPLY_CAM_VEParameter;

    case visca::ViscaPackets::INQUIRY_CAM_WDModeInq:
        if (packet_size != 4)
            return visca::ViscaPackets::UNDEFINED_PACKET;
        if (packet_data[2] == 0x02)
            return visca::ViscaPackets::REPLY_CAM_WDMode_WD_On;
        if (packet_data[2] == 0x03)
            return visca::ViscaPackets::REPLY_CAM_WDMode_WD_and_VE_Off;
        if (packet_data[2] == 0x06)
            return visca::ViscaPackets::REPLY_CAM_WDMode_VE_On;
        return visca::ViscaPackets::UNDEFINED_PACKET;

    case visca::ViscaPackets::INQUIRY_CAM_WDParameterInq:
        if (packet_size != 11)
            return visca::ViscaPackets::UNDEFINED_PACKET;
        if (packet_data[2] != 0 || packet_data[8] != 0 || packet_data[9] != 0)
            return visca::ViscaPackets::UNDEFINED_PACKET;
        param_1 = packet_data[3] & 0x0F;
        param_2 = packet_data[4] & 0x0F;
        param_3 = packet_data[5] & 0x0F;
        param_4 = packet_data[6] & 0x0F;
        param_5 = packet_data[7] & 0x0F;
        return visca::ViscaPackets::REPLY_CAM_WDParameter;

    case visca::ViscaPackets::INQUIRY_CAM_AEResponseInq:
        if (packet_size != 4)
            return visca::ViscaPackets::UNDEFINED_PACKET;
        if (packet_data[2] < 0x01 || packet_data[2] > 0x30)
            return visca::ViscaPackets::UNDEFINED_PACKET;
        param_1 = packet_data[2];
        return visca::ViscaPackets::REPLY_CAM_AEResponse;

    case visca::ViscaPackets::INQUIRY_CAM_DefogInq:
        if (packet_size != 5)
            return visca::ViscaPackets::UNDEFINED_PACKET;
        if (packet_data[2] == 0x03 && packet_data[3] == 0x00)
            return visca::ViscaPackets::REPLY_CAM_Defog_Off;
        if (packet_data[2] == 0x02)
        {
            if (packet_data[3] != 0x01 && packet_data[3] != 0x02 && packet_data[4] != 0x03)
                return visca::ViscaPackets::UNDEFINED_PACKET;
            param_1 = packet_data[3];
            return visca::ViscaPackets::REPLY_CAM_Defog_Level;
        }
        return visca::ViscaPackets::UNDEFINED_PACKET;

    case visca::ViscaPackets::INQUIRY_CAM_ApertureInq:
        if (packet_size != 7)
            return visca::ViscaPackets::UNDEFINED_PACKET;
        if (packet_data[2] != 0x00 || packet_data[3] != 0x00)
            return visca::ViscaPackets::UNDEFINED_PACKET;
        param_1 = packet_data[4] & 0x0F;
        param_2 = packet_data[5] & 0x0F;
        return visca::ViscaPackets::REPLY_CAM_Aperture;

    case visca::ViscaPackets::INQUIRY_CAM_NRInq:
        if (packet_size != 4)
            return visca::ViscaPackets::UNDEFINED_PACKET;
        param_1 = packet_data[2];
        return visca::ViscaPackets::REPLY_CAM_NR;

    case visca::ViscaPackets::INQUIRY_CAM_NR2D3Dinq:
        if (packet_size != 5)
            return visca::ViscaPackets::UNDEFINED_PACKET;
        if (packet_data[2] > 0x05 || packet_data[3] > 0x05)
            return visca::ViscaPackets::UNDEFINED_PACKET;
        param_1 = packet_data[2];
        param_2 = packet_data[3];
        return visca::ViscaPackets::REPLY_CAM_NR2D3D;

    case visca::ViscaPackets::INQUIRY_CAM_GammaInq:
        if (packet_size != 4)
            return visca::ViscaPackets::UNDEFINED_PACKET;
        if (packet_data[2] > 0x01)
            return visca::ViscaPackets::UNDEFINED_PACKET;
        param_1 = packet_data[2];
        return visca::ViscaPackets::REPLY_CAM_Gamma;

    case visca::ViscaPackets::INQUIRY_CAM_HighSensitivityInq:
        if (packet_size != 4)
            return visca::ViscaPackets::UNDEFINED_PACKET;
        if (packet_data[2] == 0x02)
            return visca::ViscaPackets::REPLY_CAM_HighSensitivity_On;
        if (packet_data[2] == 0x03)
            return visca::ViscaPackets::REPLY_CAM_HighSensitivity_Off;
        return visca::ViscaPackets::UNDEFINED_PACKET;

    case visca::ViscaPackets::INQUIRY_CAM_LR_ReverseModeInq:
        if (packet_size != 4)
            return visca::ViscaPackets::UNDEFINED_PACKET;
        if (packet_data[2] == 0x02)
            return visca::ViscaPackets::REPLY_CAM_LR_ReverseMode_On;
        if (packet_data[2] == 0x03)
            return visca::ViscaPackets::REPLY_CAM_LR_ReverseMode_Off;
        return visca::ViscaPackets::UNDEFINED_PACKET;

    case visca::ViscaPackets::INQUIRY_CAM_FreezeModeInq:
        if (packet_size != 4)
            return visca::ViscaPackets::UNDEFINED_PACKET;
        if (packet_data[2] == 0x02)
            return visca::ViscaPackets::REPLY_CAM_FreezeMode_On;
        if (packet_data[2] == 0x03)
            return visca::ViscaPackets::REPLY_CAM_FreezeMode_Off;
        return visca::ViscaPackets::UNDEFINED_PACKET;

    case visca::ViscaPackets::INQUIRY_CAM_PictureEffectModeInq:
        if (packet_size != 4)
            return visca::ViscaPackets::UNDEFINED_PACKET;
        if (packet_data[2] == 0x00)
            return visca::ViscaPackets::REPLY_CAM_PictureEffectMode_Off;
        if (packet_data[2] == 0x04)
            return visca::ViscaPackets::REPLY_CAM_PictureEffectMode_Black_and_White;
        return visca::ViscaPackets::UNDEFINED_PACKET;

    case visca::ViscaPackets::INQUIRY_CAM_PictureFlipModeInq:
        if (packet_size != 4)
            return visca::ViscaPackets::UNDEFINED_PACKET;
        if (packet_data[2] == 0x02)
            return visca::ViscaPackets::REPLY_CAM_PictureFlipMode_On;
        if (packet_data[2] == 0x03)
            return visca::ViscaPackets::REPLY_CAM_PictureFlipMode_Off;
        return visca::ViscaPackets::UNDEFINED_PACKET;

    case visca::ViscaPackets::INQUIRY_CAM_ICRModeInq:
        if (packet_size != 4)
            return visca::ViscaPackets::UNDEFINED_PACKET;
        if (packet_data[2] == 0x02)
            return visca::ViscaPackets::REPLY_CAM_ICRMode_On;
        if (packet_data[2] == 0x03)
            return visca::ViscaPackets::REPLY_CAM_ICRMode_Off;
        return visca::ViscaPackets::UNDEFINED_PACKET;

    case visca::ViscaPackets::INQUIRY_CAM_AutoICRModeInq:
        if (packet_size != 4)
            return visca::ViscaPackets::UNDEFINED_PACKET;
        if (packet_data[2] == 0x02)
            return visca::ViscaPackets::REPLY_CAM_AutoICRMode_On;
        if (packet_data[2] == 0x03)
            return visca::ViscaPackets::REPLY_CAM_AutoICRMode_Off;
        return visca::ViscaPackets::UNDEFINED_PACKET;

    case visca::ViscaPackets::INQUIRY_CAM_AutoICRThresholdInq:
        if (packet_size != 7)
            return visca::ViscaPackets::UNDEFINED_PACKET;
        if (packet_data[2] != 0x00 || packet_data[3] != 0x00)
            return visca::ViscaPackets::UNDEFINED_PACKET;
        param_1 = packet_data[4] & 0x0F;
        param_2 = packet_data[5] & 0x0F;
        return visca::ViscaPackets::REPLY_CAM_AutoICRThreshold;

    case visca::ViscaPackets::INQUIRY_CAM_AutoICRAlarmReplyInq:
        if (packet_size != 4)
            return visca::ViscaPackets::UNDEFINED_PACKET;
        if (packet_data[2] == 0x02)
            return visca::ViscaPackets::REPLY_CAM_AutoICRAlarmReply_On;
        if (packet_data[2] == 0x03)
            return visca::ViscaPackets::REPLY_CAM_AutoICRAlarmReply_Off;
        return visca::ViscaPackets::UNDEFINED_PACKET;

    case visca::ViscaPackets::INQUIRY_CAM_MemoryInq:
        if (packet_size != 4)
            return visca::ViscaPackets::UNDEFINED_PACKET;
        param_1 = packet_data[2];
        return visca::ViscaPackets::REPLY_CAM_Memory;

    case visca::ViscaPackets::INQUIRY_CAM_MemSaveInq:
        if (packet_size != 7)
            return visca::ViscaPackets::UNDEFINED_PACKET;
        param_1 = packet_data[2] & 0x0F;
        param_2 = packet_data[3] & 0x0F;
        param_3 = packet_data[4] & 0x0F;
        param_4 = packet_data[5] & 0x0F;
        return visca::ViscaPackets::REPLY_CAM_MemSave;

    case visca::ViscaPackets::INQUIRY_CAM_DisplayModeInq:
        if (packet_size != 4)
            return visca::ViscaPackets::UNDEFINED_PACKET;
        if (packet_data[2] == 0x02)
            return visca::ViscaPackets::REPLY_CAM_DisplayMode_On;
        if (packet_data[2] == 0x03)
            return visca::ViscaPackets::REPLY_CAM_DisplayMode_Off;
        return visca::ViscaPackets::UNDEFINED_PACKET;

    case visca::ViscaPackets::INQUIRY_CAM_StabilizerModeInq:
        if (packet_size != 4)
            return visca::ViscaPackets::UNDEFINED_PACKET;
        if (packet_data[2] == 0x02)
            return visca::ViscaPackets::REPLY_CAM_StabilizerMode_On;
        if (packet_data[2] == 0x03)
            return visca::ViscaPackets::REPLY_CAM_StabilizerMode_Off;
        if (packet_data[2] == 0x00)
            return visca::ViscaPackets::REPLY_CAM_StabilizerMode_Hold;
        return visca::ViscaPackets::UNDEFINED_PACKET;

    case visca::ViscaPackets::INQUIRY_CAM_MuteModeInq:
        if (packet_size != 4)
            return visca::ViscaPackets::UNDEFINED_PACKET;
        if (packet_data[2] == 0x02)
            return visca::ViscaPackets::REPLY_CAM_MuteMode_On;
        if (packet_data[2] == 0x03)
            return visca::ViscaPackets::REPLY_CAM_MuteMode_Off;
        return visca::ViscaPackets::UNDEFINED_PACKET;

    case visca::ViscaPackets::INQUIRY_CAM_PrivacyDisplayInq:
        if (packet_size != 7)
            return visca::ViscaPackets::UNDEFINED_PACKET;
        param_1 = packet_data[2];
        param_2 = packet_data[3];
        param_3 = packet_data[4];
        param_4 = packet_data[5];
        return visca::ViscaPackets::REPLY_CAM_PrivacyDisplay;

    case visca::ViscaPackets::INQUIRY_CAM_PrivacyPanTiltInq:
        if (packet_size != 9)
            return visca::ViscaPackets::UNDEFINED_PACKET;
        param_1 = packet_data[2] & 0x0F;
        param_2 = packet_data[3] & 0x0F;
        param_3 = packet_data[4] & 0x0F;
        param_4 = packet_data[5] & 0x0F;
        param_5 = packet_data[6] & 0x0F;
        param_6 = packet_data[7] & 0x0F;
        return visca::ViscaPackets::REPLY_CAM_PrivacyPanTilt;

    case visca::ViscaPackets::INQUIRY_CAM_PrivacyPTZInq:
        if (packet_size != 13)
            return visca::ViscaPackets::UNDEFINED_PACKET;
        param_1 = packet_data[2] & 0x0F;
        param_2 = packet_data[3] & 0x0F;
        param_3 = packet_data[4] & 0x0F;
        param_4 = packet_data[5] & 0x0F;
        param_5 = packet_data[6] & 0x0F;
        param_6 = packet_data[7] & 0x0F;
        param_7 = packet_data[8] & 0x0F;
        param_8 = packet_data[9] & 0x0F;
        param_9 = packet_data[10] & 0x0F;
        param_10 = packet_data[11] & 0x0F;
        return visca::ViscaPackets::REPLY_CAM_PrivacyPTZ;

    case visca::ViscaPackets::INQUIRY_CAM_PrivacyMonitorInq:
        if (packet_size != 7)
            return visca::ViscaPackets::UNDEFINED_PACKET;
        param_1 = packet_data[2];
        param_2 = packet_data[3];
        param_3 = packet_data[4];
        param_4 = packet_data[5];
        return visca::ViscaPackets::REPLY_CAM_PrivacyMonitor;

    case visca::ViscaPackets::INQUIRY_CAM_IDInq:
        if (packet_size != 7)
            return visca::ViscaPackets::UNDEFINED_PACKET;
        param_1 = packet_data[2] & 0x0F;
        param_2 = packet_data[3] & 0x0F;
        param_3 = packet_data[4] & 0x0F;
        param_4 = packet_data[5] & 0x0F;
        return visca::ViscaPackets::REPLY_CAM_ID;

    case visca::ViscaPackets::INQUIRY_CAM_VersionInq:
        if (packet_size != 10)
            return visca::ViscaPackets::UNDEFINED_PACKET;
        if (packet_data[2] != 0x00 || packet_data[3] != 0x20)
            return visca::ViscaPackets::UNDEFINED_PACKET;
        param_1 = packet_data[4];
        param_2 = packet_data[5];
        param_3 = packet_data[6];
        param_4 = packet_data[7];
        param_5 = packet_data[8];
        return visca::ViscaPackets::REPLY_CAM_Version;

    case visca::ViscaPackets::INQUIRY_CAM_MDModeInq:
        if (packet_size != 4)
            return visca::ViscaPackets::UNDEFINED_PACKET;
        if (packet_data[2] == 0x02)
            return visca::ViscaPackets::REPLY_CAM_MDMode_On;
        if (packet_data[2] == 0x03)
            return visca::ViscaPackets::REPLY_CAM_MDMode_Off;
        return visca::ViscaPackets::UNDEFINED_PACKET;

    case visca::ViscaPackets::INQUIRY_CAM_MDFunctionInq:
        if (packet_size != 9)
            return visca::ViscaPackets::UNDEFINED_PACKET;
        param_1 = packet_data[2] & 0x0F;
        param_2 = packet_data[3] & 0x0F;
        param_3 = packet_data[4] & 0x0F;
        param_4 = packet_data[5] & 0x0F;
        param_5 = packet_data[6] & 0x0F;
        param_6 = packet_data[7] & 0x0F;
        return visca::ViscaPackets::REPLY_CAM_MDFunction;

    case visca::ViscaPackets::INQUIRY_CAM_MDWindowInq:
        if (packet_size != 7)
            return visca::ViscaPackets::UNDEFINED_PACKET;
        param_1 = packet_data[2];
        param_2 = packet_data[3] & 0x0F;
        param_3 = packet_data[4];
        param_4 = packet_data[5] & 0x0F;
        return visca::ViscaPackets::REPLY_CAM_MDWindow;

    case visca::ViscaPackets::INQUIRY_CAM_ContinuousZoomPosReplyModeInq:
        if (packet_size != 4)
            return visca::ViscaPackets::UNDEFINED_PACKET;
        if (packet_data[2] == 0x02)
            return visca::ViscaPackets::REPLY_CAM_ContinuousZoomPosReplyMode_On;
        if (packet_data[2] == 0x03)
            return visca::ViscaPackets::REPLY_CAM_ContinuousZoomPosReplyMode_Off;
        return visca::ViscaPackets::UNDEFINED_PACKET;

    case visca::ViscaPackets::INQUIRY_CAM_ZoomPosReplyIntervalTimeInq:
        if (packet_size != 7)
            return visca::ViscaPackets::UNDEFINED_PACKET;
        if (packet_data[2] != 0x00 || packet_data[3] != 0x00)
            return visca::ViscaPackets::UNDEFINED_PACKET;
        param_1 = packet_data[4] & 0x0F;
        param_2 = packet_data[5] & 0x0F;
        return visca::ViscaPackets::REPLY_CAM_ZoomPosReplyIntervalTime;

    case visca::ViscaPackets::INQUIRY_CAM_ContinuousFocusPosReplyModeInq:
        if (packet_size != 4)
            return visca::ViscaPackets::UNDEFINED_PACKET;
        if (packet_data[2] == 0x02)
            return visca::ViscaPackets::REPLY_CAM_ContinuousFocusPosReplyMode_On;
        if (packet_data[2] == 0x03)
            return visca::ViscaPackets::REPLY_CAM_ContinuousFocusPosReplyMode_Off;
        return visca::ViscaPackets::UNDEFINED_PACKET;

    case visca::ViscaPackets::INQUIRY_CAM_FocusReplyIntervalTimeInq:
        if (packet_size != 7)
            return visca::ViscaPackets::UNDEFINED_PACKET;
        if (packet_data[2] != 0x00 || packet_data[3] != 0x00)
            return visca::ViscaPackets::UNDEFINED_PACKET;
        param_1 = packet_data[4] & 0x0F;
        param_2 = packet_data[5] & 0x0F;
        return visca::ViscaPackets::REPLY_CAM_FocusReplyIntervalTime;

    case visca::ViscaPackets::INQUIRY_CAM_RegisterValueInq:
        if (packet_size != 5)
            return visca::ViscaPackets::UNDEFINED_PACKET;
        param_1 = packet_data[2] & 0x0F;
        param_2 = packet_data[3] & 0x0F;
        return visca::ViscaPackets::REPLY_CAM_RegisterValue;

    case visca::ViscaPackets::INQUIRY_CAM_ChromaSuppressInq:
        if (packet_size != 4)
            return visca::ViscaPackets::UNDEFINED_PACKET;
        param_1 = packet_data[2];
        return visca::ViscaPackets::REPLY_CAM_ChromaSuppress;

    case visca::ViscaPackets::INQUIRY_CAM_ColorGainInq:
        if (packet_size != 7)
            return visca::ViscaPackets::UNDEFINED_PACKET;
        if (packet_data[2] != 0x00 || packet_data[3] != 0x00 || packet_data[4] != 0x00)
            return visca::ViscaPackets::UNDEFINED_PACKET;
        param_1 = packet_data[5] & 0x0F;
        return visca::ViscaPackets::REPLY_CAM_ColorGain;

    case visca::ViscaPackets::INQUIRY_CAM_ColorHueInq:
        if (packet_size != 7)
            return visca::ViscaPackets::UNDEFINED_PACKET;
        if (packet_data[2] != 0x00 || packet_data[3] != 0x00 || packet_data[4] != 0x00)
            return visca::ViscaPackets::UNDEFINED_PACKET;
        param_1 = packet_data[5] & 0x0F;
        return visca::ViscaPackets::REPLY_CAM_ColorHue;

    case visca::ViscaPackets::INQUIRY_CAM_TempInq:
        if (packet_size != 7)
            return visca::ViscaPackets::UNDEFINED_PACKET;
        if (packet_data[2] != 0x00 || packet_data[3] != 0x00)
            return visca::ViscaPackets::UNDEFINED_PACKET;
        param_1 = packet_data[4] & 0x0F;
        param_2 = packet_data[5] & 0x0F;
        return visca::ViscaPackets::REPLY_CAM_Temp;

    case visca::ViscaPackets::INQUIRY_CAM_GammaOffsetInq:
        if (packet_size != 9)
            return visca::ViscaPackets::UNDEFINED_PACKET;
        if (packet_data[2] != 0x00 || packet_data[3] != 0x00 || packet_data[4] != 0x00)
            return visca::ViscaPackets::UNDEFINED_PACKET;
        param_1 = packet_data[5] & 0x0F;
        param_2 = packet_data[6] & 0x0F;
        param_3 = packet_data[7] & 0x0F;
        return visca::ViscaPackets::REPLY_CAM_GammaOffset;

    case visca::ViscaPackets::INQUIRY_CAM_ContrastAdjLevelInq:
        if (packet_size != 5)
            return visca::ViscaPackets::UNDEFINED_PACKET;
        param_1 = packet_data[2] & 0x0F;
        param_2 = packet_data[3] & 0x0F;
        return visca::ViscaPackets::REPLY_CAM_ContrastAdjLevel;

    case visca::ViscaPackets::INQUIRY_CAM_ExExpCompPosInq:
        if (packet_size != 7)
            return visca::ViscaPackets::UNDEFINED_PACKET;
        if (packet_data[2] != 0x00 || packet_data[3] != 0x00)
            return visca::ViscaPackets::UNDEFINED_PACKET;
        param_1 = packet_data[4] & 0x0F;
        param_2 = packet_data[5] & 0x0F;
        return visca::ViscaPackets::REPLY_CAM_ExExpCompPos;

    case visca::ViscaPackets::INQUIRY_CAM_ExApertureInq:
        if (packet_size != 7)
            return visca::ViscaPackets::UNDEFINED_PACKET;
        if (packet_data[2] != 0x00 || packet_data[3] != 0x00)
            return visca::ViscaPackets::UNDEFINED_PACKET;
        param_1 = packet_data[4] & 0x0F;
        param_2 = packet_data[5] & 0x0F;
        return visca::ViscaPackets::REPLY_CAM_Aperture;

    case visca::ViscaPackets::INQUIRY_CAM_ExColorGainInq:
        if (packet_size != 5)
            return visca::ViscaPackets::UNDEFINED_PACKET;
        param_1 = packet_data[2] & 0x0F;
        param_2 = packet_data[3] & 0x0F;
        return visca::ViscaPackets::REPLY_CAM_ExColorGain;

    case visca::ViscaPackets::INQUIRY_CAM_ExColorHueInq:
        if (packet_size != 5)
            return visca::ViscaPackets::UNDEFINED_PACKET;
        param_1 = packet_data[2] & 0x0F;
        param_2 = packet_data[3] & 0x0F;
        return visca::ViscaPackets::REPLY_CAM_ExColorHue;

    case visca::ViscaPackets::INQUIRY_CAM_ExAutoICRThresholdInq:
        if (packet_size != 7)
            return visca::ViscaPackets::UNDEFINED_PACKET;
        if (packet_data[2] != 0x00 || packet_data[3] != 0x00)
            return visca::ViscaPackets::UNDEFINED_PACKET;
        param_1 = packet_data[4] & 0x0F;
        param_2 = packet_data[5] & 0x0F;
        return visca::ViscaPackets::REPLY_CAM_ExAutoICRThreshold;

    case visca::ViscaPackets::INQUIRY_CAM_ExAutoICROnLevelInq:
        if (packet_size != 7)
            return visca::ViscaPackets::UNDEFINED_PACKET;
        if (packet_data[2] != 0x00 || packet_data[3] != 0x00)
            return visca::ViscaPackets::UNDEFINED_PACKET;
        param_1 = packet_data[4] & 0x0F;
        param_2 = packet_data[5] & 0x0F;
        return visca::ViscaPackets::REPLY_CAM_ExAutoICROnLevel;

    case visca::ViscaPackets::INQUIRY_CAM_MinShutterInq:
        if (packet_size != 4)
            return visca::ViscaPackets::UNDEFINED_PACKET;
        if (packet_data[2] == 0x02)
            return visca::ViscaPackets::REPLY_CAM_MinShutter_On;
        if (packet_data[2] == 0x03)
            return visca::ViscaPackets::REPLY_CAM_MinShutter_Off;
        return visca::ViscaPackets::UNDEFINED_PACKET;

    case visca::ViscaPackets::INQUIRY_CAM_MinShutterLimitInq:
        if (packet_size != 7)
            return visca::ViscaPackets::UNDEFINED_PACKET;
        if (packet_data[2] != 0x00 || packet_data[3] != 0x00)
            return visca::ViscaPackets::UNDEFINED_PACKET;
        param_1 = packet_data[4] & 0x0F;
        param_2 = packet_data[5] & 0x0F;
        return visca::ViscaPackets::REPLY_CAM_MinShutterLimit;

    case visca::ViscaPackets::INQUIRY_CAM_HLCInq:
        if (packet_size != 5)
            return visca::ViscaPackets::UNDEFINED_PACKET;
        param_1 = packet_data[2] & 0x0F;
        param_2 = packet_data[3] & 0x0F;
        return visca::ViscaPackets::REPLY_CAM_HLC;

    case visca::ViscaPackets::INQUIRY_CAM_FlickerReductionInq:
        if (packet_size != 4)
            return visca::ViscaPackets::UNDEFINED_PACKET;
        if (packet_data[2] == 0x02)
            return visca::ViscaPackets::REPLY_CAM_FlickerReduction_On;
        if (packet_data[2] == 0x03)
            return visca::ViscaPackets::REPLY_CAM_FlickerReduction_Off;
        return visca::ViscaPackets::UNDEFINED_PACKET;

    case visca::ViscaPackets::INQUIRY_LenseControlSystemInq:
    {
        if (packet_size != 16)
            return visca::ViscaPackets::UNDEFINED_PACKET;
        uint8_t zoom_pos_1 = packet_data[2] & 0x0F;
        uint8_t zoom_pos_2 = packet_data[3] & 0x0F;
        uint8_t zoom_pos_3 = packet_data[4] & 0x0F;
        uint8_t zoom_pos_4 = packet_data[5] & 0x0F;
        param_1 = (uint32_t)(((zoom_pos_1 << 4) & 0xF0) + zoom_pos_2) * 256 + (uint32_t)(((zoom_pos_3 << 4) & 0xF0) + zoom_pos_4);
        uint8_t focus_near_limit_1 = packet_data[6] & 0x0F;
        uint8_t focus_near_limit_2 = packet_data[7] & 0x0F;
        param_2 = ((focus_near_limit_1 << 4) & 0xF0) + focus_near_limit_2;
        uint8_t focus_pos_1 = packet_data[8] & 0x0F;
        uint8_t focus_pos_2 = packet_data[9] & 0x0F;
        uint8_t focus_pos_3 = packet_data[10] & 0x0F;
        uint8_t focus_pos_4 = packet_data[11] & 0x0F;
        param_3 = (uint32_t)(((focus_pos_1 << 4) & 0xF0) + focus_pos_2) * 256 + (uint32_t)(((focus_pos_3 << 4) & 0xF0) + focus_pos_4);
        param_4 = packet_data[13];
        param_5 = packet_data[14];

        return visca::ViscaPackets::REPLY_LenseControlSystem;
    }

    case visca::ViscaPackets::INQUIRY_CameraControlSystemInq:
    {
        if (packet_size != 16)
            return visca::ViscaPackets::UNDEFINED_PACKET;
        uint8_t r_gain_1 = packet_data[2] & 0x0F;
        uint8_t r_gain_2 = packet_data[3] & 0x0F;
        param_1 = ((r_gain_1 << 4) & 0xF0) + r_gain_2;
        uint8_t b_gain_1 = packet_data[4] & 0x0F;
        uint8_t b_gain_2 = packet_data[5] & 0x0F;
        param_2 = ((b_gain_1 << 4) & 0xF0) + b_gain_2;
        param_3 = packet_data[6] & 0x0F;
        param_4 = packet_data[7] & 0x0F;
        param_5 = packet_data[8] & 0x0F;
        param_6 = packet_data[9];
        param_7 = packet_data[10];
        param_8 = packet_data[11];
        param_9 = packet_data[12];
        param_10 = packet_data[14];

        return visca::ViscaPackets::REPLY_CameraControlSystem;
    }

    case visca::ViscaPackets::INQUIRY_OtherDataInq:
    {
        if (packet_size != 16)
            return visca::ViscaPackets::UNDEFINED_PACKET;
        param_1 = packet_data[2] & 0x0F;
        param_2 = packet_data[3];
        param_3 = packet_data[4];
        param_4 = packet_data[5];
        uint8_t camera_id_1 = packet_data[8] & 0x0F;
        uint8_t camera_id_2 = packet_data[9] & 0x0F;
        uint8_t camera_id_3 = packet_data[10] & 0x0F;
        uint8_t camera_id_4 = packet_data[11] & 0x0F;
        param_5 = (uint32_t)(((camera_id_1 << 4) & 0xF0) + camera_id_2) * 256 + (uint32_t)(((camera_id_3 << 4) & 0xF0) + camera_id_4);
        param_6 = packet_data[12];

        return visca::ViscaPackets::REPLY_OtherData;
    }

    case visca::ViscaPackets::INQUIRY_ExtendedFunction_1_Inq:
    {
        if (packet_size != 16)
            return visca::ViscaPackets::UNDEFINED_PACKET;
        uint8_t d_zoom_pos_1 = packet_data[2] & 0x0F;
        uint8_t d_zoom_pos_2 = packet_data[3] & 0x0F;
        param_1 = ((d_zoom_pos_1 << 4) & 0xF0) + d_zoom_pos_2;
        uint8_t af_activation_time_1 = packet_data[4] & 0x0F;
        uint8_t af_activation_time_2 = packet_data[5] & 0x0F;
        param_2 = ((af_activation_time_1 << 4) & 0xF0) + af_activation_time_2;
        uint8_t af_interval_time_1 = packet_data[6] & 0x0F;
        uint8_t af_interval_time_2 = packet_data[7] & 0x0F;
        param_3 = ((af_interval_time_1 << 4) & 0xF0) + af_interval_time_2;
        param_4 = packet_data[8];
        param_5 = packet_data[9];
        param_6 = packet_data[10];
        param_7 = packet_data[11];
        param_8 = packet_data[12];
        param_9 = packet_data[13];
        param_10 = packet_data[14];

        return visca::ViscaPackets::REPLY_ExtendedFunction_1;
    }

    case visca::ViscaPackets::INQUIRY_ExtendedFunction_2_Inq:
    {
        if (packet_size != 16)
            return visca::ViscaPackets::UNDEFINED_PACKET;
        param_1 = packet_data[2];
        param_2 = packet_data[4];
        param_3 = packet_data[5];
        param_4 = packet_data[6];
        param_5 = packet_data[7];
        param_6 = packet_data[8];

        return visca::ViscaPackets::REPLY_ExtendedFunction_2;
    }

    case visca::ViscaPackets::INQUIRY_ExtendedFunction_3_Inq:
    {
        if (packet_size != 16)
            return visca::ViscaPackets::UNDEFINED_PACKET;
        param_1 = packet_data[2];

        return visca::ViscaPackets::REPLY_ExtendedFunction_3;
    }

    default:
        break;
    }

    // Reset data counter.
    input_data_counter = 0;

    return visca::ViscaPackets::UNDEFINED_PACKET;
}





