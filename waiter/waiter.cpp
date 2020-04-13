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
#include "../includes/externs.h"

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
	return myIO.getNext(anOrder);
}

//contains a loop that will get orders from filename one at a time
//then puts them in order_in_Q then signals baker(s) using cv_order_inQ
//so they can be consumed by baker(s)
//when finished exits loop and signals baker(s) using cv_order_inQ that
//it is done using b_WaiterIsFinished
void Waiter::beWaiter() {
	//Loop forever
	while(1){
		//Get order (call getNext)
		ORDER theOrder;
		int iotest = this->getNext(theOrder);

		//Check if we ran out of orders (not a critical section b/c we only have one waiter)
		if (iotest != SUCCESS){
			//handle out of orders
			b_WaiterIsFinished = true;
			break;
		}

		//grab order_in mutex w/lockguard CRITICAL SECTION
		{
			std::lock_guard<std::mutex> lck(mutex_order_inQ);
			//Push order onto order_in_q
			order_in_Q.push(theOrder);
		}

		//Notify bakers w/ notify_all on cv_order_inQ
		cv_order_inQ.notify_all();
	}
}

