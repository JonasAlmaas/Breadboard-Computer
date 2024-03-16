#include "Programmer/SerialPort.h"

#include <iostream>

SerialPort::SerialPort(const std::string& portName, int raudRate)
{
	m_handle = CreateFileA(portName.c_str(), GENERIC_READ | GENERIC_WRITE, 0, NULL, OPEN_EXISTING, 0, NULL);

	DCB serialParams = { 0 };
	serialParams.DCBlength = sizeof serialParams;

	GetCommState(m_handle, &serialParams);
	serialParams.BaudRate = raudRate;
	serialParams.ByteSize = 8;
	serialParams.StopBits = ONESTOPBIT;
	serialParams.Parity = NOPARITY;
	serialParams.fBinary = 1;

	if (!SetCommState(m_handle, &serialParams)) {
		std::cerr << "Error: Unable to set serial port state" << std::endl;
		CloseHandle(m_handle);
		exit(1);
	}

	// Set timeouts
	COMMTIMEOUTS timeout = { 0 };
	timeout.ReadIntervalTimeout = 50;
	timeout.ReadTotalTimeoutConstant = 50;
	timeout.ReadTotalTimeoutMultiplier = 10;
	timeout.WriteTotalTimeoutConstant = 100;
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

bool SerialPort::Read(char *buf, int bufSize)
{
	return ReadFile(m_handle, buf, bufSize, 0, NULL);
}

bool SerialPort::Write(char *buf, int bufSize)
{
	return WriteFile(m_handle, buf, bufSize, 0, NULL);
}
