#include <iostream>
#include <unistd.h>   // close
#include <fcntl.h>    // O_RDWR
#include <sys/ioctl.h>
#include <linux/i2c-dev.h>  // I2C_SLAVE
#include <thread>
#include <time.h>
using namespace std;

int main(void) {
  const std::string DEVICE = "/dev/i2c-1";
  const unsigned int BUFFER_SIZE = 10;

  int i2cfile;
  if ((i2cfile = open(DEVICE.c_str(), O_RDWR)) < 0) {
      cout << "Could not open bus" << endl;
      exit(1);
  }
  cout << "Successfully opened the i2c bus" << endl;

  const int SLAVE_ADDRESS = 0x14;          // The I2C address of the slave device
  if (ioctl(i2cfile, I2C_SLAVE, SLAVE_ADDRESS) < 0) {
      cout << "Failed to acquire bus access and/or talk to slave." << endl;
      exit(1);
  }
  cout << "Ready to communicate with slave device" << endl;

                cout << "geef een woord in" << endl;
                string  woord;
                cin >> woord;
                char buffer[6] = {0x00,0x00};
                for(int i = 0; i<woord.length(); i++){

                        if((i%4)==0){
                        buffer[1]++;
                        }
                        buffer[(i%4)+2] = woord.c_str()[i];

                        if(((i%4)==3) || i==woord.length()-1){
                        write(i2cfile,buffer,6);
                        }
                }
                sleep(1);
                char buffer1 [] = {0x03};
                write(i2cfile, buffer1, 1);
       }
                }
                sleep(1);
                char buffer1 [] = {0x03};
                write(i2cfile, buffer1, 1);
                sleep(1);
                char buffer2[] = { 0x01,0X08 };
                sleep(1);
                write(i2cfile,buffer2,2);
                sleep(1);
                if (read(i2cfile, buffer2, 5) != 5) {
                         cout << "Failed to read from the i2c device." << endl;
                 } else {
                        for(int i = 0;i<5; i++){
                        cout <<(char) buffer2[i];
                        }
                }
  // Make sure to close the handle
  close(i2cfile);

  return 0;
}
