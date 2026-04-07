#include <string>
#include <Windows.h>
#include <iostream>
#include <list>

class IObserver // интерфейс для наблюдателя
{
public:
    virtual ~IObserver() {};
    virtual void Update(const std::string& message, int userAnswer, int correctAnswer) = 0;
};

class ISubject // интерфейс для наблюдаемого
{
public:
    virtual ~ISubject() {};
    virtual void Subscribe(IObserver* observer) = 0;
    virtual void UnSubscribe(IObserver* observer) = 0;
    virtual void Notify() = 0;
};

class Subject : public ISubject
{
public:
    ~Subject()
    {
        std::cout << "Наблюдаемый был очищен в памяти" << std::endl;
    }

    void Subscribe(IObserver* observer) override
    {
        observerList.push_back(observer);
    }

    void UnSubscribe(IObserver* observer) override
    {
        observerList.remove(observer);
    }

    void Notify() override
    {
        std::list<IObserver*>::iterator iterator = observerList.begin();
        std::cout << "\nЗа объектом наблюдает " << observerList.size() << " наблюдателей" << std::endl;

        while (iterator != observerList.end())
        {
            (*iterator)->Update(message, userAnswer, correctAnswer);
            ++iterator;
        }
    }

    // Создание нового "события" для наблюдателей
    void CreateMessage(const std::string& message, int userAnswer, int correctAnswer)
    {
        this->message = message;
        this->userAnswer = userAnswer;
        this->correctAnswer = correctAnswer;
        Notify();
    }

    int GetObserverCount() const
    {
        return observerList.size();
    }

private:
    std::list<IObserver*> observerList;
    std::string message;
    int userAnswer = 0;
    int correctAnswer = 0;
};

class Observer : public IObserver
{
public:
    static int observerCount; // статическая переменная для подсчета

    Observer(Subject& _subject, const std::string& _name)
        : subject(_subject), name(_name)
    {
        observerCount++;
        id = observerCount;

        this->subject.Subscribe(this);
        std::cout << "Наблюдатель №" << id << " (" << name << ") проинициализирован" << std::endl;
    }

    ~Observer()
    {
        std::cout << "Наблюдатель №" << id << " (" << name << ") был очищен" << std::endl;
    }

    void Update(const std::string& message, int userAnswer, int correctAnswer) override
    {
        this->message = message;

        std::cout << "[" << name << "] получил сообщение: " << this->message << std::endl;

        if (userAnswer == correctAnswer)
        {
            std::cout << "[" << name << "] говорит: КРАСАВА! Ответ верный!" << std::endl;
        }
        else
        {
            std::cout << "[" << name << "] говорит: Эээ... вообще-то ответ неверный..." << std::endl;
        }
    }

    void UnsubscribeSubject()
    {
        subject.UnSubscribe(this);
        std::cout << "[" << name << "] был отписан от наблюдаемого!" << std::endl;
    }

    std::string GetName() const
    {
        return name;
    }

private:
    Subject& subject;
    std::string message;
    std::string name;
    int id = 0;
};

int Observer::observerCount = 0;

int main()
{
    setlocale(LC_ALL, "Russian");
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    Subject* subjectLeon = new Subject;

    // Фанаты
    Observer* observerGreka = new Observer(*subjectLeon, "Грека");
    Observer* observerRak = new Observer(*subjectLeon, "Рак");
    Observer* observerReka = new Observer(*subjectLeon, "Река");

    // Список фанатов для удобного удаления по очереди
    std::list<Observer*> fans;
    fans.push_back(observerGreka);
    fans.push_back(observerRak);
    fans.push_back(observerReka);

    int answer = 0;
    int correct = 0;

    std::cout << "\n======================================" << std::endl;
    std::cout << "Мини-игра: реши 3 уравнения подряд!" << std::endl;
    std::cout << "Если ошибаешься — теряешь одного фаната..." << std::endl;
    std::cout << "======================================\n" << std::endl;

    // ===== 1 уравнение =====
    std::cout << "Уравнение 1: 2 + 2 = ";
    std::cin >> answer;
    correct = 4;

    subjectLeon->CreateMessage("Проверка 1-го уравнения!", answer, correct);

    if (answer != correct && !fans.empty())
    {
        Observer* badFan = fans.back();
        badFan->UnsubscribeSubject();
        fans.pop_back();
    }

    // ===== 2 уравнение =====
    std::cout << "\nУравнение 2: 5 * 3 = ";
    std::cin >> answer;
    correct = 15;

    subjectLeon->CreateMessage("Проверка 2-го уравнения!", answer, correct);

    if (answer != correct && !fans.empty())
    {
        Observer* badFan = fans.back();
        badFan->UnsubscribeSubject();
        fans.pop_back();
    }

    // ===== 3 уравнение =====
    std::cout << "\nУравнение 3: 12 - 7 = ";
    std::cin >> answer;
    correct = 5;

    subjectLeon->CreateMessage("Проверка 3-го уравнения!", answer, correct);

    if (answer != correct && !fans.empty())
    {
        Observer* badFan = fans.back();
        badFan->UnsubscribeSubject();
        fans.pop_back();
    }

    // ===== Итог =====
    std::cout << "\n======================================" << std::endl;
    std::cout << "Итоги мини-игры" << std::endl;
    std::cout << "======================================" << std::endl;

    if (subjectLeon->GetObserverCount() == 0)
    {
        std::cout << "\nУ ТЕБЯ НЕ ОСТАЛОСЬ НИ ОДНОГО ФАНАТА!!!" << std::endl;
        std::cout << "ТЫ НАСТОЛЬКО ПЛОХ В МАТЕМАТИКЕ, ЧТО ДАЖЕ ЧАТ ОТ ТЕБЯ ОТПИСАЛСЯ..." << std::endl;
        std::cout << "Подключаем модератора Twitch...\n" << std::endl;

        Observer* twitchModerator = new Observer(*subjectLeon, "Twitch Moderator");
        subjectLeon->CreateMessage("Модератор вошёл в чат и следит за порядком!", 0, 0);

        delete twitchModerator;
    }
    else
    {
        std::cout << "\nПоздравляем! У тебя осталось фанатов: " << subjectLeon->GetObserverCount() << std::endl;
        subjectLeon->CreateMessage("Фанаты всё ещё с тобой!", 1, 1);
    }

    // Очистка памяти
    delete observerGreka;
    delete observerRak;
    delete observerReka;
    delete subjectLeon;

    system("pause");
    return 0;
}
