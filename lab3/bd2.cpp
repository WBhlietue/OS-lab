#include <unistd.h>
#include <sys/time.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <sys/shm.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <string.h>
#include <linux/printk.h>

ssize_t proc_write(struct file *file, char_user *usr_buf,
                   size_t count, loff_t *pos)
{
    int rv = 0;
    char *k_mem;
    /* allocate kernel memory */
    k_mem = kmalloc(count, GFP_KERNEL);
    /* copies user space usr buf to kernel memory */
    copy from user(k_mem, usr_buf, count);
    printk(KERN_INFO "%s\n", k_mem);
    /* return kernel memory */
    kfree(k_mem);
    return count;
}