##                       Controlling an DC Motor using a Finite State Machine model. 
After defining the Finite State Machine model, I implemented a thread safe system for handling different events via 3 provided functions to the user: SpeedUp, SpeedDown and Stop.

To make it thread safe I followed one rule: once an event is generated and the system is in the process to make a transition from one 
state to another one then - it cannot be interrupted.

Some references:</br>
https://en.wikipedia.org/wiki/Finite-state_machine</br>
https://baptiste-wicht.com/posts/2012/03/cpp11-concurrency-part1-start-threads.html</br>
