#include <iostream>
#include <random>
#include <map>
#include <sstream>
#include <vector>
#include <iterator>
#include <string>
#include <cstdlib>
#include <chrono>


class Expression
{
    public:
        Expression(int x, int y, char op) : left(x), right(y), operand(op) {}
        Expression() : left(0), right(0), operand('\0') {}
    private:
        std::map<int, const char> dict;
        int left;
        int right;
        char operand;
        std::string expression;
    public:
        void set()
        {
            this->dict.insert(std::pair<int, const char>(0, '+'));
            this->dict.insert(std::pair<int, const char>(1, '-'));
            this->dict.insert(std::pair<int, const char>(2, '*'));
            this->dict.insert(std::pair<int, const char>(3, '/'));
            unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
            std::default_random_engine generator(seed);
            std::uniform_int_distribution<int> d1(-100, 100);
            std::uniform_int_distribution<int> d2(0, 3);
            this->left = d1(generator);
            this->right = d1(generator);
            this->operand = this->dict[d2(generator)];
        }
        void set(int left, int right, char operand)
        {
            this->left = left;
            this->right = right;
            this->operand = operand;
        }
        void set_left(int left) { this->left = left; }
        void set_left()
        {
            unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
            std::default_random_engine generator(seed);
            std::uniform_int_distribution<int> d(-100, 100);
            this->left = d(generator);
        }
        void set_right(int right) { this->right = right; }
        void set_right()
        {
            unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
            std::default_random_engine generator(seed);
            std::uniform_int_distribution<int> d(-100, 100);
            this->right = d(generator);
        }
        void set_operand(char operand) { this->operand = operand; }
        void set_operand()
        {
            this->dict.insert(std::pair<int, const char>(0, '+'));
            this->dict.insert(std::pair<int, const char>(1, '-'));
            this->dict.insert(std::pair<int, const char>(2, '*'));
            this->dict.insert(std::pair<int, const char>(3, '/'));
            unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
            std::default_random_engine generator(seed);
            std::uniform_int_distribution<int> d(0, 3);
            this->operand = this->dict[d(generator)];
        }
        std::string get()
        {
            std::stringstream ss;
            ss << this->left << " " << this->operand << " " << this->right;
            return ss.str();
        }

        int get_left() { return this->left; }
        int get_right() { return this->right; }
        char get_operand() { return this->operand; }

        void reset()
        {
            this->left = int(0);
            this->right = int(0);
            this->operand = char('\0');
        }
};


class Evaluator
{
    public:
        Evaluator() : expression(std::string()) {}
        Evaluator(std::string expression)
        {
            this->expression = expression;
            this->parse(expression);
        }

    private:
        void parse(std::string expression)
        {
            std::vector<std::string> temp = this->split(expression);
            this->left = atoi(temp[0].c_str());
            this->operand = temp[1][0];
            this->right = atoi(temp[2].c_str());
        }
        std::string expression;
        int left;
        int right;
        char operand;
        std::vector<std::string> split(std::string const &input) { 
            std::stringstream buffer(input);
            std::vector<std::string> ret;

            std::copy(std::istream_iterator<std::string>(buffer), 
                      std::istream_iterator<std::string>(),
                      std::back_inserter(ret));
            return ret;
        }

    public:
        bool validate(std::string answer)
        {
            std::string correct = this->evaluate(this->expression);
            return (answer.compare(correct) == 0);
        }
        std::string evaluate(std::string expression)
        {
            this->parse(expression);
            std::stringstream ss;
            switch(this->operand)
            {
                case '+': ss << (this->left + this->right); break;
                case '-': ss << (this->left - this->right); break;
                case '*': ss << (this->left * this->right); break;
                case '/': ss << (double(this->left) / double(this->right)); break;
            }
            return ss.str();
        }
        std::string evaluate()
        {
            this->parse(this->expression);
            std::stringstream ss;
            switch(this->operand)
            {
                case '+': ss << (this->left + this->right); break;
                case '-': ss << (this->left - this->right); break;
                case '*': ss << (this->left * this->right); break;
                case '/': ss << (double(this->left) / double(this->right)); break;
            }
            return ss.str();
        }
        void set(std::string expression) { this->expression = expression; }
};

int main() {
    Expression ex;
    Evaluator ev;
    int correct(0);
    int incorrect(0);
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
