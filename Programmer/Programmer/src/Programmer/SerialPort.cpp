#include "Programmer/SerialPort.h"

#include <iostream>

SerialPort::SerialPort(const std::string& portName)
{
	m_handle = CreateFileA(portName.c_str(), GENERIC_READ | GENERIC_WRITE, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, 0);

	DCB serialParams = { 0 };
	serialParams.DCBlength = sizeof(serialParams);

	GetCommState(m_handle, &serialParams);
	serialParams.BaudRate = 57600;
	serialParams.ByteSize = 8;
	serialParams.StopBits = TWOSTOPBITS;
	serialParams.Parity = NOPARITY;

	if (!SetCommState(m_handle, &serialParams)) {
		std::cerr << "Error: Unable to set serial port state" << std::endl;
		CloseHandle(m_handle);
		exit(1);
	}

	// Set timeouts
	COMMTIMEOUTS timeout = { 0 };
	timeout.ReadIntervalTimeout = 50;
	timeout.ReadTotalTimeoutConstant = 50;
	timeout.ReadTotalTimeoutMultiplier = 50;
	timeout.WriteTotalTimeoutConstant = 50;
	timeout.WriteTotalTimeoutMultiplier = 10;

	if (!SetCommTimeouts(m_handle, &timeout)) {
		std::cerr << "Error: Unable to set serial port timeouts" << std::endl;
		CloseHandle(m_handle);
		exit(1);
	}
}

SerialPort::~SerialPort()
{
	CloseHandle(m_handle);
}

bool SerialPort::ReadLine(char *buf, int bufSize)
{
	/*char data{};
	
	for (size_t i = 0; i < 256; ++i) {
		if (!ReadFile(m_handle, &data, 1, 0, NULL)) {
			return false;
		}

		if (data == '\n') {
			buf[i] = 0;
			return true;
		}

		buf[i] = data;
	}
	*/
	
	return false;
}

bool SerialPort::Write(char *buf, int bufSize)
{
	return WriteFile(m_handle, buf, bufSize, 0, 0);
}
