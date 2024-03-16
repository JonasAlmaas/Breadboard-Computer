#include <Arduino.h>
#include <stdlib.h>

enum {
	PIN_BUS0 = 2,
	PIN_BUS7 = 9,
	PIN_CLR = 15, // Clear
	PIN_CLK = 16, // Clock
	PIN_MI = 17, // Memory Address Register In
	PIN_RI = 18, // RAM In
	PIN_IS_PROGRAMMING = 19 // Programming led. Prevent the program counter from progressing
};

void setBusValue(uint8_t data)
{
	for (int i = 0; i < 8; ++i) {
		digitalWrite(i + PIN_BUS0, ((data >> i) & 1));
	}
}

void pulseClock()
{
	digitalWrite(PIN_CLK, HIGH);
	delay(10);
	digitalWrite(PIN_CLK, LOW);
}

void pulseClear()
{
	digitalWrite(PIN_CLR, HIGH);
	delay(10);
	digitalWrite(PIN_CLR, LOW);
}

void setAddress(uint8_t address)
{
	setBusValue(address);
	digitalWrite(PIN_MI, HIGH);
	delay(10);
	pulseClock();
	digitalWrite(PIN_MI, LOW);
	delay(10);
}

void setData(uint8_t data)
{
	setBusValue(data);
	digitalWrite(PIN_RI, HIGH);
	delay(10);
	pulseClock();
	digitalWrite(PIN_RI, LOW);
	delay(10);
}

void setup()
{
	Serial.begin(9600, SERIAL_8N1);

	for (int i = PIN_BUS0; i <= PIN_BUS7; ++i) {
		pinMode(i, OUTPUT);
	}

	pinMode(PIN_CLR, OUTPUT);
	pinMode(PIN_CLK, OUTPUT);
	pinMode(PIN_MI, OUTPUT);
	pinMode(PIN_RI, OUTPUT);
	pinMode(PIN_IS_PROGRAMMING, OUTPUT);
}

int main()
{
	init(); // Required for Arduino to work

	setup();

	char serialBuffer[100];

	char addressStrBuffer[5];
	char dataStrBuffer[5];

	memset(addressStrBuffer, 0, sizeof(addressStrBuffer));
	memset(dataStrBuffer, 0, sizeof(dataStrBuffer));

	char commandFeedback[100] = { 0 }; // 11

	while (true) {
		if (Serial.available() > 0) { // Expected format: "Address:Data" (Example: "0x00:0x00")
			Serial.readBytesUntil('\n', serialBuffer, sizeof serialBuffer);

			// Make sure the data-format is correct
			if (serialBuffer[0] != '0' || serialBuffer[1] != 'x' || serialBuffer[4] != ':'
					|| serialBuffer[5] != '0' || serialBuffer[6] != 'x') {
				Serial.print("ERROR: Invalid format\n");
				Serial.println(serialBuffer);
				continue;
			}

			memcpy(addressStrBuffer, serialBuffer, 4);
			memcpy(dataStrBuffer, serialBuffer + 5, 4);

			uint8_t address = strtoul(addressStrBuffer, NULL, 16);
			uint8_t data = strtoul(dataStrBuffer, NULL, 16);

			digitalWrite(PIN_IS_PROGRAMMING, HIGH);

			setAddress(address);
			setData(data);

			setBusValue(0);
			pulseClear();

			digitalWrite(PIN_IS_PROGRAMMING, LOW);

			sprintf(commandFeedback, "0x%02x:0x%02x\n\0", address, data);
			Serial.print(commandFeedback);
		}

		delay(100);
	}

	return 0;
}
