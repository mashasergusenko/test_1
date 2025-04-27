#include <iostream>
#include <string>
#include <algorithm>

/// <summary>
/// Проверка симола на принадлежность к символу пробел
/// </summary>
/// <param name="value">Символ</param>
/// <returns>Значение истинности принадлежности к пробелу</returns>
bool IsSpace(char value) {
    if (value == ' ') {
        return true;
    }
    else {
        return false;
    }
}

class CreditCard {
public:
    /// <summary>
    /// Конструктор для составления банкосвкой карты
    /// </summary>
    /// <param name="creditNumber">Массив чисел</param>
    CreditCard(uint8_t creditNumber[16]);

    /// <summary>
    /// Конструктор для составления банкосвкой карты
    /// </summary>
    /// <param name="creditNumber">Строка из чисел</param>
    CreditCard(std::string creditNumber);

    /// <summary>
    /// Проверка коррекность карты по алгоритму Луны
    /// </summary>
    /// <returns>Правильность номера банковской карты</returns>
    bool IsValid() const;

private:
    /// <summary>
    /// Переделать из симола в число.
    /// Если символ не является числом, то ловится ошибка.
    /// </summary>
    /// <param name="number">Символ числа</param>
    /// <returns>Числовое значения символа</returns>
    int ConvertCharToInt(char number);

private:
    uint8_t creditNumber[16];

};

CreditCard::CreditCard(uint8_t creditNumber[16]) {
    for (size_t i = 0; i < 16; ++i) {
        this->creditNumber[i] = creditNumber[i];
    }
}

CreditCard::CreditCard(std::string creditNumber) {
    creditNumber.erase(std::remove_if(creditNumber.begin(), creditNumber.end(), IsSpace), creditNumber.end());
    if (creditNumber.size() != 16) {
        throw "Incorrect number of numbers";
        return;
    }
    else {
        for (size_t i = 0; i < 16; ++i) {
            try {
                this->creditNumber[i] = ConvertCharToInt(creditNumber.at(i));
            }
            catch (const char* err) {
                std::cerr << err << std::endl;
                std::fill(this->creditNumber, this->creditNumber + 16, 255);
                return;
            }
        }
    }
}

bool CreditCard::IsValid() const
{
    int sum = 0;
    for (size_t i = 0; i < 16; ++i) {
        if (i % 2 == 0) {
            sum += creditNumber[i] * 2;
            if (creditNumber[i] > 4) {
                sum -= 9;
            }
        }
        else {
            sum += creditNumber[i];
        }
    }
    if (sum % 10 == 0) {
        return true;
    }
    else {
        return false;
    }
}

int CreditCard::ConvertCharToInt(char number) {
    if (number < '0' || number > '9') {
        throw "Invalid Value";
        return -1;
    }
    return number - '0';
}

int main()
{
    setlocale(LC_ALL, ".1251");
    std::string value;
    std::cout << "Введите номер банковской краты: ";
    std::getline(std::cin, value); //4123 4567 8901 2349
    try {
        CreditCard credit(value);
        if (credit.IsValid() == 1) {
            std::cout << "Номер карты правильный";
        }
        else {
            std::cout << "Номер карты недостоверен";
        }
    }
    catch (const char* err) {
        //Ввывод ошибки
        std::cerr << err << std::endl;
        return -1;
    }
    return 0;
}