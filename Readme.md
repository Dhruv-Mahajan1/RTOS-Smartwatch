# Embedded Systems Course Project - RTOS for Smartwatch

This project is a real-time operating system (RTOS) for a smartwatch. It consists of two threads, one for interrupt handling and the other for running tasks. The main thread checks for interrupt from the user, and the other thread does the scheduling and execution of tasks. 

## Tasks
The implementation has 4 tasks:
1. Showing current time
2. Step Counter
3. Heart Rate Monitor
4. Alarm after k seconds

## Running the Code
To run the main file, please follow these steps:
1. Compile the code using the following command: 

```g++ -o main.o main.cpp StepCounter.cpp UpdateTime.cpp Create_Task.cpp HeartRate.cpp```

2. Run the executable file using the following command:

```./main.o```

## Dependencies
This project requires the following dependencies:
- C++ compiler
- C++ Inbuilt Functions

## Contributors
- Aayush Gautam
- Dhruv Mahajan

## License
This project is licensed under the [MIT License](https://opensource.org/licenses/MIT).
