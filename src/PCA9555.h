#pragma once

#include <Arduino.h>
#include <Wire.h>

enum class PCA9555Port : uint8_t
{
	A = 0,
	B = 1
};

/**
 * Registers addresses.
 * The library use addresses for IOCON.BANK = 0.
 * See "3.2.1 Byte mode and Sequential mode".
 */
enum class PCA9555Register : uint8_t
{
	INPUT_A		= 0x00, 		///< INPUT Register for port A.
	INPUT_B		= 0x01,			///< INPUT Register for port B.
	OUTPUT_A	= 0x02,			///< OUTPUT Register for port A.
	OUTPUT_B	= 0x03,			///< OUTPUT Register for port B.
	INVERT_A	= 0x04,			///< INVERT Register for port A.
	INVERT_B	= 0x05,			///< INVERT Register for port B.
	CONFIG_A	= 0x06,			///< CONFIG Register for port A.
	CONFIG_B	= 0x07			///< CONFIG Register for port B.
};

inline PCA9555Register operator+(PCA9555Register a, PCA9555Port b) {
	return static_cast<PCA9555Register>(static_cast<uint8_t>(a) + static_cast<uint8_t>(b));
};

class PCA9555 {
private:
	TwoWire* _bus;
	uint8_t _deviceAddr;
public:
	/**
	 * Instantiates a new instance to interact with a MCP23017 at the specified address.
	 */
	PCA9555(uint8_t address, TwoWire& bus = Wire);
	~PCA9555();

	void init();
    bool checkAck();
	uint8_t portMode(PCA9555Port port, uint8_t directions, uint8_t inverted = 0x00);
	uint8_t pinMode(uint8_t pin, uint8_t mode, bool inverted = false);
	uint8_t digitalRead(uint8_t pin, uint8_t& buffer);
	uint8_t digitalWrite(uint8_t pin, uint8_t value);
	uint8_t writePort(PCA9555Port port, uint8_t value);
	uint8_t write(uint16_t value);
	uint8_t readPort(PCA9555Port port, uint8_t& buffer);
	uint8_t read(uint16_t& buffer);
	uint8_t writeRegister(PCA9555Register reg, uint8_t value);
	uint8_t writeRegister(PCA9555Register reg, uint8_t portA, uint8_t portB);
	uint8_t readRegister(PCA9555Register reg, uint8_t& buffer);
	uint8_t readRegister(PCA9555Register reg, uint8_t& portA, uint8_t& portB);
};
