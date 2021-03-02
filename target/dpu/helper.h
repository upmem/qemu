DEF_HELPER_1(stop, void, env)
DEF_HELPER_2(read_thread, tl, env, tl)
DEF_HELPER_2(clear_thread, tl, env, tl)
DEF_HELPER_3(start_thread, tl, env, tl, i32)

DEF_HELPER_2(raise_exception, noreturn, env, i32)

DEF_HELPER_2(time, i64, env, i32)
DEF_HELPER_3(time_cfg, void, env, tl, i32)

DEF_HELPER_3(tell, void, env, tl, i32)

DEF_HELPER_4(ldma_transfer, void, env, tl, tl, tl)
DEF_HELPER_4(ldmai_transfer, void, env, tl, tl, tl)
DEF_HELPER_4(sdma_transfer, void, env, tl, tl, tl)
