#pragma once

#include <iostream>
#include <vector>
#include <conio.h>
#include <windows.h>

const char WHITE[8]{ 0x1b, '[', '0', ';', '3', '9', 'm', 0 };
const char RED[8]{ 0x1b, '[', '1', ';', '3', '1', 'm', 0 };
const char GREEN[8]{ 0x1b, '[', '1', ';', '3', '2', 'm', 0 };
const char LIGHT_YELLOW[8]{ 0x1b, '[', '1', ';', '3', '3', 'm', 0 };
const char BLUE[8]{ 0x1b, '[', '1', ';', '3', '4', 'm', 0 };
const char MAGENTA[8]{ 0x1b, '[', '1', ';', '3', '5', 'm', 0 };
const char CYAN[8]{ 0x1b, '[', '1', ';', '3', '6', 'm', 0 };

// made my own little clamp function, that takes in any variable type
template<class T> void clamp(T* value, const T min, const T max) {
    *value = (*value < min ? min : (*value > max ? max : *value));
}

template<class T> void max(T* value, const T max) {
    *value = *value > max ? max : *value;
}

template<class T> void min(T* value, const T min) {
    *value = *value < min ? min : *value;
}

void ClearScreen();
// this function supports windows only
void gotoxy(short x, short y);

struct Vector2 {
    int x{ 0 }, y{ 0 };

    void Zero() {
        x = y = 0;
    }

    void One() {
        x = y = 1;
    }
};

struct Boat {
public:
    int amount{ 0 };

    void CreateNewBoat(const int p_length, const std::string p_char, const int p_amountOfBoats) {
        m_length = p_length;
        m_icon = p_char;
        m_storeAmount = amount = p_amountOfBoats;
    }

    void Reset() {
        amount = m_storeAmount;
    }

    const int& get_Length() const {
        return m_length;
    }

    const std::string& get_Icon() const {
        return m_icon;
    }

private:
    int m_length{ 0 }, m_storeAmount{ 0 };
    std::string m_icon{ "?" };
};
