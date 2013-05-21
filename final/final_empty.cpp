#include <iostream>
#include <random>
#include <map>
#include <sstream>
#include <fstream>
#include <vector>
#include <iterator>
#include <string>
#include <cstdlib>
#include <chrono>


class Expression
{
    public:
        Expression(int x, int y, char op) {}
        Expression() {}
    private:
        std::map<int, const char> dict;
        int left;
        int right;
        char operand;
        std::string expression;
    public:
        void set()
        {
        }
        void set(int left, int right, char operand)
        {
        }
        void set_left(int left) { }
        void set_left()
        {
        }
        void set_right(int right) { }
        void set_right()
        {
        }
        void set_operand(char operand) { }
        void set_operand()
        {
        }
        std::string get()
        {
            return std::string();
        }

        int get_left() { return int(); }
        int get_right() { return int(); }
        char get_operand() { return char(); }

        void reset()
        {
        }
};


class Evaluator
{
    public:
        Evaluator() {}
        Evaluator(std::string expression)
        {
        }

    private:
        void parse(std::string expression)
        {
        }
        std::string expression;
        int left;
        int right;
        char operand;
        std::vector<std::string> split(std::string const &input)
        {
            return std::vector<std::string>();
        }

    public:
        bool validate(std::string answer)
        {
            return bool();
        }
        std::string evaluate(std::string expression)
        {
            return std::string();
        }
        std::string evaluate()
        {
            return std::string();
        }
        void set(std::string expression) {}
};

int main() {
    Expression ex;
    Evaluator ev;
    int correct(0);
    int incorrect(0);
    ex.set();
    std::string answer;
    while (answer != "q") {
        ex.set();
        ev.set(ex.get());
        std::cout << "Solve this expression: " << ex.get() << std::endl;
        std::cout << std::endl << "Enter your answer (type q to quit): ";
        std::getline(std::cin, answer);
        if (answer == "q") break;
        if (ev.validate(answer)) {
            std::cout << "You answered correctly!" << std::endl;
            ++correct;
        }
        else {
            std::cout << "You answered incorrectly. The correct answer is " << ev.evaluate() << std::endl;
            ++incorrect;
        }
    }
    std::cout << std::endl << "You correctly answered " << correct << " questions";
    std::cout << std::endl << "You incorrectly answered " << incorrect << " questions" << std::endl;
    std::cout << std::endl << "Press any key ..." << std::endl;
    std::cin.get();
}
