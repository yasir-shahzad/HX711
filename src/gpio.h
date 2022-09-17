#ifndef GPIO_HPP
#define GPIO_HPP

#define LOW     0
#define HIGH    1

#include <inttypes.h>
#include <string>
#include <fstream>

enum Dir
{
    OUTPUT,
    INPUT 
};

class Hx711Gpio
{
    public:
        Hx711Gpio(std::string pin);

        int Enable();
        int Disable();

        int Mode(Dir dir);
        int Read();
        void Write(uint8_t val);

    private:
        std::string m_pin;
        std::fstream m_io;

        std::string IOFile();
};


#endif
