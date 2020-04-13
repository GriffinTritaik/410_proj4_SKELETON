/*
 * logger.cpp
 *
 * Henry R. Wilson and Griffin P. Tritaik
 *
 * 2020-04
 */

#include <string>
#include "stdlib.h"

#include "../includes/waiter.h"

/*
 * this is where will will need to use extern.h's conditional variable to make sure we write before we bake!
 */

using namespace std;

//ID is just a number used to identify this particular baker
//(used with PRINT statements)
//filename is what waiter reads in orders from
Waiter::Waiter(int id,std::string filename):id(id),myIO(filename){
}

Waiter::~Waiter()
{
}

//gets next Order from file_IO
//if return == SUCCESS then anOrder
//contains new order
//otherwise return contains fileIO error
int Waiter::getNext(ORDER &anOrder){
	return SUCCESS;
}

//contains a loop that will get orders from filename one at a time
//then puts them in order_in_Q then signals baker(s) using cv_order_inQ
//so they can be consumed by baker(s)
//when finished exits loop and signals baker(s) using cv_order_inQ that
//it is done using b_WaiterIsFinished
void Waiter::beWaiter() {
	//Loop
		//Get order (call getNext)
			//Check if we ran out of orders
			//handle out of orders
				//set b_waiterisfinished = true
		//grab order_in mutex w/lockguard
		//Push order onto order_in_q
		//Notify bakers w/ notify_all on cv_order_inQ
		//repeat
}

