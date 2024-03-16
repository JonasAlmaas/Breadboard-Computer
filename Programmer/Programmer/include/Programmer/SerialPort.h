#pragma once

#include <string>

#include <windows.h>

class SerialPort
{
public:
	SerialPort(const std::string& portName, int raudRate);
	~SerialPort();
	
	bool Read(char* buf, int bufSize);
	bool Write(char* buf, int bufSize);
	
private:
	HANDLE m_handle;
	
};
