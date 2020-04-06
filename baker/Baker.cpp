#include <mutex>

//Will need to include externs.h
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
 * No fancy data structures, no actual implementatio.
 * Is this true?
 */
Baker::~Baker()
{
}

/*
 * I assume we get an order object from the queue
 */
void Baker::bake_and_box(ORDER &anOrder) {
	
}

/*
 * The actual behavior of a baker that causes thread interactions.
 * As long as there are orders in order_in_Q,
 * 		behave appropriately
 */
void Baker::beBaker() {
	
}
