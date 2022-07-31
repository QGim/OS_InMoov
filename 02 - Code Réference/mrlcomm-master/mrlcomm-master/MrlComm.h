#ifndef MrlComm_h
#define MrlComm_h

#include "ArduinoMsgCodec.h"

// TODO - standard convention of dev versions are odd release is even ?
#define MRLCOMM_VERSION         43

// forward defines to break circular dependency
class Device;
class Msg;
class MrlComm;
class Pin;


/***********************************************************************
 * Class MrlComm -
 * This class represents the Arduino service as a device.
 * It can hosts devices such as Motors, Servos, Steppers, Sensors, etc.
 * You can dynamically add or remove devices, and the deviceList should be in
 * synch with the Java-Land deviceList.
 * It has a list of pins which can be read from or written to.
 * It also follows some of the same methods as the Device in Device.h
 * It has an update() which is called each loop to do any necessary processing
 * 
*/
class MrlComm{
  private:
    /**
     * "global var"
     */
    // The mighty device List.  This contains all active devices that are attached to the arduino.
    LinkedList<Device*> deviceList;

    // list of pins currently being read from - can contain both digital and analog
    LinkedList<Pin*> pinList;

    // MRLComm message buffer and current count from serial port ( MAGIC | MSGSIZE | FUNCTION | PAYLOAD ...
    //unsigned char ioCmd[MAX_MSG_SIZE];  // message buffer for all inbound messages
    unsigned char* config;
    // performance metrics  and load timing
    // global debug setting, if set to true publishDebug will write to the serial port.
    int byteCount;
    int msgSize;
    bool boardStatusEnabled;
    unsigned int publishBoardStatusModulus; // the frequency in which to report the load timing metrics (in number of main loops)
    unsigned long lastMicros; // timestamp of last loop (if stats enabled.)

    bool heartbeatEnabled = false;
    unsigned long lastHeartbeatUpdate;

    byte customMsgBuffer[MAX_MSG_SIZE];
    int customMsgSize;

    // handles all messages to and from pc
    Msg* msg;

public:
    // utility methods
    int getFreeRam();
    Device* getDevice(int id);

    bool ackEnabled = false;

    Device* addDevice(Device* device);
    void update();

    // Below are generated callbacks controlled by
    // arduinoMsgs.schema
    // <generatedCallBacks>
	// > getBoardInfo
	void getBoardInfo();
	// > enableBoardStatus/bool enabled
	void enableBoardStatus( boolean enabled);
	// > enablePin/address/type/b16 rate
	void enablePin( byte address,  byte type,  int rate);
	// > setDebug/bool enabled
	void setDebug( boolean enabled);
	// > setSerialRate/b32 rate
	void setSerialRate( long rate);
	// > softReset
	void softReset();
	// > enableAck/bool enabled
	void enableAck( boolean enabled);
	// > enableHeartbeat/bool enabled
	void enableHeartbeat( boolean enabled);
	// > heartbeat
	void heartbeat();
	// > echo/bu32 sInt
	void echo( unsigned long sInt);
	// > controllerAttach/serialPort
	void controllerAttach( byte serialPort);
	// > customMsg/[] msg
	void customMsg( byte msgSize, const byte*msg);
	// > deviceDetach/deviceId
	void deviceDetach( byte deviceId);
	// > i2cBusAttach/deviceId/i2cBus
	void i2cBusAttach( byte deviceId,  byte i2cBus);
	// > i2cRead/deviceId/deviceAddress/size
	void i2cRead( byte deviceId,  byte deviceAddress,  byte size);
	// > i2cWrite/deviceId/deviceAddress/[] data
	void i2cWrite( byte deviceId,  byte deviceAddress,  byte dataSize, const byte*data);
	// > i2cWriteRead/deviceId/deviceAddress/readSize/writeValue
	void i2cWriteRead( byte deviceId,  byte deviceAddress,  byte readSize,  byte writeValue);
	// > neoPixelAttach/deviceId/pin/b32 numPixels
	void neoPixelAttach( byte deviceId,  byte pin,  long numPixels);
	// > neoPixelSetAnimation/deviceId/animation/red/green/blue/b16 speed
	void neoPixelSetAnimation( byte deviceId,  byte animation,  byte red,  byte green,  byte blue,  int speed);
	// > neoPixelWriteMatrix/deviceId/[] buffer
	void neoPixelWriteMatrix( byte deviceId,  byte bufferSize, const byte*buffer);
	// > disablePin/pin
	void disablePin( byte pin);
	// > disablePins
	void disablePins();
	// > setTrigger/pin/triggerValue
	void setTrigger( byte pin,  byte triggerValue);
	// > setDebounce/pin/delay
	void setDebounce( byte pin,  byte delay);
	// > servoAttach/deviceId/pin/initPos/b16 initVelocity
	void servoAttach( byte deviceId,  byte pin,  byte initPos,  int initVelocity);
	// > servoEnablePwm/deviceId/pin
	void servoEnablePwm( byte deviceId,  byte pin);
	// > servoDisablePwm/deviceId
	void servoDisablePwm( byte deviceId);
	// > servoSetMaxVelocity/deviceId/b16 maxVelocity
	void servoSetMaxVelocity( byte deviceId,  int maxVelocity);
	// > servoSetVelocity/deviceId/b16 velocity
	void servoSetVelocity( byte deviceId,  int velocity);
	// > servoSweepStart/deviceId/min/max/step
	void servoSweepStart( byte deviceId,  byte min,  byte max,  byte step);
	// > servoSweepStop/deviceId
	void servoSweepStop( byte deviceId);
	// > servoWrite/deviceId/target
	void servoWrite( byte deviceId,  byte target);
	// > servoWriteMicroseconds/deviceId/b16 ms
	void servoWriteMicroseconds( byte deviceId,  int ms);
	// > serialAttach/deviceId/relayPin
	void serialAttach( byte deviceId,  byte relayPin);
	// > serialRelay/deviceId/[] data
	void serialRelay( byte deviceId,  byte dataSize, const byte*data);
	// > ultrasonicSensorAttach/deviceId/triggerPin/echoPin
	void ultrasonicSensorAttach( byte deviceId,  byte triggerPin,  byte echoPin);
	// > ultrasonicSensorStartRanging/deviceId/b32 timeout
	void ultrasonicSensorStartRanging( byte deviceId,  long timeout);
	// > ultrasonicSensorStopRanging/deviceId
	void ultrasonicSensorStopRanging( byte deviceId);
    // </generatedCallBacks>
    // end

  public:
    unsigned long loopCount; // main loop count
    MrlComm();
    ~MrlComm();
    void publishBoardStatus();
    void publishVersion();
    void publishBoardInfo();
    void processCommand();
    void processCommand(int ioType);
    void updateDevices();
    unsigned int getCustomMsg();
    int getCustomMsgSize();
    void begin(HardwareSerial& serial);
    bool readMsg();
};
  
#endif
