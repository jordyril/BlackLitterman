#include "questions.h"

template<typename T>
Questions<T>::Questions(string q){
    question = q;
}

template<typename T>
T Questions<T>::answer_and_verification(bool verify_answer){
    string yes_or_no = "y";
    do {
        cout << question << endl;
        cin >> answer;
        if (verify_answer){
        cout << "You said " << answer << ". Are you sure? (y/n)" << endl;
        cin >> yes_or_no;
        }
    } while(yes_or_no != "y");

    return answer;

}






