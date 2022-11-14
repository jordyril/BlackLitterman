#include "multiplechoice.h"

template <typename T>
Multiplechoice<T>::Multiplechoice(){

}

template <typename T>
Multiplechoice<T>::Multiplechoice(string q){
    question = q;

}


template <typename T>
Multiplechoice<T>::Multiplechoice(string q, vector<T> possible_answers){
    question = q;
    choices = possible_answers;
}

template <typename T>
void Multiplechoice<T>::add_choice(T new_choice){
    choices.push_back(new_choice);
}

template <typename T>
T Multiplechoice<T>::answer_and_verification(bool verify_answer){
    string yes_or_no = "y";
    int answer;
    int j = 1;
    do {
        cout << question << endl;
        for (auto i = choices.begin(); i < choices.end(); i++){
            cout << j << ". " << (*i) << endl;
            j++;
        }
        cin >> answer;
        if (verify_answer){
        cout << "You said " << answer << ". Are you sure? (y/n)" << endl;
        cin >> yes_or_no;
        }
    } while(yes_or_no != "y");

    return choices[answer - 1];
}





