#ifndef PROTOCOL_H
#define PROTOCOL_H

#include <stdint.h>
#include <stdbool.h>

enum CommandID {
    GET_SIDEBOARD_DATA = 0x00,
    SIDEBOARD_DATA = 0x10,
    GET_FEEDBACK_DATA = 0x01,
    FEEDBACK_DATA = 0x11,
    GET_CONFIG = 0x02,
    SET_CONFIG = 0x12,
    SPEED_CMD_STEERING = 0x03,
    SPEED_CMD_LEFT = 0x13,
    SPEED_CMD_RIGHT = 0x23,
    SPEED_CMD_BOTH = 0x33,
    SPEED_CMD_ANGLES = 0x43,
    PERFORM_ACTION = 0x100
};
/* 
typedef struct CommandHandler {
    const CommandID id;
    void (*handler)(void*);
};

static void(*handlers[4][2])(void*) = {};

static void setCommandHandler(const CommandID id, void (*handler)(void*)) {
    handlers[id & 0x0f][(id & 0xf0) >> 4] = handler;
}

typedef struct {
    const CommandID id;
    void* args;
    const CommandID responseId;

} Command; */

// Rx Structures USART
typedef struct{
    uint16_t  start; 
    int16_t   steer;
    int16_t   speed;
    uint16_t  checksum;    
} SerialCommand;
typedef struct {
    uint16_t start;
    int16_t  speed;
    bool     enabled;
    uint16_t checksum;
} OneWheelCommand;
typedef struct {
    OneWheelCommand commandL;
    OneWheelCommand commandR;
} TwoWheelCommand;
typedef struct{
    uint16_t	start;
    int16_t  	roll;
    int16_t  	pitch;
    int16_t  	yaw;
    uint16_t  sensors;
    uint16_t 	checksum;
} SerialSideboard;
//------------------------------------------------------------------------
// Local variables
//------------------------------------------------------------------------
typedef struct {
  uint16_t start;
  int16_t cmd1;
  int16_t cmd2;
  int16_t speedR_meas;
  int16_t speedL_meas;
  int16_t batVoltage;
  int16_t boardTemp;
  uint16_t cmdLed;
  uint16_t checksum;
} SerialFeedback;



extern void getSideboardData(uint32_t old_pos, uint32_t pos, uint8_t* buffer);
extern void sendSideboardData(SerialSideboard* sideboard);
extern void getFeedbackData(uint32_t old_pos, uint32_t pos, uint8_t* buffer);
extern void sendFeedbackData(SerialFeedback* feedback);
extern void getConfigValue(uint32_t old_pos, uint32_t pos, uint8_t* buffer, const char* name);
extern void setConfigValue(const char* name, void* value);
extern void sendSteeringCommand(uint32_t old_pos, uint32_t pos, uint8_t* buffer, int16_t speed, int16_t steering);
extern void updateLeftWheelSpeed(uint32_t old_pos, uint32_t pos, uint8_t* buffer, int16_t speed);
extern void updateRightWheelSpeed(uint32_t old_pos, uint32_t pos, uint8_t* buffer, int16_t speed);
extern void updateBothWheelSpeeds(uint32_t old_pos, uint32_t pos, uint8_t* buffer, int16_t speedL, int16_t speedR);
extern void updateSpeedFromHBTilt(uint32_t old_pos, uint32_t pos, uint8_t* buffer, int16_t angle);

#endif