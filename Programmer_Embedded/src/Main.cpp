#include <Arduino.h>
#include <stdlib.h>

enum {
	PIN_BUS0 = 2,
	PIN_BUS8 = 10,
	PIN_MI = 17, // Memory Address Register In
	PIN_RI = 18, // RAM In
	PIN_PROGRAMMING_LED = 19
};

void setBusValue(uint8_t data)
{
	for (int i = PIN_BUS0; i <= PIN_BUS8; ++i) {
		digitalWrite(i, ((data >> (i - PIN_BUS0)) & 1));
	}
}

void setAddress(uint8_t address)
{
	setBusValue(address);
	digitalWrite(PIN_MI, HIGH);
	delay(10);
	digitalWrite(PIN_MI, LOW);
	delay(10);
}

void setData(uint8_t data)
{
	setBusValue(data);
	digitalWrite(PIN_RI, HIGH);
	delay(10);
	digitalWrite(PIN_RI, LOW);
	delay(10);
}

void setup()
{
	Serial.begin(57600);

	for (int i = PIN_BUS0; i <= PIN_BUS8; ++i) {
		pinMode(i, OUTPUT);
	}

	pinMode(PIN_MI, OUTPUT);
	pinMode(PIN_RI, OUTPUT);
	pinMode(PIN_PROGRAMMING_LED, OUTPUT);
}

int main()
{
	init(); // Required for Arduino to work

	setup();

	char serialBuffer[10];

	char addressStrBuffer[5];
	char dataStrBuffer[5];

	memset(addressStrBuffer, 0, sizeof(addressStrBuffer));
	memset(dataStrBuffer, 0, sizeof(dataStrBuffer));

	while (true) {
		if (Serial.available() > 0) { // Expected format: "Address:Data" (Example: "0x00:0x00")
			digitalWrite(PIN_PROGRAMMING_LED, HIGH);

			Serial.readBytesUntil('\n', serialBuffer, sizeof(serialBuffer));
			Serial.readBytes(serialBuffer, 9);

			// Make sure the data-format is correct
			if (serialBuffer[0] != '0' || serialBuffer[1] != 'x' || serialBuffer[4] != ':'
					|| serialBuffer[5] != '0' || serialBuffer[6] != 'x') {
				digitalWrite(PIN_PROGRAMMING_LED, LOW);
				Serial.println("ERROR: Invalid format");
				continue;
			}

			memcpy(addressStrBuffer, serialBuffer, 4);
			memcpy(dataStrBuffer, serialBuffer + 5, 4);

			uint8_t address = strtoul(addressStrBuffer, NULL, 16);
			uint8_t data = strtoul(dataStrBuffer, NULL, 16);

			setAddress(address);
			setData(data);

			setBusValue(0);
			digitalWrite(PIN_PROGRAMMING_LED, LOW);

			Serial.print("Wrote ");
			Serial.print(data, HEX);
			Serial.print(" to address ");
			Serial.println(address, HEX);
		}

		delay(100);
	}

	return 0;
}
