#include "clabs.h"

void trace(const char* msg) {
    printf("%s", msg);
}

void eval_binary(int argc, char **argv, unsigned char* raw, int raw_size){
    JSRuntime *rt = JS_NewRuntime();
    JSContext *ctx = JS_NewContextRaw(rt);
    
    JS_AddIntrinsicBaseObjects(ctx);
    js_std_add_helpers(ctx, argc, argv);
    js_std_eval_binary(ctx, raw, raw_size, 0);
    js_std_loop(ctx);
    JS_FreeContext(ctx);
    JS_FreeRuntime(rt);
}

void eval_source(int argc, char **argv, unsigned char* raw, int raw_size){
    JSRuntime *rt = JS_NewRuntime();
    JSContext *ctx = JS_NewContext(rt);

    js_std_add_helpers(ctx, argc, argv);

    JSValue val = JS_Eval(ctx, raw, raw_size, "buffer", JS_EVAL_TYPE_GLOBAL | JS_EVAL_FLAG_SHEBANG);
    if (JS_IsException(val)) {
        js_std_dump_error(ctx);
    }
    JS_FreeValue(ctx, val);

    js_std_loop(ctx);
    JS_FreeContext(ctx);
    JS_FreeRuntime(rt);
}
