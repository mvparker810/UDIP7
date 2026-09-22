//global variables


File dataFile


Byte fileCount


Byte sensPckt[]


Byte swpPckt[]


U_int16 count


Bool is_active = false


Unsigned long tInitial


Unsigned long tFinal


//function headers


...


Void setup()


Serial1 initializion


Serial initialization


While (serial not initialized){}


print statement initialization()


Wire initialization


Wire I2C speed set to 400khz



Void loop(){



Every 256 cycles, decimal point is turned on and off


If cycle modulo 8 less than or equal to 4


decimal point off


Else


decimal point on


Flush data recorded to sd card


If TE 1 is activated


Check is set to true


If check is false (ie, TE is not activated){


If IMU and HighAccel both initialized


Nothing displayed


Make sensor packet


Write packet to data file


Send packet


10 milisecond delay




If the check is true (TE line is activated)


Display 1


Make Sensor packet


Make sweep packet


Write sensor packet


Write sweep packet


Send sensor packet


Send sweep packet


}







bool sdInit()


If SD card initialized


Return false & exit function


If file already exists on SD card


Open the file in read-only


Read 1 byte from the file and store in variable


If file doesn’t exist


Open a new file to write in


Write 1 byte to the file


Flush the data from the file to the SD card


Close the file


Return true


Void SdOpen()


Initialize a new filename based on the file count


Increase the file count by 1


Update the file that contains the file count with new count value


Create a new data file with created file name & open it for writing



Void makeHedr(byte *pckt, u_int16 *count)


Store the initial timestamp that data was collected


Write sync word to header (‘U’, ‘D’)


Increase the packet count by 1


Copy packet count and timestamp into header



Void makeSensPckt(byte *pckt, u_int16 *count)


Make the packet header


Set packet type to sensor


Copy the payload length into the header


Make the sensor payload


Copy the final timestamp that data was collected into header



Void makeSensPyld(byte *pckt)


Check IMU flag


If IMU sensors are on


Read data from IMU sensors


Convert IMU data from floats to int16_t form


If IMU sensors are off


Set IMUsensor data to null value


Check high range accelerometer


If accelerometer is on


Read data from high range accelerometer


Convert accelerometer data from float to int16_t form


If accelerometer is off


Set accelerometer data to null value


Read analog board temperature data


Put data from each sensor into appropriate packets



Void makeSweepPckt(byte *pckt, uint16_t *count, byte sweepType)


Make the packet header


Set packet type to sweep


Add the voltage applied to probe into the packet


Copy the final timestamp that data was collected into packet header



Void makeSweep(byte *pckt)


Loop n times (n is number of steps in sweep)


Call doStep in each iteration



Void addVoltageRef(byte *pckt)


Read positive and negative voltage values from ADC pins


Copy the voltage values into the packet



Uint16_t getADC(int ADCpin)


Loop 18 times


Read value from ADC pin


Get minimum, maximum, and sum values from all 18 ADC pin readings Subtract maximum + minimum from sum value


Return the new sum value



Void doStep(byte *pckt, uint16_t dacLevel, int loc)


Set the sweep voltage


Read the voltage produced from the DAC


Read ADCs 1-3


Save data read from ADCs into packet



Void writePckt(File f, byte *pckt, uint16_t pcktLen)


Write the packet data into the file



Void sendPckt(byte *pckt, uint16_t pcktLen)


Send packet data via serial communication



Void displayPrint(char n)


Display 7-segment pattern based on input n