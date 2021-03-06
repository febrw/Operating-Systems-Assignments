/*
 * Round-robin Scheduling Algorithm
 * SKELETON IMPLEMENTATION -- TO BE FILLED IN FOR TASK (2)
 */

/*
 * STUDENT NUMBER: s1735009
 */
#include <infos/kernel/sched.h>
#include <infos/kernel/thread.h>
#include <infos/kernel/log.h>
#include <infos/util/list.h>
#include <infos/util/lock.h>

using namespace infos::kernel;
using namespace infos::util;

/**
 * A round-robin scheduling algorithm
 */
class RoundRobinScheduler : public SchedulingAlgorithm
{
public:
	/**
	 * Returns the friendly name of the algorithm, for debugging and selection purposes.
	 */
	const char* name() const override { return "rr"; }

	/**
	 * Called when a scheduling entity becomes eligible for running.
	 * @param entity
	 */
	void add_to_runqueue(SchedulingEntity& entity) override
	{
		
		UniqueIRQLock l;
		// check if runnable?
		runqueue.enqueue(&entity);
		
	}

	/**
	 * Called when a scheduling entity is no longer eligible for running.
	 * @param entity
	 */
	void remove_from_runqueue(SchedulingEntity& entity) override
	{
		UniqueIRQLock l;
		runqueue.remove(&entity);
	
	}

	/**
	 * Called every time a scheduling event occurs, to cause the next eligible entity
	 * to be chosen.  The next eligible entity might actually be the same entity, if
	 * e.g. its timeslice has not expired.
	 */
	SchedulingEntity *pick_next_entity() override
	{
		// not_implemented();
		if (runqueue.count() == 0) {
			return NULL;
			}

		else {
			// Disable interrupts to access runqueue
			UniqueIRQLock l;
			SchedulingEntity *current = runqueue.dequeue();
			runqueue.enqueue(current);
			return current;
		}
		// set timeslice to 40ms => at 100Hz ~4 ticks
		// check current CPU time within timeslice	
	}

private:
	// A list containing the current runqueue.
	List<SchedulingEntity *> runqueue;
};

/* --- DO NOT CHANGE ANYTHING BELOW THIS LINE --- */

RegisterScheduler(RoundRobinScheduler);
