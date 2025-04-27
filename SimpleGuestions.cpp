#include <iostream>
#include <string>
#include <algorithm>

/// <summary>
/// Проверка симола на принадлежность к символу пробел
/// </summary>
/// <param name="value">Символ</param>
/// <returns>Значение истинности принадлежности к пробелу</returns>
bool IsSpace(char value) {
    //Сравниваем 2 значения
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
    //Заполняем массив из значений другого
    for (size_t i = 0; i < 16; ++i) {
        this->creditNumber[i] = creditNumber[i];
    }
}

CreditCard::CreditCard(std::string creditNumber) {
    //Убираем все пробелы из строки
    creditNumber.erase(std::remove_if(creditNumber.begin(), creditNumber.end(), IsSpace), creditNumber.end());
    //Если количество символов не равно 16 после преобразования, то это не номер банковской карты
    if (creditNumber.size() != 16) {
        //Выкидываем ошибку
        throw "Incorrect number of numbers";
        return;
    }
    else {
        //Заполняем массив номера
        for (size_t i = 0; i < 16; ++i) {
            try {
                this->creditNumber[i] = ConvertCharToInt(creditNumber.at(i));
            }
            //Ловится ошибка
            catch (const char* err) {
                std::cerr << err << std::endl;
                //В случае ошибки заполняем весь массив одним значением во избежание получения достоверности номера
                std::fill(this->creditNumber, this->creditNumber + 16, 255);
                return;
            }
        }
    }
}

bool CreditCard::IsValid() const
{
    // Создаем переменную для хранения контрольной суммы
    int sum = 0;
    // Складываем каждое значение массива с общей суммой
    for (size_t i = 0; i < 16; ++i) {
        // Если остаток от деления равен 0, то выполняем: x * 2, где x - creditNumber[i]
        if (i % 2 == 0) {
            sum += creditNumber[i] * 2;
            //если значение больше 10 (5 * 2 = 10, а 4 * 2 = 8), то вычитаем 9
            if (creditNumber[i] > 4) {
                sum -= 9;
            }
        }
        else {
            //Обычное прибавление к контрольной сумме
            sum += creditNumber[i];
        }
    }
    //Если остаток от деления на 10 равен 0, то номер карты правильный иначе ошибка
    if (sum % 10 == 0) {
        return true;
    }
    else {
        return false;
    }
}

int CreditCard::ConvertCharToInt(char number) {
    //Если символ не является числом ['0';'9'], то бросаем значение
    if (number < '0' || number > '9') {
        throw "Invalid Value";
        return -1;
    }
    //Для получения числа нужно вычисть минимальное значение (Символы - это тоже числа, просто в определенном порядке, например ' ' (Space) = 33, а значения от '0' до '9' идут по порядку)
    return number - '0';
}

int main()
{
    //Вывод русских символов (Кодировка вроде Windows-1251)
    setlocale(LC_ALL, ".1251");
    std::string value;
    std::cout << "Введите номер банковской краты: ";
    //Записывае в строке ввод с пробелами
    std::getline(std::cin, value); //4123 4567 8901 2349
    try {
        CreditCard credit(value);
        //Проверяем коррекность номера карты
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