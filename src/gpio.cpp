#include <iostream>
#include <sstream>
#include "gpio.h"

using namespace std;

Hx711Gpio::Hx711Gpio(string pin)
    : m_pin(pin),
        m_io(IOFile().c_str())
{
}

std::string Hx711Gpio::IOFile()
{
    Enable();

    return std::string("/sys/class/gpio/gpio" + m_pin + "/value");
}

int Hx711Gpio::Enable()
{
    string path = "/sys/class/gpio/export";
    ofstream file(path.c_str());
    if (!file)
    {
        cout << "Failed to export GPIO" << m_pin << endl;
        return -1;
    }

    file << m_pin;

    return 0;
}

int Hx711Gpio::Disable()
{
    string path = "/sys/class/gpio/unexport";
    ofstream file(path.c_str());
    if (!file)
    {
        cout << "Failed to unexport GPIO" << m_pin << endl;
        return -1;
    }

    file << m_pin;

    return 0;
}

int Hx711Gpio::Mode(Dir dir)
{
    string dPath = "/sys/class/gpio/gpio" + m_pin + "/direction";

    ofstream file(dPath.c_str());
    if (!file)
    {
        cout << "Failed to set direction on GPIO" << m_pin << endl;
        return -1;
    }

    if (dir == OUTPUT)
    {
        cout << "Direction OUT for GPIO" << m_pin << endl;
        file << "out";

        if (!m_io.is_open())
        {
            cout << "Failed to open for write to GPIO" << m_pin << endl;
        }
    }
    else
    {
        cout << "Direction IN for GPIO" << m_pin << endl;
        file << "in";

        if (!m_io.is_open())
        {
            cout << "Failed to open for read from GPIO" << m_pin << endl;
        }
    }

    file.close();

    return 0;
}

int Hx711Gpio::Read()
{
    string val;
    int ret = 0;
    m_io.seekg(0);
    m_io >> val;

    if (val != "0")
    {
        ret = 1;
    }
    else
    {
        ret = 0;
    }

    return ret;
}

void Hx711Gpio::Write(uint8_t val)
{
    m_io.seekp(0);
    if (val == 0)
    {
        m_io << "0" << flush;
    }
    else
    {
        m_io << "1" << flush;
    }
}
