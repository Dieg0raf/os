#include "defs.h"
#include "memlayout.h"
#include "mmu.h"
#include "param.h"
#include "proc.h"
#include "types.h"
#include "x86.h"

static void startothers(void);
static void mpmain(void) __attribute__((noreturn));
extern pde_t* kpgdir;
extern char end[]; // first address after kernel loaded from ELF file

/*
 * Initializes the core components of the operating system.
 *kinit1*: sets up the physical memory allocator. (Manages the available physical memory memory (RAM))
 *mpinit*: detects multiple processors
 *lapicinit*: initializes the local APIC (Advanced Programmable Interrupt Controller) for handling interrupts. (Timer that generates interrupts for scheduling for allowing the OS to maintain control and implement time-sharing)
 */

// Bootstrap processor (Main CPU) starts running C code here.
// Allocate a real stack and switch to it, first
// doing some setup required for memory allocator to work.
int main(void)
{
    // *Memory Management Initialization*
    kinit1(end, P2V(4 * 1024 * 1024)); // phys page allocator (sets up the physical memory allocator. (Manages the available physical memory memory (RAM)))
    kvmalloc(); // kernel page table (sets up the translation system that converts virtual addresses (used by the OS and applications) to physical addresses (where data actually lives in RAM))

    // *Processor Initialization*
    mpinit(); // detect other processors (detects multiple processors)
    lapicinit(); // interrupt controller - PER-CPU setup (local APIC - used for handling interrupts, scheduling, and inter-processor communication - each CPU has its own local APIC)
    seginit(); // segment descriptors (PER-CPU setup)

    // *Hardware Initialization* (only happens once on the boot CPU)
    picinit(); // disable pic (disables legacy PIC - modern systems use APIC)
    ioapicinit(); // another interrupt controller (sets up I/O APIC - used for handling interrupts from devices, shared between CPUs)
    consoleinit(); // console hardware (initializes the console)
    uartinit(); // serial port (initializes serial port) (OS's "walkie-talkie" for debugging and communication with the outside world,
                // allowing the OS to send and receive messages, especially useful for debugging)

    // *OS subsystems*
    pinit(); // process table (initializes the process table - a data structure that keeps track of all processes in the system)
    tvinit(); // trap vectors (interrupt handlers) - A lookup table that tells that CPU what to do when an interrupt occurs
    binit(); // buffer cache (initializes the buffer cache - a memory area used to store frequently accessed disk blocks, improving performance)
    fileinit(); // file table (sets up the file table - a data structure that keeps track of open files in the system)
    ideinit(); // disk (initializes disk driver - Software that knows how to talk to the disk hardware, allowing the OS to read and write data to disk)

    // *Final steps*
    startothers(); // start other processors (wakes up other CPUs in the system) - multi-processor support
    kinit2(P2V(4 * 1024 * 1024), P2V(PHYSTOP)); // must come after startothers() - completes memory initialization (sets up the physical memory allocator for the rest of the system, allowing it to manage memory beyond the first 4MB)
    userinit(); // first user process (creates the first user process)
    mpmain(); // finish this processor's setup (finishes the setup for the main CPU and starts the scheduler)
}

// Other CPUs jump here from entryother.S.
static void mpenter(void)
{
    switchkvm();
    seginit();
    lapicinit();
    mpmain();
}

// Common CPU setup code.
static void mpmain(void)
{
    cprintf("cpu%d: starting %d\n", cpuid(), cpuid());
    idtinit(); // load idt register
    xchg(&(mycpu()->started), 1); // tell startothers() we're up
    scheduler(); // start running processes
}

pde_t entrypgdir[]; // For entry.S

// Start the non-boot (AP) processors.
static void startothers(void)
{
    extern uchar _binary_entryother_start[], _binary_entryother_size[];
    uchar* code;
    struct cpu* c;
    char* stack;

    // Write entry code to unused memory at 0x7000.
    // The linker has placed the image of entryother.S in
    // _binary_entryother_start.
    code = P2V(0x7000);
    memmove(code, _binary_entryother_start, (uint)_binary_entryother_size);

    for (c = cpus; c < cpus + ncpu; c++) {
        if (c == mycpu()) // We've started already.
            continue;

        // Tell entryother.S what stack to use, where to enter, and what
        // pgdir to use. We cannot use kpgdir yet, because the AP processor
        // is running in low  memory, so we use entrypgdir for the APs too.
        stack = kalloc();
        *(void**)(code - 4) = stack + KSTACKSIZE;
        *(void (**)(void))(code - 8) = mpenter;
        *(int**)(code - 12) = (void*)V2P(entrypgdir);

        lapicstartap(c->apicid, V2P(code));

        // wait for cpu to finish mpmain()
        while (c->started == 0)
            ;
    }
}

// The boot page table used in entry.S and entryother.S.
// Page directories (and page tables) must start on page boundaries,
// hence the __aligned__ attribute.
// PTE_PS in a page directory entry enables 4Mbyte pages.

__attribute__((__aligned__(PGSIZE))) pde_t entrypgdir[NPDENTRIES] = {
    // Map VA's [0, 4MB) to PA's [0, 4MB)
    [0] = (0) | PTE_P | PTE_W | PTE_PS,
    // Map VA's [KERNBASE, KERNBASE+4MB) to PA's [0, 4MB)
    [KERNBASE >>
        PDXSHIFT]
    = (0) | PTE_P | PTE_W | PTE_PS,
};

// PAGEBREAK!
//  Blank page.
// PAGEBREAK!
//  Blank page.
// PAGEBREAK!
//  Blank page.
