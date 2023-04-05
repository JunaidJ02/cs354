Lab 4 - Part 3 - Junaid Javed

Modified Functions: 
  kill.c
    - In Kill, I added some additional code to handle the termination of child processes. 
    - When a process is being killed via kill(), we check its status via the prchildstatus[cpid] from its parent process. 
    - If the status is 1:
      - We change the status to 3 (terminated without blocking) since the child is now terminated
      - Remove the child process from the process table
      - Reset the parent of all child processes of the process being killed to the null process (0)
    - If the status is 2:
      - This means that the parent is waiting for this child to finish
      - Now that it has finished, we can ready and resume the parent process (i.e. unblock the parent process)
      - We set the status to 4, terminated 

  create.c
    - I added some lines in create.c that initialize the new entries that we added to the process table
    - We set the prchildcount of the newly created process to 0
    - We increment the prchildcount of the parent of the newly created process by 1
    - We save the pid of the newly created process into parent's prchildpid array 
    - We set the status of newly created process in the parent's prchildstatus array to 1

  xchildwait.c
    - This is where the bulk of the work doen in part 3 resides
    - xchildwait() takes two arugments, the first argument can either be a 0, blocking call, or 1, non-blocking call. 
    - The second argument is the pid of the child process.
    - If its a blocking call:
      - We set the state of the parent to PR_CHLDWAIT, waiting on child to finish
      - We then call resched to allow the child process to start running
      - We don't call resume() since we don't want to resume the child process if it has not been started (i.e. had not been added to the ready list). This was confirmed by Park in office hours. 
    - If its a non-blocking call
      - We check if the child process has finished
      - If it has, we return the PID of the child process
      - Otherwise, we return SYSERR

  TODO: Talk about the changes to the process table