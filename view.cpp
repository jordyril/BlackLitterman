/**
    view.cpp
    @author Jordy Rillaerts
    @version 1.0 18/03/18
*/
#include "view.h"

/*
 * Constructor
 */
View::View(){

}

string View::name(){
    return "View";
}

ostream& operator <<(ostream& os, View* obj){
    os << obj->name();
    return os;
}
