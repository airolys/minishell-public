/* ************************************************************************** */
/**//**//*   *//**//*   By: *//**//*   Created:   by *//*   Updated:   by *//**/
/* ************************************************************************** */

#include "minishell.h"

/*
#define	SIGHUP		1	Hangup.  
#define	SIGINT		2	Interactive attention signal.  
#define	SIGQUIT		3	Quit.  
#define	SIGILL		4	Illegal instruction.  
#define	SIGTRAP		5	Trace/breakpoint trap.  
#define	SIGABRT		6	Abnormal termination.  
					7
#define	SIGFPE		8	Erroneous arithmetic operation.  
#define	SIGKILL		9	Killed.  
					10
#define	SIGSEGV		11	Invalid access to storage.  
					12
#define	SIGPIPE		13	Broken pipe.  
#define	SIGALRM		14	Alarm clock.  
#define	SIGTERM		15	Termination request.

void _handler(__attribute__((unused))int signum)
{
}

void init_signals()
{
	int sigflag;

	sigflag = SIGHUP;
	while (sigflag < 16)
	{
		signal(sigflag, (void (*[])(int)){
			_handler,
			_handler,
			_handler,
			_handler,
			_handler,
			_handler,
			_handler,
			_handler,
			_handler,
			_handler,
			_handler,
			_handler,
			_handler,
			_handler,
		}[sigflag]);
		sigflag++;
	}
}
*/

void	handle_ctrcinread(int signum)
{
	if (signum != SIGINT)
		return ;
	write(1, "\nWARNING: no EOF was given to the heredoc\n", 43);
	rl_replace_line("", 0);
	rl_on_new_line();
	exit(1);
}

void	handle_sigint(void)
{
	write(1, "\n", 1);
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
}

void	stop_signals(void)
{
	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
}

void	sig_handler(int signum)
{
	if (signum == SIGINT)
		handle_sigint();
}

void	start_signals(int fork)
{
	if (fork)
	{
		signal(SIGINT, &sig_handler);
		signal(SIGQUIT, SIG_IGN);
	}
	else
	{
		signal(SIGINT, &handlerfork);
		signal(SIGQUIT, &handlerfork);
	}
}
