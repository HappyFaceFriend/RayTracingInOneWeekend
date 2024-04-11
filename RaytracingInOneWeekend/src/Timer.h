#pragma once
#include <iostream>
#include <chrono>

class Timer 
{
public:
    Timer(const std::string& message) : m_Message(message), m_Start(std::chrono::steady_clock::now()) {}

    ~Timer()
    {
        auto end = std::chrono::steady_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - m_Start);
        std::cout << m_Message << ": " << duration.count() << " ms" << std::endl;
    }

private:
    const std::string m_Message;
    std::chrono::steady_clock::time_point m_Start;
};