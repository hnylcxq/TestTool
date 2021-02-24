#!/bin/bash

g++ model/dpu_ckp.cpp  model/dpu_cmodel.cpp  model/dpu_csc.cpp  dpu_drv.cpp dpu_ref.cpp  -I .  -I model -I include/top -I include/utils -I include/auxiliary -I include/resource -I include/memory -I ce -I vpe -I third-party -I model/code_piece -o cmode

