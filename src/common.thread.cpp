#include "common.thread.h"

Thread::Thread() {}
Thread::~Thread() {}

void* Thread::runner(void* arg) {
	return ((Thread*) arg)->run();
}

int Thread::start() {
	return pthread_create(&(this->me), NULL, Thread::runner, this);
}

int Thread::join() {
	return pthread_join(this->me, NULL);
}

