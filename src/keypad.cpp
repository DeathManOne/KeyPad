#include "../include/keypad.h"

KeyPad::KeyPad(std::vector<int> pinsColumns, std::vector<int> pinsRows) {
    this->_PINS_COLUMNS = new std::vector<int>(pinsColumns);
    this->_PINS_ROWS = new std::vector<int>(pinsRows);
    this->clear();
}

KeyPad::~KeyPad() {
    this->clear();
    delete this->_PINS_COLUMNS;
    delete this->_PINS_ROWS;
}

void KeyPad::clear() const {
    for (int row : *this->_PINS_ROWS)
        { pinMode(row, INPUT_PULLUP); }
    for (int column : *this->_PINS_COLUMNS)
        { pinMode(column, INPUT_PULLUP); }
}

int KeyPad::getRow() const {
    for (int row : *this->_PINS_ROWS)
        { pinMode(row, INPUT_PULLUP); }
    for (int column : *this->_PINS_COLUMNS) {
        pinMode(column, OUTPUT);
        digitalWrite(column, LOW);
    }

    int rowValue = -1;
    for (int r = 0; r < this->_PINS_ROWS->size(); r++) {
        if (!digitalRead(this->_PINS_ROWS->at(r)))
            { rowValue = r; }
    }
    return (rowValue < 0 || rowValue > 3) ? -1 : rowValue;
}

int KeyPad::getColumn(int rowValue) const {
    for (int column : *this->_PINS_COLUMNS)
        { pinMode(column, INPUT_PULLDOWN); }
    pinMode(this->_PINS_ROWS->at(rowValue), OUTPUT);
    digitalWrite(this->_PINS_ROWS->at(rowValue), HIGH);

    int columnValue = -1;
    for (int c = 0; c < this->_PINS_COLUMNS->size(); c++) {
        if (digitalRead(this->_PINS_COLUMNS->at(c)))
            { columnValue = c; }
    }
    return (columnValue < 0 || columnValue > 3) ? -1 : columnValue;
}

char KeyPad::getKey(int waitTimeout) const {
    this->clear();
    int rowValue = -1;
    int columnValue = -1;

    const uint32_t timeout = millis() + (1000 * waitTimeout);
    do {
        rowValue = this->getRow();
        delay(50);
    } while (rowValue == -1 && static_cast<uint32_t>(millis()) < timeout);
    if (rowValue == -1) {
        this->clear();
        return 0;
    }

    do {
        columnValue = this->getColumn(rowValue);
        delay(50);
    } while (columnValue == -1 && static_cast<uint32_t>(millis()) < timeout);

    this->clear();
    if (rowValue == -1 || columnValue == -1)
        { return 0; }
    return KeyPad::KEYPAD[rowValue][columnValue];
}