/**
 * @file profiling.h
 * @brief Macros for doing pin based profiling
 * @author Kristoffer Ödmark
 * @version 1.0
 * @date 2016-08-02
 */
#ifndef PROFILING_H
#define PROFILING_H

#define FUNCTION_ENTER(name, id)

#pragma message ("name has ID:##__COUNTER__")

#define FUNCTION_EXIT(id)


// enable printouts over semihosting
void send_command(int command, void *message);
void put_char(char c);


#endif /* PROFILING_H */
