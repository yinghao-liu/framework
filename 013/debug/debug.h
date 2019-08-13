/** @file */
#ifndef _DEBUG_H_
#define _DEBUG_H_
/**
 * @brief A gloabal quit flag, if true, your thread should do clean-up
 *
 */
extern int g_debug_quit;

/**
 * @brief debug init, after that, if receive SIGUSR1, change g_debug_quit to true
 *
 * @return 0, success  1, error
 */
int debug_init(void);

#endif
