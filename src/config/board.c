/*
 * Copyright (c) 2006-2019, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2021-05-24                  the first version
 */

#include <rthw.h>
#include <rtthread.h>

#include "SEGGER_RTT.h"
#include "main.h"

#if defined(RT_USING_USER_MAIN) && defined(RT_USING_HEAP)
/*
 * Please modify RT_HEAP_SIZE if you enable RT_USING_HEAP
 * the RT_HEAP_SIZE max value = (sram size - ZI size), 1024 means 1024 bytes
 */
#define RT_HEAP_SIZE (15 * 1024)
static rt_uint8_t rt_heap[RT_HEAP_SIZE];

RT_WEAK void *rt_heap_begin_get(void) { return rt_heap; }

RT_WEAK void *rt_heap_end_get(void) { return rt_heap + RT_HEAP_SIZE; }
#endif

void SysTick_Handler(void) {
  rt_interrupt_enter();

  rt_tick_increase();

  rt_interrupt_leave();
}

/**
 * This function will initial your board.
 */
void rt_hw_board_init(void) {
  extern void SystemClock_Config(void);

  /* Call components board initial (use INIT_BOARD_EXPORT()) */
#ifdef RT_USING_COMPONENTS_INIT
  rt_components_board_init();
#endif

#if defined(RT_USING_USER_MAIN) && defined(RT_USING_HEAP)
  rt_system_heap_init(rt_heap_begin_get(), rt_heap_end_get());
#endif

#ifdef RT_USING_CONSOLE
  SEGGER_RTT_Init();
#endif
}

#ifdef RT_USING_CONSOLE

void rt_hw_console_output(const char *str) { SEGGER_RTT_WriteString(0, str); }
#endif

#ifdef RT_USING_FINSH
char rt_hw_console_getchar(void) {
  /* Note: the initial value of ch must < 0 */
  int ch = -1;

  if (__HAL_UART_GET_FLAG(&UartHandle, UART_FLAG_RXNE) != RESET) {
    ch = UartHandle.Instance->DR & 0xff;
  } else {
    rt_thread_mdelay(10);
  }
  return ch;
}
#endif
