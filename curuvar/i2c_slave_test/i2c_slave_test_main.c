/****************************************************************************
 * apps/examples/curuvar/i2c_slave_test_main.c
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

#include <nuttx/i2c/i2c_slave.h>
#include <arch/chip/i2c_slave.h>

#define STR_HELPER(x) #x
#define STR(x) STR_HELPER(x)

#define I2C_CONTROLLER 0
#define I2C_RX_BUF_LEN 32

/****************************************************************************
 * Private Functions
 ****************************************************************************/

static uint8_t  i2c_rx_buffer[I2C_RX_BUF_LEN];

static sem_t    wait_for_i2c;
static size_t   rx_length;

// --------------------------------------------------------------------------
// Function second_loop
// --------------------------------------------------------------------------

void  * second_loop( void  * inArg )
{
  while (true)
  {
    printf( "second.\n" );
    sleep(10);
  }

  return NULL;
}

// --------------------------------------------------------------------------
// Function i2c_callback
// --------------------------------------------------------------------------

int i2c_callback( void * in_arg, size_t rx_len )
{
  rx_length = rx_len;
  nxsem_post( &wait_for_i2c );

  I2CS_WRITE( (struct i2c_slave_s *) in_arg, i2c_rx_buffer, I2C_RX_BUF_LEN );

  return OK;
}

/****************************************************************************
 * Public Functions
 ****************************************************************************/

// --------------------------------------------------------------------------
// main
// --------------------------------------------------------------------------

int main( int in_argc, FAR char *in_argv[] )
{
  printf( "Hello, world, from I2C slave test.\n" );

  nxsem_init(&wait_for_i2c,  0, 0);
  nxsem_set_protocol(&wait_for_i2c, SEM_PRIO_NONE);

  // pthread_t second_thread;

  // int stat = pthread_create( &second_thread, 
  //                            NULL, 
  //                            second_loop, 
  //                            NULL );

  // if (stat < 0)
  // {
  //   fprintf( stderr, "second pid fork failed: %d\n", errno);
  //   return -1;
  // }

  /* if we get here we're in the main thread. */

  /* Set up the I2C listener */

  struct i2c_slave_s *i2c = rp2040_i2c0_slave_initialize( i2c_rx_buffer,
                                                          I2C_RX_BUF_LEN,
                                                          i2c_callback );
  


  if (i2c == NULL)
  {
    i2cerr( "ERROR: Failed to initialize i2c.\n" );
    return -ENODEV;
  }

  while (true)
  {
    if (nxsem_wait(&wait_for_i2c) != OK)
    {
      break;
    }

    printf( "i2c: " );
    for (int i = 0; i < rx_length; ++i)
    {
      printf( "0x%02X ", i2c_rx_buffer[i] );
    }
    printf( "\n" );
  }

  return 0;
}
