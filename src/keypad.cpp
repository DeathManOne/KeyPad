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

#include "../include/keypad.h"

KeyPad::KeyPad(std::vector<int> pinsColumns, std::vector<int> pinsRows) {
    this->_PINS_COLUMNS = new std::vector<int>(pinsColumns);
    this->_PINS_ROWS = new std::vector<int>(pinsRows);
    this->_VALID = new bool(this->_PINS_ROWS->size() == 4 && (this->_PINS_COLUMNS->size() == 3 || this->_PINS_COLUMNS->size() == 4));
    this->_clear();
}

KeyPad::~KeyPad() {
    this->_clear();
    delete this->_PINS_COLUMNS;
    delete this->_PINS_ROWS;
    delete this->_VALID;
}

void KeyPad::_clear() const {
    for (int row : *this->_PINS_ROWS)
        { pinMode(row, INPUT_PULLUP); }
    for (int column : *this->_PINS_COLUMNS)
        { pinMode(column, INPUT_PULLUP); }
}

int KeyPad::_getRow() const {
    for (int row : *this->_PINS_ROWS)
        { pinMode(row, INPUT_PULLUP); }
    for (int column : *this->_PINS_COLUMNS) {
        pinMode(column, OUTPUT);
        digitalWrite(column, LOW);
    }

    delay(1);
    int rowValue = -1;

    for (size_t r = 0; r < this->_PINS_ROWS->size(); r++) {
        if (!digitalRead(this->_PINS_ROWS->at(r))) {
            rowValue = static_cast<int>(r);
            break;
        }
    }
    return rowValue;
}

int KeyPad::_getColumn(int rowValue) const {
    if (rowValue < 0 || rowValue >= static_cast<int>(this->_PINS_ROWS->size()))
        { return -1; }
    for (int column : *this->_PINS_COLUMNS)
        { pinMode(column, INPUT_PULLDOWN); }
    pinMode(this->_PINS_ROWS->at(rowValue), OUTPUT);
    digitalWrite(this->_PINS_ROWS->at(rowValue), HIGH);

    delay(1);
    int columnValue = -1;

    for (size_t c = 0; c < this->_PINS_COLUMNS->size(); c++) {
        if (digitalRead(this->_PINS_COLUMNS->at(c))) {
            columnValue = static_cast<int>(c);
            break;
        }
    }
    return columnValue;
}

int KeyPad::_getKeyValue(int rowValue, int columnValue) const {
    if (rowValue < 0 || rowValue >= 4)
        { return -1; }
    if (columnValue < 0 || columnValue >= static_cast<int>(this->_PINS_COLUMNS->size()))
        { return -1; }
    if (this->_PINS_COLUMNS->size() == 4)
        { return KeyPad::KEYPAD_4X4[rowValue][columnValue]; }
    return KeyPad::KEYPAD_4X3[rowValue][columnValue];
}

int KeyPad::getKey(uint32_t waitTimeoutSeconds) const {
    if (!this->isValid())
        { return -1; }
    this->_clear();

    int rowValue = -1;
    int columnValue = -1;

    const uint32_t start = millis();
    const uint32_t timeoutMs = waitTimeoutSeconds * 1000UL;

    while ((millis() - start) < timeoutMs) {
        rowValue = this->_getRow();
        if (rowValue != -1)
            { break; }
        delay(20);
    }

    if (rowValue == -1) {
        this->_clear();
        return -1;
    }
    delay(30);

    while ((millis() - start) < timeoutMs) {
        columnValue = this->_getColumn(rowValue);
        if (columnValue != -1)
            { break; }
        delay(20);
    }

    while (this->_getRow() != -1)
        { delay(10); }
    this->_clear();

    if (columnValue == -1)
        { return -1; }
    return this->_getKeyValue(rowValue, columnValue);
}