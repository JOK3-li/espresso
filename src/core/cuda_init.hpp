/*
  Copyright (C) 2010,2012,2013,2014,2015,2016 The ESPResSo project
  
  This file is part of ESPResSo.
  
  ESPResSo is free software: you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation, either version 3 of the License, or
  (at your option) any later version.
  
  ESPResSo is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.
  
  You should have received a copy of the GNU General Public License
  along with this program.  If not, see <http://www.gnu.org/licenses/>. 
*/
#ifndef _CUDA_INIT_H
#define _CUDA_INIT_H

#include "config.hpp"
#include <vector>

/** Struct to hold information relevant to Espresso
   about GPUs. Should contain only fixed length plain
   old datatypes, as it is intended for MPI communication */

struct EspressoGpuDevice {
  /* Local CUDA device id */
  int id;
  /* Node identification */
  char proc_name[64];
  /* MPI process identification */
  int node;
  /* Compute capability */
  int compute_capability_major;
  int compute_capability_minor;
  /* Name */
  char name[64];
  /* Total Memory */
  int total_memory;
  /* Number of cores */
  int n_cores;
};

/** Initializes the CUDA stream.
*/
void cuda_init();

/** get the number of CUDA devices.

    @return the number of GPUs, or -1 if CUDA could not be
    initialized. The error message from CUDA can be found in \ref
    cuda_error. 
*/
int cuda_get_n_gpus();

/** check that a given GPU is capable of what we need, that is, at
    least compute capability 1.1.

    @param dev CUDA device number
    @return \ref ES_OK if and only if the GPU with the given id is
    usable for CUDA computations.  Only devices with compute
    capability of 1.1 or higher are ok, since atomic operations are
    required for CUDA-LB.
*/
int cuda_check_gpu(int dev);

/** get the name of a CUDA device.

    @param dev the CUDA device number to ask the name for
    @param name a buffer to write the name to, at least 64 characters
*/
void cuda_get_gpu_name(int dev, char name[64]);

/** choose a device for future CUDA computations.

    @param dev the device to use
    @return \ref ES_OK on sucess, \ref ES_ERROR else. The error
    message from CUDA can be found in \ref cuda_error.
*/
int cuda_set_device(int dev);

/** get the current CUDA device.

    @return the current device's number or -1 if an error occured. The error
    message from CUDA can be found in \ref cuda_error.
*/
int cuda_get_device();

/** Test if actual CUDA device works.
    @return \ref ES_OK on sucess, \ref ES_ERROR else.
    The error message from CUDA can be found in \ref cuda_error.
*/

int cuda_test_device_access();

/** Gather unique list of CUDA devices from nodes 
    @return vector of device on master, empty vector on other nodes.
*/

std::vector<EspressoGpuDevice> cuda_gather_gpus(void);

/** Get properties of a CUDA device 
 */
int cuda_get_device_props(const int dev, EspressoGpuDevice &d);

/** current error message of CUDA. */
extern const char *cuda_error;

#endif
