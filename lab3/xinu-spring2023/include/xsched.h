#define DYNSCHEDENABLE 0

struct xsched_tab {
    uint16  xtqexp;         // new priority: CPU-bound (time quantum expired)
    uint16  xslpret;        // new priority: I/O-bound (called sleepms())
    uint16  xquantum;       // time slice associated with priority level
};

extern struct xsched_tab xdynprio[];