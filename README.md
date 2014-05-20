## stuck_at_shutdown ##

Under the following conditions, this program leads to a stuck and unpreemptable rosnode, producing 100% CPU load:

 * single-core CPU or only one CPU core accessible
 * the roscore process is running with normal priority

If you do not have a single-core platform at hand, you can also use cgroups to bind the roscore and the stuck_at_shutdown process to one CPU core.
This can be done by executing the following commands on your multi-core Linux machine (as root):

        mount -t tmpfs cgroup_root /sys/fs/cgroup
        mkdir /sys/fs/cgroup/cpuset
        mount -t cgroup -ocpuset cpuset /sys/fs/cgroup/cpuset
        cd /sys/fs/cgroup/cpuset
        echo 0 > cpuset.cpu_exclusive
        echo 0 > cpuset.mem_exclusive
        mkdir foo
        cd foo
        echo 0 > cpuset.cpus
        echo 0 > cpuset.mems

Now we have created a new cgroup called "foo" which is bound to CPU core 0.
To start the roscore and the stuck_at_shutdown binary as members of that cgroup, execute the following commands (still as root):

        cgexec -g cpuset:foo roscore &
        cgexec -g cpuset:foo ./stuck_at_shutdown

By running htop from a different shell, you see that one of the threads ROS created now uses 100% CPU time and does not stop.

