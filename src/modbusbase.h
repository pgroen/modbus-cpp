/*
 *  Copyright (c) 2022 Peter M. Groen
 *  
 *  This source code is licensed under the MIT license found in the
 *  LICENSE file in the root directory of this source tree.
 */

#pragma once

// Create a simple logger for console output during debugging.
// TODO: Replace with a custom logger by using std::function
// to keep it consistent with TrueMQTT.
#ifdef ENABLE_MODBUS_LOGGING
#include <cstdio>
#define LOG(fmt, ...) printf("[ modbus-cpp ]" fmt, ##__VA_ARGS__)
#else
#define LOG(...) (void)0
#endif

#define MAX_MSG_LENGTH 260

// Function Codes
#define READ_COILS          0x01
#define READ_INPUT_BITS     0x02
#define READ_REGS           0x03
#define READ_INPUT_REGS     0x04
#define WRITE_COIL          0x05
#define WRITE_REG           0x06
#define WRITE_COILS         0x0F
#define WRITE_REGS          0x10

// Exception codes
#define EX_ILLEGAL_FUNCTION 0x01
#define EX_ILLEGAL_ADDRESS  0x02
#define EX_ILLEGAL_VALUE    0x03
#define EX_SERVER_FAILURE   0x04
#define EX_ACKNOWLEDGE      0x05
#define EX_SERVER_BUSY      0x06
#define EX_NEGATIVE_ACK     0x07
#define EX_MEM_PARITY_PROB  0x08
#define EX_GATEWAY_PROBLEMP 0x0A
#define EX_GATEWAY_PROBLEMF 0x0B
#define EX_BAD_DATA         0xFF

#define BAD_CON             -1

// Modbus base class. Providing all Modbus PDUs without transport implementation
class ModbusBase
{
public:
    bool            err{};
    int             err_no{};
    std::string     m_error_msg;
    
    ModbusBase();
    virtual ~ModbusBase();

    /*! 
     * Set slave id for this context 
     * \param slave_id - The slave id this system is known under.
     */
    void    setSlaveId(int slave_id) { m_slaveId = slave_id; }

    // Pure virtuals. Override when inherited.
    virtual bool Connect() const = 0;
    virtual void Close() = 0;
    virtual bool isConnected() const - 0;
    
    // Modbus implementation(s)
    int readCoils(uint16_t address, uint16_t amount, bool *buffer);     // Replace buffer with something sensible?
    int readInputBits(uint16_t address, uint16_t amount, bool *buffer); // Replace buffer with something sensible?

    /*!
     * Read Holding Registers 
     * MODBUS Function 0x03 
     * \param address  - Reference Address
     * \param amount   - Amount of Registers to Read
     * \param buffer   - Buffer to Store Data Read from Registers
     */
    int readHoldingRegisters(uint16_t address, uitn16_t amount, uint16_t *buffer);

    /*!
     * Read Input Registers 
     * MODBUS Function 0x04 
     * \param address - Reference Address
     * \param amount  - Amount of registers to read
     * \param buffer  - Buffer to store Data Read from Registers
     */
    int readInputRegisters(uint16_t address, uint16_t amount, uint16_t *buffer);

    int writeCoil(uint16_t address, const bool &to_write);
    int writeRegister(uint16_t address, const uint16_t &value);
    int writeCoils(uint16_t address, uint16_t amount, const bool *value);
    int writeRegisters(uint16_t address, uint16_t amount, const uint16_t *value);

private:        // Methods
    /*!
     * Modbus Request Builder
     * \param to_send       - Message buffer to be send
     * \param address       - Reference Address
     * \param function_code - Modbus Functional Code
     */
    void        buildRequest(uint8_t *to_send, uint16_t address, int function_code) const;
    int         modbusRead(uint16_t address, uint16_t amount, int function_code);
    /*!
     * Write Request Builder and Sender
     * \param address       - Reference address
     * \param amount        - Amount of data to be written
     * \param function_code - Modbus Functional Code
     * \param value         - Data to be written
     * 
     * \return int 
     */
    int                 modbusWrite(uint16_t address, uint16_t amount, int function_code, const uint16_t *value);
    virtual ssize_t     modbusSend(uint8_t *to_send, size_t length) = 0;
    virtual ssize_t     modbusReceive(uint8_t *buffer) const = 0;

    void                modbusErrorHandle(const uint8_t *msg, int function_code);
    void                setBadConnection();
    void                setBadInput();

private:        // Members (Giggity!)
    bool                m_connected{};
    uint32_t            m_msg_id{};
    int                 m_slaveId{};

};
