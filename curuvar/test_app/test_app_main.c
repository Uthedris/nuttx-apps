/****************************************************************************
 * apps/examples/curuvar/test_app_main.c
 *
 * Licensed to the Apache Software Foundation (ASF) under one or more
 * contributor license agreements.  See the NOTICE file distributed with
 * this work for additional information regarding copyright ownership.  The
 * ASF licenses this file to you under the Apache License, Version 2.0 (the
 * "License"); you may not use this file except in compliance with the
 * License.  You may obtain a copy of the License at
 *
 *   http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS, WITHOUT
 * WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.  See the
 * License for the specific language governing permissions and limitations
 * under the License.
 *
 ****************************************************************************/

/****************************************************************************
 * Included Files
 ****************************************************************************/

#include <nuttx/config.h>

#include <debug.h>
#include <errno.h>
#include <fcntl.h>
#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/ioctl.h>
#include <unistd.h>

#include <nuttx/wireless/ieee80211/bcmf_gpio.h>

#define STR_HELPER(x) #x
#define STR(x) STR_HELPER(x)

#define I2C_BUS         0
#define I2C_ADDRESS  0x42
#define I2C_ADDR_LEN    7

/****************************************************************************
 * Private Functions
 ****************************************************************************/


/****************************************************************************
 * Public Functions
 ****************************************************************************/

// --------------------------------------------------------------------------
// main
// --------------------------------------------------------------------------

int main( int in_argc, FAR char *in_argv[] )
{
  printf( "Hello, world, from test app\n" );

  for (int i = 0; i < 20; ++i)
    {
      bool value;
      bool ret;

      bcmf_set_gpio("wlan0", 0, (i & 1) == 0);
      usleep(500000);

      ret = bcmf_get_gpio("wlan0", 0, &value);

      if (ret != OK)
        {
          printf("ret = %d\n", ret);
        }
      else
        {
          printf("value = %d\n", value);
        }
    }

  return 0;
}
