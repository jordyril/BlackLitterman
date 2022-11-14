#ifndef QUESTIONS_H
#define QUESTIONS_H
#include <iostream>
#include <string.h>

using namespace std;

template <typename T>
class Questions{
public:
    Questions(string q);

    string question;

    T answer;

    T answer_and_verification(bool verify_answer = false);



};

#endif // QUESTIONS_H
