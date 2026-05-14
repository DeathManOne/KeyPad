/*
 * keypad.cpp
 *
 * Copyright (c) 2026 DeathManOne
 * https://github.com/DeathManOne
 * 
 * This file is part of the KeyPad library.
 *
 * KeyPad is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * KeyPad is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with KeyPad.
 * If not, see <https://www.gnu.org/licenses/>.
 */

#ifndef _KEYPAD_H_
#define _KEYPAD_H_

#include <Arduino.h>
#include <vector>

class KeyPad {
    private:
        static constexpr char KEYPAD_4X4[4][4] = {
            {'1','2','3','A'},
            {'4','5','6','B'},
            {'7','8','9','C'},
            {'*','0','#','D'}
        };
        static constexpr char KEYPAD_4X3[4][3] = {
            {'1','2','3'},
            {'4','5','6'},
            {'7','8','9'},
            {'*','0','#'}
        };

        std::vector<int> *_PINS_COLUMNS, *_PINS_ROWS;
        bool *_VALID;
        int _getRow() const;
        int _getColumn(int rowValue) const;
        int _getKeyValue(int rowValue, int columnValue) const;
        void _clear() const;

    public:
        /**
         * @brief constructor
         * @param pinsColumns GPIO columns pins
         * @param pinsRows GPIO rows pins
         */
        KeyPad(std::vector<int> pinsColumns, std::vector<int> pinsRows);

        /**
         * @brief disable copy constructor
         */
        KeyPad(const KeyPad&) = delete;

        /**
         * @brief disable copy assignment
         */
        KeyPad& operator=(const KeyPad&) = delete;

        /**
         * @brief destructor
         */
        ~KeyPad();

        /**
         * @brief check if keypad configuration is valid
         * @return true if keypad is valid, otherwise false
         */
        inline bool isValid() const { return *this->_VALID; }

        /**
         * @brief wait for key press
         * @param waitTimeoutSeconds (default: 10) timeout in seconds
         * @return pressed key or -1 on timeout/error
         */
        int getKey(uint32_t waitTimeoutSeconds = 10) const;
};

#endif