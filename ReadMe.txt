1. For cluster with multiple VMs we just have to specify number of running slaves/processes in machine file and it will work.

2. Parsing is shown in both screenshots. It gets salt/result values of any valid username input.

3. In screenshot 01, The task distribution on 2 slaves is shown.
   In screenshot 02, The task distribution on 3 slaves is shown.
   Similarly, it will distribute it for any given number of processes.

4. Code contians functions and comments where needed.

5. The password does crack successfully as shown in screenshot 02. 
   As soon as any process find password, abort signal is sent to all other processes searching.
