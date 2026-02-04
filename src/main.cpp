#include "main.hpp"

#include <rtthread.h>

void thread1(void *parameter) {
  while (true) {
    rt_thread_mdelay(500);
    rt_kprintf("this is thread1\n");
  }
}

void thread2(void *parameter) {
  while (true) {
    rt_thread_mdelay(500);
    rt_kprintf("this is thread2\n");
  }
}

void main_app() {

  rt_thread_t thread1_ptr =
      rt_thread_create("thread1", thread1, RT_NULL, 512, 9, 5);

  if (thread1_ptr != RT_NULL)
    rt_thread_startup(thread1_ptr);

  auto thread2_ptr = rt_thread_create("thread2", thread2, RT_NULL, 512, 9, 5);
  if (thread2_ptr != RT_NULL)
    rt_thread_startup(thread2_ptr);
}
