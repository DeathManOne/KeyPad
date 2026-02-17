#ifndef _KEYPAD_H_
#define _KEYPAD_H_

#include <Arduino.h>
#include <vector>

class KeyPad {
    private:
        const char KEYPAD[4][4] = {
            {'1','2','3','A'},
            {'4','5','6','B'},
            {'7','8','9','C'},
            {'*','0','#','D'}
        };
        std::vector<int> *_PINS_COLUMNS, *_PINS_ROWS;
        int getRow() const;
        int getColumn(int rowValue) const;
        void clear() const;
    public:
        /**
         * @brief constructor
         * @param pinsColumns vector (ex: {4,9,10,14})
         * @param pinsRows vector (ex: {7,6,8,3})
         */
        KeyPad(std::vector<int> pinsColumns, std::vector<int> pinsRows);

        /**
         * @brief destructor
         */
        ~KeyPad();

        /**
         * @brief get the pushed key
         * @param waitTimeout (default: 10) max wait time to push in seconds
         * @return char of number/letter you have pushed or 0 (false) in case of timeout
         */
        char getKey(int waitTimeout = 10) const;
};
#endif