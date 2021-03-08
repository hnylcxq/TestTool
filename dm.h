#ifndef  _DM_H_
#define _DM_H_

#include"types.h"

i32 dm_init_sw(struct dpu_adapter_t *dpu_adapter);

void dm_deinit_sw(struct dpu_adapter_t *dpu_adapter);

void dm_init_hw(struct dpu_adapter_t *dpu_adapter);

void dm_deinit_hw(struct dpu_adapter_t *dpu_adapter);

void dm_init_crtc(struct dpu_adapter_t *dpu_adapter);

void dm_init_plane(struct dpu_adapter_t *dpu_adapter);

void dm_init_output(struct dpu_adapter_t *dpu_adapter);

void_t dm_deinit_output(struct dpu_adapter_t *dpu_adapter);

void init_dm(struct dpu_adapter_t *dpu_adapter);

void deinit_dm(struct dpu_adapter_t *dpu_adapter);

void dm_deinit_sw(struct dpu_adapter_t *dpu_adapter);

#endif