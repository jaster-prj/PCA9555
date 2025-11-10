#include "PCA9555.h"


PCA9555::PCA9555(uint8_t address, TwoWire& bus) {
	_deviceAddr = address;
	_bus = &bus;
}

PCA9555::~PCA9555() {}

void PCA9555::init() {}

bool PCA9555::checkAck() {
    uint8_t error;
    _bus->beginTransmission(_deviceAddr);
	_bus->write(static_cast<uint8_t>(PCA9555Register::OUTPUT_A));
	error = _bus->endTransmission();

    if(error != 0){
      return false;
    }else{
      return true;
    }
}

uint8_t PCA9555::portMode(PCA9555Port port, uint8_t directions, uint8_t inverted)
{
	uint8_t err = 0;
	err = writeRegister(PCA9555Register::CONFIG_A + port, directions);
	if (err != 0) {
		return err;
	}
	return writeRegister(PCA9555Register::INVERT_A + port, inverted);
}

uint8_t PCA9555::pinMode(uint8_t pin, uint8_t mode, bool inverted)
{
	PCA9555Register confreg = PCA9555Register::CONFIG_A;
	PCA9555Register invreg = PCA9555Register::INVERT_A;
	uint8_t conf, inv;
	uint8_t err = 0;

	if(pin > 7)
	{
		confreg = PCA9555Register::CONFIG_B;
		invreg = PCA9555Register::INVERT_B;
		pin -= 8;
	}

	err = readRegister(confreg, conf);
	if (err != 0) { return err; }
	if(mode == INPUT) bitSet(conf, pin);
	else bitClear(conf, pin);

	err = readRegister(invreg, inv);
	if (err != 0) { return err; }
	if(inverted) bitSet(inv, pin);
	else bitClear(inv, pin);

	err = writeRegister(confreg, conf);
	if (err != 0) { return err; }
	return writeRegister(invreg, inv);
}

uint8_t PCA9555::digitalWrite(uint8_t pin, uint8_t state)
{
	PCA9555Register gpioreg = PCA9555Register::OUTPUT_A;
	uint8_t gpio;
	uint8_t err = 0;
	if(pin > 7)
	{
		gpioreg = PCA9555Register::OUTPUT_B;
		pin -= 8;
	}
	err = readRegister(gpioreg, gpio);
	if (err != 0) { return err; }
	if(state == HIGH) bitSet(gpio, pin);
	else bitClear(gpio, pin);
	return writeRegister(gpioreg, gpio);
}

uint8_t PCA9555::digitalRead(uint8_t pin, uint8_t& buffer)
{
	PCA9555Register inputreg = PCA9555Register::INPUT_A;
	uint8_t gpio;
	uint8_t err = 0;
	if(pin > 7)
	{
		inputreg = PCA9555Register::INPUT_B;
		pin -=8;
	}
	err = readRegister(inputreg, gpio);
	if (err != 0) { return err; }
	if(bitRead(gpio, pin)) { 
		buffer = HIGH; 
	} else {
		buffer = LOW;
	}
	return 0;
}

uint8_t PCA9555::writePort(PCA9555Port port, uint8_t value) {
	return writeRegister(PCA9555Register::OUTPUT_A + port, value);
}

uint8_t PCA9555::write(uint16_t value) {
	return writeRegister(PCA9555Register::OUTPUT_A, lowByte(value), highByte(value));
}

uint8_t PCA9555::readPort(PCA9555Port port, uint8_t& buffer) {
	return readRegister(PCA9555Register::INPUT_A + port, buffer);
}

uint8_t PCA9555::read(uint16_t& buffer) {

	uint8_t a, b;
	uint8_t err = 0;
	err = readPort(PCA9555Port::A, a);
	if (err != 0) { return err; }
	err = readPort(PCA9555Port::B, b);
	if (err != 0) { return err; }
	buffer = a | b << 8;
	return 0;
}

/**
 * @name writeRegister
 * @param reg Register to write to.
 * @param value value to write to Register.
 * Writes the value from addressed chip to selected register.
 */
uint8_t PCA9555::writeRegister(PCA9555Register reg, uint8_t value)
{
	_bus->beginTransmission(_deviceAddr);
	_bus->write(static_cast<uint8_t>(reg));
	_bus->write(value);
	return _bus->endTransmission();
}

/**
 * @name writeRegister
 * @param reg Register to write to.
 * @param portA value to write to Register of Port A.
 * @param portB value to write to Register of Port B.
 * Writes the value from addressed chip to selected register.
 */
uint8_t PCA9555::writeRegister(PCA9555Register reg, uint8_t portA, uint8_t portB)
{
	_bus->beginTransmission(_deviceAddr);
	_bus->write(static_cast<uint8_t>(reg));
	_bus->write(portA);
	_bus->write(portB);
	return _bus->endTransmission();
}

/**
 * @name readRegister
 * @param reg Register to read from
 * @return data in register
 * Reads the data from addressed chip at selected register.
 */
uint8_t PCA9555::readRegister(PCA9555Register reg, uint8_t& buffer) {
    
	_bus->beginTransmission(_deviceAddr);
	_bus->write(static_cast<uint8_t>(reg));
	uint8_t err = _bus->endTransmission(false);
	if (err != 0) { return err; }
	_bus->requestFrom(_deviceAddr, (uint8_t)1);
	buffer = _bus->read();
	return 0;
}

/**
 * @name readRegister
 * @param reg Register to read from
 * @param portA Pointer to write value from Register of Port A.
 * @param portB Pointer to write value from Register of Port B.
 * Reads the data from addressed chip at selected register.
 */
uint8_t PCA9555::readRegister(PCA9555Register reg, uint8_t& portA, uint8_t& portB) {

	_bus->beginTransmission(_deviceAddr);
	_bus->write(static_cast<uint8_t>(reg));
	uint8_t err = _bus->endTransmission();
	if (err != 0) { return err; }
	_bus->requestFrom(_deviceAddr, (uint8_t)2);
	portA = _bus->read();
	portB = _bus->read();
	return 0;
}