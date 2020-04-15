/*
 * logger.cpp
 *
 * Henry R. Wilson and Griffin P. Tritaik
 *
 * 2020-04
 */

#include <mutex>

//Will need to include externs.h
#include "../includes/externs.h"
#include "../includes/baker.h"
using namespace std;

/*
 * I believe that this ID will be provided by a thread spawning loop;
 * we'll want 20 bakers on different threads with IDs 0-19
 */
Baker::Baker(int id):id(id)
{
}

/*
 * No fancy data structures, no actual implementationes.
 * Is this true?
 */
Baker::~Baker()
{
}

/*
 * I assume we get an order object from the queue
 */
void Baker::bake_and_box(ORDER &anOrder) {

	int boxes_needed = anOrder.number_donuts/12;
	int extra_donuts = anOrder.number_donuts%12;
	if(extra_donuts){
		boxes_needed++;
	}

	int donuts_left = anOrder.number_donuts;

	for(int i = 0; i < boxes_needed; i++){
		if(donuts_left > 11){
			Box aBox;
			for(int j = 0; j < 12; j++){
				donuts_left--;
				DONUT aDonut;
				aBox.addDonut(aDonut);
			}
			anOrder.boxes.push_back(aBox);
		}
		else{
			Box aBox;
			while(donuts_left > 0){
				donuts_left--;
				DONUT aDonut;
				aBox.addDonut(aDonut);
			}
			anOrder.boxes.push_back(aBox);
		}
	}
}

/*
 * The actual behavior of a baker that causes thread interactions.
 * As long as there are orders in order_in_Q,
 * 		behave appropriately
 */
void Baker::beBaker() {
	//Loop (not waiter_done)
	while(!b_WaiterIsFinished){
		//Sleep on cv
		{
		std::unique_lock<std::mutex> lck(mutex_order_inQ);
		cv_order_inQ.wait(lck);
		}

		ORDER theOrder;
		//get mutex_order_inQ lock
		{
		std::lock_guard<std::mutex> lck(mutex_order_inQ);
		//get ONE order from oreder_in_q
		theOrder = order_in_Q.front();
		order_in_Q.pop();
		//release previous lg
		}


		//call bake_and_box
		this->bake_and_box(theOrder);
		//get orderout mutex (lg)
		{
			std::lock_guard<std::mutex> lck(mutex_order_outQ);
		//push finished order onto oov
			order_out_Vector.push_back(theOrder);
		//release previous lg
		}

		//Will the two mutices give us DEADLOCK???
			//No.

		//repeat
	}

	//When out of loop: (when waiter is done)
	//loop (while queue not empty):
	while(!order_in_Q.empty()){

		ORDER theOrder;
		//get mutex_order_inQ lock
		{
		std::lock_guard<std::mutex> lck(mutex_order_inQ);
		//get ONE order from oreder_in_q
		theOrder = order_in_Q.front();
		order_in_Q.pop();
		//release previous lg
		}

		//call bake_and_box
		this->bake_and_box(theOrder);
		//get orderout mutex (lg)
		{
			std::lock_guard<std::mutex> lck(mutex_order_outQ);
		//push finished order onto oov
			order_out_Vector.push_back(theOrder);
		//release previous lg
		}

	}

}
