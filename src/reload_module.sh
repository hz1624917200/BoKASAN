#!/bin/bash

# This script is used to reload the module
rmmod bokasan
make
insmod bokasan.ko
