/**
    viewscombiner.cpp
    @author Jordy Rillaerts
    @version 1.0 18/03/18
*/

#include "viewscombiner.h"

/*!
 * Constructor.
 *
 */
ViewsCombiner::ViewsCombiner(){
    number_of_views = 0;
}

/*!
  Constructor 2
* @param po. Portfolio concerning the views
*/
ViewsCombiner::ViewsCombiner(Portfolio* po){
    port = po;
    number_of_views = 0;
}


/*!
 * Setting the portfolio on which this combination of views applies
 * @param po. Portfolio concerning the views
 */
void ViewsCombiner::set_portfolio(Portfolio* po){
    port = po;
}

/*!
 * Adding views
 * Adds a new Relative view to the mix
 * @param new_view. the view that needs to be added
 */
void ViewsCombiner::add_view(View* new_view){
    /*
     * This function adds the necessary components to the P and Q vector for all Relative views
     */

    // Adding a row with 0's and a 1 and a -1 to the P vector, depending on the subject and relative subject of the view
    vector<double> P_row;

    for (unsigned i = 0; i < port->number_of_assets; i++){
        if (new_view->subject->name == port->assets(i, 0).name &&
                new_view->subject->adress == port->assets(i, 0).adress){
            P_row.push_back(1);
        }
        else {
            if (new_view->relative != NULL){
                if ( *new_view->relative == port->assets(i, 0)){
                    P_row.push_back(-1);
                }
                else {
                    P_row.push_back(0);
                }
            }

            else {
                P_row.push_back(0);
            }
        }
    }
    P.add_row(P_row);

    // Adding a row to the Q vector, which will be the value of the view
    vector<double> Q_row;
    Q_row.push_back(new_view->expectation);
    Q.add_row(Q_row);

    // Adding the confidence to the confidence matrix
    vector<double> c_row;
    c_row.push_back(new_view->confidence);
    confidence_matrix.add_row(c_row);

    number_of_views += 1;
    views.push_back(*new_view);
}
