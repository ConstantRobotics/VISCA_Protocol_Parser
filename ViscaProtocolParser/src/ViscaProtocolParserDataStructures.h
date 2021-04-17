#pragma once
#include <cstdint>


namespace visca
{
    // Enum of VISCA packets type.
    enum class ViscaPackets
    {
        /*
        Not VISCA packets.
        */
        UNDEFINED_PACKET,

        /*
        ERROR MESSAGES.
        */
        ERROR_Message_Length,
        ERROR_Syntax,
        ERROR_Command_Buffer_Full,
        ERROR_Command_Canceled,
        ERROR_No_Socket,
        ERROR_Command_Not_Executable,

        /*
        COMMAND MESSAGES.
        */

        /// Address setting. Parameters: camera address.
        COMMAND_AddressSet,

        /// Clears the command buffers in the camera and cancels the command currently being executed. No parameters.
        COMMAND_IF_Clear_Broadcast,
        /// Clears the command buffers in the camera and cancels the command currently being executed. Parameters: camera address.
        COMMAND_IF_Clear,

        /// Cancels the command currently being executed. Parameters: camera address, param_1 - socet number (1 or 2).
        COMMAND_CommandCancel,

        /// Camera power On. Parameters: camera address.
        COMMAND_CAM_Power_On,
        /// Camera power Off (Standby). Parameters: camera address.
        COMMAND_CAM_Power_Off,

        /// Zoom stop. Parameters: camera address.
        COMMAND_CAM_Zoom_Stop,
        /// Zoom tele. Parameters: camera address.
        COMMAND_CAM_Zoom_Tele,
        /// Zoom wide. Parameters: camera address.
        COMMAND_CAM_Zoom_Wide,
        /// Zoom tele with variable speed. Parameters: camera_address, param_1 - speed (0 - low, 7 - high).
        COMMAND_CAM_Zoom_Tele_Variable,
        /// Zoom wide with variable speed. Parameters: camera_address, param_1 - speed (0 - low, 7 - high).
        COMMAND_CAM_Zoom_Wide_Variable,
        /// Direct zoom position. Parameters: camera address, param_1 - zoom position, param_2 - zoom position, param_3 - zoom position, param_4 - zoom position.
        COMMAND_CAM_Zoom_Direct,

        /// Digital zoom On. Parameters: camera address.
        COMMAND_CAM_DZoom_On,
        /// Digital zoom Off. Parameters: camera address.
        COMMAND_CAM_DZoom_Off,
        /// Optical/Digital Zoom Combined.
        COMMAND_CAM_DZoom_Combine_Mode,
        /// Optical/Digital Zoom Separate.
        COMMAND_CAM_DZoom_Separate_Mode,
        /// Digital zoom Stop.
        COMMAND_CAM_DZoom_Stop,
        /// Digital zoom tele with variable speed. Enabled during Separate Mode. Parameters: camera_address, param_1 - speed (0 - low, 7 - high).
        COMMAND_CAM_DZoom_Tele_Variable,
        /// Digital zoom wide with variable speed. Enabled during Separate Mode. Parameters: camera_address, param_1 - speed (0 - low, 7 - high).
        COMMAND_CAM_DZoom_Wide_Variable,
        /// Direct digital zoom position. Enabled during Separate Mode. Parameters: camera address, param_1 - zoom position.
        COMMAND_CAM_DZoom_Direct,

        /// Focus Stop. Parameters: camera address.
        COMMAND_CAM_Focus_Stop,
        /// Focus Far. Parameters: camera address.
        COMMAND_CAM_Focus_Far,
        /// Focus Near. Parameters: camera address.
        COMMAND_CAM_Focus_Near,
        /// Focus Far with variable speed. Parameters: camera address.
        COMMAND_CAM_Focus_Far_Variable,
        /// Focus Near with variable speed. Parameters: camera address.
        COMMAND_CAM_Focus_Near_Variable,
        /// Direct focus position. Parameters: camera address, param_1 - focus position, param_2 - focus position, param_3 - focus position, param_4 - focus position.
        COMMAND_CAM_Focus_Direct,
        /// Auto focus On. Parameters: camera address.
        COMMAND_CAM_Focus_Auto_Focus_On,
        /// Manual focus On. Parameters: camera address.
        COMMAND_CAM_Focus_Manual_Focus_On,
        /// Auto or Manual focus. Parameters: camera address.
        COMMAND_CAM_Focus_Auto_Manual,
        /// Auto focus one push trigger. Parameters: camera address.
        COMMAND_CAM_Focus_One_Push_Trigger,
        /// Auto focus Full Scan One Push Trigger. Parameters: camera address.
        COMMAND_CAM_Focus_Full_Scan_One_Push_Trigger,
        /// Focus near limit position. Parameters: camera address, param_1 - Focus Near Limit Position.
        COMMAND_CAM_Focus_Near_Limit,

        /// Auto focus sensetivitu normal. Parameters: camera address.
        COMMAND_CAM_AFSensitivity_Normal,
        /// Auto focus sensetivitu low. Parameters: camera address.
        COMMAND_CAM_AFSensitivity_Low,

        /// Auto focus Movement Mode Normal. Parameters: camera address.
        COMMAND_CAM_AFMode_Normal_AF,
        /// Auto focus Movement Mode Interval. Parameters: camera address.
        COMMAND_CAM_AFMode_Interval_AF,
        /// Auto focus Movement Mode Zoom Trigger. Parameters: camera address.
        COMMAND_CAM_AFMode_Zoom_Trigger_AF,
        /// Auto focus Movement Mode Active/Interval Time. Parameters: camera address, param_1 - Movement Time, param_2 - Interval.
        COMMAND_CAM_AFMode_Active_or_Interval_Time,

        /// Focus IR compensation data standard. Parameters: camera address.
        COMMAND_CAM_IRCorrection_Standard,
        /// Focus IR compensation data IR light. Parameters: camera address.
        COMMAND_CAM_IRCorrection_IR_Light,

        /// Direct zoom and focus position. Parameters: camera address, param_1 - zoom position, param_2 - focus position.
        COMMAND_CAM_ZoomFocus_Direct,

        /// Lens Initialization Start. Parameters: camera address.
        COMMAND_CAM_Initialize_Lens,
        /// Camera reset. Parameters: camera address.
        COMMAND_CAM_Initialize_Camera,

        /// White balance Normal Auto. Parameters: camera address.
        COMMAND_CAM_WB_Auto,
        /// White balance Indoor mode. Parameters: camera address.
        COMMAND_CAM_WB_Indoor,
        /// White balance Outdoor mode. Parameters: camera address.
        COMMAND_CAM_WB_Outdoor,
        /// White balance One Push mode. Parameters: camera address.
        COMMAND_CAM_WB_One_Push_WB,
        /// White balance Auto Tracing. Parameters: camera address.
        COMMAND_CAM_WB_ATW,
        /// White balance Manual Control mode. Parameters: camera address.
        COMMAND_CAM_WB_Manual,
        /// White balance One Push Trigger. Parameters: camera address.
        COMMAND_CAM_WB_One_Push_Trigger,
        /// White balance Outdoor auto. Parameters: camera address.
        COMMAND_CAM_WB_Outdoor_Auto,
        /// White balance Auto including sodium lamp source. Parameters: camera address.
        COMMAND_CAM_WB_Sodium_Lamp_Auto,
        /// White balance Sodium lamp source fixed mode. Parameters: camera address.
        COMMAND_CAM_WB_Sodium_Lamp,
        /// White balance Outdoor auto including sodium lamp source. Parameters: camera address.
        COMMAND_CAM_WB_Sodium_Lamp_Outdoor_Auto,

        /// RGain Reset. Parameters: camera address.
        COMMAND_CAM_RGain_Reset,
        /// RGain Up. Parameters: camera address.
        COMMAND_CAM_RGain_Up,
        /// RGain Down. Parameters: camera address.
        COMMAND_CAM_RGain_Down,
        /// Direct value of RGain. Parameters: camera address, param_1 - RGain value.
        COMMAND_CAM_RGain_Direct,

        /// BGain Reset. Parameters: camera address.
        COMMAND_CAM_BGain_Reset,
        /// BGain Up. Parameters: camera address.
        COMMAND_CAM_BGain_Up,
        /// BGain Down. Parameters: camera address.
        COMMAND_CAM_BGain_Down,
        /// Direct value of BGain. Parameters: camera address, param_1 - BGain value.
        COMMAND_CAM_BGain_Direct,

        /// Auto Exposure mode. Parameters: camera address.
        COMMAND_CAM_AE_Full_Auto,
        /// Manual Exposure mode. Parameters: camera address.
        COMMAND_CAM_AE_Manual,
        /// Shutter Priority Auto Exposure mode. Parameters: camera address.
        COMMAND_CAM_AE_Shutter_Priority,
        /// Iris Priority Auto Exposure mode. Parameters: camera address.
        COMMAND_CAM_AE_Iris_Priority,

        /// Auto Slow Shutter On. Parameters: camera address.
        COMMAND_CAM_AutoSlowShutter_On,
        /// Auto Slow Shutter Off. Parameters: camera address.
        COMMAND_CAM_AutoSlowShutter_Off,

        /// Shutter Reset. Parameters: camera address.
        COMMAND_CAM_Shutter_Reset,
        /// Shutter Up. Parameters: camera address.
        COMMAND_CAM_Shutter_Up,
        /// Shutter Down. Parameters: camera address.
        COMMAND_CAM_Shutter_Down,
        /// Direct shutter position. Parameters: camera address, param_1 - Shutter position.
        COMMAND_CAM_Shutter_Direct,

        /// Iris Reset. Parameters: camera address.
        COMMAND_CAM_Iris_Reset,
        /// Iris Up. Parameters: camera address.
        COMMAND_CAM_Iris_Up,
        /// Iris Down. Parameters: camera address.
        COMMAND_CAM_Iris_Down,
        /// Direct iris position. Parameters: camera address, param_1 - Iris position.
        COMMAND_CAM_Iris_Direct,

        /// Gain reset. Parameters: camera address.
        COMMAND_CAM_Gain_Reset,
        /// Gain Up. Parameters: camera address.
        COMMAND_CAM_Gain_Up,
        /// Gain Down. Parameters: camera address.
        COMMAND_CAM_Gain_Down,
        /// Direct Gain value. Parameters: camera address, param_1 - Gain position.
        COMMAND_CAM_Gain_Direct,
        /// Direct Gain limit. Parameters: camera address, param_1 - Gain limit.
        COMMAND_CAM_Gain_Limit,

        /// Exposure Compensation On. Parameters: camera address.
        COMMAND_CAM_ExpComp_On,
        /// Exposure Compensation Off. Parameters: camera address.
        COMMAND_CAM_ExpComp__Off,
        /// Exposure Compensation Reset. Parameters: camera address.
        COMMAND_CAM_ExpComp_Reset,
        /// Exposure Compensation Up. Parameters: camera address.
        COMMAND_CAM_ExpComp_Up,
        /// Exposure Compensation Down. Parameters: camera address.
        COMMAND_CAM_ExpComp_Down,
        /// Direct position of Exposure Compensation. Parameters: camera address, param_1 - ExpComp Position.
        COMMAND_CAM_ExpComp_Direct,

        /// Back Light Compensation On. Parameters: camera address.
        COMMAND_CAM_BackLight_On,
        /// Back Light Compensation Off. Parameters: camera address.
        COMMAND_CAM_BackLight_Off,

        /// Spot Auto Exposure On. Parameters: camera address.
        COMMAND_CAM_SpotAE_On,
        /// Spot Auto Exposure Off. Parameters: camera address.
        COMMAND_CAM_SpotAE_Off,
        /// Spot Auto Exposure position. Parameters: camera address, param_1 - SpotAE position.
        COMMAND_CAM_SpotAE_Position,

        /// Auto Exposure Response Setting (01h to 30h). initial setting: 01h. Parameters: camera address, param_1 - value.
        COMMAND_CAM_AE_Response_Direct,

        /// VE On. Parameters: camera address.
        COMMAND_CAM_VE_On,
        /// VE Off. Parameters: camera address.
        COMMAND_CAM_VE_Off,
        /// VE Set Parameters. Parameters: camera address, param_1 - Display brightness level (0: Dark to 6: Bright), param_2 - Brightness compensation selection (0: Very dark, 1: Dark, 2: Standard, 3: Bright), param_3 - Compensation level (0: Low, 1: Mid, 2: High).
        COMMAND_CAM_VE_Set_Parameter,

        /// WD On. Parameters: camera address.
        COMMAND_CAM_WD_On,
        /// WD Off. Parameters: camera address.
        COMMAND_CAM_WD_Off,
        /// WS Set Parameters: Parameters: camera_address, param_1 - Display brightness level (0: Dark to 6: Bright), param_2 - Brightness compensation selection (0: Very dark, 1: Dark, 2: Standard, 3: Bright), param_3 - Compensation level (0: Low, 1: Mid, 2: High). 
        COMMAND_CAM_WD_Set_Parameter,

        /// Defog On. Parameters: camera_address, param_1 - Defog level (1: Low, 2: Mid, 3: High).
        COMMAND_CAM_Defog_On,
        /// Defog Off. Parameters: camera address.
        COMMAND_CAM_Defog_Off,

        /// Aperture Reset (aperture control). Parameters: camera_address.
        COMMAND_CAM_Aperture_Reset,
        /// Aperture Up (aperture control). Parameters: camera_address.
        COMMAND_CAM_Aperture_Up,
        /// Aperture Down (aperture control). Parameters: camera_address.
        COMMAND_CAM_Aperture_Down,
        /// Aperture Direct (aperture control). Parameters: camera_address, param_1 - aperture gain (from 0 to 15).
        COMMAND_CAM_Aperture_Direct,

        /// Noise reduction. Parameters: camera_address, param_1 - setting (0x00: Off, from 0x01 to 0x05: Level from 1 to 5, 0x7F: 2D/3D NR independend setting available).
        COMMAND_CAM_NR_Noise_Reduction,
        /// 2D/3D NR independent setting. Parameters: camera_address, param_1 - 2DNR level (0: Off, from 1 to 5: Level from 1 to 5), param_2 - 3DNR level (0: Off, from 1 to 5: Level from 1 to 5).
        COMMAND_CAM_NR_2D_3D_Independent_Setting,

        /// Gamma Setting. Parameters: camera_address, param_1 - 0: Standard, 1: Straight.
        COMMAND_CAM_Gamma,

        /// Camera hight sensetivity On. Parameters: camera_address.
        COMMAND_CAM_HighSensitivity_On,
        /// Camera hight sensetivity Off. Parameters: camera_address.
        COMMAND_CAM_HighSensitivity_Off,

        /// LR Reverse On. Parameters: camera_address.
        COMMAND_CAM_LR_Reverse_On,
        /// LR Reverse Off. Parameters: camera_address.
        COMMAND_CAM_LR_Reverse_Off,

        /// Camera Freeze On. Parameters: camera_address.
        COMMAND_CAM_Freeze_On,
        /// Camera Freeze Off. Parameters: camera_address.
        COMMAND_CAM_Freeze_Off,

        /// Picture effect Off. Parameters: camera_address.
        COMMAND_CAM_PictureEffect_Off,
        /// Picture effect Black & White. Parameters: camera_address.
        COMMAND_CAM_PictureEffect_Black_and_White,

        /// Minimum shutter On. Parameters: camera_address.
        COMMAND_CAM_MinShutter_On,
        /// Minimum shutter Off. Parameters: camera_address.
        COMMAND_CAM_MinShutter_Off,
        /// Minimum shutter Limit. Parameters: camera_address, param_1 - Minimum Shutter Position (from 0x05 to 0x14).
        COMMAND_CAM_MinShutter_Limit,

        /// Picture flip On. Parameters: camera_address.
        COMMAND_CAM_PictureFlip_On,
        /// Picture flip Off. Parameters: camera_address.
        COMMAND_CAM_PictureFlip_Off,

        /// ICR Mode On. Parameters: camera_address.
        COMMAND_CAM_ICR_On,
        /// ICR Mode Off. Parameters: camera_address.
        COMMAND_CAM_ICR_Off,

        /// Auto ICR Mode On. Parameters: camera_address.
        COMMAND_CAM_AutoICR_On,
        /// Auto ICR Mode Off. Parameters: camera_address.
        COMMAND_CAM_AutoICR_Off,
        /// Auto ICR Mode Threshold. Parameters: camera_address, param_1 - threshold level (from 0x00 to 0xFF).
        COMMAND_CAM_AutoICR_Threshold,

        /// Auto ICR switching Alarm On. Parameters: camera_address.
        COMMAND_CAM_AutoICRAlarmReply_On,
        /// Auto ICR switching Alarm Off. Parameters: camera_address.
        COMMAND_CAM_AutoICRAlarmReply_Off,

        /// Camera stabilizer On. Parameters: camera_address.
        COMMAND_CAM_Stabilizer_On,
        /// Camera stabilizer Off. Parameters: camera_address.
        COMMAND_CAM_Stabilizer_Off,
        /// Camera stabilizer Hold. Parameters: camera_address.
        COMMAND_CAM_Stabilizer_Hold,

        /// Camera memory Reset. Parameters: camera_address, param_1 - Memory Number (from 0x00 to 0x0F).
        COMMAND_CAM_Memory_Reset,
        /// Camera memory Set. Parameters: camera_address, param_1 - Memory Number (from 0x00 to 0x0F).
        COMMAND_CAM_Memory_Set,
        /// Camera memory Recall. Parameters: camera_address, param_1 - Memory Number (from 0x00 to 0x0F).
        COMMAND_CAM_Memory_Recall,

        /// Custom memory Reset: Starts up in this mode when the power is turned on. Parameter: camera_address.
        COMMAND_CAM_Custom_Reset,
        /// Custom memory Set: Starts up in this mode when the power is turned on. Parameter: camera_address.
        COMMAND_CAM_Custom_Set,
        /// Custom memory Recall: Starts up in this mode when the power is turned on. Parameter: camera_address.
        COMMAND_CAM_Custom_Recall,

        /// Write memory. Parameters: camera_address, param_1 - address (from 0x00 to 0x07), param_2 - data (from 0x0000 to 0xFFFF).
        COMMAND_CAM_MemSave_Write,

        /// Display On. Parameters: camera_address.
        COMMAND_CAM_Display_On,
        /// Display Off. Parameters: camera_address.
        COMMAND_CAM_Display_Off,
        /// Display On/Off switch. Parameters: camera_address.
        COMMAND_CAM_Display_On_Off_Switch,

        /// Multi line title 1 set. Parameters: camera_address, param_1 - Line Number (from 0x00 to 0x0F), param_2 - H position (from 0x00 to 0xFF), param_3 - color (from 0x00 to 0xFF), param_4 - blink (from 0x00 to 0xFF).
        COMMAND_CAM_MultiLineTitle_Title_Set_1,
        /// Multi line title 2 set. Parameters: camera_address, param_1 - param_1 - Setting of characters from 1 to 10.
        COMMAND_CAM_MultiLineTitle_Title_Set_2,
        /// Multi line title 3 set. Parameters: camera_address, param_1 - param_1 - Setting of characters from 11 to 20.
        COMMAND_CAM_MultiLineTitle_Title_Set_3,
        /// Clear title. Parameters: camera_address, param_1 - Title Setting clear (from 0x00 to 0x0A, 0x0F = all lines).
        COMMAND_CAM_MultiLineTitle_Title_Clear,
        /// Multi line title On. Parameters: camera_address, param_1 - Title display On (from 0x00 to 0x0A, 0x0F = all lines).
        COMMAND_CAM_MultiLineTitle_On,
        /// Multi line title Off. Parameters: camera_address, param_1 - Title display Off (from 0x00 to 0x0A, 0x0F = all lines).
        COMMAND_CAM_MultiLineTitle_Off,

        /// Muting On. Parameters: camera_address.
        COMMAND_CAM_Mute_On,
        /// Muting Off. Parameters: camera_address.
        COMMAND_CAM_Mute_Off,
        /// Muting On/Off. Parameters: camera_address.
        COMMAND_CAM_Mute_On_Off,

        /// Privacy zone masking. Parameters: camera_address, param_1 - Mask Settings (from 0x00 to 0xFF), param_2 - 0x00: Modify, 0x01: New, param_3 - W (from 0x00 to 0xFF), param_4 - H (from 0x00 to 0xFF).
        COMMAND_CAM_PrivacyZone_SetMask,
        /// Privacy Mask Display. Parameters: camera_address, param_1 - 0 (Off) or 1 (On), param_2 - 0 (Off) or 1 (On), param_3 - 0 (Off) or 1 (On), param_4 - 0 (Off) or 1 (On), param_5 - 0 (Off) or 1 (On), param_6 - 0 (Off) or 1 (On), param_7 - 0 (Off) or 1 (On), param_8 - 0 (Off) or 1 (On).
        COMMAND_CAM_PrivacyZone_Display,
        /// Privacy Mask Color Settings. Parameters: camera_address, param_1 - 0 (Off) or 1 (On), param_2 - 0 (Off) or 1 (On), param_3 - 0 (Off) or 1 (On), param_4 - 0 (Off) or 1 (On), param_5 - 0 (Off) or 1 (On), param_6 - 0 (Off) or 1 (On), param_7 - 0 (Off) or 1 (On), param_8 - 0 (Off) or 1 (On), param_9 - Color when 0 selected, param_10 - Color when 1 selected.
        COMMAND_CAM_PrivacyZone_SetMaskColor,
        /// Set pan-tilt angle. Parameters: camera_address, param_1 - Pan angle (from 0x000 to 0xFFF), param_2  - Tilt angle (from 0x000 to 0xFFF).
        COMMAND_CAM_PrivacyZone_SetPanTiltAngle,
        /// Pan/Tilt/Zoom Settings for Mask. Parameters: camera_address, param_1 - Mask Settings (from 0x00 to 0xFF), param_2 - Pan value (from 0x000 to 0xFFF), param_3 - Tilt value (from 0x000 to 0xFFF), param_4 - Zoom value (from 0x0000 to 0xFFFF).
        COMMAND_CAM_PrivacyZone_SetPTZMask,
        /// Non_Interlock Mask Settings. Parameters: camera_address, param_1 - Non_Interlock Mask Settings (from 0x00 to 0xFF), param_2 - X (from 0x00 to 0xFF), param_3 - Y (from 0x00 to 0xFF), param_4 - W (from 0x00 to 0xFF), param_5 - H (from 0x00 to 0xFF).
        COMMAND_CAM_PrivacyZone_Non_InterlockMask,
        /// Center Line Display Off. Parameters: camera_address.
        COMMAND_CAM_PrivacyZone_CenterLineOff,
        /// Center Line Display On. Para,eters: cemra_address.
        COMMAND_CAM_PrivacyZone_CenterLineOn,

        /// Write camera ID. Parameters: camera_address, param_1 - Camera ID (from 0x0000 to 0xFFFF).
        COMMAND_CAM_IDWrite,

        /// Motion detector On. Parameters: camera_address.
        COMMAND_CAM_MD_On,
        /// Motion detector On. Parameters: camera_address.
        COMMAND_CAM_MD_Off,
        /// Motion detector function set. Parameters: camera_address, param_1 - Display mode (from 0x00 to 0xFF), param_2 - Detection Frame Set (from 0x00 to 0x0F), param_3 - Threshold Level (from 0x00 to 0xFF), param_4 - Interval Time set (from 0x00 to 0xFF).
        COMMAND_CAM_MD_Function_Set,
        /// Motion detector Window Set. Parameters: camera_address, param_1 - Select Detection Frame (0, 1, 2, 3), param_2 - Start Horizontal Position (from 0x00 to 0x10), param_3 - Start Vertical Position (from 0x00 to 0x0E), param_4 - Stop Horizontal Position (from 0x01 to 0x11), param_5 - Stop Vertical Position (from 0x01 to 0x0F).
        COMMAND_CAM_MD_Window_Set,

        REPLY_CAM_MD_Alarm,

        /// Zoom Position data Continuous Output On. Parameters: camera_address.
        COMMAND_CAM_ContinuousZoomPosReply_On,
        /// Zoom Position data Continuous Output Off. Parameters: camera_address.
        COMMAND_CAM_ContinuousZoomPosReply_Off,

        REPLY_CAM_ContinuousZoomPos,

        /// Zoom Position data Continuous Output Time Set. Parameters: camera_address, param_1 - Interval time (V cycle, from 0x00 to 0xFF).
        COMMAND_CAM_ZoomPosReplyIntervalTimeSet,

        /// Focus Position data Continuous Output On. Parameters: camera_address.
        COMMAND_CAM_ContinuousFocusPosReply_On,
        /// Focus Position data Continuous Output Off. Parameters: camera_address.
        COMMAND_CAM_ContinuousFocusPosReply_Off,

        REPLY_CAM_ContinuousFocusPos,

        /// Focus Position data Continuous Output Time set. Parameters: camera_address, param_1 - Interval time (V cycle, from 0x00 to 0xFF).
        COMMAND_CAM_FocusPosReplyIntervalTimeSet,

        /// Set register value. Parameters: camera_address, param_1 - register number (from 0x00 to 0x7F), param_2 - register value (from 0x00 to 0xFF).
        COMMAND_CAM_RegisterValue,
        
        /// Chroma Suppress setting level. Parameters: camera_address, param_1 - Chroma Suppress setting level (0xFF - Off, from 0x01 to 0x03 - 3 levels. Effect increases as the level number increases).
        COMMAND_CAM_ChromaSuppress,

        /// Color Gain Setting. Parameters: camera_address, param_1 - Color Gain Setting (from 0x00 to 0x0E).
        COMMAND_CAM_ColorGain_Direct,

        /// Color Hue Setting. Parameters: camera_address, param_1 - Color Hue Setting (from 0x00 to 0x0E).
        COMMAND_CAM_ColorHue_Direct,

        /// Gamma offset. Parameters: camera_address, param_1 - Polarity offset (0 is plus, 1 is minus), param_2 - Offset value (brightness) setting (from 0x00 to 0x40).
        COMMAND_CAM_GammaOffset_Direct,

        /// Contrast Adjastment Level. Parameters: camera_address, param_1 - Level (from 0x00 to 0xFF, 0x00 to 0x7F: The smaller the value is, the lower the contrast becomes. 0x80 (Initial setting): No contrast adjustment, 81h to FFh: The larger the value is, the higher the contrast becomes).
        COMMAND_CAM_ContrastAdjLevel_Direct,

        /// Exposure compensation reset. Parameters: camera_address.
        COMMAND_CAM_ExExpComp_Reset,
        /// Exposure compensation up. Parameters: camera_address, param_1 - Step number (from 0x00 to 0x7F, However, 00h is the same operation as 01h).
        COMMAND_CAM_ExExpComp_Up,
        /// Exposure compensation down. Parameters: camera_address, param_1 - Step number (from 0x00 to 0x7F, However, 00h is the same operation as 01h).
        COMMAND_CAM_ExExpComp_Down,
        /// Set the exposure compensation to the specified level. Parameters: camera_address, param_1 - Level (from 0x00 to 0xFF).
        COMMAND_CAM_ExExpComp_Direct,
        
        /// Aperture control reset. Parameters: camera_address.
        COMMAND_CAM_ExAperture_Reset,
        /// Aperture control up. Parameters: camera_address, param_1 - Step number (from 0x00 to 0x7F, However, 00h is the same operation as 01h).
        COMMAND_CAM_ExAperture_Up,
        /// Aperture control down. Parameters: camera_address, param_1 - Step number (from 0x00 to 0x7F, However, 00h is the same operation as 01h).
        COMMAND_CAM_ExAperture_Down,
        /// Set the aperture control to the specified level. Parameters: camera_address, param_1 - Level (from 0x00 to 0xFF).
        COMMAND_CAM_ExAperture_Direct,

        /// Auto ICR threshold. Parameters: camera_address, param_1 - ICR On→Off threshold level when Auto ICR (from 0x00 to 0xFF).
        COMMAND_CAM_ExAutoICR_Threshold,
        /// Auto ICR level. Parameters: camera_address, param_1 - ICR Off→On threshold level when Auto ICR (from 0x00 to 0x1C).
        COMMAND_CAM_ExAutoICR_Level,

        /// Color Gain Setting. Parameters: camera_address, param_1 - Gain setting level (from 0x00 to 0xFF).
        COMMAND_CAM_ExColorGain_Direct,

        /// Color Hue Setting. Parameters: camera_address, param_1 - Phase setting level (from 0x00 to 0xFF).
        COMMAND_CAM_ExColorHue_Direct,

        /// HLC parameters setting. Parameters: camera_address, param_1 - HLC level (0: Off, 1: Low, 2: Mid, 3: High), param_2 - HLC mask level (0: Off, 1: Low, 2: Mid, 3: High).
        COMMAND_CAM_HLC_Parameter_Set,

        /// Flicker Reduction On. Parameters: camera_address.
        COMMAND_CAM_FlickerReduction_On,
        /// Flicker Reduction Off. Parameters: camera_address.
        COMMAND_CAM_FlickerReduction_Off,

        /*
        INQUIRY.
        */

        /// Camera power status inquiry. Parameters: camera_address.
        INQUIRY_CAM_PowerInq,
        REPLY_CAM_Power_On,
        REPLY_CAM_Power_Off,
        
        /// Zoom position inquiry. Parameters: camera_address.
        INQUIRY_CAM_ZoomPosInq,
        REPLY_CAM_ZoomPos,

        /// Digital zoom mode inquiry. Parameters: camera_address.
        INQUIRY_CAM_DZoomModeInq,
        REPLY_CAM_DZoomMode_On,
        REPLY_CAM_DZoomMode_Off,

        /// Digital zoom combined/separate mode inquiry. Parameters: camera_address.
        INQUIRY_CAM_DZoom_C_S_ModeInq,
        REPLY_CAM_DZoom_Combine_Mode,
        REPLY_CAM_DZoom_Separate_Mode,

        /// Digital zoom position inquiry. Parameters: camera_address.
        INQUIRY_CAM_DZoomPosInq,
        REPLY_CAM_DZoomPos,

        /// Focus mode inquiry. Parameters: camera_address.
        INQUIRY_CAM_FocusModeInq,
        REPLY_CAM_FocusMode_Auto_Focus,
        REPLY_CAM_FocusMode_Manual_Focus,

        /// Focus position inquiry. Parameters: camera_address.
        INQUIRY_CAM_FocusPosInq,
        REPLY_CAM_FocusPos,

        /// Focus near limit inquiry. Parameters: camera_address.
        INQUIRY_CAM_FocusNearLimitInq,
        REPLY_CAM_FocusNearLimit,

        /// Autofocus sesetivity inquity. Parameters: camera_address.
        INQUIRY_CAM_AFSensitivityInq,
        REPLY_CAM_AFSensitivity_Normal,
        REPLY_CAM_AFSensitivity_Low,

        /// Autoficus mode inquiry. Parameters: camera_address.
        INQUIRY_CAM_AFModeInq,
        REPLY_CAM_AFMode_Normal_AF,
        REPLY_CAM_AFMode_Interval_AF,
        REPLY_CAM_AFMode_Zoom_Trigger_AF,

        /// Autofocus time settings inquiry. Parameters: camera_address.
        INQUIRY_CAM_AFTimeSettingInq,
        REPLY_CAM_AFTimeSetting,

        /// IR coreection mode inquiry. Parameters: camera_address.
        INQUIRY_CAM_IRCorrectionInq,
        REPLY_CAM_IRCorrection_Standard,
        REPLY_CAM_IRCorrection_IR_Light,

        /// White balance mode inquiry. Parameters: camera_address.
        INQUIRY_CAM_WBModeInq,
        REPLY_CAM_WBMode_Auto,
        REPLY_CAM_WBMode_Indoor,
        REPLY_CAM_WBMode_Outdoor,
        REPLY_CAM_WBMode_One_Push_WB,
        REPLY_CAM_WBMode_ATW,
        REPLY_CAM_WBMode_Manual,
        REPLY_CAM_WBMode_Outdoor_Auto,
        REPLY_CAM_WBMode_Sodium_Lamp_Auto,
        REPLY_CAM_WBMode_Sodium_Lamp,
        REPLY_CAM_WBMode_Sodium_Lamp_Outdoor_Auto,

        /// R gain inquiry. Parameters: camera_address.
        INQUIRY_CAM_RGainInq,
        REPLY_CAM_RGain,

        /// B gain inquiry. Parameters: camera_address.
        INQUIRY_CAM_BGainInq,
        REPLY_CAM_BGain,

        /// Auto exposure mode inquiry. Parameters: camera_address.
        INQUIRY_CAM_AEModeInq,
        REPLY_CAM_AEMode_Full_Auto,
        REPLY_CAM_AEMode_Manual,
        REPLY_CAM_AEMode_Shutter_Priority,
        REPLY_CAM_AEMode_Iris_Priority,

        /// Auto slow shutter status inquiry. Parameters: camera_address.
        INQUIRY_CAM_AutoSlowShutterInq,
        REPLY_CAM_AutoSlowShutter_On,
        REPLY_CAM_AutoSlowShutter_Off,

        /// Shutter position inquiry. Parameters: camera_address.
        INQUIRY_CAM_ShutterPosInq,
        REPLY_CAM_ShutterPos,

        /// Iris position inquiry. Parameters: camera_address.
        INQUIRY_CAM_IrisPosInq,
        REPLY_CAM_IrisPos,

        /// Gain position inquiry. Parameters: camera_address.
        INQUIRY_CAM_GainPosInq,
        REPLY_CAM_GainPos,

        /// Gain limit inquiry. Parameters: camera_address.
        INQUIRY_CAM_GainLimitInq,
        REPLY_CAM_GainLimit,

        /// Exposure compensation mode inquiry. Parameters: camera_address.
        INQUIRY_CAM_ExpCompModeInq,
        REPLY_CAM_ExpCompMode_On,
        REPLY_CAM_ExpCompMode_Off,

        /// Exposure compensation position inquiry. Parameters: camera_address.
        INQUIRY_CAM_ExpCompPosInq,
        REPLY_CAM_ExpCompPos,

        /// Back light mode inquiry. Parameters: camera_address.
        INQUIRY_CAM_BackLightModeInq,
        REPLY_CAM_BackLightMode_On,
        REPLY_CAM_BackLightMode_Off,

        /// Spot autofocus mode inquiry. Parameters: camera_address.
        INQUIRY_CAM_SpotAEModeInq,
        REPLY_CAM_SpotAEMode_On,
        REPLY_CAM_SpotAEMode_Off,

        /// Spot autofocus position inquiry. Parameters: camera_address.
        INQUIRY_CAM_SpotAEPosInq,
        REPLY_CAM_SpotAEPos,

        /// VE mode inquiry. Parameters: camera_address.
        INQUIRY_CAM_VEModeInq,
        REPLY_CAM_VEMode_Off,
        REPLY_CAM_VEMode_On,

        /// VE parameter inquiry. Parameters: camera_address.
        INQUIRY_CAM_VEParameterInq,
        REPLY_CAM_VEParameter,

        /// WD Mode inquiry. Parameters: camera_address.
        INQUIRY_CAM_WDModeInq,
        REPLY_CAM_WDMode_WD_On,
        REPLY_CAM_WDMode_WD_and_VE_Off,
        REPLY_CAM_WDMode_VE_On,

        /// WD parameter inquiry. Parameters: camera_address.
        INQUIRY_CAM_WDParameterInq,
        REPLY_CAM_WDParameter,

        /// AE response inquiry. Parameters: camera_address.
        INQUIRY_CAM_AEResponseInq,
        REPLY_CAM_AEResponse,

        /// Defog mode inguiry. Parameters: camera_address.
        INQUIRY_CAM_DefogInq,
        REPLY_CAM_Defog_Level,
        REPLY_CAM_Defog_Off,

        /// Aperture inquiry. Parameters: camera_address.
        INQUIRY_CAM_ApertureInq,
        REPLY_CAM_Aperture,

        /// Noise reduction level and mode inquiry. Parameters: camera_address.
        INQUIRY_CAM_NRInq,
        REPLY_CAM_NR,

        /// Noise reduction level and mode inquiry. Parameters: camera_address.
        INQUIRY_CAM_NR2D3Dinq,
        REPLY_CAM_NR2D3D,

        /// Gamma inquiry. Parameters: camera_address.
        INQUIRY_CAM_GammaInq,
        REPLY_CAM_Gamma,

        // High sensetivity mode inquiry. Parameters: camera_address.
        INQUIRY_CAM_HighSensitivityInq,
        REPLY_CAM_HighSensitivity_On,
        REPLY_CAM_HighSensitivity_Off,

        /// LR reverse mode inquiry. Parameters: camera_address.
        INQUIRY_CAM_LR_ReverseModeInq,
        REPLY_CAM_LR_ReverseMode_On,
        REPLY_CAM_LR_ReverseMode_Off,

        // Freeze mode inquiry. Parameters: camera_address.
        INQUIRY_CAM_FreezeModeInq,
        REPLY_CAM_FreezeMode_On,
        REPLY_CAM_FreezeMode_Off,

        // Picture effect mode inquiry. Parameters: camera_address.
        INQUIRY_CAM_PictureEffectModeInq,
        REPLY_CAM_PictureEffectMode_Off,
        REPLY_CAM_PictureEffectMode_Black_and_White,

        /// Picture flip mode inquiry. Parameters: camera_address.
        INQUIRY_CAM_PictureFlipModeInq,
        REPLY_CAM_PictureFlipMode_On,
        REPLY_CAM_PictureFlipMode_Off,

        /// ICR mode inquiry.  Parameters: camera_address.
        INQUIRY_CAM_ICRModeInq,
        REPLY_CAM_ICRMode_On,
        REPLY_CAM_ICRMode_Off,

        /// Auto ICR mode inquiry. Parameters: camera_address.
        INQUIRY_CAM_AutoICRModeInq,
        REPLY_CAM_AutoICRMode_On,
        REPLY_CAM_AutoICRMode_Off,

        /// Auto ICR threshold inquiry. Parameters: camera_address.
        INQUIRY_CAM_AutoICRThresholdInq,
        REPLY_CAM_AutoICRThreshold,

        /// Auto ICR Alarm reply inquity. Parameters: camera_address.
        INQUIRY_CAM_AutoICRAlarmReplyInq,
        REPLY_CAM_AutoICRAlarmReply_On,
        REPLY_CAM_AutoICRAlarmReply_Off,

        /// Camera memory inquiry. Parameters: camera_address.
        INQUIRY_CAM_MemoryInq,
        REPLY_CAM_Memory,

        /// Camera memory value inquiry. Parameters: camera_address, param_1 - address (from 0x00 to 0x07).
        INQUIRY_CAM_MemSaveInq,
        REPLY_CAM_MemSave,

        /// Display mode inquiry. Parameters: camera_address.
        INQUIRY_CAM_DisplayModeInq,
        REPLY_CAM_DisplayMode_On,
        REPLY_CAM_DisplayMode_Off,

        /// Video stabilizer mode inquiry. Parameters: camera_address. 
        INQUIRY_CAM_StabilizerModeInq,
        REPLY_CAM_StabilizerMode_On,
        REPLY_CAM_StabilizerMode_Off,
        REPLY_CAM_StabilizerMode_Hold,

        /// Mute mode inquiry. Parameters: camera_address. 
        INQUIRY_CAM_MuteModeInq,
        REPLY_CAM_MuteMode_On,
        REPLY_CAM_MuteMode_Off,

        /// Privacy display mask inquiry. Parameters: camera_address. 
        INQUIRY_CAM_PrivacyDisplayInq,
        REPLY_CAM_PrivacyDisplay,

        /// Pricacy pan-tilt inquiry. Parameters: camera_address. 
        INQUIRY_CAM_PrivacyPanTiltInq,
        REPLY_CAM_PrivacyPanTilt,

        /// Pricacy PTX inquiry. Parameters: camera_address, param_1 - Mask Settings (from 0x00 to 0xFF).
        INQUIRY_CAM_PrivacyPTZInq,
        REPLY_CAM_PrivacyPTZ,

        /// Privacy monitoring inquiry. Parameters: camera_address.
        INQUIRY_CAM_PrivacyMonitorInq,
        REPLY_CAM_PrivacyMonitor,

        /// Camera ID inquiry. Parameters: camera_address.
        INQUIRY_CAM_IDInq,
        REPLY_CAM_ID,

        /// Camera version inquiry. Parameters: camera_address.
        INQUIRY_CAM_VersionInq,
        REPLY_CAM_Version,

        /// Motion detector mode inquiry. Parameters: camera_address.
        INQUIRY_CAM_MDModeInq,
        REPLY_CAM_MDMode_On,
        REPLY_CAM_MDMode_Off,
        
        /// Motion detector function inquiry. Parameters: camera_address.
        INQUIRY_CAM_MDFunctionInq,
        REPLY_CAM_MDFunction,

        /// Motion detector window inquiry. Parameters: camera_address, param_1 - Select Detection Frame (0, 1, 2, 3).
        INQUIRY_CAM_MDWindowInq,
        REPLY_CAM_MDWindow,

        /// Continious zoom reply mode inquiry. Parameters: camera_address.
        INQUIRY_CAM_ContinuousZoomPosReplyModeInq,
        REPLY_CAM_ContinuousZoomPosReplyMode_On,
        REPLY_CAM_ContinuousZoomPosReplyMode_Off,

        /// Zoom position reply interval time inquiry. Parameters: camera_address.
        INQUIRY_CAM_ZoomPosReplyIntervalTimeInq,
        REPLY_CAM_ZoomPosReplyIntervalTime,

        /// Continuous focus pos reply mode inquiry. Parameters: camera_address.
        INQUIRY_CAM_ContinuousFocusPosReplyModeInq,
        REPLY_CAM_ContinuousFocusPosReplyMode_On,
        REPLY_CAM_ContinuousFocusPosReplyMode_Off,

        /// Focur reply interval time inquiry. Parameters: camera_address.
        INQUIRY_CAM_FocusReplyIntervalTimeInq,
        REPLY_CAM_FocusReplyIntervalTime,

        /// Register value inquiry. Parameters: camera_address, param_1 - Register No (from 0x00 to 0x7F).
        INQUIRY_CAM_RegisterValueInq,
        REPLY_CAM_RegisterValue,

        /// Chroma suppress inquiry. Parameters: camera_address.
        INQUIRY_CAM_ChromaSuppressInq,
        REPLY_CAM_ChromaSuppress,

        /// Color gain inquiry. Parameters: camera_address.
        INQUIRY_CAM_ColorGainInq,
        REPLY_CAM_ColorGain,

        /// Color hue inquiry. Parameters: camera_address.
        INQUIRY_CAM_ColorHueInq,
        REPLY_CAM_ColorHue,

        /// Camera temperature inquiry. Parameters: camera_address.
        INQUIRY_CAM_TempInq,
        REPLY_CAM_Temp,

        /// Gamma offset inquiry. Parameters: camera_address.
        INQUIRY_CAM_GammaOffsetInq,
        REPLY_CAM_GammaOffset,

        /// Contrast ajasment level inquiry. Parameters: camera_address.
        INQUIRY_CAM_ContrastAdjLevelInq,
        REPLY_CAM_ContrastAdjLevel,

        /// Exposure compensation position inquiry. Parameters: camera_address.
        INQUIRY_CAM_ExExpCompPosInq,
        REPLY_CAM_ExExpCompPos,

        /// Aperture control level inquiry. Parameters: camera_address.
        INQUIRY_CAM_ExApertureInq,
        REPLY_CAM_ExAperture,

        /// Gain setting level inquiry. Parameters: camera_address.
        INQUIRY_CAM_ExColorGainInq,
        REPLY_CAM_ExColorGain,

        /// Phase setting level. Parameters: camera_address.
        INQUIRY_CAM_ExColorHueInq,
        REPLY_CAM_ExColorHue,

        /// On->Off threshold level when Auto ICR inquiry. Parameters: camera_address.
        INQUIRY_CAM_ExAutoICRThresholdInq,
        REPLY_CAM_ExAutoICRThreshold,

        /// Off-On threshold level when Auto ICR inquiry. Parameters: camera_address.
        INQUIRY_CAM_ExAutoICROnLevelInq,
        REPLY_CAM_ExAutoICROnLevel,

        /// Min shutter level inquiry. Parameters: camera_address.
        INQUIRY_CAM_MinShutterInq,
        REPLY_CAM_MinShutter_On,
        REPLY_CAM_MinShutter_Off,

        /// Min shutter limit inquiry. Parameters: camera_address.
        INQUIRY_CAM_MinShutterLimitInq,
        REPLY_CAM_MinShutterLimit,

        /// HLC level inquiry. Parameters: camera_address.
        INQUIRY_CAM_HLCInq,
        REPLY_CAM_HLC,

        /// Flicker reduction mode inquiry. Parameters: camera_address.
        INQUIRY_CAM_FlickerReductionInq,
        REPLY_CAM_FlickerReduction_On,
        REPLY_CAM_FlickerReduction_Off,

        /// Lens Control System Inquiry. Parameters: camera_address.
        INQUIRY_LenseControlSystemInq,
        REPLY_LenseControlSystem,

        /// Camera Control System Inquiry. Parameters: camera_address.
        INQUIRY_CameraControlSystemInq,
        REPLY_CameraControlSystem,

        /// Other data Inquiry. Parameters: camera_address.
        INQUIRY_OtherDataInq,
        REPLY_OtherData,

        /// Extended Function 1 Query. Parameters: camera_address.
        INQUIRY_ExtendedFunction_1_Inq,
        REPLY_ExtendedFunction_1,

        /// Extended Function 2 Query. Parameters: camera_address.
        INQUIRY_ExtendedFunction_2_Inq,
        REPLY_ExtendedFunction_2,

        /// Extended Function 3 Query. Parameters: camera_address.
        INQUIRY_ExtendedFunction_3_Inq,
        REPLY_ExtendedFunction_3,

        /*
        NETWORK CHANGE MESSAGE
        */
        NETWORK_CHANGE,

        /*
        ACKNOWLEDGE MESSAGES.
        */
        ACKNOWLEDGE,

        /*
        COMMAND COMPLETION MESSAGES
        */
        COMPLETION_COMMANDS,
        /*
        INQUIRIES COMPLETION MESSAGES
        */
        COMPLETION_INQUIRY,
        /*
        REPLY MESSAGES.
        */
        REPLY

    };
}


