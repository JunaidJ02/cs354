/*  main.c  - main */

#include <xinu.h>

void testCPUUsage1(void);
void testCPUUsage2(void);
void testResponseTime1(void);
void testResponseTime2(void);

void testDynamicSchedA(void);
void testDynamicSchedB(void);
void testDynamicSchedC(void);
void testDynamicSchedD(void);
void testBonus(void);

volatile extern int msclkcounter2;

process	main(void)
{

	/* Run the Xinu shell */

	recvclr();

	/* Test CPU Usage */
	// resume(create((void *)testCPUUsage1, 12, INITPRIO, "Test CPU Usage 1", 0, NULL));
	// resume(create((void *)testCPUUsage2, 13, INITPRIO, "Test CPU Usage 2", 0, NULL));


	/* Test Response Time */
	// resume(create((void *)testResponseTime1, 30, INITPRIO, "Test Response Time 2", 0, NULL));

	// struct	procent	*prptr;		/* Pointer to proc. table entry */
	// prptr = &proctab[getpid()];

	// pid32 benchmarkA = create(testDynamicSchedA, 8192, 5, "Test dynamic resched A", 0, NULL);
	// resume(benchmarkA);
	
	// pid32 benchmarkB = create(testDynamicSchedB, 8192, 5, "Test dynamic resched B", 0, NULL);
	// resume(benchmarkB);

	// pid32 benchmarkC = create(testDynamicSchedC, 8192, 5, "Test dynamic resched C", 0, NULL);
	// resume(benchmarkC);

	// pid32 benchmarkD = create(testDynamicSchedD, 8192, 5, "Test dynamic resched D", 0, NULL);
	// resume(benchmarkD);

	// pid32 benchmarkBonus = create(testBonus, 8192, 5, "", 0, NULL);
	// resume(benchmarkBonus);

	return OK;
}

void testCPUUsage1(void) {
	int i = 0;
	while (i < 10000000) {
		i++;
	}

	uint32 cpuUsage = cpuusage(getpid());
	#ifdef XINUDEBUG
		kprintf("CPU usage 1: %d\n", cpuUsage);
	#endif
}

void testCPUUsage2(void) {
	int i = 0;
	while (i < 20000000) {
		i++;
	}

	uint32 cpuUsage = cpuusage(getpid());
	#ifdef XINUDEBUG
		kprintf("CPU usage 2: %d\n", cpuUsage);
	#endif
}

void testResponseTime1(void) {
	pid32 process1 = create((void *)testResponseTime2, 1024, 23, "Test Response Time 1", 0);
	resume(process1);
	int i = 0;

	while (i < 100000000) {
		/* do nothing */
		i++;
	}

	uint32 responseTime = responsetime(getpid());
	#ifdef XINUDEBUG
		kprintf("Reponse Time 1: %d\n", responseTime);
	#endif
}

void testResponseTime2(void) {
	int i = 0;

	uint32 responseTime = responsetime(getpid());
	#ifdef XINUDEBUG
		kprintf("Reponse Time 2: %d\n", responseTime);
	#endif
}

void testDynamicSchedA(void) {
	sleepms(0);
	sleepms(0);

	pid32 process1 = create(cpubnd, 1024, 3, "", 0);
	pid32 process2 = create(cpubnd, 1024, 3, "", 0);
	pid32 process3 = create(cpubnd, 1024, 3, "", 0);
	pid32 process4 = create(cpubnd, 1024, 3, "", 0);
	pid32 process5 = create(cpubnd, 1024, 3, "", 0);
	pid32 process6 = create(cpubnd, 1024, 3, "", 0);

	resume(process1);
	resume(process2);
	resume(process3);
	resume(process4);
	resume(process5);
	resume(process6);
}

void testDynamicSchedB(void) {
	sleepms(0);
	sleepms(0);

	pid32 process1 = create(iobnd, 1024, 3, "", 0);
	pid32 process2 = create(iobnd, 1024, 3, "", 0);
	pid32 process3 = create(iobnd, 1024, 3, "", 0);
	pid32 process4 = create(iobnd, 1024, 3, "", 0);
	pid32 process5 = create(iobnd, 1024, 3, "", 0);
	pid32 process6 = create(iobnd, 1024, 3, "", 0);

	resume(process1);
	resume(process2);
	resume(process3);
	resume(process4);
	resume(process5);
	resume(process6);
}

void testDynamicSchedC(void) {
	sleepms(0);
	sleepms(0);

	pid32 process1 = create(cpubnd, 1024, 3, "", 0);
	pid32 process4 = create(iobnd, 1024, 3, "", 0);
	pid32 process2 = create(cpubnd, 1024, 3, "", 0);
	pid32 process5 = create(iobnd, 1024, 3, "", 0);
	pid32 process3 = create(cpubnd, 1024, 3, "", 0);
	pid32 process6 = create(iobnd, 1024, 3, "", 0);

	resume(process1);
	resume(process2);
	resume(process3);
	resume(process4);
	resume(process5);
	resume(process6);
}

void testDynamicSchedD(void) {
	sleepms(0);
	sleepms(0);

	pid32 process1 = create(cpubnd, 1024, 3, "", 0);
	pid32 process2 = create(cpubnd, 1024, 3, "", 0);
	pid32 process3 = create(iobnd, 1024, 3, "", 0);
	pid32 process4 = create(iobnd, 1024, 3, "", 0);
	pid32 process5 = create(chameleon, 1024, 3, "", 0);

	resume(process1);
	resume(process2);
	resume(process3);
	resume(process4);
	resume(process5);
}

void testBonus(void) {
	sleepms(0);
	sleepms(0);

	pid32 process1 = create(iobnd9, 1024, 3, "", 0);
	pid32 process2 = create(iobnd9, 1024, 3, "", 0);
	pid32 process3 = create(iobnd9, 1024, 3, "", 0);
	pid32 process4 = create(iobnd9, 1024, 3, "", 0);
	pid32 process5 = create(cpubnd, 1024, 3, "", 0);

	resume(process1);
	resume(process2);
	resume(process3);
	resume(process4);
	resume(process5);
}