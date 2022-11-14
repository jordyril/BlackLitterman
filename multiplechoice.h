#ifndef MULTIPLECHOICE_H
#define MULTIPLECHOICE_H
#include <vector>
#include <iostream>


using namespace std;

template <typename T>
class Multiplechoice {
public:
    Multiplechoice();
    Multiplechoice(string q);
    Multiplechoice(string q, vector<T> possible_answers);

    string question;

    T answer;

    vector<T> choices;

    void add_choice(T new_choice);

    T answer_and_verification(bool verify_answer = false);

};

#endif // MULTIPLECHOICE_H
