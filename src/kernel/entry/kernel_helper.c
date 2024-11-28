#include <kernel_helper.h>
#include <nic_controller.h>
#include <system.h>
#include <task.h>
#include <types.h>
#include <util.h>


Task *netHelperTask = 0;

void netHelperEntry() {
  while (true) {
    for (int i = 0; i < QUEUE_MAX; i++) {
      if (!netQueue[i].exists)
        continue;

      handlePacket(netQueue[i].nic, netQueue[i].buff, netQueue[i].packetLength);
      netQueue[i].exists = false;
    }

    // wait until we're called back again
    netHelperTask->state = TASK_STATE_IDLE;
    while (netHelperTask->state == TASK_STATE_IDLE)
      handControl();
  }
}

void initiateKernelThreads() {
  // a
  netHelperTask = taskCreateKernel((size_t)netHelperEntry, 0);
}