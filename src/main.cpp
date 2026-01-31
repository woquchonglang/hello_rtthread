#include "main.hpp"

#include <rtthread.h>

void main_app() {
  rt_thread_mdelay(1000);
  rt_kprintf("hello RT-Thread!\n");
}
