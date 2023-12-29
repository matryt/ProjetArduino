# Untitled - By: mathi - ven. déc. 29 2023

import gc
import KPU as kpu

kpu.deinit(kpu.load(0x300000))
kpu.deinit(kpu.load(0x400000))
kpu.deinit(kpu.load(0x500000))

gc.collect()
gc.mem_free()

print("Done !")
