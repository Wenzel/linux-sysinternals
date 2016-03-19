# linux-sysinternals

This project is an attempt to recreate some of the tools available in the sysinternals suite available on Windows,
like vmmap or procexp.

# build

    ./configure.sh
    make

# vmmap

This tool reads the content of `/proc/<pid>/maps` to display an overview of a
process's virtual memory, and sort pages into different categories, like `stack`,
`heap`, `mapped file`, or `image`.

Unfortunately, it is not possible to rely on the description field of each
page to sort them :

If the size of a memory allocation is above a certain threshold, a new memory mapping
will be created, while it's description will not contain the `[heap]` flag, as one
might expect. [see this post on SO](https://stackoverflow.com/questions/17782536/missing-heap-section-in-proc-pid-maps)


# procexp

This tool is a simple process explorer for now, but it aims to be able to
monitor disk IO or network usage per process, as well as sending process images 
to virustotal for analysis.

To be able to update the view in realtime and be notified when a new process
is created or have just died, it uses a feature in the kernel named `Process Connector`,
which sends notification of events like `fork`, `exec` or `exit` on a `netlink` socket.
More information [here](http://netsplit.com/the-proc-connector-and-socket-filters)

The connection to the socket is done by the `helper` program, running as root,
and sending these events on `DBus`.
