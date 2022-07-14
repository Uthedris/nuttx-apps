/****************************************************************************
 * apps/examples/curuvar/motor_control_main.c
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

#include <nuttx/leds/ws2812.h>

#define STR_HELPER(x) #x
#define STR(x) STR_HELPER(x)

#define I2C_BUS         0
#define I2C_ADDRESS  0x42
#define I2C_ADDR_LEN    7

/****************************************************************************
 * Private Functions
 ****************************************************************************/

// --------------------------------------------------------------------------
// Function i2c_callback
// --------------------------------------------------------------------------

int (i2c_callback( void * in_arg )
{

}

/****************************************************************************
 * Public Functions
 ****************************************************************************/

// --------------------------------------------------------------------------
// ws2812_main
// --------------------------------------------------------------------------

int main( int in_argc, FAR char *in_argv[] )
{
  printf( "Hello, world, from motor_control\n" );

  // int i2c_pid = fork();

  // if (i2c_pid < 0)
  // {
  //   fprintf( stderr, "I2C listener fork failed: %d\n", errno);
  //   return -1;
  // }

  // if (i2c_pid == 0)
  // {
  //   /* new fork */
  //   return i2c_listener_loop();
  // }

  /* if we get here we're in the main thread. */

  /* Set up the I2C listener */

  struct i2c_master_s *i2c = rp2040_i2cbus_initialize( I2C_BUS );
  
  if (!i2c)
  {
    i2cerr( "ERROR: Failed to initialize i2c.\n" );
    return -ENODEV;
  }

  I2CS_SETOWNADDRESS( i2c, I2C_ADDRESS, I2C_ADDR_LEN );
  I2CS_REGISTERCALLBACK( i2c, i2c_callback, NULL );


}
