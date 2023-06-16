# kinematics_lib
fixed point library for kinematics enabling robot control

I am using the Introduction to Robotics Mechanics and Control 3rd edition by John J. Craig as a reference

This is a 32 bit integer math library using scaled longs only on stack memory

Using the Q16.16 format, this library has a granulatiry of 1/2^16 which is 0.00001525878 and a range of numbers of 2^15 which is -32768 to 32767, which should encompass most all use cases quite handily if 1 is equal to a meter or centimeter.

You should be very careful of overflows, there is no inherint error handling for that, just make sure to use numbers less than 30,000, and dont use numbers smaller than 0.0001.
