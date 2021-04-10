// Author: Jingting Liu

#ifndef MAVLINKFUNCTIONS_HPP
#define MAVLINKFUNCTIONS_HPP

#include "Mavlink2_lib/common/mavlink.h"

typedef enum {
    MAVLINK_DECODING_INCOMPLETE=0,
    MAVLINK_DECODING_OKAY=1,
    MAVLINK_DECODING_FAIL=2,
    MAVLINK_DECODING_BAD_PARSING=3,
} mavlink_decoding_status_t;

typedef enum {
    MAVLINK_ENCODING_OKAY=1,
    MAVLINK_ENCODING_FAIL=2,
} mavlink_encoding_status_t;

typedef enum {
    MESSAGE_ID_GPS,
    MESSAGE_ID_GIMBAL,
    Message_ID_TAKEOFF,
    Message_ID_CUSTOM_CMD,
} Message_IDs_t;

typedef enum {
    MAVLINK_CMD_TAKEOFF, //TODO change to begin take off or stuff
    MAVLINK_CMD_LANDING,
    MAVLINK_CMD_DISCONNECT,
} mavlink_bool_command_t;



//-------------------------- Prototypes ---------------------------------------------------------------

/**
 * This decoder is consists of two parts, parser and decoder.
 * The parser handles mavlink messages one byte at a time. 
 * Once the complete packet could be successfully decoded, the decoder would translate the message into telemetry data.
 * 
 * mavlink_decoding_status_t decoderStatus = MAVLINK_DECODING_INCOMPLETE;
    mavlink_global_position_int_t global_position_decoded;

    while(byteavailable == true) // 50 is just a random number larger than message length (for GPS message length is 39)
    {
        // get incoming byte here, decoder can pick up the starting byte by itself

        if (decoderStatus != MAVLINK_DECODING_OKAY) //this make sure it stops after a whole message is received
        {
            decoderStatus = Mavlink_decoder(MAVLINK_COMM_0, current_byte, (uint8_t*) &global_position_decoded);
        }
    }
 * 
 **/
mavlink_decoding_status_t Mavlink_decoder(int channel, uint8_t incomingByte, uint8_t *telemetryData);

/**
 * @brief Encode an selected struct
 *
 * @param type The type of telemetry data e.g. GPS or takeoff or landing...
 * @param message The MAVLink message to compress the data into, this is guarenteed to be a full message starts from byte 0xfd
 * @param struct_ptr C-struct to read the message contents from
 * 
 * @return the status of encoding
 * 
 * Example usage, give the address of the struct you want to encode
 *     mavlink_global_position_int_t global_position = 
    {
        ...
    };

    mavlink_message_t encoded_msg;

    uint8_t encoderStatus = Mavlink_encoder(MESSAGE_ID_GPS, &encoded_msg, (const uint8_t*) &global_position);
 */
mavlink_encoding_status_t Mavlink_encoder(Message_IDs_t id, mavlink_message_t *message, const uint8_t *struct_ptr);


int test__encode_then_decode(void);

uint16_t custom_mavlink_msg__begin_takeoff_command_encode(uint8_t system_id, uint8_t component_id, mavlink_message_t* message, const mavlink_custom_cmd_takeoff_t* struct_ptr);
void custom_mavlink_msg__begin_takeoff_command_decode(const mavlink_message_t* message, mavlink_custom_cmd_takeoff_t* takeoff_command);


uint16_t custom_fcn__calculate_crc(mavlink_message_t* msg, uint8_t crc_extra);



#endif //MAVLINKFUNCTIONS_HPP
